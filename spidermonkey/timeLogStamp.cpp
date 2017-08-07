#include <sys/time.h>
#include <unistd.h>//sleep
#include <iostream>
#include <stdio.h>

using namespace std;

int main() {
	struct timeval beginTime, endTime;
	gettimeofday(&beginTime, NULL);

	sleep(1);

	gettimeofday(&endTime, NULL);
	unsigned long diff = (endTime.tv_sec * 1000000 + endTime.tv_usec) - (beginTime.tv_sec * 1000000 + beginTime.tv_usec);

	cout << diff << endl;
	printf("%ld", diff);
}