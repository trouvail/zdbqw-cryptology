#include "iostream"
#include "Server.h"

using namespace std;

int main() {
	char mode[10] = { 0 };
	printf("Server:\n");
	while (true) {
		runServer();
		break;
	}
	system("pause");
	return 1;
}