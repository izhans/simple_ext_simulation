#include "cabeceras.h"

int		ComprobarComando(char *strcomando, char *orden, char *argumento1, char *argumento2)
{
	char *token = strtok(strcomando, " \n");
	if (token == NULL)
	{
		printf("Comando desconocido\n");
		return (1);
	}
	strcpy(orden, token);

	if (strcmp(orden, "info") && strcmp(orden, "bytemaps") && strcmp(orden, "dir")
		&& strcmp(orden, "rename") && strcmp(orden, "imprimir") && strcmp(orden, "remove")
		&& strcmp(orden, "copy") && strcmp(orden, "salir")
	)
	{
		printf("Comando desconocido\n");
		return (1);
	}

	token = strtok(NULL, " \n");
	if (token == NULL)
		return (0);
	
	// ? añadir validaciones de que hay argumentos para los comandos que los requieren?
	strcpy(argumento1, token);

	token = strtok(NULL, " \n");
	if (token == NULL)
		return (0);
	strcpy(argumento2, token);

	return (0);
}
