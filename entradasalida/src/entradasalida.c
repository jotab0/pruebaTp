#include "../include/entradasalida.h"
#include "../include/inicializar_es.h"
#include "../include/es_gestor.h"
#include "../src/utils/include/cliente/cliente.h"
#include "/home/utnso/Documents/tp-2024-1c-ubuntunel/utils/src/utils/include/cliente/cliente.h"

// SERVIDOR DE: -
// CLIENTE DE: KERNEL, MEMORIA 

// Declaracion de varibales
t_log* es_logger;
t_log* es_logger_extra;

t_config* es_config;

int fd_kernel;
int fd_memoria;

// Variables de config
char* TIPO_INTERFAZ;
int TIEMPO_UNIDAD_TRABAJO;

char* IP_KERNEL;
char* PUERTO_KERNEL;

char* IP_MEMORIA;
char* PUERTO_MEMORIA;

char* PATH_BASE_DIALFS;
int BLOCK_SIZE;
int BLOCK_COUNT;

int main(int argc, char* argv[]) {

    // Inicializar estructuras de ES
    inicializar_es();

    //Me conecto como Cliente a MEMORIA
    fd_memoria = crear_conexion(IP_MEMORIA, PUERTO_MEMORIA);
    log_info(es_logger, "Conexion con Memoria exitosa.");
    
    //Me conecto como Cliente a KERNEL
    fd_kernel = crear_conexion(IP_KERNEL, PUERTO_KERNEL);
    log_info(es_logger, "Conexion con Kernel exitosa.");

    return 0; 
}
