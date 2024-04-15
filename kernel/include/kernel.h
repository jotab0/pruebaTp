#ifndef KERNEL_H_
#define KERNEL_H_

#include <stdlib.h>
#include <stdio.h>
#include <utils/include/shared.h> 

// VARIABLES GLOBALES

t_log* kernel_logger;
t_log* kernel_logger_extra;

t_config* kernel_config;

// Variables de config
char* PUERTO_ESCUCHA;

char* IP_MEMORIA;
char* PUERTO_MEMORIA;

char* IP_CPU;
char* PUERTO_CPU_DISPATCH;
char* PUERTO_CPU_INTERRUPT;

char* ALGORITMO_PLANIFICACION;
int QUANTUM;
char** RECURSOS;
char** INSTANCIAS_RECURSOS;
int GRADO_MULTIPROGRAMACION;

#endif