#define _CRT_SECURE_NO_WARNINGS
#include "Client.h"
#include "Data.h"
#include <iostream>
#include <cstdio>
using namespace std;

int main(int argc, char** argv)
{
	bool isCMD = true;
	if (argc > 1) {
		freopen(argv[1], "r", stdin);
		isCMD = false;
	}
	Client client(isCMD);
	client.work();
	return 0;
}
