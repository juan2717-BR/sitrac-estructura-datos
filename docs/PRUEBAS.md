# Plan de pruebas de SITRAC

**Nota:** son casos propuestos. No se consideran aprobados hasta ejecutarlos y registrar el resultado real.

| ID | Módulo | Acción | Resultado esperado |
|---|---|---|---|
| P01 | Pasajeros | Registrar pasajero válido | Se asigna un ID |
| P02 | Pasajeros | Repetir documento | Se rechaza el duplicado |
| P03 | Pasajeros | Buscar ID existente | Se muestran sus datos |
| P04 | Pasajeros | Buscar ID inexistente | Se informa que no existe |
| P05 | Pasajeros | Eliminar ID existente | Se elimina el nodo |
| R01 | Ciudades | Agregar ciudad nueva | Se registra en el grafo |
| R02 | Ciudades | Repetir ciudad | Se rechaza |
| R03 | Rutas | Crear ruta entre ciudades registradas | Se agrega en ambos sentidos |
| R04 | Rutas | Consultar conexión existente | Se confirma conexión directa |
| R05 | Rutas | Usar ciudad inexistente o distancia no positiva | Se rechaza |
| S01 | Solicitudes | Crear viaje válido | Se agrega al final de la cola |
| S02 | Solicitudes | Pasajero inexistente | Se rechaza |
| S03 | Solicitudes | Atender varias solicitudes | Se atienden en orden FIFO |
| S04 | Solicitudes | Atender cola vacía | Se informa que está vacía |
| A01 | Archivos | Guardar datos | Se crea sitrac_datos.txt |
| A02 | Archivos | Cargar datos guardados | Se reconstruyen registros válidos |
| M01 | Menú | Elegir opción fuera de rango | Se informa que no es válida |
| M02 | Menú | Escribir letras donde se espera entero | Se solicita un valor válido |

## Registro de ejecución
Completar esta tabla después de ejecutar el programa:

| Grupo | Resultado real | Estado | Observaciones |
|---|---|---|---|
| P01–P05 | Pendiente | Pendiente | Ejecutar |
| R01–R05 | Pendiente | Pendiente | Ejecutar |
| S01–S04 | Pendiente | Pendiente | Ejecutar |
| A01–A02 | Pendiente | Pendiente | Ejecutar |
| M01–M02 | Pendiente | Pendiente | Ejecutar |

## Para la sustentación
- Explicar la lista enlazada de pasajeros.
- Mostrar las ciudades y sus conexiones en el grafo.
- Demostrar la atención FIFO de la cola.
- Mostrar cómo se guardan y recuperan los datos.
- Aclarar que esta versión consulta rutas directas y no calcula caminos mínimos.
