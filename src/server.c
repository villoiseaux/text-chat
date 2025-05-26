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

// Initialisation de la structure sockaddr_in
void initAdresse(struct sockaddr_in * adresse) {
	(*adresse).sin_family = AF_INET;
	(*adresse).sin_addr.s_addr = IP;
	(*adresse).sin_port = htons( PORT);
}
// Démarrage de la socket serveur
int initSocket(struct sockaddr_in * adresse) {
	int fdsocket;
	// Nombre d'options
	int opt = 1;
	// Création de la socket en TCP
	if ((fdsocket = socket(AF_INET, SOCK_STREAM, IPPROTO_TCP)) == -1) {
		FATAL("Echéc de la création", (errno));
	}
	OUT_LOG("Création de la socket");
	// Paramètrage de la socket
	if (setsockopt(fdsocket, SOL_SOCKET, SO_REUSEADDR | SO_REUSEPORT, &opt,
			sizeof(opt)) != 0) {
		FATAL("Echéc de paramètrage", (errno));
	}
	// Attachement de la socket sur le port et l'adresse IP
	if (bind(fdsocket, (struct sockaddr *) adresse, sizeof(*adresse)) != 0) {
		FATAL("Echéc d'attachement", (errno));
	}
	OUT_LOGINT("Attachement de la socket sur le port", PORT);
	// Passage en écoute de la socket
	if (listen(fdsocket, BACKLOG) != 0) {
		FATAL("Echéc de la mise en écoute", (errno));
	}
	// Passage en mode non bloquant
	fcntl(fdsocket, F_SETFL, O_NONBLOCK);
	OUT_LOG("Mise en écoute de la socket");
	return fdsocket;
}
// Attente de connexion d'un client
int waitForClient(int * serverSocket) {
	int clientSocket;
	// Structure contenant l'adresse du client
	struct sockaddr_in clientAdresse;
	int addrLen = sizeof(clientAdresse);
	if ((clientSocket = accept(*serverSocket, (struct sockaddr*) &clientAdresse,
			(socklen_t*) &addrLen)) != -1) {
		// Convertion de l'IP en texte
		char ip[INET_ADDRSTRLEN];
		inet_ntop(AF_INET, &(clientAdresse.sin_addr), ip, INET_ADDRSTRLEN);
		OUT_LOG("Connection établie");
		OUT_LOGCHAR("IP source",ip);
		OUT_LOGINT("Port",clientAdresse.sin_port);		
		// Passage en mode non bloquant
		int opt = 1;
		setsockopt(clientSocket, SOL_SOCKET, SO_KEEPALIVE, &opt, sizeof(1));
	}
	return clientSocket;
}
// Ajoute les clients au tableau
void addClientToTab(int clientSocket, int clients[]) {
	// On vérifie si on à de la place de libre
	OUT_LOG("Nouveau client");
	int found = -1;
	for (int i = 0; i < NB_CLIENTS; i++) {
		// On cherche de la place
		if (clients[i] == -1) {
			// On ajoute le client
			OUT_LOGINT("Ajout du client à l'index", i);
			clients[i] = clientSocket;
			// Nouvelle connexion, envoie du message de bienvenu
			send(clientSocket, "Entrez 'exit' pour quitter\n", 	strlen("Entrez 'exit' pour quitter\n"),
					MSG_DONTWAIT);
			found = 0;
			OUT_LOGINT("Clients restants",(NB_CLIENTS-i)-1);
			break;
		}
	}
	if (found == -1) {
		// On a plus de place de libre
		OUT_ERR("Trop d'utilisateurs max=",NB_CLIENTS);
		close(clientSocket);
	}
}
// On traite l'input des clients
void manageClient(int clients[]) {
	// Création d'un tampon pour stocker les messages des clients dans la heap
	static char buffer[BUFFER_LEN + 1];
	static char first[10];
	for (int i = 0; i < NB_CLIENTS; i++) {
		// On vérifie les messages
		int clientSocket = clients[i];
		if (clientSocket == -1) {
			continue;
		}
		int len = recv(clientSocket, buffer, BUFFER_LEN, MSG_DONTWAIT);
		// Booléen pour suivre l'état de la socket
		int isClosed = 0;
		if (len == -1 && errno != EAGAIN) {
			// Une erreur est survenue
			OUT_ERR(strerror(errno),errno);
			isClosed = 1;
		} else if (len == 0) {
			// Le client s'est déconnecté (extrémité de la socket fermée)
			isClosed = 1;
		} else if (len > 0) {
			// Ajout du terminateur de chaîne
			buffer[len] = '\0';
			if (strncmp(buffer, EXIT_WORD, 4) == 0) {
				// Le client veut se déconnecter
				send(clientSocket, "Bye\n", strlen("Bye\n"), 0);
				isClosed = 1;
			} else {
				// On renvoie le texte au client dans un buffer assez grand
				int len = strlen("Vous avez dit : ") + strlen(buffer) + 1;
				char response[len];
				strcpy(response, "Vous avez dit : ");
				strcat(response, buffer);
				// Un seul envoie permet de ne pas surcharger le réseau
				send(clientSocket, response, strlen(response), 0);
				OUT_LOGINT("Message du client",i);
				strncpy(first,buffer,10);
				first[strcspn(first, "\n")] = 0;
				OUT_LOGCHAR("Texte",first);
			}
		}
		if (isClosed == 1) {
			// La socket est fermé ou le client veut quitter le serveur !
			OUT_LOG("Fermeture de la connexion avec le client");
			// Fermeture de la socket
			close(clientSocket);
			// On fait de la place dans le tableau
			clients[i] = -1;
		}
	}
}
