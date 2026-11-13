# SITRAC — Sistema Inteligente de Transporte y Gestión de Rutas

Proyecto académico en C++ para administrar pasajeros, ciudades, rutas y solicitudes de viaje.

## Funcionalidades
1. Gestión de pasajeros: registrar, listar, buscar por ID y eliminar.
2. Gestión de ciudades y rutas: agregar ciudades, crear rutas bidireccionales y consultar conexiones directas.
3. Solicitudes de viaje: crear solicitudes, ver la cola y atender la siguiente.
4. Consultas y reportes: pasajeros, red de rutas, solicitudes e historial.
5. Persistencia: guardar y cargar información en el archivo sitrac_datos.txt.
6. Validaciones: documentos duplicados, IDs inexistentes, ciudades repetidas y solicitudes sin pasajero o sin conexión directa.

## Estructuras de datos
- Lista simplemente enlazada propia para pasajeros.
- Grafo ponderado con listas de adyacencia para ciudades y distancias.
- Cola simplemente enlazada FIFO para solicitudes.
- Vector para historial y listas de adyacencia.

## Compilación
Requiere un compilador C++14.

Linux / macOS:
~~~bash
g++ -std=c++14 -Wall -Wextra -pedantic src/main.cpp -o sitrac
./sitrac
~~~

Windows con MinGW:
~~~bash
g++ -std=c++14 -Wall -Wextra -pedantic src/main.cpp -o sitrac.exe
sitrac.exe
~~~

El archivo sitrac_datos.txt se crea en el directorio desde el que se ejecuta el programa. Usa la opción 5 para guardar y la opción 6 para cargar.

## Archivos
- src/main.cpp: código fuente.
- docs/DIAGRAMA_Y_ESTRUCTURAS.md: diseño y explicación de estructuras.
- docs/PRUEBAS.md: plan y registro de pruebas.

## Alcance
La versión actual verifica conexiones directas entre ciudades; todavía no calcula el camino más corto entre varias ciudades. El archivo de datos utiliza el carácter | como separador, por lo que los campos no deben contener ese carácter. Ejecuta y registra las pruebas antes de entregar.

## Autor
Juan Esteban Benito Bernal
