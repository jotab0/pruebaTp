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


// para enviar y recibir mensajes
typedef struct{
    int size;
    void* stream;
}t_buffer;

//estructura para crear paquete
typedef struct{
    //op_code codigo_operacion;
    t_buffer* buffer;
}t_paquete;

int crear_conexion(char *ip, char* puerto);

#endif
