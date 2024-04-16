#ifndef KERNEL_H_
#define KERNEL_H_

#include "../include/k_gestor.h"

#include "inicializar_kernel.h"
#include "kernel_cpu_dispatch.h"
#include "kernel_cpu_interrupt.h"
#include "kernel_entradasalida.h"
#include "kernel_memoria.h"

#include <stdlib.h>
#include <stdio.h>
#include <utils/include/shared.h> 
#include <utils/include/cliente/cliente.h>
#include <utils/include/servidor/servidor.h>



// VARIABLES GLOBALES
t_log* kernel_logger;
t_log* kernel_logger_extra;

t_config* kernel_config;

char* path_config_Kernel = "/home/utnso/Documents/tp-2024-1c-ubuntunel/kernel/Kernel.config";

int fd_memoria;
int fd_entradasalida;
int fd_cpu_dispath;
int fd_cpu_interrupt;

// Variables de config
char* PUERTO_ESCUCHA;

char* IP_MEMORIA;
char* PUERTO_MEMORIA;

char* IP_ENTRADASALIDA;
char* PUERTO_ENTRADASALIDA;

char* IP_CPU;
char* PUERTO_CPU_DISPATCH;
char* PUERTO_CPU_INTERRUPT;

char* ALGORITMO_PLANIFICACION;
int QUANTUM;
char** RECURSOS;
char** INSTANCIAS_RECURSOS;
int GRADO_MULTIPROGRAMACION;

void atender_kernel_cpu_dispatch();

#endif