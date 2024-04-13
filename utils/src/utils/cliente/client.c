#include "client.h"

int main(void)
{
	/*---------------------------------------------------PARTE 2-------------------------------------------------------------*/

	int conexion;
	char* ip;
	char* puerto;
	char* valor;

	t_log* logger;
	t_config* config;

	/* ---------------- LOGGING ---------------- */

	logger = log_create("tp0.log", "Primer Log", true, LOG_LEVEL_INFO);

	// Usando el logger creado previamente
	// Escribi: "Hola! Soy un log"

	log_info(logger, "Soy un Log"); //Como logger está configurado para loggear como mínimo hasta info por "LOG_LEVEL_INFO"
									//aparece el mensaje en el archivo "tp0.log" cuando llamo a la función log_info()
	log_destroy(logger); 			//Lo destruyo porque no deja de ser una especie de puntero

	/* ---------------- ARCHIVOS DE CONFIGURACION ---------------- */

	config = config_create("cliente.config");

	if (config == NULL) {
		exit(-4);
	}

	// Usando el config creado previamente, leemos los valores del config y los 
	// dejamos en las variables 'ip', 'puerto' y 'valor'

	valor = config_get_string_value(config, "CLAVE");
	ip = config_get_string_value(config, "IP");
	puerto = config_get_string_value(config, "PUERTO");

	// Loggeamos el valor de config
	
	logger = log_create("tp0.log", "Adress log", true, LOG_LEVEL_INFO);
	
	log_info(logger, valor);
	log_destroy(logger); 

	// config_destroy(config); Esto quita los valores asignados a los punteros (ip,valor,puerto)

	/* ---------------- LEER DE CONSOLA ---------------- */
	
	logger = log_create("tp0.log", "Leer consola", true, LOG_LEVEL_INFO);
	leer_consola(logger);

	/*---------------------------------------------------PARTE 3-------------------------------------------------------------*/
	
	
	printf("Chequeo de ip: %s \n",ip);
	printf("Chequeo de puerto: %s \n",puerto);
	
	// ADVERTENCIA: Antes de continuar, tenemos que asegurarnos que el servidor esté corriendo para poder conectarnos a él
	
	// Creamos una conexión hacia el servidor

	conexion = crear_conexion(ip,puerto); //Conecta el cliente con el servidor directamente con IP y Puerto

	// Enviamos al servidor el valor de CLAVE como mensaje
	enviar_mensaje(valor, conexion); // Utiliza numero de socket para mandar mensaje al servidor

	// Armamos y enviamos el paquete
	paquete(conexion);

	terminar_programa(conexion, logger, config); //Con esto no hace falta destruir config

	/*---------------------------------------------------PARTE 5-------------------------------------------------------------*/
	// Proximamente
}

t_log* iniciar_logger(void)
{
	t_log* nuevo_logger;

	return nuevo_logger;
}

t_config* iniciar_config(void)
{
	t_config* nuevo_config;

	return nuevo_config;
}

void leer_consola(t_log* logger) //OK
{
	char* leido;

	// La primera te la dejo de yapa
	leido = readline("> ");

	if(strcmp(leido,"")== 0){
		log_destroy(logger);
		exit(-1);
	}

	// El resto, las vamos leyendo y logueando hasta recibir un string vacío
	while(strcmp(leido,"")!= 0){
		log_info(logger,leido);
		free (leido);
		leido = readline("> ");
	}
	// ¡No te olvides de liberar las lineas antes de regresar!
	free(leido);
}

void paquete(int conexion) //Envía paquete
{
	// Ahora toca lo divertido!
	char* leido;
	t_paquete* paquete;

	// Leemos y esta vez agregamos las lineas al paquete

	leido = readline("> ");

	if (strcmp(leido,"")==0)
	{
		printf("No se ingresaron datos al paquete");
		return;
	}
	
	paquete = crear_paquete();

	while (strcmp(leido,"")!=0)
	{
		agregar_a_paquete(paquete,leido,strlen(leido)+1);
		free(leido);
		leido = readline("> ");
	}

	// ¡No te olvides de liberar las líneas y el paquete antes de regresar!
	enviar_paquete(paquete,conexion);

	free(leido);
	eliminar_paquete(paquete);

	return;
}

void terminar_programa(int conexion, t_log* logger, t_config* config)
{
/* Y por ultimo, hay que liberar lo que utilizamos (conexion, log y config) 
con las funciones de las commons y del TP mencionadas en el enunciado */
	
	log_destroy(logger);
	config_destroy(config);
	liberar_conexion(conexion);
	
	return;
}

