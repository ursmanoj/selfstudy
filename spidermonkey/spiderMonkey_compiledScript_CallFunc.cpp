//Spidermonkdey 24.x based code

// following code might be needed in some case
 #define __STDC_LIMIT_MACROS
#include <stdint.h>
#include <jsapi.h>
#include <iostream>
#include <stdio.h>
#include <sys/time.h>
using namespace std;

static char * readJSFile() {
	FILE* fp;
	// Open java script file.
	if (!(fp = fopen("./Smart_Plug.js", "r"))) {
		cout << "Failed to open javascript " << endl;
		return NULL;
	}
	long file_len = 0;
	fseek(fp, 0, SEEK_END);
	file_len = ftell(fp);
	fseek(fp, 0, SEEK_SET);

	char * buf = new char[file_len + 1];
	// Read java script file.
	int len = fread(buf, 1, file_len, fp);
	buf[file_len] = 0;
	fclose(fp);
	return buf;
}
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
		//sleep(3);
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
	if (!rt) {
		cout << "runtime" << endl;
		return 1;
	}

	JSContext *cx = JS_NewContext(rt, 8192);
	if (!cx) {
		cout << "JSContext" << endl;
		return 1;
	}

	{ // Scope for our various stack objects (JSAutoRequest, RootedObject), so they all go
	  // out of scope before we JS_DestroyContext.

		JSAutoRequest ar(cx); // In practice, you would want to exit this any
							  // time you're spinning the event loop

		JS::RootedObject global(cx, JS_NewGlobalObject(cx, &global_class, nullptr));
		if (!global) {
			cout << "global" << endl;
			return 1;
		}

		JS::RootedValue rval(cx);

		{ // Scope for JSAutoCompartment
			JSAutoCompartment ac(cx, global);
			JS_InitStandardClasses(cx, global);

			//const char *script = "'hello'+' Manoj, it is '+new Date()";
			//const char *script = "while (true){};\n'hello'+' Manoj, it is '+new Date()";
			//const char *script = "var a = 5+2;\n'hello'+' Manoj, it is '+new Date()+ ' a:'+a";
			//readJSFile();
			//const char *script = "var a=8;function testFunctionManoj() {return 5+4;}\n'hello'+' Manoj, it is '+new Date()+ ' a:'+a";
			const char *script = readJSFile();
			const char *filename = "sample.js";
			int lineno = 1;
			//bool ok = JS_EvaluateScript(cx, global, script, strlen(script), filename, lineno, rval.address());
			//bool ok = JS_EvaluateScript(cx, global, script, 0, filename, lineno, rval.address());
           
            JSScript * jss = JS_CompileScript(cx, global, script, strlen(script), filename, lineno);
			cout <<"Len: "<< strlen(script) << endl;

			if (!jss) {
				cout << "Error compiling" << endl;
				return 1;   /* compilation error */
			}

            jsval result;

			//startLongScriptWatcher(cx, rt);

			
#if 1//try calling func without executing script
            if (!JS_ExecuteScript(cx, global, jss, &result)) {
				cout << "Error JS_ExecuteScript" << endl;
				return 1;   /* compilation error */
			}

           /* JSString *str = result.toString();
		    printf("%s\n", JS_EncodeString(cx, str));*/
#endif
			//later execute the function, then script, lets c effect of func execution
			jsval rval;
			struct timeval beginTime, endTime;
			gettimeofday(&beginTime, NULL);
			if (JS_CallFunctionName(cx, global, "testFunctionManoj", 0, NULL, &rval)) {
				printf("call function sucessfully!");
				//JSString *str = r.toString();
				printf("function result: %d\n", rval);
				gettimeofday(&endTime, NULL);
				unsigned long diff = (endTime.tv_sec * 1000000 + endTime.tv_usec) - (beginTime.tv_sec * 1000000 + beginTime.tv_usec);
				cout << "Time taken in microsec: " << diff << endl;
			}
			else
				printf("Failed function:\n");
		}

		//JSString *str = rval.toString();
		//printf("%s\n", JS_EncodeString(cx, str));
	}

	JS_DestroyContext(cx);
	JS_DestroyRuntime(rt);
	JS_ShutDown();
	return 0;
}