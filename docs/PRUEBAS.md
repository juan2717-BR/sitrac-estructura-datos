# Pruebas de SITRAC

No marques una prueba como aprobada hasta ejecutarla y observar el resultado. Adjunta capturas propias de tu ejecución.

## Casos obligatorios de la guía
| Caso | Pasos | Resultado esperado | Estado |
|---|---|---|---|
| CP-01 | Ciudades > Registrar ciudad: Bogotá; repetir Bogotá | Rechaza duplicado y no crea otro vértice | Pendiente de evidencia |
| CP-02 | Pasajeros > Eliminar; escribir un ID inexistente, por ejemplo 999 | Informa que no existe y la lista sigue funcionando | Pendiente de evidencia |
| CP-03 | Cola > Atender siguiente sin solicitudes | Informa cola vacía, sin fallar | Pendiente de evidencia |
| CP-04 | Rutas > Agregar conexión; ingresar -5 como distancia | Rechaza distancia no positiva | Pendiente de evidencia |
| CP-05 | Crear Bogotá, Tunja y ruta Bogotá-Tunja; eliminar Bogotá; mostrar grafo | Tunja permanece sin conexión inválida | Pendiente de evidencia |
| CP-06 | Escribir letras cuando el menú pide número | Informa entrada inválida y vuelve a pedir número sin ciclo infinito | Pendiente de evidencia |

## Pruebas adicionales recomendadas
- Registrar pasajero y repetir su documento.
- Actualizar pasajero existente.
- Crear solicitud válida y comprobar atención FIFO.
- Guardar y luego cargar los datos.

## Registro de evidencia del estudiante
| Prueba ejecutada | Resultado observado | Nombre del archivo de captura |
|---|---|---|
| CP-01 | Completar después de ejecutar | |
| CP-02 | Completar después de ejecutar | |
| CP-03 | Completar después de ejecutar | |
| CP-04 | Completar después de ejecutar | |
| CP-05 | Completar después de ejecutar | |
| CP-06 | Completar después de ejecutar | |

## Funcionalidades y responsables
| Funcionalidad | Estado del código | Responsable de verificar y explicar |
|---|---|---|
| Menú y submenús | Implementado en código; falta prueba en equipo | Juan Esteban Benito Bernal |
| Lista enlazada de pasajeros | Implementada | Juan Esteban Benito Bernal |
| Grafo y eliminación segura | Implementados | Juan Esteban Benito Bernal |
| Cola enlazada | Implementada | Juan Esteban Benito Bernal |
| Historial, búsquedas y reportes | Implementados | Juan Esteban Benito Bernal |
| Guardar/cargar | Implementado; requiere prueba | Juan Esteban Benito Bernal |
| Capturas y registro de CP-01 a CP-06 | Pendiente | Juan Esteban Benito Bernal |
