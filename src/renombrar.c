#include "cabeceras.h"

/**
 * @brief cambia el nombre a un fichero existente. No puede repetir nombre
 * @param directorio el directorio con los ficheros
 * @param inodos la lista de inodos
 * @param nombreantiguo nombre con el que ubicar el fichero
 * @param nombrenuevo nombre que se va a asignar al fichero
 * @param returns 1 si ha habido un error o 0 si se ha hecho el cambio
 */
int	Renombrar(EXT_ENTRADA_DIR *directorio, EXT_BLQ_INODOS *inodos,
	char *nombreantiguo, char *nombrenuevo, FILE *fich)
{
	int entrada_fichero = BuscaFich(directorio, nombreantiguo);
	if (!entrada_fichero)
	{
		printf("ERROR: El fichero %s no existe\n", nombreantiguo);
		return (1);
	}
	if (BuscaFich(directorio, nombrenuevo))
	{
		printf("ERROR: El fichero %s ya existe\n", nombrenuevo);
		return (1);
	}
	if (strlen(nombrenuevo) > LEN_NFICH -1)
	{
		printf("ERROR: El nombre nuevo para el fichero (%s) es demasiado largo. Max %d caracteres.\n", nombrenuevo, LEN_NFICH);
		return (1);
	}
	
	strncpy(directorio[entrada_fichero].dir_nfich, nombrenuevo, LEN_NFICH);
	Grabarinodosydirectorio(directorio, inodos, fich);
	
	return (0);
}
