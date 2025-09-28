#include <iostream>
#include <string>
#include <vector>
#include <fstream>
#include <cctype>
#include <algorithm>
#include <ctime> //Para controlar el tiempo
#include <sstream>

using namespace std;

struct Autor {    // Clase Autor que habia designado en mi mapa, que tienen los elementos que dije
    int id_autor;
    string nombre;
    string nacionalidad;

    void mostrar_autor() const {
        cout << "------------------------------" << endl;
        cout << "Id: " << id_autor << endl;
        cout << "Nombre: " << nombre << endl;
        cout << "Pais: " << nacionalidad << endl;
    }
};

struct Libro {  //Clase Libro que tiene lo que habia dicho
    int id_libro;
    string titulo;
    int id_autor;
    string genero;
    bool estaDisponible;
    int anioPublicacion;
    string usuario;

    Libro() : anioPublicacion(0), estaDisponible(true) {}

    void mostrarDetallesCompletos(const vector<Autor>& autores) const {
        cout << "---------------------------------" << endl;
        cout << "Id: " << id_libro << endl;
        cout << "Titulo: " << titulo << endl;
        cout << "Genero: " << genero << endl;
        cout << "Año de publicacion: " << anioPublicacion << endl;
        cout << "Disponibilidad: " << (estaDisponible ? "Disponible" : "No disponible") << endl;

        for (const auto& autor : autores) {
            if (autor.id_autor == id_autor) {
                cout << "Autor: " << autor.nombre << endl;
                break;
            }
        }
    }
};

int obtenerFechaActual() {    //Para manejar las fechas actuales
    time_t t = time(0);
    tm* now = localtime(&t);
    return (now->tm_year + 1900) * 10000 + (now->tm_mon + 1) * 100 + now->tm_mday;
}

struct Prestamo {     //Clase prestamo, para controlar mejor el movimiento
    int id_prestamo;
    int id_libro;
    int idUsuario;
    int fecha_prestamo;
    int fecha_devolucion;

    void mostrar_prestamo() const {
        cout << "------------------------------" << endl;
        cout << "Id: " << id_prestamo << endl;
        cout << "Id Usuario: " << idUsuario << endl;
        cout << "Fecha prestamo: " << fecha_prestamo << endl;
        cout << "Fecha devolucion: " << fecha_devolucion << endl;
    }
};

struct Usuario {    //Clase usuario para tener un mejor flujo de gente
    string nombre;
    string trabajo;
    int idUsuario;
    vector<Prestamo> prestamos;

    void mostrar() const {
        cout << "---------------------------------" << endl;
        cout << "Nombre: " << nombre << endl;
        cout << "Trabajo: " << trabajo << endl;
        cout << "ID: " << idUsuario << endl;
    }
};

class Biblioteca { // Cada cosa que contiene la bilbioteca
private:
    vector<Libro> coleccion;
    vector<Usuario> usuarios;
    vector<Autor> autores;
    vector<Prestamo> prestamos;

public:

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
};

void Biblioteca::cargarDatos() { //Carga de datos
    ifstream archivoLibros("libros.txt");       //Subir todo lo de los libros
    if (archivoLibros.is_open()) {
        string line;
        while (getline(archivoLibros, line)) {
            stringstream ss(line);
            Libro nuevoLibro;
            string id_libro, titulo, id_autor, genero, estaDisponible, anioPublicacion, usuario;
            getline(ss, id_libro, ',');
            getline(ss, titulo, ',');
            getline(ss, id_autor, ',');
            getline(ss, genero, ',');
            getline(ss, estaDisponible, ',');
            getline(ss, anioPublicacion, ',');
            getline(ss, usuario, ',');
            nuevoLibro.id_libro = stoi(id_libro);
            nuevoLibro.titulo = titulo;
            nuevoLibro.id_autor = stoi(id_autor);
            nuevoLibro.genero = genero;
            nuevoLibro.estaDisponible = (estaDisponible == "1");
            nuevoLibro.anioPublicacion = stoi(anioPublicacion);
            nuevoLibro.usuario = usuario;
            coleccion.push_back(nuevoLibro);
        }
        archivoLibros.close();
    }

    ifstream archivoAutores("autores.txt");    //Subir todo lo de autores
    if (archivoAutores.is_open()) {
        string line;
        while (getline(archivoAutores, line)) {
            stringstream ss(line);
            Autor nuevoAutor;
            string id_autor, nombre, nacionalidad;
            getline(ss, id_autor, ',');
            getline(ss, nombre, ',');
            getline(ss, nacionalidad, ',');
            nuevoAutor.id_autor = stoi(id_autor);
            nuevoAutor.nombre = nombre;
            nuevoAutor.nacionalidad = nacionalidad;
            autores.push_back(nuevoAutor);
        }
        archivoAutores.close();
    }

    ifstream archivoUsuarios("usuarios.txt");    //Usuarios toda la informacion
    if (archivoUsuarios.is_open()) {
        string line;
        while (getline(archivoUsuarios, line)) {
            stringstream ss(line);
            Usuario nuevoUsuario;
            string idUsuario, nombre, trabajo;
            getline(ss, idUsuario, ',');
            getline(ss, nombre, ',');
            getline(ss, trabajo, ',');
            nuevoUsuario.idUsuario = stoi(idUsuario);
            nuevoUsuario.nombre = nombre;
            nuevoUsuario.trabajo = trabajo;
            usuarios.push_back(nuevoUsuario);
        }
        archivoUsuarios.close();
    }

    ifstream archivoPrestamos("prestamos.txt");            //Prestamos cargar la informacion
    if (archivoPrestamos.is_open()) {
        string line;
        while (getline(archivoPrestamos, line)) {
            stringstream ss(line);
            Prestamo nuevoPrestamo;
            string id_prestamo, id_libro, idUsuario, fecha_prestamo, fecha_devolucion;
            getline(ss, id_prestamo, ',');
            getline(ss, id_libro, ',');
            getline(ss, idUsuario, ',');
            getline(ss, fecha_prestamo, ',');
            getline(ss, fecha_devolucion, ',');
            nuevoPrestamo.id_prestamo = stoi(id_prestamo);
            nuevoPrestamo.id_libro = stoi(id_libro);
            nuevoPrestamo.idUsuario = stoi(idUsuario);
            nuevoPrestamo.fecha_prestamo = stoi(fecha_prestamo);
            nuevoPrestamo.fecha_devolucion = stoi(fecha_devolucion);
            prestamos.push_back(nuevoPrestamo);
        }
        archivoPrestamos.close();
    }
}

// Paso de definiciones:
string toLowerCase(const string& str) {
    string lowerStr = str;
    for (char& c : lowerStr) {
        c = tolower(c);
    }
    return lowerStr;
}

void Biblioteca::agregarUsuario(const Usuario& nuevoUsuario) {    //Para meter usuarios
    for (Usuario& usuario : usuarios) { //Para Buscar si ya existe el usuario que queria crear
        if (usuario.nombre == nuevoUsuario.nombre or usuario.idUsuario == nuevoUsuario.idUsuario) {
            cout << "Ya esta registrado" << endl; // Si ya existe
            return;
        }
    }
    usuarios.push_back(nuevoUsuario); //Si no existe agregarlo.
    cout << "Usuario registrado" << endl;
}

Usuario* Biblioteca::buscarusuarios(const string& nombre) {      //Para buscar la gente
    for (auto& usuario : usuarios) {
        if (toLowerCase(usuario.nombre) == toLowerCase(nombre)) {
            return &usuario;
        }
    }
    return nullptr;
}

void Biblioteca::mostrarUsuarios() const { // Para mostrar los usuarios
    if (usuarios.empty()) {
        cout << "No hay usuarios en la plataforma." << endl;
        return;
    }
    for (auto& u : usuarios) {
        u.mostrar();
    }
}

void Biblioteca::agregarAutor(const Autor& nuevoAutor) { //Meter mas autores
    for (const auto& autor : autores) {
        if (autor.id_autor == nuevoAutor.id_autor) {
            cout << "Este autor ya está registrado." << endl;  //Si ya estan registramos
            return;
        }
    }
    autores.push_back(nuevoAutor);
    cout << "Autor registrado" << endl; //Si no estaba y lo agregamos
}

void Biblioteca::mostrarAutor() const {     //Ensenamos los autores
    if (autores.empty()) {
        cout << "No hay autores registrados." << endl;
        return;
    }
    for (const auto& autor : autores) {
        autor.mostrar_autor();
    }
}

void Biblioteca::agregarLibro(const Libro& nuevoLibro) {// Definicion de la promesa de agregar los libros
    if (nuevoLibro.anioPublicacion <= 0 || nuevoLibro.anioPublicacion > 2025) {   //Validacion del anio como decia el feedback
        cout << "Anio no vaido, no se admiten numeros imaginarios, negativos ni mayores al anio actual" << endl;
        cout << "Libro no registrado, por anio invalido (el anio debe de estar entre 0 a 2025)" << endl;
        return;
    }
    for (Libro& libro : coleccion) {
        if (toLowerCase(libro.titulo) == toLowerCase(nuevoLibro.titulo)) {
            cout << "Este libro ya existe en el inventario." << endl;   //Si el libro que se queria agregar ya existe
            return;
        }
    }
    coleccion.push_back(nuevoLibro);
    cout << "Libro registrado " << endl;   //Si no existia y lo agregamos
}

void Biblioteca::mostrarInventario() { //Ensenamos los libros
    if (coleccion.empty()) {    //Chequeamos sino hay
        cout << "No hay libros" << endl;
        return;
    }
    for (Libro& libro : coleccion) {
        libro.mostrarDetallesCompletos(autores);    //Si hay los mostramos
    }
}

Libro* Biblioteca::buscarLibro(const std::string& tituloBuscado) {     //Busca libros
    string tituloBuscadoLower = toLowerCase(tituloBuscado);
    for (auto& l : coleccion) {
        if (toLowerCase(l.titulo) == tituloBuscadoLower) {
            return &l;
        }
    }
    return nullptr;
}

bool esRespuestaValida(const string& respuesta) {    //Para evitar problemas de mayusculas y minusculas validando respuestas, generalisamos y el codigo convierte todo a minusculas.
    string respuestaLower = toLowerCase(respuesta);
    return respuestaLower == "si" || respuestaLower == "no";
}

void Biblioteca::prestarLibro(const std::string &tituloPrestamo) {    //Si queremos un libro prestado
    Libro* libro = buscarLibro(tituloPrestamo);
    if (!libro) {
        cout << "No esta el libro en el inventario" << endl;    //Si el libro no existe
        return;
    }

    if (!libro->estaDisponible) {
        cout << "El libro no esta, intente mas tarde" << endl;  //Si fue prestado anteriormente
        return;
    }

    string nombreUsuario;
    cout << "Ingrese su usuario: ";     //Si el libro se encuentra registre su usuario para poder pedirlo prestado y que el chequeo lo indique como portador.
    cin >> nombreUsuario;

    Usuario* usuario = buscarusuarios(nombreUsuario);
    if (!usuario) {
        cout << "No lo encontramos" << endl;    //Si no tiene usuario
        return;
    }

    if (usuario->prestamos.size() >= 1) {
        cout << "No puede tener más de 1 libro prestado." << endl;     //Limite de libros a prestar
        return;
    }

    string respuesta;
    cout << "El libro está disponible, quiere prestarlo? (si/no): ";    //Confirmacion
    cin >> respuesta;

    if (respuesta != "si" && respuesta != "no") {
        cout << "Respuesta inválida." << endl;    //Validacion
        return;
    }

    if (toLowerCase(respuesta) == "si") {
        Prestamo nuevoPrestamo;
        nuevoPrestamo.id_libro = libro->id_libro;
        nuevoPrestamo.idUsuario = usuario->idUsuario;
        nuevoPrestamo.fecha_prestamo = obtenerFechaActual() ;
        nuevoPrestamo.fecha_devolucion = 0;

        prestamos.push_back(nuevoPrestamo);

        libro->estaDisponible = false;
        libro->usuario = nombreUsuario;
        usuario->prestamos.push_back(nuevoPrestamo);

        cout << "Disfruta de tu libro " << libro->titulo << endl;   //Finalizacion
    } else {
        cout << "Cancelamos su préstamo" << endl;   //Cancelacion
    }
}

void Biblioteca::devolverLibro(const std::string& tituloDevolucion) {     //Cuando terminaron el libro o ya no lo quieren
    Libro* libro = buscarLibro(tituloDevolucion);
    if (!libro) {
        cout << "Este libro no existe" << endl;    //No existe el libro en nuestro sistema
        return;
    }

    if (libro->estaDisponible) {
        cout << "Este libro está en el inventario, no ha sido prestado." << endl;    //Si el libro nunca salio
        return;
    }

    string nombreUsuario;
    cout << "Ingrese su nombre de usuario para devolver el libro: ";    //Datos para poder limpiar el historial
    cin >> nombreUsuario;

    Usuario* usuario = buscarusuarios(nombreUsuario);
    if (!usuario) {
        cout << "Usuario no registrado" << endl;    //Error con el usuario que pidio el libro por falta de credenciales
        return;
    }

    auto it = find_if(usuario->prestamos.begin(), usuario->prestamos.end(),    //Encontrar el libro conectado con el usuario para poder devolverlo.
                      [&libro, &usuario](const Prestamo& prestamo) {
                          return prestamo.id_libro == libro->id_libro && prestamo.idUsuario == usuario->idUsuario;
                      });

    if (it != usuario->prestamos.end()) {
        if (it->fecha_devolucion == 0) {
            it->fecha_devolucion = obtenerFechaActual();
        } else {
            cout << "El libro ya ha sido devuelto previamente." << endl;   //Si el libro ya habia sido devuelto
            return;
        }

        usuario->prestamos.erase(it);
        libro->estaDisponible = true;
        libro->usuario = "";

        cout << "Libro devuelto." << endl;    //Confirmacion de proceso hecho
    } else {
        cout << "El libro no estaba registrado en este usuario" << endl; //Si se equivoco de usuario
    }
}

void Biblioteca::guardarLibros() {       //Guardar los libros en archivos txt
    ofstream archivo("libros.txt");
    if (archivo.is_open()) {
        for (const auto& libro : coleccion) {
            archivo << libro.id_libro << ","
                    << libro.titulo << ","
                    << libro.id_autor << ","
                    << libro.genero << ","
                    << libro.estaDisponible << ","
                    << libro.anioPublicacion << ","
                    << libro.usuario << endl;
        }
        archivo.close();
        cout << "Libros guardados" << endl;
    } else {
        cout << "Error" << endl;
    }
}

void Biblioteca::guardarAutores() {          //Guardar los autores en un txt
    ofstream archivo("autores.txt");
    if (archivo.is_open()) {
        for (const auto& autor : autores) {
            archivo << autor.id_autor << ","
                    << autor.nombre << ","
                    << autor.nacionalidad << endl;
        }
        archivo.close();
        cout << "Guardado autores" << endl;
    } else {
        cout << "Error" << endl;
    }
}

void Biblioteca::guardarUsuarios() {           //Guardar los usuarios en txt
    ofstream archivo("usuarios.txt");
    if (archivo.is_open()) {
        for (const auto& usuario : usuarios) {
            archivo << usuario.idUsuario << ","
                    << usuario.nombre << ","
                    << usuario.trabajo << endl;
        }
        archivo.close();
        cout << "Guardado" << endl;
    } else {
        cout << "Error" << endl;
    }
}

void Biblioteca::guardarPrestamos() {      //Guardar los prestamos en txt
    ofstream archivo("prestamos.txt");
    if (archivo.is_open()) {
        for (const auto& prestamo : prestamos) {
            archivo << prestamo.id_prestamo << ","
                    << prestamo.id_libro << ","
                    << prestamo.idUsuario << ","
                    << prestamo.fecha_prestamo << ","
                    << prestamo.fecha_devolucion << endl;
        }
        archivo.close();
        cout << "Guardado" << endl;
    } else {
        cout << "Error" << endl;
    }
}

int main() {
    Biblioteca miBiblioteca;

    miBiblioteca.cargarDatos();

    string opcion;

    Libro libroInicial;
    libroInicial.titulo = "El Hobbit";
    libroInicial.id_libro = 1;
    libroInicial.id_autor = 1;
    libroInicial.genero = "Novela/Fantasia";
    libroInicial.anioPublicacion = 1937;
    libroInicial.estaDisponible = true;
    miBiblioteca.agregarLibro(libroInicial);

    Usuario usuarioInicial;
    usuarioInicial.nombre = "Diego Carpio";
    usuarioInicial.trabajo = "Ingeniero Industrial";
    usuarioInicial.idUsuario = 000011;
    miBiblioteca.agregarUsuario(usuarioInicial);

    Autor autorInicial;
    autorInicial.id_autor = 1;
    autorInicial.nombre = "J.R.R. Tolkien";
    autorInicial.nacionalidad = "Inglaterra";
    miBiblioteca.agregarAutor(autorInicial);

    while (opcion != "9") {
        cout << "-----------------------------------------------" << endl;
        cout << "1. Añadir libro" << endl;
        cout << "2. Mostrar inventario" << endl;
        cout << "3. Prestar libro" << endl;
        cout << "4. Devolver libro" << endl;
        cout << "5. Añadir usuario" << endl;
        cout << "6. Mostrar usuarios" << endl;
        cout << "7. Añadir autor" << endl;
        cout << "8. Mostrar autores" << endl;
        cout << "9. Salir" << endl;
        cout << "Seleccione una opción: ";
        cin >> opcion;

        switch (opcion[0]) {
            case '1': {
                string libro_nuevo, autor_libro, genero_libro;
                int anioPublicacion, idAutor;
                Libro nuevo;

                cin.ignore();
                cout << "Título: ";
                getline(cin, libro_nuevo);
                cout << "ID del Autor: ";
                cin >> idAutor;
                cout << "Género: ";
                cin.ignore();
                getline(cin, genero_libro);
                cout << "Año: ";
                cin >> anioPublicacion;

                nuevo.titulo = libro_nuevo;
                nuevo.id_autor = idAutor;
                nuevo.genero = genero_libro;
                nuevo.anioPublicacion = anioPublicacion;

                miBiblioteca.agregarLibro(nuevo);
                break;
            }

            case '2':
                miBiblioteca.mostrarInventario();
                break;

            case '3': {
                string titulo;
                cin.ignore();
                cout << "Título del libro que desea prestar: ";
                getline(cin, titulo);
                miBiblioteca.prestarLibro(titulo);
                break;
            }

            case '4': {
                string devolver;
                cin.ignore();
                cout << "Qué libro desea devolver: ";
                getline(cin, devolver);
                miBiblioteca.devolverLibro(devolver);
                break;
            }

            case '5': {
                string name, job;
                int id;

                Usuario reciente;
                cin.ignore();
                cout << "Nombre: ";
                getline(cin, name);
                cout << "Trabajo: ";
                getline(cin, job);
                cout << "ID: ";
                cin >> id;

                reciente.nombre = name;
                reciente.trabajo = job;
                reciente.idUsuario = id;
                miBiblioteca.agregarUsuario(reciente);
                break;
            }

            case '6': {
                miBiblioteca.mostrarUsuarios();
                break;
            }

            case '7': {
                string nombreAutor, paisAutor;
                int idAutor;
                Autor nuevoAutor;

                cin.ignore();
                cout << "Nombre del autor: ";
                getline(cin, nombreAutor);
                cout << "País del autor: ";
                getline(cin, paisAutor);
                cout << "ID del autor: ";
                cin >> idAutor;

                nuevoAutor.id_autor = idAutor;
                nuevoAutor.nombre = nombreAutor;
                nuevoAutor.nacionalidad = paisAutor;
                miBiblioteca.agregarAutor(nuevoAutor);
                break;
            }

            case '8': {
                miBiblioteca.mostrarAutor();
                break;
            }

            case '9':
                cout << "Gracias por venir" << endl;
                break;

            default:
                cout << "Opcion no valida" << endl;
        }
    }
    return 0;
}