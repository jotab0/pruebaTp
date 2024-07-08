# include "../include/comunicaciones_es.h"

void iterator(char* value){
	log_info(es_logger,"%s",value);
}

void enviar_handshake(){
	
	t_paquete* un_paquete = crear_paquete_con_buffer(HANDSHAKE_K_ES);

	cargar_string_a_paquete(un_paquete,"una_interfaz");
	cargar_int_a_paquete(un_paquete,IO_GEN_SLEEP);
	cargar_int_a_paquete(un_paquete,IO_FS_CREATE);
	cargar_int_a_paquete(un_paquete,IO_FS_READ);
	
	log_info(es_logger,"Enviando interfaz a kernel...");
	enviar_paquete(un_paquete,fd_kernel);
	destruir_paquete(un_paquete);
}

void esperar_kernel_es(){
    int estado_while = 1;
	sleep(5);
	enviar_handshake();
    while (estado_while) {
		log_trace(es_logger,"E/S: ESPERANDO MENSAJES DE KERNEL...");
        int cod_op = recibir_operacion(fd_kernel);
		switch (cod_op) {
		case MENSAJE:
		 	recibir_mensaje_tp0(fd_kernel,es_logger);
			break;
		case -1:
			log_error(es_logger, "KERNEL se desconecto. Terminando servidor");
			estado_while = 0;
            break;
		default:
			log_warning(es_logger,"Operacion desconocida");
			break;
		}
	}
}

void esperar_memoria_es(){
    int estado_while = 1;

    while (estado_while) {
		log_trace(es_logger,"E/S: ESPERANDO MENSAJES DE MEMORIA...");
        int cod_op = recibir_operacion(fd_memoria);
        switch (cod_op) {
		case MENSAJE:
		 	recibir_mensaje_tp0(fd_memoria,es_logger);
			break;

		case -1:
			log_error(es_logger, "MEMORIA se desconecto. Terminando servidor");
			estado_while = 0;
            break;
		default:
			log_warning(es_logger,"Operacion desconocida");
			break;
		}
	}
}

