#include "../include/comunicaciones_cpu.h"

int proceso_actual;

void iterator(char* value){
	log_info(cpu_logger,"%s",value);
}

void esperar_kernel_cpu_interrupt(){
    int estado_while = 1;

    while (estado_while) {
		log_trace(cpu_logger,"CPU INTERRUPT: ESPERANDO MENSAJES DE KERNEL...");
        int cod_op = recibir_operacion(fd_kernel_interrupt);
		switch (cod_op) {
		case MENSAJE:
		 	recibir_mensaje_tp0(fd_kernel_interrupt,cpu_logger);
			break;

		
		case EXIT_PROCESS:
			t_buffer* un_buffer = recibir_buffer(fd_kernel_interrupt);
			int pid = extraer_int_del_buffer(un_buffer);
			log_info(cpu_logger,"Me llegó solicitud para interrumpir el proceso con PID: %d",pid);
			log_info(cpu_logger,"Eliminando proceso con PID: %d",pid);

				t_paquete* un_paquete = crear_paquete_con_buffer(EXIT_PROCESS);

				cargar_int_a_paquete(un_paquete,pid);
				cargar_int_a_paquete(un_paquete,2);

				cargar_int_a_paquete(un_paquete,3);
				cargar_int_a_paquete(un_paquete,4);
				cargar_int_a_paquete(un_paquete,5);
				cargar_int_a_paquete(un_paquete,6);
				cargar_int_a_paquete(un_paquete,7);
				cargar_int_a_paquete(un_paquete,8);

				cargar_int_a_paquete(un_paquete,0);

				enviar_paquete(un_paquete,fd_kernel_dispatch);

			break;
		case QUANTUM_INTERRUPT:

			un_buffer = recibir_buffer(fd_kernel_interrupt);
			pid = extraer_int_del_buffer(un_buffer);
			log_info(cpu_logger,"Me llegó solicitud para interrumpir el proceso con PID: %d",pid);

			un_paquete = crear_paquete_con_buffer(QUANTUM_INTERRUPT);

			cargar_int_a_paquete(un_paquete,pid);
			cargar_int_a_paquete(un_paquete,2);

			cargar_int_a_paquete(un_paquete,3);
			cargar_int_a_paquete(un_paquete,4);
			cargar_int_a_paquete(un_paquete,5);
			cargar_int_a_paquete(un_paquete,6);
			cargar_int_a_paquete(un_paquete,7);
			cargar_int_a_paquete(un_paquete,8);

			cargar_int_a_paquete(un_paquete,0);

			enviar_paquete(un_paquete,fd_kernel_dispatch);

		break;

		case -1:
			log_error(cpu_logger, "KERNEL se desconecto de cpu interrupt. Terminando servidor");
			estado_while = 0;
            break;
		default:
			log_warning(cpu_logger,"Operacion desconocida de KERNEL (Interrupt)");
			break;
		}
	}
}

void esperar_kernel_cpu_dispatch(){
    int estado_while = 1;
    while (estado_while) {
		t_list* lista;
		log_trace(cpu_logger,"CPU DISPATCH: ESPERANDO MENSAJES DE KERNEL...");
        int cod_op = recibir_operacion(fd_kernel_dispatch);
		switch (cod_op) {
		case MENSAJE:
		 	recibir_mensaje_tp0(fd_kernel_dispatch,cpu_logger);
			break;
		case PAQUETE:
			lista = recibir_paquete(fd_kernel_dispatch);
			log_info(cpu_logger,"Me llegaron los siguientes mensajes:\n");
			list_iterate(lista,(void*)iterator);
			break;
		case EJECUTAR_PROCESO_KCPU:

			t_buffer* un_buffer = recibir_buffer(fd_kernel_dispatch);
			pthread_mutex_lock(&mutex_proceso_actual);
			int dato = extraer_int_del_buffer(un_buffer);
			log_info(cpu_logger,"PID: %d",dato);
			proceso_actual = dato;
			pthread_mutex_unlock(&mutex_proceso_actual);
			 dato = extraer_int_del_buffer(un_buffer);
			log_info(cpu_logger,"PC: %d", dato);
			 dato = extraer_int_del_buffer(un_buffer);
			log_info(cpu_logger,"TIEMPO EJECUTADO: %d",dato);
			 dato = extraer_int_del_buffer(un_buffer);
			log_info(cpu_logger,"TICKET: %d", dato);
			 dato = extraer_uint32_del_buffer(un_buffer);
			log_info(cpu_logger,"DX: %d", dato);
			 dato = extraer_uint32_del_buffer(un_buffer);
			log_info(cpu_logger,"AX: %d", dato);
			 dato = extraer_uint32_del_buffer(un_buffer);
			log_info(cpu_logger,"CX: %d", dato);
			 dato = extraer_uint32_del_buffer(un_buffer);
			log_info(cpu_logger,"BX: %d", dato);
			 dato = extraer_uint32_del_buffer(un_buffer);
			log_info(cpu_logger,"SI: %d", dato);
			 dato = extraer_uint32_del_buffer(un_buffer);
			log_info(cpu_logger,"DI: %d", dato);
			
			break;
			
		case -1:
			log_error(cpu_logger, "KERNEL se desconecto de cpu dispatch. Terminando servidor");
			estado_while = 0;
            break;
		default:
			log_warning(cpu_logger,"Operacion desconocida de KERNEL (Distaptch)");
			break;
		}
	}
}

void esperar_memoria_cpu(){
    int estado_while = 1;
    while (estado_while) {
		log_trace(cpu_logger,"CPU: ESPERANDO MENSAJES DE MEMORIA");
		t_list* lista;
        int cod_op = recibir_operacion(fd_memoria);
		switch (cod_op) {
		case MENSAJE:
		 	recibir_mensaje_tp0(fd_memoria,cpu_logger);
			break;
		case PAQUETE:
			lista = recibir_paquete(fd_memoria);
			log_info(cpu_logger,"Me llegaron los siguientes mensajes:\n");
			list_iterate(lista,(void*)iterator);
			break;
		case -1:
			log_error(cpu_logger, "MEMORIA se desconecto. Terminando servidor");
			estado_while= 0;
            break;
		default:
			log_warning(cpu_logger,"Operacion desconocida de MEMORIA");
			break;
		}
	}
}

void solicitar_recurso(char* un_recurso){

	t_paquete* un_paquete = crear_paquete_con_buffer(WAIT_KCPU);
	cargar_string_a_paquete(un_paquete,un_recurso);

	// Contexto pcb
	pthread_mutex_lock(&mutex_proceso_actual);
	cargar_int_a_paquete(un_paquete, proceso_actual); 
	pthread_mutex_unlock(&mutex_proceso_actual);

	cargar_int_a_paquete(un_paquete, 15);

	cargar_int_a_paquete(un_paquete, 12);
	cargar_int_a_paquete(un_paquete, 13);
	cargar_int_a_paquete(un_paquete, 14);
	cargar_int_a_paquete(un_paquete, 15);
	cargar_int_a_paquete(un_paquete, 16);
	cargar_int_a_paquete(un_paquete, 17);

	cargar_int_a_paquete(un_paquete, 18);

	enviar_paquete(un_paquete,fd_kernel_dispatch);

	destruir_paquete(un_paquete);
}

void signal_recurso(char* un_recurso){

	t_paquete* un_paquete = crear_paquete_con_buffer(SIGNAL_KCPU);
	
	cargar_string_a_paquete(un_paquete,un_recurso);

	enviar_paquete(un_paquete,fd_kernel_dispatch);

	destruir_paquete(un_paquete);

}

void solicitar_instruccion(instruccion_interfaz una_instruccion){
	t_paquete* un_paquete = crear_paquete_con_buffer(ATENDER_INSTRUCCION_CPU);
	cargar_int_a_paquete(un_paquete, una_instruccion);

	cargar_string_a_paquete(un_paquete, "una_interfaz");
	cargar_int_a_paquete(un_paquete,5);

	// Datos auxiliares
	cargar_int_a_paquete(un_paquete,5);

	// Contexto pcb
	cargar_int_a_paquete(un_paquete, proceso_actual); // Recordar que deben coincidir

	cargar_int_a_paquete(un_paquete, 15);

	cargar_int_a_paquete(un_paquete, 0);
	cargar_int_a_paquete(un_paquete, 0);
	cargar_int_a_paquete(un_paquete, 0);
	cargar_int_a_paquete(un_paquete, 0);
	cargar_int_a_paquete(un_paquete, 0);
	cargar_int_a_paquete(un_paquete, 0);

	cargar_int_a_paquete(un_paquete, 0);

	enviar_paquete(un_paquete,fd_kernel_dispatch);
	destruir_paquete(un_paquete);

}

void hilo_extra_funciones(){
	
	log_trace(cpu_logger, "CPU lista para enviar instrucciones extra");
	sleep(20);
	
	solicitar_instruccion(IO_GEN_SLEEP);
	sleep(25);

	solicitar_recurso("RB");
	sleep(2);

	solicitar_recurso("RB");
	sleep(2);

	solicitar_recurso("RB");
	sleep(30);

	signal_recurso("RB");
	sleep(2);
	signal_recurso("RB");
}