#include "cabeceras.h"

/**
 * Las funciones de este fichero se encargan de escribir los datos en particion.bin.
 * Todas funcionan de la misma forma:
 * 1. Situan el cursor en la parte del fichero donde se encuentran los datos que van a sobreescribir
 * 2. Sobreescriben los datos haciendo un write de la estructura que los almacena 
 */

void	GrabarSuperBloque(EXT_SIMPLE_SUPERBLOCK *ext_superblock, FILE *fich)
{
	fseek(fich, 0, SEEK_SET);
	fwrite(ext_superblock, sizeof(EXT_SIMPLE_SUPERBLOCK), 1, fich);
}

void	GrabarByteMaps(EXT_BYTE_MAPS *ext_bytemaps, FILE *fich)
{
	fseek(fich, 1 * SIZE_BLOQUE, SEEK_SET);
	fwrite(ext_bytemaps, sizeof(EXT_BYTE_MAPS), 1, fich);
}

void	Grabarinodosydirectorio(EXT_ENTRADA_DIR *directorio, EXT_BLQ_INODOS *inodos, FILE *fich)
{
	// inodos
	fseek(fich, 2 * SIZE_BLOQUE, SEEK_SET);
	fwrite(inodos, sizeof(EXT_BLQ_INODOS), 1, fich);

	// dir
	fseek(fich, 3 * SIZE_BLOQUE, SEEK_SET);
	fwrite(directorio, sizeof(EXT_ENTRADA_DIR), MAX_FICHEROS, fich);
}

void	GrabarDatos(EXT_DATOS *memdatos, FILE *fich)
{
	fseek(fich, PRIM_BLOQUE_DATOS * SIZE_BLOQUE, SEEK_SET);
	fwrite(memdatos, sizeof(EXT_DATOS), MAX_BLOQUES_DATOS, fich);
}
