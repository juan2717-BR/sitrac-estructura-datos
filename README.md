# SITRAC — Sistema Inteligente de Transporte y Gestión de Rutas

Proyecto de Estructura de Datos en C++.

## Funcionalidades
- Menú principal persistente: Ciudades, Rutas, Pasajeros, Cola, Historial, Búsquedas, Reportes, Guardar/cargar y Salir.
- Submenús con opción Volver.
- Lista enlazada propia de pasajeros: insertar, buscar, actualizar, eliminar y listar.
- Grafo de ciudades con listas de adyacencia: alta/baja de ciudades y conexiones, consulta de vecinos y conexiones directas.
- Cola enlazada propia de solicitudes: encolar, atender y mostrar frente.
- Historial de operaciones y persistencia en archivo de texto.

## Compilar y ejecutar
Se necesita un compilador C++14.

Windows con MinGW:
```bash
g++ -std=c++14 -Wall -Wextra -pedantic src/main.cpp -o sitrac.exe
sitrac.exe
```

Linux/macOS:
```bash
g++ -std=c++14 -Wall -Wextra -pedantic src/main.cpp -o sitrac
./sitrac
```

El archivo sitrac_datos.txt se crea en la carpeta desde la que se ejecuta el programa. En el menú, elige 8 y luego 1 para guardar o 2 para cargar.

## Estructuras y justificación
| Operación | Estructura | Justificación |
|---|---|---|
| Pasajeros | Lista simplemente enlazada propia | Inserción y eliminación de nodos sin std::list |
| Ciudades y rutas | Grafo con listas de adyacencia | Representa vecinos y distancias entre ciudades |
| Solicitudes | Cola enlazada propia | Atención FIFO, sin std::queue |
| Historial | vector<string> | Conserva eventos en orden de ocurrencia |

## Organización
- src/main.cpp: implementación modular mediante clases.
- docs/DIAGRAMA_Y_ESTRUCTURAS.md: arquitectura y explicación.
- docs/PRUEBAS.md: casos de prueba y registro real de resultados.

## Uso de IA
Se utilizó ChatGPT como apoyo para estructurar, revisar y corregir partes del código y la documentación. El estudiante debe compilar, ejecutar, revisar y comprender cada módulo, corregir lo que encuentre y poder explicar las decisiones de implementación durante la sustentación.

## Alcance conocido
La búsqueda de rutas consulta conexiones directas; no calcula todavía la ruta más corta entre varias ciudades. Los campos de texto guardados no deben contener el separador |.
