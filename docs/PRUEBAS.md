# Pruebas de SITRAC

## Resultado de las pruebas CP-01 a CP-06

Las seis pruebas se ejecutaron manualmente en Windows con MSYS2 UCRT64 y GCC g++ 16.2.0. Los resultados se documentan a partir de las capturas de terminal compartidas por el estudiante durante la revisión. **Las imágenes aún deben guardarse y adjuntarse al repositorio en `evidencias/`**. El programa compiló y abrió el menú principal; inicialmente se observó una advertencia de indentación engañosa en `GrafoCiudades::conectadas`, corregida posteriormente en el código fuente. La nueva versión requiere recompilación local.

| Caso | Entrada y procedimiento observados | Resultado observado | Estado |
|---|---|---|---|
| CP-01 | Registrar `bogota` dos veces; listar ciudades | `Ciudad vacia o duplicada; no se agrego.`; `bogota` aparece una sola vez | Aprobada (ejecución manual) |
| CP-02 | Pasajeros > Eliminar, ID `99999` | `No existe pasajero con ese ID.`; el submenú continúa | Aprobada (ejecución manual) |
| CP-03 | Cola > Atender siguiente con cola vacía | `Cola vacia: no hay elementos para atender.`; el submenú continúa | Aprobada (ejecución manual) |
| CP-04 | Agregar conexión `bogota` - `villavicencio`, distancia `-5` | `Distancia invalida: debe ser mayor que cero.`; no se registra la ruta negativa | Aprobada (ejecución manual) |
| CP-05 | Agregar conexión bidireccional `bogota` - `villavicencio` de 120 km; eliminar `villavicencio`; mostrar grafo | El reporte y el grafo muestran `bogota -> sin conexiones`; el historial registra la eliminación | Aprobada (ejecución manual) |
| CP-06 | Escribir `abc` en `Seleccione:` | `Entrada invalida. Escriba un numero entero.`; vuelve a solicitar opción | Aprobada (ejecución manual) |

**Nota de alcance:** estas son pruebas funcionales manuales observadas, no una batería automatizada. En CP-05 se comprobó el grafo después de borrar una ciudad conectada, no todas las posibles topologías. En CP-06 se comprobó la recuperación al pedir una nueva opción; conviene volver a seleccionar un número válido para ampliar la evidencia.

## Capturas pendientes de adjuntar

Guarda capturas reales, sin alterarlas, en una carpeta `evidencias/` del repositorio, con estos nombres sugeridos:

- `CP-01-ciudad-duplicada.png`
- `CP-02-pasajero-inexistente.png`
- `CP-03-cola-vacia.png`
- `CP-04-distancia-negativa.png`
- `CP-05-eliminar-ciudad-conectada.png`
- `CP-06-entrada-invalida.png`

## Pruebas adicionales pendientes

- Registrar, buscar y actualizar un pasajero existente.
- Encolar dos solicitudes válidas y comprobar el orden FIFO.
- Guardar y cargar `sitrac_datos.txt`.
- Recompilar la última versión con `-Wall -Wextra -pedantic` y comprobar que no aparecen advertencias.

## Funcionalidades y responsables

| Funcionalidad | Estado | Responsable de verificar y explicar |
|---|---|---|
| Menú y submenús | Ejecución básica verificada | Juan Esteban Benito Bernal |
| Lista enlazada de pasajeros | Implementada; eliminación inexistente verificada | Juan Esteban Benito Bernal |
| Grafo y eliminación de ciudad conectada | Implementados; CP-01, CP-04 y CP-05 verificados | Juan Esteban Benito Bernal |
| Cola enlazada | Implementada; cola vacía verificada; FIFO pendiente | Juan Esteban Benito Bernal |
| Historial, búsquedas y reportes | Reporte e historial visualizados; búsquedas pendientes | Juan Esteban Benito Bernal |
| Guardar/cargar | Implementado; ejecución pendiente | Juan Esteban Benito Bernal |
| Capturas de CP-01 a CP-06 | Vistas durante la revisión; pendiente adjuntar archivos | Juan Esteban Benito Bernal |

## Uso de asistencia

Se utilizó ChatGPT para apoyar la implementación, la corrección de código y la documentación de las pruebas. Las pruebas descritas se ejecutaron en la terminal del estudiante y se revisaron mediante capturas compartidas; el estudiante debe comprender y poder explicar el código y los resultados.
