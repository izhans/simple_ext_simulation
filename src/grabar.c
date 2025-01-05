#include "cabeceras.h"

void	GrabarSuperBloque(EXT_SIMPLE_SUPERBLOCK *ext_superblock, FILE *fich)
{
	printf("Grabar superbloque\n");
	fseek(fich, 0, SEEK_SET);
	fwrite(ext_superblock, sizeof(EXT_SIMPLE_SUPERBLOCK), 1, fich);
}

void	GrabarByteMaps(EXT_BYTE_MAPS *ext_bytemaps, FILE *fich)
{
	printf("Grabar bytemaps\n");
	fseek(fich, 1 * SIZE_BLOQUE, SEEK_SET);
	fwrite(ext_bytemaps, sizeof(EXT_BYTE_MAPS), 1, fich);
}

void	Grabarinodosydirectorio(EXT_ENTRADA_DIR *directorio, EXT_BLQ_INODOS *inodos, FILE *fich)
{
	printf("Grabar inodos y dir\n");
	// inodos
	fseek(fich, 2 * SIZE_BLOQUE, SEEK_SET);
	fwrite(inodos, sizeof(EXT_BLQ_INODOS), 1, fich);

	// dir
	fseek(fich, 3 * SIZE_BLOQUE, SEEK_SET);
	fwrite(directorio, sizeof(EXT_ENTRADA_DIR), MAX_FICHEROS, fich);
}

void	GrabarDatos(EXT_DATOS *memdatos, FILE *fich)
{
	printf("Grabar datos\n");
	fseek(fich, PRIM_BLOQUE_DATOS * SIZE_BLOQUE, SEEK_SET);
	fwrite(memdatos, sizeof(EXT_DATOS), MAX_BLOQUES_DATOS, fich);
}
