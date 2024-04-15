#include "../include/entradasalida.h"

// SERVIDOR DE: -
// CLIENTE DE: KERNEL, MEMORIA 

int main(int argc, char* argv[]) {

    es_logger = log_create("EntradaSalida.log", "ES_log", true, LOG_LEVEL_INFO);
    if (es_logger == NULL){
        perror ("No se pudo crear log para el módulo E/S");
        exit(EXIT_FAILURE);
    }

    es_logger_extra = log_create("EntradaSalida_extra_log.log", "ES_extra_log", true, LOG_LEVEL_TRACE);
    if (es_logger_extra == NULL){
        perror ("No se pudo crear log extra para el módulo E/S");
        exit(EXIT_FAILURE);
    }

    es_config = config_create(path_config_ES);

	if (es_config == NULL) {
        perror ("No se pudo crear el config para el módulo E/S");
		exit(EXIT_FAILURE);
	}

    TIPO_INTERFAZ = config_get_string_value(es_config,"TIPO_INTERFAZ");
    TIEMPO_UNIDAD_TRABAJO = config_get_int_value(es_config,"TIEMPO_UNIDAD_TRABAJO");
    IP_KERNEL = config_get_string_value(es_config,"IP_KERNEL");
    PUERTO_KERNEL = config_get_string_value(es_config,"PUERTO_KERNEL");
    IP_MEMORIA = config_get_string_value(es_config,"IP_MEMORIA");
    PUERTO_MEMORIA = config_get_string_value(es_config,"PUERTO_MEMORIA");
    PATH_BASE_DIALFS = config_get_string_value(es_config,"PATH_BASE_DIALFS");
    BLOCK_SIZE = config_get_int_value(es_config,"BLOCK_SIZE");
    BLOCK_COUNT = config_get_int_value(es_config,"BLOCK_COUNT");

    log_info(es_logger,"PATH INSTRUCCIONES: %s",IP_MEMORIA);

    return 0;
}
