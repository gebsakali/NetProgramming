#include <arpa/inet.h>
#include <netinet/in.h>
#include <stdbool.h>
#include <stdio.h>
#include <string.h>

//void doCirculant(int matrixSize, int vector[]);
void doCirculant(int matrixSize, int vector[], int len);
struct sockaddr_in client_address;	//holds client's socket address
int client_address_len = 0;
int sock;

int main(int argc, char *argv[]) {
	int SERVER_PORT = 8000;

	struct sockaddr_in server_address;
	memset(&server_address, 0, sizeof(server_address));
	server_address.sin_family = AF_INET;
	server_address.sin_port = htons(SERVER_PORT);
	server_address.sin_addr.s_addr = htonl(INADDR_ANY);

	//int sock;
	if ((sock = socket(PF_INET, SOCK_DGRAM, 0)) < 0) {	//creates and initializes UDP socket
		printf("could not create socket\n");
		return 1;
	}

	if ((bind(sock, (struct sockaddr *)&server_address,	sizeof(server_address))) < 0) {		//bind it ... listens for incoming connections
		printf("could not bind socket\n");
		return 1;
	}

	// struct sockaddr_in client_address;	//holds client's socket address
	// int client_address_len = 0;

	while (true) {
		//char buffer[500];
		int array[100];
		int len = recvfrom(sock, array, sizeof(array), 0, (struct sockaddr *)&client_address, &client_address_len);

		array[len] = '\0';
		printf("from client '%s', received: \n\n", inet_ntoa(client_address.sin_addr));
		printf("[\t");
		for(int i = 0; i < 5; i++) {
			printf("%d\t", array[i]);	// neatly presents client's IP
		}
		printf("]");
		printf("\n\n");

		doCirculant(5, array, len);

		//sendto(sock, array, len, 0, (struct sockaddr *)&client_address, sizeof(client_address));	// echo to client 
	}

	return 0;
}

void doCirculant(int matrixSize, int vector[], int len) {
    
    int matrix[matrixSize][matrixSize];

    for (int j = 0; j < matrixSize; ++j) {
        for (int k = 0; k < matrixSize; ++k) {
            int offset = (j+k);
            if (offset < matrixSize){
                matrix[j][offset] = vector[k];
            } else{
                int pos = offset - matrixSize;
                matrix[j][pos] = vector[k];
            }
        }
    }

    //Print matrix
    for(int i = 0; i < matrixSize; i++) {
        for(int j = 0; j < matrixSize; j++) {
            printf("%d\t", matrix[i][j]);
        }
        printf("\n");
    }

	//sendto(sock, matrix, len, 0, (struct sockaddr *)&client_address, sizeof(client_address));	// echo to client
	sendto(sock, matrix, sizeof(matrix), 0, (struct sockaddr *)&client_address, sizeof(client_address));	// echo to client
}

/*void doCirculant(int matrixSize, int vector[]) {
    
    int matrix[matrixSize][matrixSize];

    for (int j = 0; j < matrixSize; ++j) {
        for (int k = 0; k < matrixSize; ++k) {
            int offset = (j+k);
            if (offset < matrixSize){
                matrix[j][offset] = vector[k];
            } else{
                int pos = offset - matrixSize;
                matrix[j][pos] = vector[k];
            }
        }
    }

    //Print matrix
    for(int i = 0; i < matrixSize; i++) {
        for(int j = 0; j < matrixSize; j++) {
            printf("%d\t", matrix[i][j]);
        }
        printf("\n");
    }

	sendto(sock, array, len, 0, (struct sockaddr *)&client_address, sizeof(client_address));	// echo to client
}*/
