#include "../servidor/servidor.h"

int iniciar_servidor(char* puerto, t_log* log, char* msj_del_server)
{
	int socket_servidor;

	struct addrinfo hints, *servinfo;

	memset(&hints, 0, sizeof(hints));
	hints.ai_family = AF_INET;
	hints.ai_socktype = SOCK_STREAM;
	hints.ai_flags = AI_PASSIVE;

	getaddrinfo(NULL, puerto, &hints, &servinfo); 

	socket_servidor = socket(
		servinfo->ai_family,
        servinfo->ai_socktype,
        servinfo->ai_protocol);
	bind(socket_servidor, servinfo->ai_addr, servinfo->ai_addrlen);
	listen(socket_servidor,SOMAXCONN);

	freeaddrinfo(servinfo);
	log_trace(log, "Server: %s",msj_del_server);

	return socket_servidor;
}