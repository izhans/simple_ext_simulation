#include "cabeceras.h"

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
	char *token = strtok(strcomando, " \n");
	if (token == NULL)
	{
		printf("Comando desconocido\n");
		return (1);
	}
	strcpy(orden, token);

	// si no es ninguno de los comandos conocidos, devuelve error
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
	
	token = strtok(NULL, " \n");
	if (token == NULL)
	{
		printf("El comando %s requiere argumentos\n", orden);
		return (1);
	}
	strcpy(argumento1, token);

	// TODO pendiente validacion del 2o argumento
	token = strtok(NULL, " \n");
	if (token == NULL)
		return (0);
	strcpy(argumento2, token);

	return (0);
}
