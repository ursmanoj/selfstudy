//Spidermonkdey 24.x based code

// following code might be needed in some case
 #define __STDC_LIMIT_MACROS
 #include <stdint.h>
#include <jsapi.h>
#include <unistd.h>//sleep

/* The class of the global object. */
static JSClass global_class = {
	"global",
	JSCLASS_GLOBAL_FLAGS,
	JS_PropertyStub,
	JS_DeletePropertyStub,
	JS_PropertyStub,
	JS_StrictPropertyStub,
	JS_EnumerateStub,
	JS_ResolveStub,
	JS_ConvertStub,
};

static void* watcherThread(void *ptr) {
	JSRuntime *rt = static_cast<JSRuntime *>(ptr);
	while (1) {
		sleep(3);
		JS_TriggerOperationCallback(rt);
	}
	return NULL;
}

static bool stopJSExe = false;

static void* inputThread(void *ptr) {
	char ch;

	printf("Enter 'x' to exit: ");
	do {
		scanf("%c", &ch);
	} while (ch != 'x');
	stopJSExe = true;
	return NULL;
}

static JSBool JSOperation_cb(JSContext *cx) {
	printf("JSOperation_cb\n");

	return stopJSExe?JS_FALSE:JS_TRUE;
}

static void startLongScriptWatcher(JSContext *cx, JSRuntime *rt) {
	JS_SetOperationCallback(cx, JSOperation_cb);

	static pthread_t thread;
	static pthread_t inputThrd;
	//void *ptr = (void*)rt;

	int ret = pthread_create(&thread, NULL, &watcherThread, (void*)(rt));
	ret = pthread_create(&inputThrd, NULL, &inputThread, (void*)(rt));

}



int main(int argc, const char *argv[])
{
	JSRuntime *rt = JS_NewRuntime(8L * 1024 * 1024, JS_USE_HELPER_THREADS);
	if (!rt)
		return 1;

	JSContext *cx = JS_NewContext(rt, 8192);
	if (!cx)
		return 1;

	{ // Scope for our various stack objects (JSAutoRequest, RootedObject), so they all go
	  // out of scope before we JS_DestroyContext.

		JSAutoRequest ar(cx); // In practice, you would want to exit this any
							  // time you're spinning the event loop

		JS::RootedObject global(cx, JS_NewGlobalObject(cx, &global_class, nullptr));
		if (!global)
			return 1;

		JS::RootedValue rval(cx);

		{ // Scope for JSAutoCompartment
			JSAutoCompartment ac(cx, global);
			JS_InitStandardClasses(cx, global);

			//const char *script = "'hello'+' Manoj, it is '+new Date()";
			const char *script = "while (true){};\n'hello'+' Manoj, it is '+new Date()";
			//const char *script = "var a = 5+2;\n'hello'+' Manoj, it is '+new Date()+ ' a:'+a";
			const char *filename = "sample.js";
			int lineno = 1;
			//bool ok = JS_EvaluateScript(cx, global, script, strlen(script), filename, lineno, rval.address());
			//bool ok = JS_EvaluateScript(cx, global, script, 0, filename, lineno, rval.address());
           
            JSScript * jss = JS_CompileScript(cx, global, script, strlen(script), filename, lineno);

            if (!jss)
                    return 1;   /* compilation error */

            jsval result;

			startLongScriptWatcher(cx, rt);

            if (!JS_ExecuteScript(cx, global, jss, &result))
                        return 1;

            JSString *str = result.toString();
		    printf("%s\n", JS_EncodeString(cx, str));
		}

		//JSString *str = rval.toString();
		//printf("%s\n", JS_EncodeString(cx, str));
	}

	JS_DestroyContext(cx);
	JS_DestroyRuntime(rt);
	JS_ShutDown();
	return 0;
}