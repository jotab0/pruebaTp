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

// El proceso servidor se queda bloqueado en accept()
// hasta que se le conecte un cliente.
// Si el servidor no esta en accept(), el cliente no podra llamar a connect(), la cual fallara.
int esperar_cliente(int socket_servidor, t_log* log){
	int socket_para_cliente = accept(socket_servidor, NULL, NULL);
	log_info(log, "Se conecto un cliente");

	return socket_para_cliente;
}

// segun el cod_op (es un enum) que devuelve, el SERVIDOR sabra que hacer
int recibir_operacion(int socket_cliente){
	int cod_op;
	if(recv(socket_cliente, &cod_op, sizeof(int), MSG_WAITALL) > 0){
		return cod_op;
	}else{
		close(socket_cliente);
		return -1;
	}
}





