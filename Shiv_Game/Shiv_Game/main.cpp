#include "framework.h"
#include <iostream>

using namespace std;

int main( int argc, char* args[] ){
	
	if( frameworkInit() ){
	}

	frameworkQuit();

	return 0;
}