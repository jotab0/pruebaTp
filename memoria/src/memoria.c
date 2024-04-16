#include "../include/memoria.h"
#include "../include/inicializar_memoria.h"
#include "/home/utnso/Documents/tp-2024-1c-ubuntunel/utils/src/utils/include/servidor/servidor.h"
#include "/usr/include/commons/log.h"

// SERVIDOR DE: CPU, KERNEL, ENTRADASALIDA
// CLIENTE DE: - 

// Declaracion de varibales
t_log* memoria_logger;
t_log* memoria_logger_extra;
t_config* memoria_config;


int fd_memoria;
int fd_cpu;
int fd_interfaz;
int fd_kernel;

char* PUERTO_ESCUCHA;
int TAM_PAGINA;
char* PATH_INSTRUCCIONES;
int TAM_MEMORIA;
int RETARDO_RESPUESTA;

int main(int argc, char* argv[]) {
    
    // Inicializar estructuras de memoria
    inicializar_memoria();

    // Iniciar servidor de memoria
    fd_memoria = iniciar_servidor(PUERTO_ESCUCHA, memoria_logger,"Servidor memoria iniciada");  
    
    // Esperar conexion de entrada y salida
    log_info(memoria_logger, "Esperando conexion a Interfaz de I/O");
    fd_interfaz = esperar_cliente(fd_memoria, memoria_logger);
    
    // Esperar conexion de CPU
    log_info(memoria_logger, "ESperando conexion a CPU");
    fd_cpu = esperar_cliente(fd_memoria, memoria_logger);
    
    // Esperar conexion de kernel 
    log_info(memoria_logger, "ESperando conexion a Kernel");
    fd_kernel = esperar_cliente(fd_memoria, memoria_logger);
    
    // FINALIZAR MEMORIA 
    
    //int fd_kernel = iniciar_servidor()

    return 0;
}