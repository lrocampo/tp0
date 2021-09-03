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

	logger = iniciar_logger();

	// Usando el logger creado previamente
	// Escribi: "Hola! Soy un log"
	log_info(logger, "Soy un log!");

	config = iniciar_config();

	ip = config_get_string_value(config, "IP");
	puerto = config_get_string_value(config, "Puerto");

	// Usando el config creado previamente
	// Lee las variables de IP, Puerto y Valor

	//Loggear valor de config

	leer_consola(logger);


	/*---------------------------------------------------PARTE 3-------------------------------------------------------------*/

	// Antes de continuar, tenemos que asegurarnos que el servidor esté corriendo porque lo necesitaremos para lo que sigue.

	// Creamos una conexión hacia el servidor
	conexion = crear_conexion(ip, puerto);

	//enviar CLAVE al servirdor

	paquete(conexion);

	terminar_programa(conexion, logger, config);
	/*---------------------------------------------------PARTE 5-------------------------------------------------------------*/
	// Proximamente
}

t_log* iniciar_logger(void)
{
	t_log* nuevo_logger;
	if((nuevo_logger = log_create("tp0.log","TP0",1, LOG_LEVEL_INFO)) == NULL) {
		printf("No pude crear el logger\n");
		exit(1);
	}
	return nuevo_logger;
}

t_config* iniciar_config(void)
{
	t_config* nuevo_config;
	if((nuevo_config = config_create("./tp0.config")) == NULL) {
		printf("No pude leer la config\n");
		exit(2);
	}

	return nuevo_config;
}

void leer_consola(t_log* logger)
{
	char* leido;
	char* vacio;

	//El primero te lo dejo de yapa
	leido = readline(">");

	// Acá la idea es que imprimas por el log lo que recibis de la consola.
	while(strcmp(leido, "") != 0) {
		log_info(logger,"Console: %s\n", leido);
		leido = readline(">");
	}

	free(leido);
}

void paquete(int conexion)
{
	//Ahora toca lo divertido!
	char* leido;
	t_paquete* paquete = crear_paquete();
	enviar_mensaje(leido, conexion);
	agregar_a_paquete(paquete, leido, strlen(leido)+1);
	enviar_paquete(paquete, conexion);
}

void terminar_programa(int conexion, t_log* logger, t_config* config)
{
	if (logger != NULL) {
		log_destroy(logger);
	}

	if (config != NULL) {
		config_destroy(config);
	}
	
	
	liberar_conexion(conexion);
}
