# Diagrama modular y estructuras de SITRAC

## Diagrama
~~~text
                         MENU PRINCIPAL
                               |
       +-----------+-----------+-----------+-----------+
       |           |           |           |           |
    CIUDADES     RUTAS     PASAJEROS      COLA      HISTORIAL
       |           |           |           |           |
       +-----------+-----------+-----------+-----------+
                               |
                 BUSQUEDAS / REPORTES / ARCHIVOS
                               |
                    sitrac_datos.txt
~~~

## Tabla de estructuras
| Operación | Estructura usada | Justificación |
|---|---|---|
| Insertar/listar/buscar/actualizar/eliminar pasajeros | Lista simplemente enlazada propia | Cada pasajero es un nodo enlazado; permite gestionar memoria dinámica |
| Registrar ciudades y consultar conexiones | Grafo con listas de adyacencia | Cada ciudad es vértice y cada ruta es arista con peso en kilómetros |
| Agregar/quitar rutas | Listas de adyacencia | Actualiza la conexión en ambos sentidos |
| Eliminar ciudad | Grafo y recorrido de adyacencias | Elimina aristas incidentes y reajusta índices para evitar referencias colgantes |
| Encolar/atender solicitudes | Cola enlazada propia | Mantiene FIFO: primero en entrar, primero en salir |
| Historial | vector<string> | Mantiene los eventos en orden de llegada |
| Guardar/cargar | Archivo de texto | Permite persistencia básica de los registros |

## Contrato del menú
1 Ciudades, 2 Rutas, 3 Pasajeros, 4 Cola, 5 Historial, 6 Búsquedas, 7 Reportes, 8 Guardar/cargar y 0 Salir. Todos los submenús ofrecen Volver.
