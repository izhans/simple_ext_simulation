#include "cabeceras.h"

void	Directorio(EXT_ENTRADA_DIR *directorio, EXT_BLQ_INODOS *inodos)
{
	int i;
	int inodo;
	EXT_SIMPLE_INODE datos_inodo;

	i = 1; // empieza en 1 por que la entrada 0 es la del directorio (.)
	while (i < MAX_FICHEROS) // recorro las 20 entradas (posibles ficheros) del directorio
	{
		// si la entrada del directorio tiene un inodo significa que hay un fichero
		if (directorio[i].dir_inodo != NULL_INODO)
		{
			inodo = directorio[i].dir_inodo;
			datos_inodo = inodos->blq_inodos[inodo];

			printf("%s\t", directorio[i].dir_nfich);
			printf("tamaño: %u\t", datos_inodo.size_fichero);
			printf("inodo: %u\t", inodo);
			
			// dentro de los datos del inodo veo a que bloques apunta su lista de bloques
			printf("bloques:");
			for (size_t j = 0; datos_inodo.i_nbloque[j] != NULL_BLOQUE; j++)
				printf(" %u", datos_inodo.i_nbloque[j]);
			printf("\n");
		}
		i++;
	}
	
}
