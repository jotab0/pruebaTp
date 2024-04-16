#ifndef ENTRADASALIDA_H_
#define ENTRADASALIDA_H_

#include <stdlib.h>
#include <stdio.h>
#include <utils/include/shared.h> 


// VARIABLES GLOBALES
extern t_log* es_logger;
extern t_log* es_logger_extra;

extern t_config* es_config;

extern char* path_config_ES= "/home/utnso/Documents/tp-2024-1c-ubuntunel/entradasalida/ES.config";

extern int fd_kernel;
extern int fd_memoria;

// Variables de config
extern char* TIPO_INTERFAZ;
extern int TIEMPO_UNIDAD_TRABAJO;

extern char* IP_KERNEL;
extern char* PUERTO_KERNEL;

extern char* IP_MEMORIA;
extern char* PUERTO_MEMORIA;

extern char* PATH_BASE_DIALFS;
extern int BLOCK_SIZE;
extern int BLOCK_COUNT;

#endif