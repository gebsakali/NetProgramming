#include <arpa/inet.h>
#include <stdio.h>
#include <stdlib.h>
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

	int n, p;
	int array[100];
	printf("enter vector length...\n>");
	scanf("%d", &n);
	printf("input: %d digits on by one\n", n);
	for(int i = 0; i < n; i++) {
		scanf("%d", &array[i]);
	}
	//int array[100] = { 3, 4, 5, 3, 1 ,9 };
	
	printf("sending: ");
	for(int i = 0; i < n; i++) {
		printf("%d\t", array[i]);
	}
	printf("\n");
	int len = sendto(sock, array, sizeof(array), 0, (struct sockaddr*)&server_address, sizeof(server_address));	// send data

	int array2[5][5];
	recvfrom(sock, array2, len, 0, NULL, NULL);		// received echo from server

	printf("received...\n\n");
    for(int i = 0; i < n; i++) {
        for(int j = 0; j < n; j++) {
            printf("%d\t", array2[i][j]);
        }
        printf("\n");
    }
	printf("\n\n");

	// close the socket
	close(sock);
	return 0;
}
