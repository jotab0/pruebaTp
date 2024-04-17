#include "../include/memoria.h"


// SERVIDOR DE: CPU, KERNEL, ENTRADASALIDA
// CLIENTE DE: - 



int main(int argc, char* argv[]) {
    
    // Inicializar estructuras de memoria
    inicializar_memoria();

    // Iniciar servidor de memoria
    fd_memoria = iniciar_servidor(PUERTO_ESCUCHA,memoria_logger,"!! Servidor MEMORIA iniciada !!");  
    
    //CONECTAR CON CLIENTES
    // Esperar conexion de CPU
    fd_cpu = esperar_cliente(fd_memoria, memoria_logger,"CPU");

    // Esperar conexion de kernel 
    fd_kernel = esperar_cliente(fd_memoria, memoria_logger,"Kernel");
    
    // Esperar conexion de entrada y salida
    fd_interfaz = esperar_cliente(fd_memoria, memoria_logger,"E/S");
    

    
    // FINALIZAR MEMORIA 

    return EXIT_SUCCESS;
}