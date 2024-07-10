#include "../include/kernel_cpu_dispatch.h"


void esperar_conexiones_cpu_dispatch(){
	
	fd_cpu_dispatch = crear_conexion(IP_CPU, PUERTO_CPU_DISPATCH);
    log_info(kernel_logger, "Conexion con CPU DISPATCH exitosa.");

	pthread_t hilo_cpu_dispatch;
	int err = pthread_create(&hilo_cpu_dispatch, NULL,(void*)esperar_cpu_dispatch_kernel, NULL);
	if (err!=0){
		perror("Fallo de creación de hilo_cpu_dispatch(kernel)\n");
		exit(-3);
	}
	pthread_detach(hilo_cpu_dispatch);
}



void esperar_cpu_dispatch_kernel(){
    int estado_while = 1;

    while (estado_while) {
		
		
		int cod_op = recibir_operacion(fd_cpu_dispatch);
		switch (cod_op) {
		// TAM + STREAM
		
		case ATENDER_INSTRUCCION_CPU:
		 	
			log_trace(kernel_logger,"Solicitud de instrucción a interfaz recibida");
			t_buffer* un_buffer = recibir_buffer(fd_cpu_dispatch);
			
			instruccion_interfaz instruccion_solicitada = extraer_int_del_buffer(un_buffer);
			char* interfaz_solicitada = extraer_string_del_buffer(un_buffer);
			int cantidad_recursos = extraer_int_del_buffer(un_buffer);

			pcb* un_pcb = NULL;
			pthread_mutex_lock(&mutex_lista_exec);
			un_pcb = list_remove(execute,0);
			pthread_mutex_unlock(&mutex_lista_exec);
			
			extraer_datos_auxiliares(un_buffer,instruccion_solicitada,un_pcb);

			obtener_contexto_pcb(un_buffer,un_pcb);
			
			un_pcb -> motivo_bloqueo = PEDIDO_A_INTERFAZ;

			un_pcb -> pedido_a_interfaz -> nombre_interfaz = malloc(sizeof(strlen(interfaz_solicitada)+1));
			strcpy(un_pcb->pedido_a_interfaz->nombre_interfaz, interfaz_solicitada);
			un_pcb -> pedido_a_interfaz -> instruccion_a_interfaz = instruccion_solicitada;

			list_add_pcb_sync(blocked,un_pcb,&mutex_lista_blocked,BLOCKED);

			manejar_bloqueo_de_proceso(un_pcb);

			sem_post(&sem_cpu_libre);	

			destruir_buffer(un_buffer);

		break;

		case WAIT_KCPU:

			un_buffer = recibir_buffer(fd_cpu_dispatch);
			char* recurso_solicitado = extraer_string_del_buffer(un_buffer);

			un_pcb = NULL;
			pthread_mutex_lock(&mutex_lista_exec);
			un_pcb = list_remove(execute,0);
			pthread_mutex_unlock(&mutex_lista_exec);

			obtener_contexto_pcb(un_buffer,un_pcb);
			
			list_add_pcb_sync(blocked,un_pcb,&mutex_lista_blocked,BLOCKED);

			un_pcb -> motivo_bloqueo = WAIT;
			un_pcb -> pedido_recurso = recurso_solicitado;

			manejar_bloqueo_de_proceso(un_pcb);	
			
			sem_post(&sem_cpu_libre);	

			destruir_buffer(un_buffer);

		break;

		case SIGNAL_KCPU:

			un_buffer = recibir_buffer(fd_cpu_dispatch);
			recurso_solicitado = extraer_string_del_buffer(un_buffer);

			pthread_mutex_lock(&mutex_lista_exec);
			un_pcb = list_get(execute,0);
			pthread_mutex_unlock(&mutex_lista_exec);

			un_pcb -> motivo_bloqueo = SIGNAL;
			un_pcb -> pedido_recurso = recurso_solicitado;

			//CONSULTA: Que pasa si hace signal de un recurso que no tiene?
			manejar_bloqueo_de_proceso(un_pcb);

			destruir_buffer(un_buffer);

		break;

		case QUANTUM_INTERRUPT:

			un_buffer = recibir_buffer(fd_cpu_dispatch);

			pthread_mutex_lock(&mutex_lista_exec);
			un_pcb = list_remove(execute,0);
			pthread_mutex_unlock(&mutex_lista_exec);

			log_info(kernel_logger,"Contexto antes de actualización");
			mostrar_contexto(un_pcb);
			obtener_contexto_pcb(un_buffer,un_pcb);
			log_info(kernel_logger,"Contexto luego de actualización");
			mostrar_contexto(un_pcb);

			agregar_a_ready(un_pcb);
			
			sem_post(&sem_pcp);
			sem_post(&sem_cpu_libre);

		break;

		case EXIT_PROCESS:

			un_buffer = recibir_buffer(fd_cpu_dispatch);

			un_pcb = list_get(execute,0);

			log_info(kernel_logger,"Solicitud proceso con PID: %d - EXIT",un_pcb->pid);
			obtener_contexto_pcb(un_buffer,un_pcb);

			cambiar_estado_pcb(un_pcb,EXIT);

			log_info(kernel_logger,"Planificando proceso con PID: %d - EXIT",un_pcb->pid);
			planificar_proceso_exit_en_hilo(un_pcb);
			
		break;

		case MENSAJE:
		 	recibir_mensaje_tp0(fd_cpu_dispatch,kernel_logger);
			break;

		case -1:
			log_error(kernel_logger, "CPU DISPATCH se desconecto. Terminando servidor");
			estado_while = 0;
            break;
		
		default:
			log_warning(kernel_logger,"Operacion desconocida de CPU DISPATCH");
			break;
		}
	}
}

void enviar_pcb_CPU_dispatch(pcb* un_pcb){

	t_paquete* un_paquete = NULL;
	un_paquete = crear_paquete_con_buffer(EJECUTAR_PROCESO_KCPU);
	cargar_int_a_paquete(un_paquete, un_pcb->pid);
	cargar_int_a_paquete(un_paquete, un_pcb->program_counter);

	// CORRECCION PENDIENTE: No hace falta enviar tiempo ejecutado ni ticket (Verlo con cami)
	cargar_int_a_paquete(un_paquete, un_pcb->tiempo_ejecutado);
	cargar_int_a_paquete(un_paquete, un_pcb->ticket);

	cargar_uint32_a_paquete(un_paquete, un_pcb->registros_CPU->AX);
	cargar_uint32_a_paquete(un_paquete, un_pcb->registros_CPU->BX);
	cargar_uint32_a_paquete(un_paquete, un_pcb->registros_CPU->CX);
	cargar_uint32_a_paquete(un_paquete, un_pcb->registros_CPU->DX);
	cargar_uint32_a_paquete(un_paquete, un_pcb->registros_CPU->SI);
	cargar_uint32_a_paquete(un_paquete, un_pcb->registros_CPU->DI);
	

	log_info(kernel_logger,"PID: %d", un_pcb->pid);
	log_info(kernel_logger,"PC: %d", un_pcb->program_counter);
	log_info(kernel_logger,"TIEMPO EJECUTADO: %d", un_pcb->tiempo_ejecutado);
	log_info(kernel_logger,"TICKET: %d", un_pcb->ticket);
	log_info(kernel_logger,"DX: %d", un_pcb->registros_CPU->DX);
    log_info(kernel_logger,"AX: %d", un_pcb->registros_CPU->AX);
	log_info(kernel_logger,"CX: %d", un_pcb->registros_CPU->CX);
	log_info(kernel_logger,"BX: %d", un_pcb->registros_CPU->BX);
	log_info(kernel_logger,"SI: %d", un_pcb->registros_CPU->SI);
	log_info(kernel_logger,"DI: %d", un_pcb->registros_CPU->DI);

	enviar_paquete(un_paquete, fd_cpu_dispatch); 
	log_info(kernel_logger,"Proceso enviado");
	destruir_paquete(un_paquete);
}


void extraer_datos_auxiliares(t_buffer* un_buffer,instruccion_interfaz instruccion_solicitada, pcb* un_pcb){

	switch (instruccion_solicitada)
	{
		
		case IO_GEN_SLEEP:
			
			int* tiempo_extraido = malloc(sizeof(int));
			*tiempo_extraido = extraer_int_del_buffer(un_buffer);
			list_add(un_pcb->pedido_a_interfaz->datos_auxiliares_interfaz,tiempo_extraido);

			break;
		
		case IO_STDIN_READ:
			
			// Registro dirección
			int* parametro = malloc(sizeof(int));
			*parametro = extraer_int_del_buffer(un_buffer);
			list_add(un_pcb->pedido_a_interfaz->datos_auxiliares_interfaz,parametro);
			// Registro tamaño 
			int* tamanio_parametro = malloc(sizeof(int));
			*tamanio_parametro = extraer_int_del_buffer(un_buffer);
			list_add(un_pcb->pedido_a_interfaz->datos_auxiliares_interfaz,tamanio_parametro);

			break;

		case IO_STDOUT_WRITE:

			// Registro dirección
			parametro = malloc(sizeof(int));
			*parametro = extraer_int_del_buffer(un_buffer);
			list_add(un_pcb->pedido_a_interfaz->datos_auxiliares_interfaz,parametro);
			// Registro tamaño 
			tamanio_parametro = malloc(sizeof(int));
			*tamanio_parametro = extraer_int_del_buffer(un_buffer);
			list_add(un_pcb->pedido_a_interfaz->datos_auxiliares_interfaz,parametro);

			break;

		case IO_FS_CREATE:

			char* un_nombre = extraer_string_del_buffer(un_buffer);
			char* nombre_archivo = malloc(sizeof(strlen(un_nombre) + 1));
			strcpy(nombre_archivo,un_nombre);
			list_add(un_pcb->pedido_a_interfaz->datos_auxiliares_interfaz,nombre_archivo);

			break;

		case IO_FS_DELETE:

			un_nombre = extraer_string_del_buffer(un_buffer);
			nombre_archivo = malloc(sizeof(strlen(un_nombre) + 1));
			strcpy(nombre_archivo,un_nombre);
			list_add(un_pcb->pedido_a_interfaz->datos_auxiliares_interfaz,nombre_archivo);

			break;

		case IO_FS_TRUNCATE:

			un_nombre = extraer_string_del_buffer(un_buffer);
			nombre_archivo = malloc(sizeof(strlen(un_nombre) + 1));
			strcpy(nombre_archivo,un_nombre);
			list_add(un_pcb->pedido_a_interfaz->datos_auxiliares_interfaz,nombre_archivo);
			// Registro tamaño
			parametro = malloc(sizeof(int));
			*parametro = extraer_int_del_buffer(un_buffer);
			list_add(un_pcb->pedido_a_interfaz->datos_auxiliares_interfaz,parametro);

			break;

		case IO_FS_WRITE:

			un_nombre = extraer_string_del_buffer(un_buffer);
			nombre_archivo = malloc(sizeof(strlen(un_nombre) + 1));
			strcpy(nombre_archivo,un_nombre);
			list_add(un_pcb->pedido_a_interfaz->datos_auxiliares_interfaz,nombre_archivo);
			// Registro dirección
			parametro = malloc(sizeof(int));
			*parametro = extraer_int_del_buffer(un_buffer);
			list_add(un_pcb->pedido_a_interfaz->datos_auxiliares_interfaz,parametro);
			// Registro tamaño
			parametro = malloc(sizeof(int));
			*parametro = extraer_int_del_buffer(un_buffer);
			list_add(un_pcb->pedido_a_interfaz->datos_auxiliares_interfaz,parametro);
			// Registro puntero archivo
			parametro = malloc(sizeof(int));
			*parametro = extraer_int_del_buffer(un_buffer);
			list_add(un_pcb->pedido_a_interfaz->datos_auxiliares_interfaz,parametro);
			
			break;
			
		case IO_FS_READ:
			
			un_nombre = extraer_string_del_buffer(un_buffer);
			nombre_archivo = malloc(sizeof(strlen(un_nombre) + 1));
			strcpy(nombre_archivo,un_nombre);
			list_add(un_pcb->pedido_a_interfaz->datos_auxiliares_interfaz,nombre_archivo);
			// Registro dirección
			parametro = malloc(sizeof(int));
			*parametro = extraer_int_del_buffer(un_buffer);
			list_add(un_pcb->pedido_a_interfaz->datos_auxiliares_interfaz,parametro);
			// Registro tamaño
			parametro = malloc(sizeof(int));
			*parametro = extraer_int_del_buffer(un_buffer);
			list_add(un_pcb->pedido_a_interfaz->datos_auxiliares_interfaz,parametro);
			// Registro puntero archivo
			parametro = malloc(sizeof(int));
			*parametro = extraer_int_del_buffer(un_buffer);
			list_add(un_pcb->pedido_a_interfaz->datos_auxiliares_interfaz,parametro);

			break;

		default:
			log_error(kernel_logger,"No llegó ninguna instrucción a interfaz conocida");
			break;
	}
}