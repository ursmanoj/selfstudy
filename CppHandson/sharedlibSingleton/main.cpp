#include <stdio.h>
#include <iostream>
#include "LibHeader.h"

using namespace std;

int main(void) {
	LibAPI api = LibAPI::GetInstance();

	api.Display();
	cin.get();
}
