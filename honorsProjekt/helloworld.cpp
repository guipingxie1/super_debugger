#include <bits/stdc++.h>
#include <unistd.h>
#include <string.h>
#include <fstream>

using namespace std;

/*
 * 		*** To get the disassembled code ***
 *
 *	
 *
 *	g++ -S -fverbose-asm -masm=intel helloworld.cpp
 *			can add -fverbose-asm to make look better?
 *
 * 	objdump -S -d helloworld
 *
 * 
 *	nm helloworld to get symbol table
 *
 */
 

int main() {
	//cout << "Hello world\n";
	/*
	int k = 4;
	k++;
	k*=k;
	cout << k << "\n";
	k++;
	cout << k << "\n";
	*/
	write(1, "Hello world\n", 13);
	write(1, "Hello\n", 7);
	write(1, "world.\n", 8);
	write(1, "Hello worldz\n", 14);
	write(1, "Hi world\n", 10);
	
	char* str = (char*)malloc(5);
	
	strcpy(str, "hello");			// should be error here
	
	int a = 50;
		
	int b = 100;
	int retq = 100;
/*	
	ifstream parseMe( "/home/guiping/cs241/honorsProjekt/testers/test.c" );		// got from online - cppreference
	
	if ( parseMe.is_open() ) {
		string line;

		while ( getline( parseMe, line ) ) 
			cout << line << "\n";

		parseMe.close();
	}
*/	
	return 0;
}
