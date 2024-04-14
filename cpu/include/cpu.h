#ifndef CPU_H_
#define CPU_H_

#include <stdlib.h>
#include <stdio.h>
#include <utils/include/shared.h>

// VARIABLES GLOBALES

t_log* cpu_logger;
t_log* cpu_logger_extra;

t_config* cpu_config;

// Variables de config
char* IP_MEMORIA;
char* PUERTO_MEMORIA;
char* PUERTO_ESCUCHA_DISPATCH;
char* PUERTO_ESCUCHA_INTERRUPT;

int CANTIDAD_ENTRADAS_TLB;
char* ALGORITMO_TLB;

 

#endif