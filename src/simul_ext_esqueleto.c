#include "cabeceras.h"

#define LONGITUD_COMANDO 100

int main()
{
	char comando[LONGITUD_COMANDO];
	char orden[LONGITUD_COMANDO];
	char argumento1[LONGITUD_COMANDO];
	char argumento2[LONGITUD_COMANDO];

	int i, j;
	unsigned long int m;
	EXT_SIMPLE_SUPERBLOCK	ext_superblock;
	EXT_BYTE_MAPS			ext_bytemaps;
	EXT_BLQ_INODOS			ext_blq_inodos;
	EXT_ENTRADA_DIR			directorio[MAX_FICHEROS];
	EXT_DATOS				memdatos[MAX_BLOQUES_DATOS];
	EXT_DATOS				datosfich[MAX_BLOQUES_PARTICION];
	int entradadir;
	int grabardatos;
	FILE *fent;
	
	// Lectura del fichero completo de una sola vez
	fent = fopen("particion.bin", "r+b");
	if (fent == NULL)
	{
		printf("Ha habido un problema abriendo el fichero\n");
		return (1);
	}
	fread(&datosfich, SIZE_BLOQUE, MAX_BLOQUES_PARTICION, fent);

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
		printf("tokens comando en main <%s> <%s> <%s>\n", orden, argumento1, argumento2);
		printf("tokens comando en main <%p> <%p> <%p>\n", orden, argumento1, argumento2);
		if (strcmp(orden, "info") == 0)
		{
			LeeSuperBloque(&ext_superblock);
			continue;
		}
		if (strcmp(orden, "dir") == 0)
		{
			Directorio(directorio, &ext_blq_inodos);
			continue;
		}
		// TODO...
		// Escritura de metadatos en comandos rename, remove, copy
		Grabarinodosydirectorio(directorio, &ext_blq_inodos, fent);
		GrabarByteMaps(&ext_bytemaps, fent);
		GrabarSuperBloque(&ext_superblock, fent);
		if (grabardatos)
			GrabarDatos(memdatos, fent);
		grabardatos = 0;
		// Si el comando es salir se habrán escrito todos los metadatos
		// faltan los datos y cerrar
		if (strcmp(orden, "salir") == 0)
		{
			GrabarDatos(memdatos, fent);
			fclose(fent);
			return 0;
		}
	}
}
