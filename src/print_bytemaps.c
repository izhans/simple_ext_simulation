#include "cabeceras.h"

void	Printbytemaps(EXT_BYTE_MAPS *ext_bytemaps)
{
	size_t i;
	printf("Inodos: ");
	for (size_t i = 0; i < MAX_INODOS; i++)
		printf("%u ", ext_bytemaps->bmap_inodos[i]);
	printf("\n");

	printf("Bloques [0-25]:\t\t");
	for (i = 0; i < 25; i++)
		printf("%u ", ext_bytemaps->bmap_bloques[i]);
	printf("\n");
	printf("Bloques [25-50]:\t");
	for (; i < 50; i++)
		printf("%u ", ext_bytemaps->bmap_bloques[i]);
	printf("\n");
	printf("Bloques [50-75]:\t");
	for (; i < 75; i++)
		printf("%u ", ext_bytemaps->bmap_bloques[i]);
	printf("\n");
	printf("Bloques [75-100]:\t");
	for (; i < MAX_BLOQUES_PARTICION; i++)
		printf("%u ", ext_bytemaps->bmap_bloques[i]);
	printf("\n");
}
