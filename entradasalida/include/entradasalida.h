#ifndef ENTRADASALIDA_H_
#define ENTRADASALIDA_H_

#include <stdlib.h>
#include <stdio.h>
#include <utils/include/shared.h> 

// VARIABLES GLOBALES
t_log* es_logger;
t_log* es_logger_extra;

t_config* es_config;

// Variables de config
char* TIPO_INTERFAZ;
int TIEMPO_UNIDAD_TRABAJO;

char* IP_KERNEL;
char* PUERTO_KERNEL;

char* IP_MEMORIA;
char* PUERTO_MEMORIA;

char* PATH_BASE_DIALFS;
int BLOCK_SIZE;
int BLOCK_COUNT;

#endif