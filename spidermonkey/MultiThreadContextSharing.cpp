//Spidermonkdey 24.x based code

// following code might be needed in some case
 #define __STDC_LIMIT_MACROS
 #include <stdint.h>
#include <jsapi.h>
#include <iostream>
#include <stdio.h>
#include <sys/time.h>
using namespace std;

static char * readJSFile(char * fileName) {
	FILE* fp;
	// Open java script file.
	if (!(fp = fopen(fileName, "r"))) {
		cout << "Failed to open javascript "<<endl;
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
JSRuntime *rt;
JSContext *cx;
//JS::RootedObject global;
JSObject* global;


static void callJSFunc(void) {
	jsval rval;
	JSAutoCompartment ac(cx, global);
	printf("%s begin\n", __func__);
	if (JS_CallFunctionName(cx, global, "manojFuncPlug", 0, NULL, &rval)) {
		printf("call function sucessfully!");
		//JSString *str = r.toString();
		//printf("manojFuncPlug result: %d\n", rval);
		/*gettimeofday(&endTime, NULL);
		unsigned long diff = (endTime.tv_sec * 1000000 + endTime.tv_usec) - (beginTime.tv_sec * 1000000 + beginTime.tv_usec);
		cout << "Time taken in microsec: " << diff << endl;*/
	}
	else
		printf("Failed manojFuncPlug:\n");
	printf("%s end\n", __func__);
}

static void* testThread(void *ptr) {
	printf("%s\n", __func__);
	callJSFunc();
	return NULL;
}

static void startTestThread() {

	static pthread_t thread;

	int ret = pthread_create(&thread, NULL, &testThread, NULL);
	cout <<"Thread create: " <<ret<<endl;
}

int main(int argc, const char *argv[])
{
	rt = JS_NewRuntime(8L * 1024 * 1024, JS_USE_HELPER_THREADS);
	//rt = JS_NewRuntime(8L * 1024 * 1024, JS_NO_HELPER_THREADS);
	if (!rt)
		return 1;

	cx = JS_NewContext(rt, 8192);
	if (!cx)
		return 1;

	{ // Scope for our various stack objects (JSAutoRequest, RootedObject), so they all go
	  // out of scope before we JS_DestroyContext.

		JSAutoRequest ar(cx); // In practice, you would want to exit this any
							  // time you're spinning the event loop

		//JS::RootedObject global(cx, JS_NewGlobalObject(cx, &global_class, nullptr));
		global = JS_NewGlobalObject(cx, &global_class, nullptr);
		if (!global)
			return 1;

		JS::RootedValue rval(cx);
		struct timeval beginTime, endTime;
		gettimeofday(&beginTime, NULL);

		{ // Scope for JSAutoCompartment
			JSAutoCompartment ac(cx, global);
			JS_InitStandardClasses(cx, global);

			//const char *script = "var a=8;function testFunctionManoj() {return 5+4;}\n'hello'+' Manoj, it is '+new Date()+ ' a:'+a"; 
			const char *script = readJSFile("./Smart_Plug.js");
			const char *filename = "Smart_Plug.js";
			int lineno = 1;
			//gettimeofday(&beginTime, NULL);
			bool ok = JS_EvaluateScript(cx, global, script, strlen(script), filename, lineno, rval.address());
			if (!ok) {
				cout << "JS_EvaluateScript error" << endl;
				return 1;
			}
			//read second script
			script = readJSFile("./DoorSensor.js");
			filename = "Smart_Plug.js";
			//gettimeofday(&beginTime, NULL);
			ok = JS_EvaluateScript(cx, global, script, strlen(script), filename, lineno, rval.address());
			if (!ok) {
				cout << "JS_EvaluateScript error" << endl;
				return 1;
			}
			/*JSString *str = rval.toString();
			printf("%s\n", JS_EncodeString(cx, str));*/

			//later execute the function, then script, lets c effect of func execution
			jsval rval;

			if (JS_CallFunctionName(cx, global, "testFunctionManoj", 0, NULL, &rval)) {
				printf("call function sucessfully!");
				//JSString *str = r.toString();
				printf("testFunctionManoj result: %d\n", rval);
				/*gettimeofday(&endTime, NULL);
				unsigned long diff = (endTime.tv_sec * 1000000 + endTime.tv_usec) - (beginTime.tv_sec * 1000000 + beginTime.tv_usec);
				cout << "Time taken in microsec: " << diff << endl;*/
			}
			else
				printf("Failed function1:\n");


			if (JS_CallFunctionName(cx, global, "testFunctionManoj2", 0, NULL, &rval)) {
				printf("call function sucessfully!");
				//JSString *str = r.toString();
				printf("testFunctionManoj2 result: %d\n", rval);
				/*gettimeofday(&endTime, NULL);
				unsigned long diff = (endTime.tv_sec * 1000000 + endTime.tv_usec) - (beginTime.tv_sec * 1000000 + beginTime.tv_usec);
				cout << "Time taken in microsec: " << diff << endl;*/
			}
			else
				printf("Failed function2:\n");

			//if (JS_CallFunctionName(cx, global, "manojFuncPlug", 0, NULL, &rval)) {
			//	printf("call function sucessfully!");
			//	//JSString *str = r.toString();
			//	printf("manojFuncPlug result: %d\n", rval);
			//	/*gettimeofday(&endTime, NULL);
			//	unsigned long diff = (endTime.tv_sec * 1000000 + endTime.tv_usec) - (beginTime.tv_sec * 1000000 + beginTime.tv_usec);
			//	cout << "Time taken in microsec: " << diff << endl;*/
			//}
			//else
			//	printf("Failed manojFuncPlug:\n");
			

			//test func from this thread
			cout << "Main thread func" << endl;
			callJSFunc();

			//Time to call same func from another thread
			int key;
			cout << "Time to call same func from another thread, enter any key when ready!!" << endl;
			cin >> key;
			startTestThread();
			//callJSFunc();
			cout << "Function being called from another thread, now enter any key to exit()" << endl;
			cin >> key;
		}

		
	}

	//JS_DestroyContext(cx);
	//JS_DestroyRuntime(rt);
	//JS_ShutDown();

	return 0;
}