#include <bits/stdc++.h>
#include <unistd.h>
#include <string.h>

using namespace std;

// objdump -l -d helloworld > helloworld_perm.asm

int random_funct() {
	int i = 0;
	++i;
	
	int b = 5;
	i <<= b;
	b *= i;
}



int main() {
	char* hello = "hello world";
	
	double g = 1.05;
	double G = 11.0567;
	
	char c = 'a';
	
	unsigned int ui = -1;
	
	unsigned long long ull = -1;
	
	unsigned long ul = -1;
	
	long long int ll = -1;
	
	long l = 1L << 32;
	
	short s = 1 << 14; 

	int sum = 0;
	for (int i = 0; i < 10; ++i)
		sum += i;
	
	random_funct();
	
	g *= G;
	
	g += sum;
	
	s /= g;
	
	return 0;
}
