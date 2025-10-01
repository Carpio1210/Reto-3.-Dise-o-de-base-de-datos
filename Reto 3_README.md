Como compila y ejecuta el programa:

En realidad la accion de ejecutar el programa es relativamente sencilla pero ampliamente compleja en codigo, ya que tomo comienza con el menu interactivo con switch case para CRUD, que tiene 8 opciones, desde agregar libro, mostrar libro, hasta salir o prestar libro, cada funcion esta conectada a un void especifico que se encarga de realizar una tarea puntual; las 9 opciones que tenemos en nuestro menu son:

cout << "1. Añadir libro" << endl;
cout << "2. Mostrar inventario" << endl;
cout << "3. Prestar libro" << endl;
cout << "4. Devolver libro" << endl;
cout << "5. Añadir usuario" << endl;
cout << "6. Mostrar usuarios" << endl;
cout << "7. Añadir autor" << endl;
cout << "8. Mostrar autores" << endl;
cout << "9. Salir" << endl;

Cada una de estas opciones llama a un void a excepcion de salir, ya que esta solo rompe el bucle en el que esta el menu, dando un mensaje de gracias al usuario, las opciones de mostrar inventario, mostrar usuarios y mostrar autores, todas tienen un funcionamiento similar con variables distintas, buscan en el inventario que se tiene para mostrarlo pero cuando el inventario este vacio el codigo esta preparado para evitar errores de datos inexistentes ya que antes de mostrar el inventario revisa que no este vacia la lista y luego de revisar que no este sola la lista, printea todas las opciones con sus respectivas variables, en el caso de mostrar usuarios maneja 3 variables, nombre, ID y carrera, en el caso de libros maneja autor, titulo, anio, ID_libro, genero y si esta disponible o prestado, ademas tambien se manejan los autores que en ese caso solo se muestra nombre del autor, nacionalidad y ID, toda esta informacion esta manejada a traves de struct, donde estas 4 struct(prestamo, Usuario, Autor y Libro), previamente definidas se encargan de ordenar y clasificar los datos en esas 4 categorias, estas 4 categorias tienen su justificacion en la fase 1 y 2 del reto 3, donde se implementaron para tener un mejor manejo de los datos en todas las partes definiendo las llaves primarias y foraneas para cada categoria.

En la parte 2, tenemos a los anadir donde estos 3 (anadir autor, usuario y libro), siguen la misma logica, cada uno pregunta por los datos ensenciales de los datos que quiere introduccir, estos datos son tomados y agrupados formando un solo objeto con diversas caracteristicas propias, que luego se almacena en el programa, para manejar los datos en diferentes categorias como struct libro, struct autor y struct usuario, cada uno tambien en sus respectivos void tiene diferentes restricciones por ejemplo en agregar libro tenemos que los libros tienen que ser escritos entre los anios 0 a 2025, que aparte no tienen que estar previamente registrados (el previamente registrados lo cumplen los 3 anadir dado que con esto se busca comparar antes de tiempo si ya esta este objeto para no rescribirlo y si el objeto pasa las pruebas de que no hay otro como ese efectivamente se registra).

Ahora el prestar, la opcion prestar y el void prestar es el mas complejo, dado que este reune una gran cantidad de informacion y tiene el poder de cambiar esa informacion en otras areas, el prestar libro tiene una gran cantidad de restricciones por ejemplo el titulo tiene que estar registrado, tambien se le agrego un limite de 1 libro por estudiante, ademas de limitar los prestamos a varios estudiantes, ya que cuando un libro es prestado este aparecera como no disponible hasta que se devuelva con la funcion volver ademas para prestar un libro tambien se manejan las fechas de prestamo y de devolucion "si hay", si no hay fecha de devolucion exacta el codigo deja seguir, para lograr todo esto la mayoria de las restricciones se manejaron con if, el devolver basicamente borra los datos del usuario que tomo el libro y vuelve a dejar el libro como disponible, asi funcionan todas las funciones del menu pero dentro del codigo se encuentran muchas otras variables como los void:

    void agregarUsuario(const Usuario& nuevoUsuario);    //USUARIOS
    Usuario*buscarusuarios(const string& nombre);        //USUARIOS
    void mostrarUsuarios() const;                         //USUARIOS

    void agregarAutor(const Autor& nuevoAutor);              //Autor
    Autor*buscarAutor(const string& nombre);                 //Autor
    void mostrarAutor() const;                                //Autor

    void agregarLibro(const Libro& nuevoLibro);   // Promesa de agregar un libro

    void mostrarInventario();    // Promesa de mostrar inventario

    Libro* buscarLibro(const std::string& tituloBuscado);

    void prestarLibro(const std::string& tituloPrestamo);    // Promesa de prestamo de libro

    void devolverLibro(const std::string& tituloDevolucion);    // Promesa de devolver libro

    void guardarLibros();  //Para cumplir el requisito de la fase 3 (Persistencia: Guarda/carga datos en archivos .txt (usa fstream para leer/escribir en formato CSV simple).)
    void guardarAutores();
    void guardarPrestamos();
    void guardarUsuarios();

    void cargarDatos();    //Carga todos los datos de libro, autores, prestamos y usuarios

Todos esos void tienen una definicion particular hecha para una tarea especifica el de los usuarios tiene por objetivo manejar solo esa informacion al igual que el autor y libros, ademas se tiene tambien los void de guardar y cargar datos, ya que los void tambien escriben datos en archivos txt donde guardan la informacion pero tambien la retoman para llevar un mejor control, cada uno de estos void esta definido en el codigo y con una respuesta singular y puntual para lo que se necesite de cada uno de estos.

Por ultimo, los struct, con los struct se logro manejar la informacion como clases pero a la vez almacenarlo como estructuras de datos para un manejo mas sencillo, en esta parte se definieron 4 struct (autor, libro, prestamo y usuario), cada uno con sus caracteristicas individuales definidas por variables ya sean int, string o bool, todo esto junto ha logrado el funcionamiento del codigo, desde el main que nos da la interaccion con el usuario hasta los void que nos definen nuestras funciones.


README (Simplificado).

# Reto 3 Biblioteca Virtual:

Codigo de Biblioteca para institucion educativa o biblioteca publica/privada.

# Como compila y ejecuta:

# Compilar:
En el bash vamos a poner:
g++ -o biblioteca Reto3_Fase3.cpp -std=c++11

# Ejecutar:
Para ejecutarlo dependiendo de nuestro tipo de procesador vamos a usar:
./biblioteca        # Linux/macOS
biblioteca.exe      # Windows

Para uso del menu este trae diversas opciones, para que el usuario escoja la que quiera.

    Menú de Opciones
        Añadir libro
        Mostrar inventario
        Prestar libro
        Devolver libro
        Añadir usuario
        Mostrar usuarios
        Añadir autor
        Mostrar autores
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