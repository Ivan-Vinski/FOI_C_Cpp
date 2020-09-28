#include <iostream>
#include <arpa/inet.h>
#include <string.h>
#include <sys/socket.h>
using namespace std;

#define MAX_MSG 30

int main(int argc, char *argv[]){
	int udpSock, bindReturn, bytesOfDataRecieved;
	struct sockaddr_in cliAddr, servAddr;
	socklen_t cliLen = sizeof(cliAddr);
	char meduspremnik[MAX_MSG];

	//Initialize socket
	udpSock = socket(AF_INET, SOCK_DGRAM, 0);

	//Give server IP adress and bind it to a port
	servAddr.sin_family = AF_INET;
	inet_pton(AF_INET, "127.0.0.1", &(servAddr.sin_addr.s_addr));
	servAddr.sin_port = htons(8000);
	bindReturn = bind(udpSock, (struct sockaddr *) &servAddr, sizeof(servAddr));

	//Recieve message and send it back
	while(strcmp(meduspremnik, "bok") != 0){

		bytesOfDataRecieved = recvfrom(udpSock, meduspremnik, MAX_MSG, 0, (struct sockaddr*) &cliAddr, &cliLen);
		cout << meduspremnik << " (" << bytesOfDataRecieved << " bytes)" <<  endl;

		sendto(udpSock, meduspremnik, MAX_MSG, 0, (struct sockaddr*) &cliAddr, cliLen);
	}
	return 0;
}
