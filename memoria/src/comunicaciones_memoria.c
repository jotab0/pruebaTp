
# include "../include/comunicaciones_memoria.h"

void iterator(char* value){
	log_info(memoria_logger,"%s",value);
}

void esperar_cpu_memoria(){
    int estado_while = 1;
	t_list* lista;
    while (estado_while) {
        log_trace(memoria_logger,"MEMORIA: ESPERANDO MENSAJES DE CPU...");
		int cod_op = recibir_operacion(fd_cpu);
		switch (cod_op) {
		case MENSAJE:
		 	recibir_mensaje_tp0(fd_cpu,memoria_logger);
			break;
		case PAQUETE:
			lista = recibir_paquete(fd_cpu);
			log_info(memoria_logger,"Me llegaron los siguientes mensajes:\n");
			list_iterate(lista,(void*)iterator);
			break;
		

		case -1:
			log_error(memoria_logger, "CPU se desconecto. Terminando servidor");
			estado_while = 0;
            break;
		default:
			log_warning(memoria_logger,"Operacion desconocida");
			break;
		}
	}
}

void esperar_kernel_memoria(){
    int estado_while = 1;
	t_list* lista;
    while (estado_while) {
		log_trace(memoria_logger,"MEMORIA: ESPERANDO MENSAJES DE KERNEL...");
        int cod_op = recibir_operacion(fd_kernel);
		switch (cod_op) {
		case MENSAJE:
		 	recibir_mensaje_tp0(fd_kernel,memoria_logger);
			break;

		case PAQUETE:
			lista = recibir_paquete(fd_kernel);
			log_info(memoria_logger,"Me llegaron los siguientes mensajes:\n");
			list_iterate(lista,(void*)iterator);

			break;
			
		case INICIAR_ESTRUCTURA:

			t_buffer* un_buffer = recibir_buffer(fd_kernel);
			log_info(memoria_logger,"Tamaño buffer: %d",un_buffer->size);

			char* un_path = extraer_string_del_buffer(un_buffer);
			int un_pid = extraer_int_del_buffer(un_buffer);

			log_info(memoria_logger,"Me llegó proceso con PID: %d", un_pid);
			log_info(memoria_logger,"Me llegó proceso con PATH: %s", un_path);
			log_info(memoria_logger,"Tamaño buffer: %d",un_buffer->size);

			destruir_buffer(un_buffer);

			t_paquete* un_paquete = crear_paquete_con_buffer(RTA_INICIAR_ESTRUCTURA);
			cargar_int_a_paquete(un_paquete,1);

			log_info(memoria_logger,"Enviando respuesta a kernel");
			enviar_paquete(un_paquete,fd_kernel);

			destruir_paquete(un_paquete);

			break;

		case LIBERAR_ESTRUCTURAS:
			
			un_buffer = recibir_buffer(fd_kernel);
			int pid = extraer_int_del_buffer(un_buffer);
			log_info(memoria_logger, "Me llegó solicitud para eliminar de memoria proceso con PID: %d",pid );
			
		break;

		case -1:
			log_error(memoria_logger, "KERNEL se desconecto. Terminando servidor");
			estado_while = 0;
            break;
		default:
			log_warning(memoria_logger,"Operacion desconocida");
			break;
		}
	}
}

void esperar_es_memoria(){
    int estado_while = 1;
	t_list* lista;
    while (estado_while) {
		log_trace(memoria_logger,"MEMORIA: ESPERANDO MENSAJES DE E/S...");
        int cod_op = recibir_operacion(fd_es);
		switch (cod_op) {
		case MENSAJE:
		 	recibir_mensaje_tp0(fd_es,memoria_logger);
			break;
		case PAQUETE:
			lista = recibir_paquete(fd_es);
			log_info(memoria_logger,"Me llegaron los siguientes mensajes:\n");
			list_iterate(lista,(void*)iterator);
			break;
		case -1:
			log_error(memoria_logger, "ENTRADASALIDA se desconecto. Terminando servidor");
			estado_while = 0;
            break;
		default:
			log_warning(memoria_logger,"Operacion desconocida");
			break;
		}
	}
}

