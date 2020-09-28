#include <iostream>
#include <stdlib.h>
#include <string.h>
#include <arpa/inet.h>
#include <sys/socket.h>
using namespace std;

#define MAX_MSG 30

int main(int argc, char *argv[]){ // Server port number as argument
	if (argc < 2){
		cout << "Usage: './udp_client <port>'" << endl;
		return 0;
	}
	int port = atoi(argv[1]);
	int bytesOfDataSent, bytesOfDataRecieved, udpSock;
	struct sockaddr_in servAddr, cliAddr;
	char sendMsg[MAX_MSG], recvMsg[MAX_MSG];
	socklen_t servLen = sizeof(servAddr);

	//Initialize client socket
	udpSock = socket(AF_INET, SOCK_DGRAM, 0);

	//Give client IP adress and bind it to a port
	cliAddr.sin_family = AF_INET;
	inet_pton(AF_INET, "127.0.0.1", &(cliAddr.sin_addr.s_addr));
	cliAddr.sin_port = htons(8001);
	bind(udpSock, (struct sockaddr*) &cliAddr, sizeof(cliAddr));

	//Specify server IP adress and port
	servAddr.sin_family = AF_INET;
	inet_pton(AF_INET, "127.0.0.1", &(servAddr.sin_addr.s_addr));
	servAddr.sin_port = htons(port);

	memset(sendMsg, 0, MAX_MSG);
	while (strcmp(sendMsg, "bok") != 0){
		cout << "Message you want echoed: ";
		cin.getline(sendMsg, MAX_MSG);
		bytesOfDataSent = sendto(udpSock, sendMsg, MAX_MSG, 0,(struct sockaddr*) &servAddr, sizeof(servAddr));

		bytesOfDataRecieved = recvfrom(udpSock, recvMsg, MAX_MSG, 0, (struct sockaddr*) &servAddr, &servLen);
		cout << "Echo: " << recvMsg << " (" << bytesOfDataRecieved << " bytes" << ")" <<  endl;
	}
	return 0;
}
