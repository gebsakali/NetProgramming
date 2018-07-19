#include <arpa/inet.h>
#include <stdio.h>
#include <string.h>
#include <sys/socket.h>
#include <unistd.h>

int main() {
	const char* server_name = "localhost";
	const int server_port = 8000;

	struct sockaddr_in server_address;
	memset(&server_address, 0, sizeof(server_address));
	server_address.sin_family = AF_INET;

	inet_pton(AF_INET, server_name, &server_address.sin_addr);

	server_address.sin_port = htons(server_port);	// htons: port in network order format

	int sock;
	if ((sock = socket(PF_INET, SOCK_DGRAM, 0)) < 0) {
		printf("could not create socket\n");
		return 1;
	}

	const char* string = "This ia a UDP transmission";

	int len = sendto(sock, string, strlen(string), 0, (struct sockaddr*)&server_address, sizeof(server_address));	// send data

	char buffer[100];
	recvfrom(sock, buffer, len, 0, NULL, NULL);		// received echo from server

	buffer[len] = '\0';
	printf("recieved: '%s'\n", buffer);

	// close the socket
	close(sock);
	return 0;
}
