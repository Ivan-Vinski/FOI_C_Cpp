#include <iostream>
#include <sys/types.h>
#include <sys/socket.h>
#include <cstring>
#include <stdio.h>
#include <unistd.h>
#include <netdb.h>
using namespace std;

#define IPV4 "127.0.0.1"
#define PORT "8000"
#define SIZE 500

int main(int argc, char *argv[]){
	struct addrinfo hints;
	struct addrinfo *res;
	int socketDescriptor, ret;
	char buffer[SIZE] = {'\0'};
	char *cmdArg = argv[1];
	if (!strcmp(cmdArg, "SIMPLE TIME")){
		cout << "Only command line argument I know is 'SIMPLE_TIME'" << endl;
		return 0;
	}

	strcpy(buffer, cmdArg);
	memset(&hints, 0, sizeof(struct addrinfo));
	hints.ai_family = AF_INET;
	hints.ai_socktype = SOCK_STREAM;
	ret = getaddrinfo(IPV4, PORT, &hints, &res);
	if (ret != 0){
		cout <<"Something went wrong on getaddrinfo" << endl;
		return 0;
	}

	socketDescriptor = socket(res->ai_family, res->ai_socktype, res->ai_protocol);
	if (socketDescriptor == -1){
		cout << "Cannot create socket" << endl;
		return 0;
	}

	ret = connect(socketDescriptor, res->ai_addr, res->ai_addrlen);
	if (ret != 0){
		cout << "Cant connect: " << ret << endl << "Try again in a few min" << endl;
		return 0;
	}

	send(socketDescriptor, buffer, strlen(buffer), 0);

	ret = recv(socketDescriptor, buffer, SIZE, 0);

	if (ret > 0 && ret < SIZE){
		buffer[ret] = '\0';
		cout << buffer << endl;
	}

	close(socketDescriptor);
	return 0;
}
