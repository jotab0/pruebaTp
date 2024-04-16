#include "../include/kernel.h"

// SERVIDOR DE: ENTRADASALIDA
// CLIENTE DE: MEMORIA, CPU 

int main(int argc, char* argv[]) {

    kernel_logger = log_create("Kernel.log", "Kernel_log", true, LOG_LEVEL_INFO);
    if (kernel_logger == NULL){
        perror ("No se pudo crear log para el Kernel");
        exit(EXIT_FAILURE);
    }

    kernel_logger_extra = log_create("Kernel_extra.log", "Kernel_extra_log", true, LOG_LEVEL_TRACE);
    if (kernel_logger == NULL){
        perror ("No se pudo crear log extra para el Kernel");
        exit(EXIT_FAILURE);
    }

    kernel_config = config_create(path_config_Kernel);

	if (kernel_config == NULL) {
        perror ("No se pudo crear el config para el módulo kernel");
		exit(EXIT_FAILURE);
	}


    log_info(kernel_logger,"RECURSOS: %s|%s|%s",RECURSOS[0],RECURSOS[1],RECURSOS[2]);

    //Inicializar Kernel
    inicializar_kernel();

    //Conectarse con Memoria
    fd_memoria = crear_conexion(IP_MEMORIA, PUERTO_MEMORIA);
    log_info(kernel_logger, "Conexion con memoria exitosa.");

    //Conectarse con CPU
    fd_cpu_dispath = crear_conexion(IP_CPU, PUERTO_CPU_DISPATCH);
    log_info(kernel_logger, "Conexion con CPU DISPATCH exitosa.");

    fd_cpu_interrupt = crear_conexion(IP_CPU, PUERTO_CPU_INTERRUPT);
    log_info(kernel_logger, "Conexion con CPU INTERRUPT exitosa.");

    //Atender los mensajes de CPU - Dispatch
    pthread_t hilo_cpu_dispatch;
    pthread_create(&hilo_cpu_dispatch, NULL, (void*)atender_kernel_cpu_dispatch, NULL);
    pthread_detach(hilo_cpu_dispatch);

    //Atender los mensajes de CPU - Interrupt

    pthread_t hilo_cpu_interrupt;
    pthread_create(&hilo_cpu_interrupt, NULL, (void*)atender_kernel_cpu_interrupt, NULL);
    pthread_detach(hilo_cpu_dispatch);

    //Atender los mensajes de EntradaSalida

    pthread_t hilo_entradasalida;
    pthread_create(&hilo_entradasalida, NULL, (void*)atender_kernel_entradasalida, NULL);
    pthread_detach(hilo_entradasalida);
     
    //Atender los mensajes de Memoria

    pthread_t hilo_memoria;
    pthread_create(&hilo_memoria, NULL, (void*)atender_kernel_memoria, NULL);
    pthread_join(hilo_memoria, NULL);

    //Iniciar la consola interactiva
    

    return 0;
}