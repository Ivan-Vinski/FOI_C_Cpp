#include <iostream>
#include <cstring>
#include <sys/socket.h>
#include <netdb.h>
#include <string>
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <time.h>
using namespace std;

#define IPV4 "127.0.0.1"
#define PORT "8000"
#define QUEUE_LENGTH 5
#define SIZE  500

int main(){
	int socketDescriptor, socketDescriptorClient, ret;
	struct addrinfo hints;
	struct addrinfo *res;
	struct sockaddr_storage clientAddr;
	socklen_t clientAddrSize;
	char buffer[SIZE] = {'\0'};

	memset(&hints, 0, sizeof(struct addrinfo));
	hints.ai_family = AF_INET;
	hints.ai_socktype = SOCK_STREAM;
	getaddrinfo(IPV4, PORT, &hints, &res);

	socketDescriptor = socket(res->ai_family, res->ai_socktype, res->ai_protocol);
	bind(socketDescriptor, res->ai_addr, res->ai_addrlen);

	freeaddrinfo(res);
	listen(socketDescriptor, QUEUE_LENGTH);
	cout << "Listening..." << endl;
	while (1){
		clientAddrSize = sizeof(clientAddr);

		socketDescriptorClient = accept(socketDescriptor, (struct sockaddr*)&clientAddr, &clientAddrSize);
		if (socketDescriptor == -1){
			cout << "Something went wrong with TCP connection" << endl;
			return 0;
		}
		else cout << "Cient connected" << endl;

		ret = recv(socketDescriptorClient, buffer, SIZE, 0);
		if (ret > 0 && ret < SIZE){
			time_t now = time(0);
			string timeString = (string)ctime(&now);
			if (strcmp(buffer, "SIMPLE_TIME") == 0){ // if recieved msg is "SIMPLE TIME", send back time in string
				cout << "timeString sent: " << timeString << endl;
				send(socketDescriptorClient, timeString.c_str(), strlen(timeString.c_str()), 0);
				break;
			}

			else if (buffer[0] == 'G' && buffer[1] == 'E' && buffer[2] == 'T'){ // if recieved msg starts with "GET", send back HTML file
				string timeHTML = "HTTP/1.1 200 OK\r\n\r\n <!DOCTYPE html><body> " + timeString + "</body></html>" ;
				send(socketDescriptorClient, timeHTML.c_str(), strlen(timeHTML.c_str()), 0);
				break;
			}
			else {
				cout << "Recieved command not recognized" << endl;
				break;
			}
		}
		else{
			cout << "Something went wrong when recieving a msg)" << endl;
			return 0;
		}
	}
	cout << "closing sockets" << endl;
	close(socketDescriptorClient);
	close(socketDescriptor);
	return 0;
}
