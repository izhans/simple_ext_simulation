#include "cabeceras.h"

EXT_DATOS GetBloque(EXT_DATOS *memdatos, int i_nbloque);

/**
 * @brief imprime los contenidos de un fichero
 * @param directorio el directorio que contiene los ficheros
 * @param inodos el bloque/lista de inodos
 * @param memdatos los bloques con los datos de los ficheros
 * @param nombre el nombre del fichero que se quiere imprimir
 * @returns 0 si ha encontrado e impreso el fichero, 1 si no
 */
int	Imprimir(EXT_ENTRADA_DIR *directorio, EXT_BLQ_INODOS *inodos, EXT_DATOS *memdatos, char *nombre)
{
	int i;
	int inodo;
	EXT_SIMPLE_INODE fichero;
	EXT_DATOS bloque;

	i = 1; // empieza en 1 por que la entrada 0 es la del directorio (.)
	while (i < MAX_FICHEROS) // recorro las 20 entradas (posibles ficheros) del directorio
	{
		// si la entrada del directorio tiene un inodo significa que hay un fichero
		if (strcmp(nombre, directorio[i].dir_nfich) == 0)
		{
			inodo = directorio[i].dir_inodo;
			fichero = inodos->blq_inodos[inodo];
			
			// recorro la lista de bloques que contiene el inodo y voy imprimiendo su contenido
			for (size_t j = 0; fichero.i_nbloque[j] != NULL_BLOQUE; j++)
			{
				bloque = GetBloque(memdatos, fichero.i_nbloque[j]);
				printf("%s", bloque.dato);
			}
			printf("\n");
			return (0);
		}
		i++;
	}
	printf("ERROR: No se ha encontrado el fichero %s\n", nombre);
	return (1);
}

/**
 * @brief calcula el indice y devuelve el bloque de datos correspondiente al numero que se pide
 * @param memdatos los bloques de datos, que ,OJO, no es lo mismo que todos los datos de la particion
 * @param i_nbloque el numero de bloque que se quiere recuperar
 * @returns el bloque de datos correspondiente al numero que se pide
 * esta funcion existe para ayudar a la legibilidad de la funcion Imprimir
 * simplemente tiene en cuenta que en memdatos hay 96 bloques en vez de 100 y
 * 	resta 4 (donde empiezan los datos) para acceder al indice real
 */
EXT_DATOS GetBloque(EXT_DATOS *memdatos, int i_nbloque)
{
	return (memdatos[i_nbloque - PRIM_BLOQUE_DATOS]);
}
