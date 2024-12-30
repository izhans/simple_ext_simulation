#include "cabeceras.h"

/**
 * @brief borra un fichero
 * @param directorio el directorio en el que esta la entrada del fichero
 * @param inodos la lista de inodos
 * @param ext_bytemaps estructura con los bytemaps de inodos y bloques
 * @param ext_superblock superbloque
 * @param nombre nombre del fichero a borrar
 * @param fich fichero abierto de particion.bin
 * @returns 1 si ha habido algun error, 0 si se ha borrado correctamente
 * - no es necesario borrar el contenido fisico de los bloques (con el bytemap ya sabemos que estan libres)
 * - hay que actualizar los datos de bloques e inodos libres del superbloque
 * cosas que la funcion hace para borrar un fichero
 * - actualizar bytemaps y superbloque
 * | - se marcan como libres (0) el inodo y los bloques que usase el fichero
 * | - se suma 1 inodo libre al superbloque
 * | - se suma el numero de bloques que usase el fichero a los libres del superbloque
 * - liberar el inodo
 * | - se cambia su tamaño a 0
 * | - los 7 punteros a bloque se marcan con 0xFFFF (NULL_BLOQUE)
 * - borrar la entrada del directorio
 * | - cambiar el nombre del fichero a "" (string vacio)
 * | - poner el inodo a 0xFFFF (NULL_INODO)
 */
int	Borrar(EXT_ENTRADA_DIR *directorio, EXT_BLQ_INODOS *inodos,
	EXT_BYTE_MAPS *ext_bytemaps, EXT_SIMPLE_SUPERBLOCK *ext_superblock,
	char *nombre, FILE *fich)
{
	int entrada_fichero = BuscaFich(directorio, inodos, nombre);
	if (!entrada_fichero)
	{
		printf("ERROR: El fichero %s no existe\n", nombre);
		return (1);
	}

	int num_inodo;
	EXT_SIMPLE_INODE *inodo;
	unsigned short num_bloque;

	num_inodo = directorio[entrada_fichero].dir_inodo;
	inodo = &inodos->blq_inodos[num_inodo];

	// actualizar bytemaps y superbloque
	// 	- inodos
	ext_bytemaps->bmap_inodos[num_inodo] = 0;
	ext_superblock->s_free_inodes_count++;
	//  - bloques
	for (int i = 0; i < MAX_NUMS_BLOQUE_INODO; i++)
	{
		num_bloque = (*inodo).i_nbloque[i];
		if (num_bloque != NULL_BLOQUE)
		{
			ext_bytemaps->bmap_bloques[num_bloque] = 0;
			ext_superblock->s_free_blocks_count++;
		}
	}

	// liberar el inodo
	//  - tamaño del fichero = 0
	(*inodo).size_fichero = 0;
	//  - punteros a bloque = 0xFFFF
	for (int i = 0; i < MAX_NUMS_BLOQUE_INODO; i++)
		(*inodo).i_nbloque[i] = NULL_BLOQUE;

	// borrar la entrada del directorio
	//  - nombre del fichero = ""
	strncpy(directorio[entrada_fichero].dir_nfich, "", LEN_NFICH);
	//  - inodo = 0xFFFF
	directorio[entrada_fichero].dir_inodo = NULL_INODO;

	return (0);
}
