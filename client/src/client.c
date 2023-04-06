#include "client.h"
#include <string.h>
#include <stdlib.h>
#include <stdio.h>
#include <unistd.h>

#ifndef MAX
#define MAX 100
#endif

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

	logger = iniciar_logger();

	logger = log_create("tp0.log", "logs", true, LOG_LEVEL_INFO);
	log_info(logger, "Hola! Soy un log");


	/* ---------------- ARCHIVOS DE CONFIGURACION ---------------- */

	config = iniciar_config();
    char *current_dir = getcwd(NULL, 0);

    char buffer[MAX];
    memccpy(memccpy(buffer, current_dir, '\0', MAX) - 1, "/cliente.config", '\0', MAX);

	config = config_create(buffer);
	if (config != NULL) {
		if(config_has_property(config, "CLAVE"))
		{
			valor = config_get_string_value(config, "CLAVE");
			log_info(logger, valor);
		}
		if(config_has_property(config, "IP"))
		{
			ip = config_get_string_value(config, "IP");
			log_info(logger, ip);
		}
		if(config_has_property(config, "PUERTO"))
		{
			puerto = config_get_string_value(config, "PUERTO");
			log_info(logger, puerto);
		}
	}

	/* ---------------- LEER DE CONSOLA ---------------- */

	// leer_consola(logger);

	/*---------------------------------------------------PARTE 3-------------------------------------------------------------*/

	// ADVERTENCIA: Antes de continuar, tenemos que asegurarnos que el servidor esté corriendo para poder conectarnos a él

	conexion = crear_conexion(ip, puerto);
	enviar_mensaje(valor, conexion);
	//char *mensaje = recibir_mensaje(conexion);
	//log_info(logger, mensaje);
	// Armamos y enviamos el paquete
	paquete(conexion);

	terminar_programa(conexion, logger, config);

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

void leer_consola(t_log* logger)
{
	char* leido;

	while (1) {
		 leido = readline(">");

	        if (!strcmp(leido, "")) {
	            break;
	        }
	        log_info(logger, leido);
	        free(leido);
	} ;
}

void paquete(int conexion)
{
	char* leido;
	t_paquete* paquete;
	paquete = crear_paquete();
	printf(" ANTES WHILE :%s\n", leido);
	while (1) {
		 leido = readline(">");
			printf(" ANTES if  :%s\n", leido);
	        if (!strcmp(leido, "")) {
	            break;
	        }
	    	printf("Desp if :%s\n", leido);
	        agregar_a_paquete(paquete, leido, strlen(leido));
	    	printf(" DESP DE AGREGAR :%s\n", leido);
	        free(leido);
	} ;
	printf(" Voy a enviar el paquete :%s\n", paquete);
	enviar_paquete(paquete, conexion);
	eliminar_paquete(paquete);
	free(paquete);

}

void terminar_programa(int conexion, t_log* logger, t_config* config)
{
	if(logger != NULL ){
		log_destroy(logger);
		free(logger);
	}
	if(config != NULL ){
		config_destroy(config);
		free(config);
	}
	liberar_conexion(conexion);
	free(conexion);

}
