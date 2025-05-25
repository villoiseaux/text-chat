#include <unistd.h>
#include <stdio.h>
#include <sys/socket.h>
#include <stdlib.h>
#include <netinet/in.h>
#include <string.h>
#include <errno.h>
#include <arpa/inet.h>
#include <fcntl.h>
#include "server.h"
#include "logs.h"

int main(void) {
	// Création et initialisation du tableau contenant les descripteurs des sockets clients
	OUT_LOG("Lancement TextChat");
	int clients[NB_CLIENTS];
	for (int i = 0; i < NB_CLIENTS; i++) {
		clients[i] = -1;
	}
	// Structure contenant l'adresse
	struct sockaddr_in adresse;
	initAdresse(&adresse);
	// Descripteur de la socket du serveur
	int serverSocket = initSocket(&adresse);
	int clientSocket;
	while (1) {
		// Descripteur de la socket du client, on attend une connexion
		if ((clientSocket = waitForClient(&serverSocket)) != -1) {
			// On ajoute le nouveau client au tableau des descripteurs
			addClientToTab(clientSocket, clients);
		}
		manageClient(clients);
	}
	return EXIT_SUCCESS;
}
