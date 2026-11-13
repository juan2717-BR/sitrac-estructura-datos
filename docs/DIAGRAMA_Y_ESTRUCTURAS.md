# Diseño y estructuras de SITRAC

## Diagrama general
~~~text
                 +----------------------+
                 |    MENU PRINCIPAL    |
                 +----------+-----------+
                            |
       +--------------------+--------------------+
       |                    |                    |
+------v-------+    +-------v--------+   +-------v--------+
|  Pasajeros   |    | Ciudades/rutas |   | Solicitudes    |
| Lista enlaz. |    | Grafo ponderado|   | Cola enlazada  |
+------+-------+    +-------+--------+   +-------+--------+
       |                    |                    |
       +--------------------+--------------------+
                            |
                 +----------v-----------+
                 | Consultas y reportes |
                 | Historial / archivos |
                 +----------------------+
~~~

## Lista simplemente enlazada
Cada nodo de pasajero contiene ID, nombre, documento, teléfono y puntero al siguiente nodo. Permite insertar, recorrer, buscar por ID y eliminar. Se valida que el documento no esté repetido y se libera la memoria al destruir la lista.

## Grafo ponderado
Las ciudades son vértices y las rutas son aristas con distancia en kilómetros. Cada ciudad conserva una lista de adyacencia. Las rutas se agregan en ambos sentidos, por lo que el grafo es no dirigido. La versión actual consulta conexiones directas; no calcula caminos mínimos.

## Cola enlazada FIFO
Cada solicitud guarda código, ID del pasajero, origen, destino y puntero siguiente. Se inserta al final y se atiende desde el frente, respetando primero en entrar, primero en salir.

## Historial y persistencia
El historial se guarda en un vector. Los registros se almacenan en sitrac_datos.txt con identificadores de tipo P (pasajero), C (ciudad), R (ruta), S (solicitud) y H (historial). La carga reconstruye los registros válidos.

## Integración
Una solicitud solo se acepta cuando existe el pasajero y se ha registrado una conexión directa entre las ciudades de origen y destino.
