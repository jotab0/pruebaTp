#ifndef SERVIDOR_H_
#define SERVIDOR_H_

#include<stdio.h>
#include<stdlib.h>
#include<sys/socket.h>
#include<unistd.h>
#include<netdb.h>
#include<commons/log.h>
#include<commons/collections/list.h>
#include<string.h>
#include<assert.h>

int iniciar_servidor(char* puerto, t_log* log, char* msj_del_server); 
int esperar_cliente(int socket_servidor, t_log* log);
int recibir_operacion(int socket_cliente);

#endif