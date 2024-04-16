#ifndef MEMORIA_H_
#define MEMORIA_H_

#include <stdlib.h>
#include <stdio.h>
#include <utils/include/shared.h> 

// VARIABLES GLOBALES
extern t_log* memoria_logger;
extern t_log* memoria_logger_extra;

extern t_config* memoria_config;

extern char* path_config_Memoria;

extern int fd_memoria;
extern int fd_cpu;
extern int fd_interfaz;
extern int fd_kernel;

// Variables de config
extern char* PUERTO_ESCUCHA;
extern int TAM_MEMORIA;
extern int TAM_PAGINA;
extern char* PATH_INSTRUCCIONES;
extern int RETARDO_RESPUESTA;

#endif