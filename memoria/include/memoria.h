#ifndef MEMORIA_H_
#define MEMORIA_H_

#include <stdlib.h>
#include <stdio.h>
#include <utils/include/shared.h> 

t_log* memoria_logger;
t_log* memoria_logger_extra;

t_config* memoria_config;

char* PUERTO_ESCUCHA;

int TAM_MEMORIA;
int TAM_PAGINA;

char* PATH_INSTRUCCIONES;
int RETARDO_RESPUESTA;

#endif