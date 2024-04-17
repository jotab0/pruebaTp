#include "../include/entradasalida.h"

// SERVIDOR DE: -
// CLIENTE DE: KERNEL, MEMORIA 


int main(int argc, char* argv[]) {

    // Inicializar estructuras de ES
    inicializar_es();

    //Me conecto como Cliente a MEMORIA
    fd_memoria = crear_conexion(IP_MEMORIA, PUERTO_MEMORIA);
    log_info(es_logger, "Conexion con Memoria exitosa.");
    
    //Me conecto como Cliente a KERNEL
    fd_kernel = crear_conexion(IP_KERNEL, PUERTO_KERNEL);
    log_info(es_logger, "Conexion con Kernel exitosa.");

     
    pthread_t hilo_memoria;
    pthread_create(&hilo_memoria,NULL,(void*)esperar_memoria_es,NULL);
    pthread_detach(esperar_memoria_es);
        
    pthread_t hilo_kernel;
    pthread_create(&hilo_kernel,NULL,(void*)esperar_kernel_es,NULL);
    pthread_join(esperar_kernel_es,NULL);
    
    return 0; 
}
