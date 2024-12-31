#include "cabeceras.h"

#define LONGITUD_COMANDO 100

/**
 * @brief comprueba si un comando existe y lo separa en orden y argumentos
 * @param strcomando el comando que se recibe del usuario
 * @param orden donde hay que copiar el mandato del comando
 * @param argumento1 donde hay que copiar el primer argumento del comando
 * @param argumento2 donde hay que copiar el segundo argumento del comando
 * @returns 0 si el comando es valido
 * 			1 si el comando no es valido
 */
int		ComprobarComando(char *strcomando, char *orden, char *argumento1, char *argumento2)
{
	// limpio los datos recogidos del comando anterior
	bzero(orden, LONGITUD_COMANDO);
	bzero(argumento1, LONGITUD_COMANDO);
	bzero(argumento2, LONGITUD_COMANDO);

	// recojo la orden
	char *token = strtok(strcomando, " \n");
	if (token == NULL)
	{
		printf("Comando desconocido\n");
		return (1);
	}
	strcpy(orden, token);

	// si no es ninguna de las ordenes conocidas, devuelve error
	if (strcmp(orden, "info") && strcmp(orden, "bytemaps") && strcmp(orden, "dir")
		&& strcmp(orden, "rename") && strcmp(orden, "imprimir") && strcmp(orden, "remove")
		&& strcmp(orden, "copy") && strcmp(orden, "salir")
	)
	{
		printf("Comando desconocido\n");
		return (1);
	}

	// si es un comando que no requiere argumentos se devuelve como valido y no se comprueban los argumentos
	if (strcmp(orden, "info") == 0 || strcmp(orden, "bytemaps") == 0
		|| strcmp(orden, "dir") == 0 || strcmp(orden, "salir") == 0)
		return (0);
	
	// recojo argumento1
	token = strtok(NULL, " \n");
	if (token == NULL)
	{
		printf("El comando %s requiere al menos un argumento\n", orden);
		return (1);
	}
	strcpy(argumento1, token);

	// si es un comando que solo requiere un argumento se devuelve como valido y no se comprueba el 2o argumento
	if (strcmp(orden, "imprimir") == 0 || strcmp(orden, "remove") == 0)
		return (0);

	// recojo argumento2
	token = strtok(NULL, " \n");
	if (token == NULL)
	{
		printf("El comando %s requiere 2 argumentos\n", orden);
		return (1);
	}
	strcpy(argumento2, token);

	return (0);
}
