# Entrega y sustentación de SITRAC

## Archivos para entregar

- `src/main.cpp`: código fuente en C++14.
- `README.md`: descripción, instrucciones de compilación y declaración de uso de IA.
- `docs/DIAGRAMA_Y_ESTRUCTURAS.md`: diagrama modular y explicación de estructuras.
- `docs/PRUEBAS.md`: resultados de CP-01 a CP-06 y pruebas pendientes.
- `docs/GUIA_EJECUCION.md`: pasos para ejecutar el proyecto.
- `evidencias/`: agregar las capturas reales de la ejecución; no están incluidas todavía.

Repositorio: https://github.com/juan2717-BR/sitrac-estructura-datos

## Actualizar y ejecutar en MSYS2 UCRT64

```bash
cd ~/sitrac-estructura-datos
git pull
g++ -std=c++14 -Wall -Wextra -pedantic src/main.cpp -o sitrac.exe
cmd.exe /c sitrac.exe
```

En la consola de Windows que se abre dentro de la terminal, escribir `sitrac.exe` y presionar Enter. Si el archivo se puede ejecutar directamente desde UCRT64, usar `./sitrac.exe`. Para cerrar el programa, seleccionar `0`.

## Subir capturas desde GitHub web

1. Abrir el repositorio y pulsar **Add file > Upload files**.
2. Arrastrar la carpeta `evidencias` con capturas PNG reales (o crearla localmente y subir los PNG).
3. Escribir el mensaje de commit: `Agregar evidencias de pruebas CP-01 a CP-06`.
4. Confirmar el commit y comprobar que los archivos aparecen en el repositorio.

Si la guía exige un commit hecho en clase, realizar uno realmente durante la clase; los commits previos no prueban ese requisito.

## Guion breve de sustentación

“Mi proyecto se llama SITRAC, Sistema Inteligente de Transporte y Gestión de Rutas, y está desarrollado en C++. Tiene un menú para administrar ciudades, rutas, pasajeros y solicitudes de viaje. Implementé una lista simplemente enlazada propia para los pasajeros, un grafo con listas de adyacencia para las conexiones entre ciudades y una cola enlazada FIFO para atender solicitudes. También incluye historial, búsquedas, reportes y guardar/cargar datos. Probé que rechaza ciudades duplicadas, IDs inexistentes, colas vacías, distancias negativas y entradas de texto donde se requieren números. Además, al eliminar una ciudad conectada, el grafo no conserva esa conexión. Utilicé asistencia de IA en la implementación y documentación, y revisé las funciones mediante ejecución manual.”

## Antes de entregar

- [ ] Recompilar la última versión y comprobar el resultado.
- [ ] Adjuntar capturas reales de al menos cuatro pruebas, incluidas dos entradas inválidas.
- [ ] Verificar guardar/cargar y, si hay tiempo, una solicitud FIFO válida.
- [ ] Confirmar que el repositorio es accesible para el profesor.
- [ ] Saber explicar los nodos, los punteros, la adyacencia y el menú.
