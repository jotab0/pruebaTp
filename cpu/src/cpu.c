#include "../include/cpu.h"

// SERVIDOR DE: KERNEL (x2)
// CLIENTE DE:  MEMORIA

int main(void){
    
    // INICIAR CPU
    inicializar_cpu();

    // CONEXIONES CPU
    
    // iniciar server de CPU - Dispatch
    fd_cpu_dispatch = iniciar_servidor(PUERTO_ESCUCHA_DISPATCH, cpu_logger, "!! Servidor CPU-DISPATCH iniciado !!");

    // iniciar server de CPU - Interrupt
    fd_cpu_interrupt = iniciar_servidor(PUERTO_ESCUCHA_INTERRUPT, cpu_logger, "!! Servidor CPU-DISPATCH iniciado !!");
   
    // conectarnos como cliente a MEMORIA
    fd_memoria = crear_conexion(IP_MEMORIA, PUERTO_MEMORIA);
    log_info(cpu_logger, "Conexion con MEMORIA exitosa");

    // esperar al cliente KERNEL en Dispatch
    fd_kernel_dispatch = esperar_cliente(fd_cpu_dispatch, cpu_logger, "KERNEL - Dispathc");

    // esperar al cliente KERNEL en Interrupt
    fd_kernel_interrupt = esperar_cliente(fd_cpu_interrupt, cpu_logger, "KERNEL - Interrupt");

    return EXIT_SUCCESS;
}
   
