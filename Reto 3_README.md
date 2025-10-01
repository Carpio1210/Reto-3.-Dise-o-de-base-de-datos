Cómo compila y ejecuta el programa:

En realidad, la acción de ejecutar el programa es relativamente sencilla, pero ampliamente compleja en código, ya que todo comienza con el menú interactivo con switch case para CRUD, que tiene 17 opciones, desde agregar libro, mostrar libro, hasta salir o prestar libro. Cada función está conectada a un void específico que se encarga de realizar una tarea puntual; las 17 opciones que tenemos en nuestro menú son:

cout << "1. Agregar libro" << endl;
cout << "2. Mostrar inventario" << endl;
cout << "3. Prestar libro" << endl;
cout << "4. Devolver libro" << endl;
cout << "5. Buscar préstamo por estudiante" << endl;
cout << "6. Agregar usuario" << endl;
cout << "7. Mostrar usuarios" << endl;
cout << "8. Agregar autor" << endl;
cout << "9. Mostrar autores" << endl;
cout << "10. Actualizar libro" << endl;
cout << "11. Eliminar libro" << endl;
cout << "12. Actualizar autor" << endl;
cout << "13. Eliminar autor" << endl;
cout << "14. Actualizar usuario" << endl;
cout << "15. Eliminar usuario" << endl;
cout << "16. Autores con más libros" << endl;
cout << "17. Salir" << endl;

Cada una de estas opciones llama a un void, a excepción de Salir, ya que esta solo rompe el bucle en el que está el menú, dando un mensaje de gracias al usuario. Las opciones de mostrar inventario, mostrar usuarios y mostrar autores, todas tienen un funcionamiento similar con variables distintas. Buscan en el inventario que se tiene para mostrarlo, pero cuando el inventario esté vacío, el código está preparado para evitar errores de datos inexistentes. Ya que antes de mostrar el inventario, revisa que no esté vacía la lista, y luego de revisar que no esté sola la lista, printea todas las opciones con sus respectivas variables.

En el caso de mostrar usuarios, maneja 3 variables: nombre, ID y carrera; en el caso de libros, maneja autor, título, año, ID_libro, género y si está disponible o prestado. Además, también se manejan los autores, donde en ese caso solo se muestra nombre del autor, nacionalidad e ID. Toda esta información está manejada a través de struct, donde estas 4 struct (prestamo, Usuario, Autor y Libro), previamente definidas, se encargan de ordenar y clasificar los datos en esas 4 categorías. Estas 4 categorías tienen su justificación en la fase 1 y 2 del reto 3, donde se implementaron para tener un mejor manejo de los datos en todas las partes, definiendo las llaves primarias y foráneas para cada categoría.

En la parte 2, tenemos a los "añadir", donde estos 3 (añadir autor, usuario y libro) siguen la misma lógica. Cada uno pregunta por los datos esenciales de los datos que quiere introducir. Estos datos son tomados y agrupados, formando un solo objeto con diversas características propias, que luego se almacena en el programa para manejar los datos en diferentes categorías como struct libro, struct autor y struct usuario. Cada uno también en sus respectivos void tiene diferentes restricciones; por ejemplo, en agregar libro, tenemos que los libros tienen que ser escritos entre los años 0 a 2025, y aparte no tienen que estar previamente registrados (el previamente registrados lo cumplen los 3 "añadir", dado que con esto se busca comparar antes de tiempo si ya está este objeto para no reescribirlo, y si el objeto pasa las pruebas de que no hay otro como ese, efectivamente se registra).

Ahora, el prestar, la opción prestar y el void prestar es el más complejo, dado que este reúne una gran cantidad de información y tiene el poder de cambiar esa información en otras áreas. El prestar libro tiene una gran cantidad de restricciones. Por ejemplo, el título tiene que estar registrado, también se le agregó un límite de 1 libro por estudiante, además de limitar los préstamos a varios estudiantes. Ya que cuando un libro es prestado, este aparecerá como no disponible hasta que se devuelva con la función "volver". Además, para prestar un libro también se manejan las fechas de préstamo y de devolución "si hay". Si no hay fecha de devolución exacta, el código deja seguir. Para lograr todo esto, la mayoría de las restricciones se manejaron con if. El devolver básicamente borra los datos del usuario que tomó el libro y vuelve a dejar el libro como disponible.

Así funcionan todas las funciones del menú, pero dentro del código se encuentran muchas otras variables como los void:
    void agregarUsuario(const Estudiante& nuevoUsuario);    //USUARIOS
    Estudiante*buscarusuarios(const string& nombre);        //USUARIOS
    void mostrarUsuarios() const;                           //USUARIOS
    void actualizarUsuario(int idUsuario);
    void eliminarUsuario(int idUsuario);

    void mostrarPrestamosPorEstudiante(int idEstudiante);

    void agregarAutor(const Autor& nuevoAutor);              //Autor
    void mostrarAutor() const;                               //Autor
    void actualizarAutor(int id_autor);
    void eliminarAutor(int id_autor);
    void mostrarAutoresConMasLibros() const;

    void agregarLibro(const Libro& nuevoLibro);   // Promesa de agregar un libro

    void mostrarInventario();    // Promesa de mostrar inventario

    Libro* buscarLibro(const std::string& tituloBuscado);

    void prestarLibro(const std::string& tituloPrestamo);    // Promesa de prestamo de libro

    void devolverLibro(const std::string& tituloDevolucion);    // Promesa de devolver libro

    void actualizarLibro(int id_libro);
    void eliminarLibro(int id_libro);

    void guardarLibros();  //Para cumplir el requisito de la fase 3 (Persistencia: Guarda/carga datos en archivos .txt (usa fstream para leer/escribir en formato CSV simple).)
    void guardarAutores();
    void guardarPrestamos();
    void guardarUsuarios();

    void cargarDatos();    //Carga todos los datos de libro, autores, prestamos y usuarios

Todos esos void tienen una definición particular hecha para una tarea específica. El de los usuarios tiene por objetivo manejar solo esa información, al igual que el autor y los libros. Además, se tiene también los void de guardar y cargar datos, ya que los void también escriben datos en archivos .txt donde guardan la información, pero también la retoman para llevar un mejor control. Cada uno de estos void está definido en el código y con una respuesta singular y puntual para lo que se necesite de cada uno de estos.

También se agregaron distintos void como actualizar y eliminar diversos datos de las bases de datos. Esto también se realizó con un void donde se buscaba poder cambiar y eliminar datos de la base sin necesidad de entrar a editarla. Para esto, se pide el ID de lo que se quiera cambiar como método de seguridad, para que no cualquiera pueda eliminar y cambiar los datos de otra persona. También se agregó un void para poder buscar cuál es el autor con más libros y también un void para reconocer si un usuario tiene préstamos, para poder saber toda esa información de un solo vistazo.

Por último, los struct, con los struct se logró manejar la información como clases, pero a la vez almacenarlo como estructuras de datos para un manejo más sencillo. En esta parte se definieron 4 struct (autor, libro, prestamo y usuario), cada uno con sus características individuales definidas por variables, ya sean int, string o bool. Todo esto junto ha logrado el funcionamiento del código, desde el main que nos da la interacción con el usuario hasta los void que nos definen nuestras funciones.


README (Simplificado).

# Reto 3: Biblioteca Virtual

Este programa simula un sistema de gestión de biblioteca, que puede ser utilizado tanto por instituciones educativas como bibliotecas publicas o privadas.

## Cómo compilar y ejecutar el programa

### Compilar:

Para compilar el programa en tu terminal, utiliza el siguiente comando:

```bash
g++ -o biblioteca Reto3_Fase3.cpp -std=c++11

# Ejecutar:
Para ejecutarlo dependiendo de nuestro tipo de procesador vamos a usar:
./biblioteca        # Linux/macOS
biblioteca.exe      # Windows

Para uso del menu este trae diversas opciones, para que el usuario escoja la que quiera.

    Menu de Opciones
    Añadir libro
    Mostrar inventario
    Prestar libro
    Devolver libro
    Buscar préstamo por estudiante
    Añadir usuario
    Mostrar usuarios
    Añadir autor
    Mostrar autores
    Actualizar libro
    Eliminar libro
    Actualizar autor
    Eliminar autor
    Actualizar usuario
    Eliminar usuario
    Ver autores con más libros
    Salir

Caracteristicas propias del codigo y de como funciona:

Guardado automático en archivos .txt

Límite de 1 libro por usuario

Validación de datos y años

Búsquedas case-insensitive

Datos de ejemplo incluidos

Archivos Generados:

libros.txt

autores.txt

usuarios.txt

prestamos.txt

Estos mismos archivos se cargan cuando se vuelve a usar.