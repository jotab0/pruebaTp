#include "../include/manejo_recursos.h"

///////// RECURSOS

void manejar_pedido_de_recurso(pcb *pcb_recibido){
	
	bool _buscar_recurso(instancia_recurso *un_recurso)
	{
		return strcmp(pcb_recibido->pedido_recurso, un_recurso->nombre_recurso) == 0;
	}

	instancia_recurso* un_recurso;

	pthread_mutex_lock(&mutex_lista_recursos);
	if(list_any_satisfy(lista_recursos,(void *)_buscar_recurso)){
		
		un_recurso = list_find(lista_recursos,(void *)_buscar_recurso);
		log_info(kernel_logger,"Proceso con PID: %d se encuentra esperando recurso: %s",pcb_recibido->pid,un_recurso->nombre_recurso);
		list_add(un_recurso->lista_procesos_en_cola,pcb_recibido);
		pthread_mutex_unlock(&mutex_lista_recursos);
		sem_post(&un_recurso->semaforo_request_recurso);

	}else{
		pthread_mutex_unlock(&mutex_lista_recursos);
		planificar_proceso_exit_en_hilo(pcb_recibido);
	}
}

void control_request_de_recursos(instancia_recurso* un_recurso){
	log_trace(kernel_logger,"MÓDULO - manejo_recursos: Recurso %s inicializado", un_recurso->nombre_recurso);
	while(1){
		
		// Se le envía signal solamente cuando algún proceso hace la request del recurso
		sem_wait(&un_recurso->semaforo_request_recurso);

		// Se le envía señal cada vez que se libera una instancia - Se inicializa según instancias iniciales disponibles
		sem_wait(&un_recurso->semaforo_recurso);

		pcb* un_pcb = NULL;

		pthread_mutex_lock(&un_recurso->mutex_lista_procesos_en_cola);
		un_pcb = list_remove(un_recurso->lista_procesos_en_cola,0);
		pthread_mutex_unlock(&un_recurso->mutex_lista_procesos_en_cola);

		if(_eliminar_pcb_de_lista_sync(un_pcb,blocked,&mutex_lista_blocked)){
			un_pcb->pedido_recurso = NULL;
			agregar_recurso_a_pcb(un_pcb,un_recurso->nombre_recurso);
			log_info(kernel_logger,"MÓDULO - manejo_recursos: Se entrego recurso %s inicializado a proceso con PID: %d", un_recurso->nombre_recurso, un_pcb->pid);
			agregar_a_ready(un_pcb);
			sem_post(&sem_pcp);
		}
	}
}

// CONSULTAR: Si están bien las siguientes funciones con listas
void agregar_recurso_a_pcb (pcb* un_pcb, char* un_recurso){

	bool _buscar_recurso(instancia_recurso_pcb* recurso_encontrado)
	{
		return strcmp(recurso_encontrado->nombre_recurso,un_recurso) == 0;
	}

	instancia_recurso_pcb* recurso = NULL;

	if(list_is_empty(un_pcb->recursos_en_uso)){

		recurso = malloc(sizeof(instancia_recurso_pcb));
		recurso->nombre_recurso = malloc(strlen(un_recurso)+1);
		strcpy(recurso->nombre_recurso,un_recurso);
		recurso->instancias_recurso = 1;
		list_add(un_pcb->recursos_en_uso,recurso);
	}
	else{
		
		if(list_any_satisfy(un_pcb->recursos_en_uso, (void *)_buscar_recurso))
		{
			recurso = list_find(un_pcb->recursos_en_uso, (void *)_buscar_recurso);
			recurso->instancias_recurso += 1;
		}
		else
		{
			recurso = malloc(sizeof(instancia_recurso_pcb));
			recurso->nombre_recurso = malloc(strlen(un_recurso)+1);
			strcpy(recurso->nombre_recurso,un_recurso);
			recurso->instancias_recurso = 1;
			list_add(un_pcb->recursos_en_uso,recurso);
			// CONSULTA: Debería hacer free del puntero recurso?
		}
	}

}

void manejar_signal_de_recurso(pcb *pcb_recibido){
	
	bool _buscar_recurso(instancia_recurso *un_recurso)
	{
		return strcmp(pcb_recibido->pedido_recurso, un_recurso->nombre_recurso) == 0;
	}

	instancia_recurso* un_recurso;

	pthread_mutex_lock(&mutex_lista_recursos);
	if(list_any_satisfy(lista_recursos,(void *)_buscar_recurso)){
		
		un_recurso = list_find(lista_recursos,(void *)_buscar_recurso);
		sem_post(&un_recurso->semaforo_recurso);

	}else{
		planificar_proceso_exit_en_hilo(pcb_recibido);
	}
	pthread_mutex_unlock(&mutex_lista_recursos);
	quitar_recurso(pcb_recibido, pcb_recibido->pedido_recurso);
}


void quitar_recurso (pcb* un_pcb, char* un_recurso){

	bool _buscar_recurso(instancia_recurso_pcb* recurso_encontrado)
	{
		return strcmp(recurso_encontrado->nombre_recurso,un_recurso)== 0;
	}

	instancia_recurso_pcb* recurso = NULL;

	if(list_any_satisfy(un_pcb->recursos_en_uso, (void *)_buscar_recurso))
	{
		recurso = list_find(un_pcb->recursos_en_uso, (void *)_buscar_recurso);
		
		if(recurso->instancias_recurso > 0){

			recurso->instancias_recurso -= 1;

		}
		else
		{
			list_remove_by_condition(un_pcb->recursos_en_uso,(void *)_buscar_recurso);
		}
	}
}

