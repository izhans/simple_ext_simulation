#ifndef CABECERAS_H
# define CABECERAS_H

#include <stdio.h>
#include <string.h>
#include <ctype.h>

#define SIZE_BLOQUE 512
#define MAX_INODOS 24
#define MAX_FICHEROS 20
#define MAX_BLOQUES_DATOS 96
#define PRIM_BLOQUE_DATOS 4
#define MAX_BLOQUES_PARTICION MAX_BLOQUES_DATOS + PRIM_BLOQUE_DATOS
	// superbloque + bytemap inodos y bytemap bloques + inodos + directorio
#define MAX_NUMS_BLOQUE_INODO 7
#define LEN_NFICH 17
#define NULL_INODO 0xFFFF
#define NULL_BLOQUE 0xFFFF

/* Estructura del superbloque */
typedef struct
{
	unsigned int s_inodes_count;									 /* inodos de la partición */
	unsigned int s_blocks_count;									 /* bloques de la partición */
	unsigned int s_free_blocks_count;								 /* bloques libres */
	unsigned int s_free_inodes_count;								 /* inodos libres */
	unsigned int s_first_data_block;								 /* primer bloque de datos */
	unsigned int s_block_size;										 /* tamaño del bloque en bytes */
	unsigned char s_relleno[SIZE_BLOQUE - 6 * sizeof(unsigned int)]; /* relleno a 0's*/
} EXT_SIMPLE_SUPERBLOCK;

/* Bytemaps, caben en un bloque */
typedef struct
{
	unsigned char bmap_bloques[MAX_BLOQUES_PARTICION];
	unsigned char bmap_inodos[MAX_INODOS]; /* inodos 0 y 1 reservados, inodo 2 directorio */
	unsigned char bmap_relleno[SIZE_BLOQUE - (MAX_BLOQUES_PARTICION + MAX_INODOS) * sizeof(char)];
} EXT_BYTE_MAPS;

/* inodo */
typedef struct
{
	unsigned int size_fichero;
	unsigned short int i_nbloque[MAX_NUMS_BLOQUE_INODO];
} EXT_SIMPLE_INODE;

/* Lista de inodos, caben en un bloque */
typedef struct
{
	EXT_SIMPLE_INODE blq_inodos[MAX_INODOS];
	unsigned char blq_relleno[SIZE_BLOQUE - MAX_INODOS * sizeof(EXT_SIMPLE_INODE)];
} EXT_BLQ_INODOS;

/* Entrada individual del directorio */
typedef struct
{
	char dir_nfich[LEN_NFICH];
	unsigned short int dir_inodo;
} EXT_ENTRADA_DIR;

/* Bloque de datos */
typedef struct
{
	unsigned char dato[SIZE_BLOQUE];
} EXT_DATOS;

/* ---------- Funciones ---------- */
void	Printbytemaps(EXT_BYTE_MAPS *ext_bytemaps);
int		ComprobarComando(char *strcomando, char *orden, char *argumento1, char *argumento2);
void	LeeSuperBloque(EXT_SIMPLE_SUPERBLOCK *psup);
int		BuscaFich(EXT_ENTRADA_DIR *directorio, char *nombre);
void	Directorio(EXT_ENTRADA_DIR *directorio, EXT_BLQ_INODOS *inodos);
int		Renombrar(EXT_ENTRADA_DIR *directorio, EXT_BLQ_INODOS *inodos,
			  char *nombreantiguo, char *nombrenuevo, FILE *fich);
int		Imprimir(EXT_ENTRADA_DIR *directorio, EXT_BLQ_INODOS *inodos,
			 EXT_DATOS *memdatos, char *nombre);
int		Borrar(EXT_ENTRADA_DIR *directorio, EXT_BLQ_INODOS *inodos,
		   EXT_BYTE_MAPS *ext_bytemaps, EXT_SIMPLE_SUPERBLOCK *ext_superblock,
		   char *nombre, FILE *fich);
int		Copiar(EXT_ENTRADA_DIR *directorio, EXT_BLQ_INODOS *inodos,
		   EXT_BYTE_MAPS *ext_bytemaps, EXT_SIMPLE_SUPERBLOCK *ext_superblock,
		   EXT_DATOS *memdatos, char *nombreorigen, char *nombredestino, FILE *fich);
void	Grabarinodosydirectorio(EXT_ENTRADA_DIR *directorio, EXT_BLQ_INODOS *inodos, FILE *fich);
void	GrabarByteMaps(EXT_BYTE_MAPS *ext_bytemaps, FILE *fich);
void	GrabarSuperBloque(EXT_SIMPLE_SUPERBLOCK *ext_superblock, FILE *fich);
void	GrabarDatos(EXT_DATOS *memdatos, FILE *fich);

#endif // CABECERAS_H
