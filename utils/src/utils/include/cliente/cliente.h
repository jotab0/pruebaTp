#ifndef CLIENTE_H_
#define CLIENTE_H_

#include <stdlib.h>
#include <stdio.h>
#include <signal.h>
#include <unistd.h>
#include <sys/socket.h>
#include <netdb.h>
#include <string.h>
#include <commons/log.h>

typedef enum{
    MENSAJE, 
    PAQUETE,
    HANDSHAKE,
    //KERNEL-MEMORIA,
    RPTA_HANDSHAKE,
    CREAR_PROCESO_KM,
    RPTA_CREAR_PROCESO_MK
    //KERNEL-CPU,
    //KERNEL-ENTRADASALIDA,
    //ENTRADASALIDA-MEMORIA,
    //CPU-MEMORIA
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
