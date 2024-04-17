#ifndef M_GESTOR_H_
#define M_GESTOR_H_

#include <stdio.h>
#include <stdlib.h>

#include <utils/include/shared.h> 

#include <commons/log.h>
#include <commons/config.h>

// variables globales

extern t_log* memoria_logger;
extern t_log* memoria_logger_extra;
extern t_config* memoria_config;

extern char* PUERTO_ESCUCHA;
extern int TAM_MEMORIA;
extern int TAM_PAGINA;
extern char* PATH_INSTRUCCIONES;
extern int RETARDO_RESPUESTA;

extern char* path_config_Memoria; 

extern int fd_memoria;
extern int fd_cpu;
extern int fd_interfaz;
extern int fd_kernel;

#endif