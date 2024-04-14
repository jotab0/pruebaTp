#ifndef CLIENTE_H_
#define CLIENTE_H_

#include <stdlib.h>
#include <stdio.h>
#include<signal.h>
#include<unistd.h>
#include<sys/socket.h>
#include<netdb.h>
#include<string.h>
#include<commons/log.h>

// despues se van a ir agregando mas
typedef enum
{
	MENSAJE,
	PAQUETE
    //HANDSHAKE,
    //RTA_HANDSHAKE,
    //------- KERNEL -> MEMORIA ----- (poner esto para tenerlo mas ordenado)
    //CREAR_PROCESO_KM 
    //------- MEMORIA -> KERNEL -----
    //RTA_CREAR_PROCESO_MK
    //------- KERNEL -> CPU --------
    // etc
}op_code;

// para enviar y recibir mensajes
typedef struct{
    int size;
    void* stream;
}t_buffer;

//estructura para crear paquete
typedef struct{
    op_code codigo_operacion;
    t_buffer* buffer;
}t_paquete;

int crear_conexion(char *ip, char* puerto);

#endif
