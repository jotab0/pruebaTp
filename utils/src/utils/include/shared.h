#ifndef SHARED_H_
#define SHARED_H_

#include <stdlib.h>
#include <stdio.h>

//las agregue 16/04 17:15hs
#include <signal.h>
#include <unistd.h>
#include <sys/socket.h>
#include <netdb.h>
#include <string.h>

#include <commons/log.h> 
#include <commons/config.h>  // de esta manera agregamos librerías de las commons

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

/*typedef struct 
{
    int size;
    void* stream;
} t_buffer;

typedef struct{
    op_code codigo_operacion;
    t_buffer* buffer;
} t_paquete;
*/
/*
void prueba_de_shared(char* mensaje);
int sumador_de_dos_numeros(int valor1, int valor2);
int crear_conexion(char* ip, char* puerto);
int iniciar_servidor(char* puerto, t_log* un_log, char* msj_server);
int esperar_cliente(int socket_servidor, t_log* un_log, char* msj);
int recibir_operacion(int socket_cliente);
*/

#endif