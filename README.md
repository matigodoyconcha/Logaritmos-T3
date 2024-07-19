## Tarea 3 CC4102
### Optimización en la Búsqueda de Cadenas de Texto usando un Filtro de Bloom
Integrantes:
- Matías Godoy C.
- Claudio Morel M.
- Damián González G.

### Descripción General

Esta tarea tiene como objetivo analizar las mejoras en los tiempos reales de búsqueda de texto al implementar un filtro de Bloom. Para ello, se dispuso de dos archivos distintos: uno con nombres de personas para entrenar el filtro, y un segundo archivo, disjunto del primero, con nombres populares de películas. Este segundo archivo se utilizó para evaluar cómo varían los tiempos de ejecución cuando se utiliza un filtro de Bloom al buscar determinadas palabras en el primer archivo.

### Instrucciones para Ejecutar el Código

#### Compilación

Usando un compilador de C++ como g++, se necesita compilar los archivos necesarios. Para esto, se puede ejecutar el siguiente conjunto de comandos en el terminal:

```sh
g++ -c Hash.cpp -o Hash.o
g++ -c bloom_filter.cpp -o bloom_filter.o
g++ -c Testing.cpp -o Testing.o
g++ -c main.cpp -o main.o
g++ Hash.o bloom_filter.o Testing.o main.o -o bloom_filter_program
```

#### Ejecución

Para ejecutar el archivo compilado, utilice el siguiente comando en el terminal:

```sh
./bloom_filter_program
```



### Resultados

Este programa, al ejecutarse, llevará a cabo las pruebas y guardará los resultados en un archivo llamado Resultados.txt, en donde se guardarán los resultados con el siguiente formato:
```sh
N;p;Time without Bloom filter;Time with Bloom filter;Error rate
```
En donde N es la cantidad de elementos a buscar y p es la proporción de elementos que realmenté están en el vector a buscar.
