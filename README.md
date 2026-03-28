# TP Final — Laboratorio de Computación II (2do cuatrimestre 2022)
Sistema de gestión de competidores desarrollado en C, que permite migrar datos desde un archivo de texto CSV a un archivo binario y operar sobre ellos mediante un menú interactivo.

### Menú de visualización
- **Todos los registros** — lista activos e inactivos
- **Solo activos** — filtra por `act == 1`
- **Por país** — ingreso por teclado, se convierte a mayúsculas y se recorta a 3 caracteres
- **Por rango de tiempo** — se ingresan un mínimo y un máximo en formato `230.0-300.0`
- **Por número de orden** — acceso directo con `fseek`, validado positivo
- **Por número de corredor (ID)** — búsqueda secuencial validada
 
### Menú de modificaciones
- **Alta** — registra un nuevo competidor en la posición indicada por el número de orden; valida que el orden y el ID no estén en uso, que la edad esté entre 18 y 99, y que el tiempo esté entre 100 y 500. El mes se guarda en minúsculas y el país se recorta a 3 caracteres en mayúsculas.
- **Modificar** — permite cambiar la edad o el tiempo de un competidor buscándolo por número de orden, con acceso directo vía `fseek`.
- **Baja lógica** — localiza el registro por número de orden y setea `act = 0` sin eliminar el registro físicamente.
