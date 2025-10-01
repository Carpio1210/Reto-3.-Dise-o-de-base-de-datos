Sistema de Gestión de Biblioteca - Reto 3:
Descripción:
Este proyecto implementa un sistema completo de gestión de biblioteca desarrollado en C++, que permite administrar libros, autores, estudiantes y préstamos de manera eficiente. El sistema está diseñado para ser utilizado por instituciones educativas, bibliotecas públicas o privadas.

Compilación y Ejecución:
Compilación:
bash:
g++ -o biblioteca Reto3_Fase3.cpp -std=c++11

Ejecución:
bash:
./biblioteca        # Linux/macOS
biblioteca.exe      # Windows

Menú de Operaciones:
El sistema ofrece un menú interactivo completo con 17 opciones:

GESTION DE LIBROS:

Agregar libro
Mostrar inventario
Actualizar libro
Eliminar libro

GESTION DE USUARIOS:
6. Agregar usuario
7. Mostrar usuarios
14. Actualizar usuario
15. Eliminar usuario

GESTION DE AUTORES:
8. Agregar autor
9. Mostrar autores
12. Actualizar autor
13. Eliminar autor

OPERACIONES DE PRESTAMO:
3. Prestar libro
4. Devolver libro
5. Buscar préstamo por estudiante

CONSULTAS ESPECIALES:
16. Autores con más libros

SISTEMA:
17. Salir

Arquitectura del Sistema:
Estructuras de Datos:
El sistema utiliza 4 estructuras principales para organizar la información:

cpp
struct Autor {
    int id_autor;
    string nombre;
    string nacionalidad;
};

struct Libro {
    int id_libro;
    string titulo;
    string isbn;
    string nombreAutor;  // Diseño centrado en usabilidad
    bool estaDisponible;
    int anioPublicacion;
};

struct Estudiante {
    string nombre;
    string grado;
    int idUsuario;
    vector<Prestamo> prestamos;
};

struct Prestamo {
    int id_prestamo;
    int id_libro;
    int idUsuario;
    int fecha_prestamo;
    int fecha_devolucion;
};

Características Técnicas:
Validaciones y Seguridad:
Validación de años: Los libros deben tener año de publicación entre 0 y el año actual.

Límite de préstamos: Máximo 1 libro por estudiante simultáneamente.

Prevención de duplicados: Verificación de libros, autores y usuarios existentes.

Búsquedas case-insensitive: No distingue entre mayúsculas y minúsculas.

Persistencia de Datos:
El sistema genera y gestiona automáticamente 4 archivos:

libros.txt: Catálogo completo de libros.

autores.txt: Base de datos de autores.

estudiantes.txt: Registro de usuarios.

prestamos.txt: Historial de préstamos.

Gestión de Estado:
Carga inteligente: Reconstruye el estado completo al iniciar.

Guardado automático: Persiste cambios después de cada operación.

Sincronización: Mantiene consistencia entre todas las entidades.

Funcionalidades Destacadas.
Gestión de Préstamos:
cpp
void prestarLibro() {
    // Validaciones múltiples:
    // - Libro existe y está disponible
    // - Usuario registrado y sin préstamos activos
    // - Confirmación del usuario
    // - Actualización automática de estado
}
Consultas Avanzadas:
Préstamos por estudiante: Visualización completa del historial.

Autores más prolíficos: Ranking basado en cantidad de libros.

Inventario inteligente: Muestra disponibilidad en tiempo real.

Operaciones CRUD Completas:
Cada entidad (Libro, Autor, Estudiante, Préstamo) cuenta con operaciones:

Create (Crear): Registro con validaciones.

Read (Leer): Visualización organizada.

Update (Actualizar): Modificación segura por ID.

Delete (Eliminar): Eliminación con integridad referencial.

Características de Usabilidad:
Diseño Centrado en el Usuario:
Nombres en lugar de IDs: Los usuarios trabajan con nombres de autores en lugar de IDs numéricos.

Mensajes descriptivos: Feedback claro para cada operación.

Manejo de errores robusto: Previene crashes y datos inconsistentes.

Flujo de Trabajo Optimizado:
Inicialización: Carga datos existentes automáticamente.

Operaciones: Menú intuitivo con 17 opciones organizadas.

Persistencia: Guardado automático después de cada modificación.

Salida: Cierre seguro con confirmación de guardado.

Datos de Ejemplo Incluidos:
El sistema incluye datos iniciales para demostración:

Libro: "El Hobbit" por J.R.R. Tolkien.

Autor: J.R.R. Tolkien (Inglaterra).

Estudiante: Diego Carpio (Segundo año General).

Consideraciones de Uso:
Los archivos de datos se crean automáticamente en el primer uso.

El sistema mantiene la consistencia incluso después de reinicios.

Todas las operaciones incluyen validaciones para prevenir errores.

El diseño prioriza la experiencia del usuario final sobre tecnicismos.

Tecnologías Utilizadas:
Lenguaje: C++11.

Persistencia: Archivos CSV con fstream.

Estructuras: Vectores y Structs nativos.

Interfaz: Consola con menú interactivo.
