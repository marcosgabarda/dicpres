# Compresor Dicpres #


---


Programa que implementa distintos métodos de compresión, el LZ-77, LZ-78 y LZW.


---


## Notas de la implementación ##

**LZ78**

Se ha implementado un control del número mínimo de bits necesarios para codificar el entero en cada tupla de la codificación.

**LZW**

Los índices de la codificación están formados por un primer byte que indica el numero de bytes siguientes que contienen el número del índice del diccionario.

## Modo de empleo ##

Modo de empleo del programa principal:

$dicpres (modo) [opciones ](.md) fichero-entrada [fichero-salida]

Opciones:

--help : Muestra este texto de ayuda.

-v     : Activa el modo verbose, sacando por pantalla información de depuración.

Modo:

-c     : Comprime.

-e     : Descomprime.


Métodos:

-lz78  : Comprime con el método del LZ78 (Por defecto).

-lzw   : Comprime con el método del LZW.