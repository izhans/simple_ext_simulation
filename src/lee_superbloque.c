#include "cabeceras.h"

void	LeeSuperBloque(EXT_SIMPLE_SUPERBLOCK *psup)
{
	printf("Bloque %u bytes\n", psup->s_block_size);
	printf("Inodos particion = %u\n", psup->s_inodes_count);
	printf("Inodos libres = %u\n", psup->s_free_inodes_count);
	printf("Bloques particion = %u\n", psup->s_blocks_count);
	printf("Bloques libres = %u\n", psup->s_free_blocks_count);
	printf("Primer bloque de datos = %u\n", psup->s_first_data_block);
}
