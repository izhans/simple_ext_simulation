#include "cabeceras.h"

int ErroresIniciales(EXT_ENTRADA_DIR *directorio, char *nombreorigen, char *nombredestino, int entrada_fichero);
int BuscaInodoLibre(EXT_BYTE_MAPS *ext_bytemaps);
int BuscaBloqueLibre(EXT_BYTE_MAPS *ext_bytemaps);
int	BuscaEntradaDirLibre(EXT_ENTRADA_DIR *directorio);

/**
 * @brief copia los datos de un fichero existente a otro. No puede repetir nombre
 * @param directorio el directorio con los ficheros
 * @param inodos la lista de inodos
 * @param ext_bytemaps los bytemaps de inodos y bloques
 * @param ext_superblock el superbloque
 * @param memdatos los bloques de datos
 * @param nombreorigen nombre con el que ubicar el fichero
 * @param nombredestino nombre que se va a asignar al nuevo fichero
 * @param fich particion.bin
 * @param returns 1 si ha habido un error o 0 si se ha hecho el cambio
 */
int	Copiar(EXT_ENTRADA_DIR *directorio, EXT_BLQ_INODOS *inodos,
	EXT_BYTE_MAPS *ext_bytemaps, EXT_SIMPLE_SUPERBLOCK *ext_superblock,
	EXT_DATOS *memdatos, char *nombreorigen, char *nombredestino, FILE *fich)
{
	// tratamiento de errores iniciales
	int entrada_fichero = BuscaFich(directorio, nombreorigen);
	if (ErroresIniciales(directorio, nombreorigen, nombredestino, entrada_fichero))
		return (1);

	// buscar inodo libre
	int index_inodo_copia = BuscaInodoLibre(ext_bytemaps);
	if (index_inodo_copia == -1)
	{
		printf("ERROR: No hay inodos disponibles para crear el fichero %s\n", nombredestino);
		return (1);
	}
	// buscar entrada de directorio libre
	int entrada_copia = BuscaEntradaDirLibre(directorio);
	if (entrada_copia == -1)
	{
		printf("ERROR: Se ha alcanzado el número máximo de ficheros y no se puede crear %s\n", nombredestino);
		return (1);
	}
	
	int index_inodo_original = directorio[entrada_fichero].dir_inodo;
	EXT_SIMPLE_INODE *inodo_copia = &inodos->blq_inodos[index_inodo_copia];
	EXT_SIMPLE_INODE *inodo_original = &inodos->blq_inodos[index_inodo_original];
	
	// copiar tamaño del fichero
	(*inodo_copia).size_fichero = (*inodo_original).size_fichero;
	// marcar inodo ocupado en el bytemap
	ext_bytemaps->bmap_inodos[index_inodo_copia] = 1;
	// restar inodo libre en el superbloque
	ext_superblock->s_free_inodes_count--;

	// copiar bloques
	int bloque_libre;
	int num_bloque_libre;
	for (int i = 0; (*inodo_original).i_nbloque[i] != NULL_BLOQUE; i++)
	{
		bloque_libre = BuscaBloqueLibre(ext_bytemaps);
		if (bloque_libre == -1)
		{
			printf("ERROR: Se ha alcanzado el número máximo de bloques de datos y no se puede seguir copiando\n");
			break;
		}
		num_bloque_libre = bloque_libre + PRIM_BLOQUE_DATOS;
		(*inodo_copia).i_nbloque[i] = num_bloque_libre;
		memmove(&memdatos[bloque_libre], &memdatos[(*inodo_original).i_nbloque[i] - PRIM_BLOQUE_DATOS], SIZE_BLOQUE);
		// marcar como ocupado en el bytemap de bloques
		ext_bytemaps->bmap_bloques[num_bloque_libre] = 1;
		// restar bloque libre en el superbloque
		ext_superblock->s_free_blocks_count--;
	}
	
	// crear entrada en el directorio
	directorio[entrada_copia].dir_inodo = index_inodo_copia;
	strncpy(directorio[entrada_copia].dir_nfich, nombredestino, LEN_NFICH);

	// grabar datos
	GrabarDatos(memdatos, fich);
	Grabarinodosydirectorio(directorio, inodos, fich);
	GrabarByteMaps(ext_bytemaps, fich);
	GrabarSuperBloque(ext_superblock, fich);

	return (0);
}

/**
 * @brief checkea si hay errores iniciales
 */
int ErroresIniciales(EXT_ENTRADA_DIR *directorio, char *nombreorigen, 
	char *nombredestino, int entrada_fichero)
{
	if (!entrada_fichero)
	{
		printf("ERROR: El fichero %s no existe\n", nombreorigen);
		return (1);
	}
	if (BuscaFich(directorio, nombredestino))
	{
		printf("ERROR: El fichero %s ya existe\n", nombredestino);
		return (1);
	}
	if (strlen(nombredestino) > LEN_NFICH -1)
	{
		printf("ERROR: El nombre nuevo para el fichero (%s) es demasiado largo. Max %d caracteres.\n", nombredestino, LEN_NFICH);
		return (1);
	}
	return (0);
}

/**
 * @brief busca el primer inodo libre en el bytemap
 */
int BuscaInodoLibre(EXT_BYTE_MAPS *ext_bytemaps)
{
	for (size_t i = 0; i < MAX_INODOS; i++)
	{
		if (ext_bytemaps->bmap_inodos[i] == 0)
			return (i);
	}
	return (-1);
}

/**
 * @brief busca el primer bloque de datos libre en el bytemap
 */
int BuscaBloqueLibre(EXT_BYTE_MAPS *ext_bytemaps)
{
	for (size_t i = PRIM_BLOQUE_DATOS; i < MAX_BLOQUES_PARTICION; i++)
	{
		if (ext_bytemaps->bmap_bloques[i] == 0)
			return (i - PRIM_BLOQUE_DATOS);
	}
	return (-1);
}

/**
 * @brief busca la primera entrada libre del directorio
 */
int	BuscaEntradaDirLibre(EXT_ENTRADA_DIR *directorio)
{
	int i;

	i = 1;
	while (i < MAX_FICHEROS)
	{
		if (directorio[i].dir_inodo == NULL_INODO)
			return (i);
		i++;
	}
	return (-1);
}
