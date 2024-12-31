# simple_ext_simulation by Izhan Sastre
Este proyecto es una práctica para la asignatura de Sistemas Operativos.

Consiste en desarrollar un simulador de un sistema de ficheros tipo Linux ext muy simplificado.

Aquí se encuentra el [enunciado completo](subject/INSD_SSOO_U5_Actividad_Práctica%202024%20v1.pdf).

## Estado de la entrega
| Comando o funcionalidad | Puntuación | Estado |
|-|-|-|
| Arranque del programa, lectura de particion.bin e inicialización de variables con control de errores.<br>Bucle de petición y lectura de comandos| 1 punto | ✅ |
| Salir y mensaje de error si no existe el comando | 0.5 puntos | 🏗️ : falta guardar datos al salir |
| Info | 0.5 puntos | ✅ |
| Bytemaps | 0.5 puntos | ✅ |
| Dir | 0.5 puntos | ✅ |
| Rename | 0.5 puntos | 🏗️ : falta guardar datos |
| Remove | 1 punto para ficheros de 1 bloque<br>1.5 puntos para ficheros multibloque | 🏗️ : falta guardar datos |
| Imprimir | 1 punto para ficheros de 1 bloque<br>1.5 puntos para ficheros multibloque | ✅ con multibloque |
| Copiar | 1 punto para ficheros de 1 bloque<br>2.5 puntos para ficheros multibloque |-|
| Commits y código documentado y estructurado.<br>El video forma parte de la documentación. | 1 punto |-|

---

## Dificultades o problemas encontrados durante el desarrollo:
- Arranque, lectura e inicialización de variables:
	
	Con el main original, la lista de entradas de directorio no se estaba inicializando bien por el tamaño que se le pedía a memcpy que copiase.
	
	Tuve que ajustar el tamaño para que fuese el mismo y decidí cambiar memcpy por memmove para evitar posibles solapamientos de memoria a la hora de copiar datos.

	También decidí cambiar el sizeof(SIZE_BLOQUE) por el sizeof de la estructura que correspondiese (a pesar de que el tamaño sea el mismo) porque me parece más limpio, legible y escalable.

- Control de argumentos:

	Me dí cuenta de que si al escribir un comando no mandaba un argumento "nuevo", en los comandos que hacían uso de argumentos (rename, copy, imprimir o remove) utilizaban el valor del argumento que se había asignado en el último comando en el que se hubiese completado.

	Para solucionarlo, añadí un limpiado con bzero de las variables que conforman el comando y además un control para que comandos que necesitasen argumentos no pudiesen ejecutarse si no venían acompañados de ellos.

- Comando imprimir:

	Al probar lo que había desarrollado, vi que el contenido imprimido no se correspondia con lo que realmente debía imprimir. Me di cuenta de esto a base de hacer un hexdump del fichero binario y de más tarde imprimir todos los bloques de la partición.

	El problema fue tan simple como que se me había olvidado tener en cuenta que los bloques de datos eran 96, no 100 que corresponde a los bloques de toda la partición (incluyendo superbloque, bytemaps, lista de inodos y directorio).

	Lo solucioné haciendo una "traducción" del índice del bloque al que intentaba acceder restandole 4 (que corresponde al número de bloques que no son de datos).
