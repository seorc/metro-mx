***********************
 Autor: Daniel Abraján
 DT: 20110730_0443
***********************

Implementación del grafo
========================

Se utilizaron estructuras para representar los puntos (*station*) y los
vértices (*link*). Cada estructura *station* tiene una lista de tipo puntero a
*link* de todas las otras estaciones con las que tiene conexión. Por
simplicidad, el *link* no es una estructura bidireccional, y es por ello que
cada estación debe definir su propio conjunto de links para describir sus
conexiones. Se dearrolló un conjunto de funciones que se encargan de vincular
dos estaciones y de definir la longitud de los dos links, que es la misma.

Para evitar problemas con la duplicidad de datos, se construyó, con ayudad de
calloc(), un cuerpo de punteros a punteros de estaciones y líneas que mantienen
dicha información: todas las estructuras *station* son referenciadas desde un
solo array de punteros y se les asigna un id que es determinado por la posición
de cada *station* dentro del array. Las líneas se definen como arrays de ids,
que son utilizados por las funciones correspondientes para generar las
estructuras *line* y alojar dentro de ellas arrays dinámicos de punteros a
*station* que señalan a las estaciones que son parte de la *line*. Así, todas
las estructuras tipo *station* son creadas sólo una vez, y solamente se crean
punteros para referenciarlas en cada lugar donde se necesita.

Dado que no se encontró un listado o mapa de las distancias estación a estación
de la red del metro, se utilizó el tamaño global de cada línea, dividido entre
su número de estaciones, para definir dichas distancias, por lo que las
búsquedas son aproximadas.  

Instrucciones de compilación y ejecución
========================================

Se generó un Makefile para la compilación automatizada del programa. La
estructura del directorio es la siguiente:

  metro
   |
   |__include
   |   |
   |   |__[ todos los archivos fuente ]
   |
   |
   |__src
   |   |
   |   |__[ todos los archivos de cabecera ]
   |   |
   |   |__obj
   |       |
   |       |__[ todos los archivos objeto ]
   |
   |
   |__Makefile
   |
   |__README.txt
  
 En Linux, la compilación se realiza accesando al directorio raíz (metro) y
 ejecutando la instrucción "make". Esto genera el ejecutable en la misma raíz.
 Si se edita cualquiera de los archivos, basta con volver a ejecutar "make"
 para recompliar lo que sea necesario.
