#include "cabeceras.h"

int		BuscaFich(EXT_ENTRADA_DIR *directorio, EXT_BLQ_INODOS *inodos, char *nombre)
{
	(void) inodos;
	int i;

	i = 1; // empieza en 1 por que la entrada 0 es la del directorio (.)
	while (i < MAX_FICHEROS) // recorro las 20 entradas (posibles ficheros) del directorio
	{
		// busco el fichero por su nombre
		if (strcmp(nombre, directorio[i].dir_nfich) == 0)
			return (i);
		i++;
	}
	return (0);
}
