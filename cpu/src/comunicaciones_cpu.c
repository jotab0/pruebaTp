#include "../include/comunicaciones_cpu.h"

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

			if(pid == 2){

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

			}else{
				t_paquete* un_paquete = crear_paquete_con_buffer(QUANTUM_INTERRUPT);

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
			}

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
			int dato = extraer_int_del_buffer(un_buffer);
			log_info(cpu_logger,"PID: %d",dato);
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