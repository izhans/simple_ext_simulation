#include "cabeceras.h"

#define LONGITUD_COMANDO 100

int main()
{
	char comando[LONGITUD_COMANDO];
	char orden[LONGITUD_COMANDO];
	char argumento1[LONGITUD_COMANDO];
	char argumento2[LONGITUD_COMANDO];

	EXT_SIMPLE_SUPERBLOCK	ext_superblock;
	EXT_BYTE_MAPS			ext_bytemaps;
	EXT_BLQ_INODOS			ext_blq_inodos;
	EXT_ENTRADA_DIR			directorio[MAX_FICHEROS];
	EXT_DATOS				memdatos[MAX_BLOQUES_DATOS];
	EXT_DATOS				datosfich[MAX_BLOQUES_PARTICION];
	FILE *fent;
	
	// Lectura del fichero completo de una sola vez
	fent = fopen("particion.bin", "r+b");
	if (fent == NULL)
	{
		printf("Ha habido un problema abriendo el fichero\n");
		return (1);
	}
	int bloques_leidos = fread(&datosfich, SIZE_BLOQUE, MAX_BLOQUES_PARTICION, fent);
	if (bloques_leidos != MAX_BLOQUES_PARTICION)
	{
		printf("No se han podido leer correctamente todos los datos de la particion. Abortando programa.\n");
		return (1);
	}

	/**
	 * Volcado de datos del fichero a las estructuras del sistema de ficheros.
	 * El superbloque, los bytemaps y la lista de inodos ocupan un bloque cada uno,
	 * por lo que me parece mas limpio y legible poner el tamaño de su propia estructura
	 */
	memmove(&ext_superblock, &datosfich[0], sizeof(EXT_SIMPLE_SUPERBLOCK));
	memmove(&ext_bytemaps, &datosfich[1], sizeof(EXT_BYTE_MAPS));
	memmove(&ext_blq_inodos, &datosfich[2], sizeof(EXT_BLQ_INODOS));
	memmove(&directorio, &datosfich[3], MAX_FICHEROS * sizeof(EXT_ENTRADA_DIR));
	memmove(&memdatos, &datosfich[4], MAX_BLOQUES_DATOS * SIZE_BLOQUE);

	// Bucle de tratamiento de comandos
	for (;;)
	{
		do
		{
			printf(">> ");
			fflush(stdin);
			fgets(comando, LONGITUD_COMANDO, stdin);
		} while (ComprobarComando(comando, orden, argumento1, argumento2) != 0);

		if (strcmp(orden, "info") == 0)
		{
			LeeSuperBloque(&ext_superblock);
			continue;
		}
		if (strcmp(orden, "bytemaps") == 0)
		{
			Printbytemaps(&ext_bytemaps);
			continue;
		}
		if (strcmp(orden, "dir") == 0)
		{
			Directorio(directorio, &ext_blq_inodos);
			continue;
		}
		if (strcmp(orden, "imprimir") == 0)
		{
			Imprimir(directorio, &ext_blq_inodos, memdatos, argumento1);
			continue;
		}
		if (strcmp(orden, "rename") == 0)
		{
			Renombrar(directorio, &ext_blq_inodos, argumento1, argumento2, fent);
			continue;
		}
		if (strcmp(orden, "remove") == 0)
		{
			Borrar(directorio, &ext_blq_inodos, &ext_bytemaps, &ext_superblock, argumento1, fent);
			continue;
		}
		if (strcmp(orden, "copy") == 0)
		{
			Copiar(directorio, &ext_blq_inodos, &ext_bytemaps, &ext_superblock, memdatos, argumento1, argumento2, fent);
			continue;
		}
		if (strcmp(orden, "salir") == 0)
		{
			fclose(fent);
			return 0;
		}
	}
}
