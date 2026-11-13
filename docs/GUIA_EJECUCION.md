# Guía rápida para ejecutar SITRAC en Windows

1. Abre el repositorio en GitHub y pulsa **Code > Download ZIP**.
2. Extrae el ZIP en una carpeta fácil de encontrar.
3. Instala un compilador C++ que incluya g++ (por ejemplo, MinGW-w64 o MSYS2) y asegúrate de que g++ esté en PATH.
4. Abre la carpeta extraída y haz doble clic en `compilar.bat`.
5. El programa se compila y se abre en la consola. Si el archivo .bat indica que no encuentra g++, falta instalar/configurar el compilador.
6. Para salir de cada submenú, escribe 0. En el menú principal, escribe 0 para terminar.

## Ejemplo mínimo de recorrido

- Opción 1: registra Bogotá y luego intenta registrarla otra vez.
- Opción 3: registra un pasajero y prueba eliminar el ID 999.
- Opción 4: intenta atender la cola vacía.
- Opción 2: agrega una conexión con distancia -5.
- Opción 1: registra Tunja; en el módulo 2 crea Bogotá-Tunja y después elimina Bogotá.
- Escribe letras cuando el menú pida una opción para probar la validación.

Toma capturas de tu propia ejecución y registra el resultado real en `docs/PRUEBAS.md`.
