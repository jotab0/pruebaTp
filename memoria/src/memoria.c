#include "../include/memoria.h"


// SERVIDOR DE: CPU, KERNEL, ENTRADASALIDA
// CLIENTE DE: - 



int main(int argc, char* argv[]) {
    
    // Inicializar estructuras de memoria
    inicializar_memoria();

    // Iniciar servidor de memoria
    fd_memoria = iniciar_servidor(PUERTO_ESCUCHA,memoria_logger,"Servidor memoria iniciada");  
    
    // Esperar conexion de entrada y salida
    log_info(memoria_logger, "Esperando conexion a Interfaz de I/O");
    fd_interfaz = esperar_cliente(fd_memoria, memoria_logger,"Esperando E/S");
    
    // Esperar conexion de CPU
    log_info(memoria_logger, "ESperando conexion a CPU");
    fd_cpu = esperar_cliente(fd_memoria, memoria_logger,"Esperando CPU");
    
    // Esperar conexion de kernel 
    log_info(memoria_logger, "ESperando conexion a Kernel");
    fd_kernel = esperar_cliente(fd_memoria, memoria_logger,"Esperando kernel");
    
    // FINALIZAR MEMORIA 
    
    //int fd_kernel = iniciar_servidor()

    return EXIT_SUCCESS;
}