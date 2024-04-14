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

// despues se van a ir agregando mas
typedef enum
{
	MENSAJE,
	PAQUETE
    //HANDSHAKE,
    //RTA_HANDSHAKE,
    //------- KERNEL MEMORIA----- (poner esto para tenerlo mas ordenado)
    //CREAR_PROCESO_KM 
    //RTA_CREAR_PROCESO_MK
    //------- KERNEL CPU --------
    // etc
}op_code;

// para enviar y recibir mensajes
typedef struct{
    int size;
    void* stream;
}t_buffer;

//estructura que tiene adentro otra estructura(buffer)
typedef struct{
    op_code codigo_operacion;
    t_buffer* buffer;
}t_paquete;

int iniciar_servidor(char* puerto, t_log* log, char* msj_del_server); 
int esperar_cliente(int socket_servidor, t_log* log);
int recibir_operacion(int socket_cliente);

#endif