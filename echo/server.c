#include <arpa/inet.h>
#include <netinet/in.h>
#include <stdbool.h>
#include <stdio.h>
#include <string.h>

int main(int argc, char *argv[]) {
	int SERVER_PORT = 8000;

	struct sockaddr_in server_address;
	memset(&server_address, 0, sizeof(server_address));
	server_address.sin_family = AF_INET;
	server_address.sin_port = htons(SERVER_PORT);
	server_address.sin_addr.s_addr = htonl(INADDR_ANY);

	int sock;
	if ((sock = socket(PF_INET, SOCK_DGRAM, 0)) < 0) {	//creates and initializes UDP socket
		printf("could not create socket\n");
		return 1;
	}

	if ((bind(sock, (struct sockaddr *)&server_address,	sizeof(server_address))) < 0) {		//bind it ... listens for incoming connections
		printf("could not bind socket\n");
		return 1;
	}

	struct sockaddr_in client_address;	//holds client's socket address
	int client_address_len = 0;

	while (true) {
		char buffer[500];

		int len = recvfrom(sock, buffer, sizeof(buffer), 0, (struct sockaddr *)&client_address, &client_address_len);

		buffer[len] = '\0';
		printf("received: '%s' from client %s\n", buffer, inet_ntoa(client_address.sin_addr));	// neatly presents client's IP

		sendto(sock, buffer, len, 0, (struct sockaddr *)&client_address, sizeof(client_address));	// echo to client 
	}

	return 0;
}
