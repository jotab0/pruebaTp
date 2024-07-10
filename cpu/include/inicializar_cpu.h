#ifndef INICIALIZAR_CPU_H
#define INICIALIZAR_CPU_H

#include "c_gestor.h"

void inicializar_cpu();
void iniciar_logs();
void iniciar_config();
void imprimir_config();

pthread_mutex_t mutex_proceso_actual;

#endif 

