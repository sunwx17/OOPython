#include "Client.h"
#include "Data.h"
#include <iostream>
#include <cstdio>
using namespace std;

int main(int argc, char** argv)
{
	if (argc > 1) {
		freopen(argv[1], "r", stdin);
	}
	Client client(cin);
	client.work();
	return 0;
}
