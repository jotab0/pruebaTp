#ifndef MEMORIA_H_
#define MEMORIA_H_

#include <stdlib.h>
#include <stdio.h>
#include <utils/include/shared.h> 

// VARIABLES GLOBALES
t_log* memoria_logger;
t_log* memoria_logger_extra;

t_config* memoria_config;

char* path_config_Memoria = "/home/utnso/Documents/tp-2024-1c-ubuntunel/memoria/Memoria.config";

// Variables de config
char* PUERTO_ESCUCHA;

int TAM_MEMORIA;
int TAM_PAGINA;

char* PATH_INSTRUCCIONES;
int RETARDO_RESPUESTA;

#endif