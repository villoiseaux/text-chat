#ifndef __textchat__server_h
	#define __textchat__server_h
	// Port d'écoute de la socket
	#define PORT 8080
	// Adresse d'écoute (toutes les adresses)
	#define IP INADDR_ANY
	// Taille de la file d'attente
	#define BACKLOG 3
	// Nombre de connexions clients
	#define NB_CLIENTS 2
	// Taille du tampon de lecture des messages
	#define BUFFER_LEN 200
	// Commande pour arrêter le serveur
	#define EXIT_WORD "exit"

	void initAdresse(struct sockaddr_in * adresse);
	int initSocket(struct sockaddr_in * adresse);
	int waitForClient(int * serverSocket);
	void addClientToTab(int clientSocket, int clients[]);
	void manageClient(int clients[]);
#endif