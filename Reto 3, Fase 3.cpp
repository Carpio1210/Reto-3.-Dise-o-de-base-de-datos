#include <iostream>
#include <string>
#include <vector>
#include <fstream>
#include <cctype>
#include <algorithm>
#include <ctime> //Para controlar el tiempo
#include <sstream>

using namespace std;

// Clase Autor que habia designado en mi mapa, que tienen los elementos que dije

struct Autor {    
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

//Clase Libro que tiene lo que habia dicho

struct Libro {
    int id_libro;
    string titulo;
    string isbn;
    string nombreAutor;   //En este caso se implemento el nombre autor en vez del ID, porque es mas sencillo para el usuario que conozca un nombre especifico y no un id puntual de un autor.
    bool estaDisponible;
    int anioPublicacion;

    Libro() : anioPublicacion(0), estaDisponible(true) {}

    void mostrarDetallesCompletos() const {
        cout << "---------------------------------"<< endl;
        cout << "Id del libro: " << id_libro << endl;
        cout << "Titulo: " << titulo << endl;
        cout << "ISBN: " << isbn << endl;
        cout << "Anio de publicacion: " << anioPublicacion << endl;
        cout << "Autor: " << nombreAutor << endl;
        cout << "Disponibilidad: " << (estaDisponible ? "Disponible" : "No disponible") << endl;
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

struct Estudiante {    //Clase usuario para tener un mejor flujo de gente
    string nombre;
    string grado;
    int idUsuario;
    vector<Prestamo> prestamos;

    void mostrar() const {
        cout << "---------------------------------" << endl;
        cout << "Nombre: " << nombre << endl;
        cout << "Grado: " << grado << endl;
        cout << "ID: " << idUsuario << endl;
    }
};

class Biblioteca { // Cada cosa que contiene la bilbioteca
private:
    vector<Libro> coleccion;
    vector<Estudiante> usuarios;
    vector<Autor> autores;
    vector<Prestamo> prestamos;
public:
    int generarIdLibro() {
        if (coleccion.empty()) return 1;
        int maxId = 0;
        for (const auto& libro : coleccion) {
            if (libro.id_libro > maxId) maxId = libro.id_libro;
        }
        return maxId + 1;
    }

    int generarIdUsuario() {
        if (usuarios.empty()) return 1;
        int maxId = 0;
        for (const auto& usuario : usuarios) {
            if (usuario.idUsuario > maxId) maxId = usuario.idUsuario;
        }
        return maxId + 1;
    }

    int generarIdAutor() {
        if (autores.empty()) return 1;
        int maxId = 0;
        for (const auto& autor : autores) {
            if (autor.id_autor > maxId) maxId = autor.id_autor;
        }
        return maxId + 1;
    }


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
};

void Biblioteca::cargarDatos() { // Carga datos desde archivos .txt en forma de CSV
    ifstream archivoLibros("libros.txt");       // Cargar libros
    if (archivoLibros.is_open()) {
        string line;
        while (getline(archivoLibros, line)) {
            stringstream ss(line);
            Libro nuevoLibro;
            string temp;
            getline(ss, temp, ','); nuevoLibro.id_libro = stoi(temp);
            getline(ss, nuevoLibro.titulo, ',');
            getline(ss, nuevoLibro.isbn, ',');
            getline(ss, temp, ','); nuevoLibro.anioPublicacion = stoi(temp);
            getline(ss, nuevoLibro.nombreAutor, ',');
            getline(ss, temp, ','); nuevoLibro.estaDisponible = (temp == "1");
            coleccion.push_back(nuevoLibro);
        }
        archivoLibros.close();
    }

    ifstream archivoAutores("autores.txt");     // Cargar autores
    if (archivoAutores.is_open()) {
        string line;
        while (getline(archivoAutores, line)) {
            stringstream ss(line);
            Autor nuevoAutor;
            string temp;
            getline(ss, temp, ','); nuevoAutor.id_autor = stoi(temp);
            getline(ss, nuevoAutor.nombre, ',');
            getline(ss, nuevoAutor.nacionalidad, ',');
            autores.push_back(nuevoAutor);
        }
        archivoAutores.close();
    }

    ifstream archivoEstudiantes("estudiantes.txt"); // Cargar usuarios (usando struct Estudiante)
    if (archivoEstudiantes.is_open()) {
        string line;
        while (getline(archivoEstudiantes, line)) {
            stringstream ss(line);
            Estudiante nuevoUsuario;
            string temp;
            getline(ss, temp, ','); nuevoUsuario.idUsuario = stoi(temp);
            getline(ss, nuevoUsuario.nombre, ',');
            getline(ss, nuevoUsuario.grado, ',');
            usuarios.push_back(nuevoUsuario);
        }
        archivoEstudiantes.close();
    }

    ifstream archivoPrestamos("prestamos.txt");    // Cargar prestamos
    if (archivoPrestamos.is_open()) {
        string line;
        while (getline(archivoPrestamos, line)) {
            stringstream ss(line);
            Prestamo nuevoPrestamo;
            string temp;
            getline(ss, temp, ','); nuevoPrestamo.id_prestamo = stoi(temp);
            getline(ss, temp, ','); nuevoPrestamo.id_libro = stoi(temp);
            getline(ss, temp, ','); nuevoPrestamo.idUsuario = stoi(temp);
            getline(ss, temp, ','); nuevoPrestamo.fecha_prestamo = stoi(temp);
            getline(ss, temp, ','); nuevoPrestamo.fecha_devolucion = stoi(temp);
            prestamos.push_back(nuevoPrestamo);
        }
        archivoPrestamos.close();
    }

    for (const auto& p : prestamos) {
        for (auto& l : coleccion) {
            if (l.id_libro == p.id_libro) {
                if (p.fecha_devolucion == 0) {
                    l.estaDisponible = false;
                }
                break;
            }
        }
        for (auto& u : usuarios) {
            if (u.idUsuario == p.idUsuario) {
                if (p.fecha_devolucion == 0) u.prestamos.push_back(p);
                break;
            }
        }
    }
}


// Comienzo para definir mis promesas:
string toLowerCase(const string& str) {     //Para minisculas para no tener problemas con titulos
    string lowerStr = str;
    for (char& c : lowerStr) {
        c = tolower(c);
    }
    return lowerStr;
}

// Paso de definiciones:
void Biblioteca::actualizarUsuario(int idUsuario) {
    for (auto& usuario : usuarios) {
        if (usuario.idUsuario == idUsuario) {
            cout << "Actualizar usuario con ID: " << idUsuario << endl;
            cout << "Nuevo nombre: ";
            cin.ignore();
            getline(cin, usuario.nombre);
            cout << "Nuevo grado: ";
            getline(cin, usuario.grado);
            guardarUsuarios();
            cout << "Usuario actualizado!!" << endl;
            return;
        }
    }
    cout << "Usuario con ID: " << idUsuario << " ,no encontrado" << endl;
}

void Biblioteca::eliminarUsuario(int idUsuario) {
    auto it = remove_if(usuarios.begin(), usuarios.end(),
                        [idUsuario](const Estudiante& u) { return u.idUsuario == idUsuario; });
    if (it != usuarios.end()) {
        usuarios.erase(it, usuarios.end());
        auto prestamo_it = remove_if(prestamos.begin(), prestamos.end(),
                                    [idUsuario](const Prestamo& p) { return p.idUsuario == idUsuario; });
        prestamos.erase(prestamo_it, prestamos.end());
        guardarUsuarios();
        guardarPrestamos();
        cout << "Usuario con ID: " << idUsuario << " ,eliminado" << endl;
    } else {
        cout << "Usuario con ID: " << idUsuario << " ,no encontrado" << endl;
    }
}

void Biblioteca::agregarUsuario(const Estudiante& nuevoUsuario) {    //Para meter usuarios
    for (const auto& usuario : usuarios) { //Para Buscar si ya existe el usuario que queria crear
        if (usuario.nombre == nuevoUsuario.nombre or usuario.idUsuario == nuevoUsuario.idUsuario) {
            cout << "Ya existe este usuario" << endl; // Si ya existe
            return;
        }
    }
    usuarios.push_back(nuevoUsuario); //Si no existe agregarlo.
    guardarUsuarios();
    cout << "Usuario registrado" << endl;
}

void Biblioteca::actualizarAutor(int id_autor) {
    for (auto& autor : autores) {
        if (autor.id_autor == id_autor) {
            cout << "Actualizar autor con ID: " << id_autor << endl;
            cout << "Nuevo nombre: ";
            cin.ignore();
            getline(cin, autor.nombre);
            cout << "Nueva nacionalidad: ";
            getline(cin, autor.nacionalidad);
            guardarAutores();
            cout << "Autor actualizado!!!" << endl;
            return;
        }
    }
    cout << "Autor con ID: " << id_autor << " ,no encontrado" << endl;
}

void Biblioteca::mostrarAutoresConMasLibros() const {
    if (autores.empty() || coleccion.empty()) {
        cout << "No hay datos suficientes" << endl;
        return;
    }
    vector<pair<string,int>> conteo;
    conteo.reserve(autores.size());
    for (const auto& a : autores) conteo.push_back({a.nombre, 0});
    for (const auto& l : coleccion) {
        for (auto& par : conteo) {
            if (toLowerCase(l.nombreAutor) == toLowerCase(par.first)) {
                par.second++;
                break;
            }
        }
    }
    int maxc = 0;
    for (const auto& par : conteo) if (par.second > maxc) maxc = par.second;
    if (maxc == 0) {
        cout << "No hay libros asociados a los autores registrados." << endl;
        return;
    }
    cout << "El Autor con mas libros (" << maxc << "):" << endl;
    for (const auto& par : conteo) if (par.second == maxc) cout << par.first << endl;
}

void Biblioteca::eliminarAutor(int id_autor) {
    auto it = remove_if(autores.begin(), autores.end(),
                        [id_autor](const Autor& a) { return a.id_autor == id_autor; });
    if (it != autores.end()) {
        autores.erase(it, autores.end());
        guardarAutores();
        cout << "Autor con ID: " << id_autor << " ,eliminado" << endl;
    } else {
        cout << "Autor con ID: " << id_autor << " ,no encontrado" << endl;
    }
}

Estudiante* Biblioteca::buscarusuarios(const string& nombre) {      //Para buscar la gente osea los estudiantes
    for (auto& usuario : usuarios) {
        if (toLowerCase(usuario.nombre) == toLowerCase(nombre)) {
            return &usuario;
        }
    }
    return nullptr;
}

void Biblioteca::mostrarUsuarios() const { // Para mostrar los usuarios, estudiantes en el programa
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
            cout << "Este autor ya esta en la plataforma" << endl;  //Si ya estan registramos
            return;
        }
    }
    autores.push_back(nuevoAutor);
    guardarAutores();
    cout << "Autor registrado" << endl; //Si no estaba y lo agregamos
}

void Biblioteca::mostrarAutor() const {     //Ensenamos los autores
    if (autores.empty()) {
        cout << "No hay autores en la plataforma" << endl;
        return;
    }
    for (const auto& autor : autores) {
        autor.mostrar_autor();
    }
}

void Biblioteca::agregarLibro(const Libro& nuevoLibro) {          // Definicion de la promesa de agregar los libros
    int currentYear = obtenerFechaActual() / 10000;
    if (nuevoLibro.anioPublicacion <= 0 || nuevoLibro.anioPublicacion > currentYear) {   //Validacion del anio como decia el feedback
        cout << "Anio no vaido, no se admiten numeros imaginarios, negativos ni mayores al anio actual" << endl;
        cout << "Libro no registrado, por anio invalido (el anio debe de estar entre 0 a " << currentYear << ")" << endl;
        return;
    }
    if (nuevoLibro.titulo.empty() || nuevoLibro.isbn.empty() || nuevoLibro.nombreAutor.empty()) {
        cout << "Datos del libro incompletos" << endl;
        return;
    }
    for (const auto& libro : coleccion) {
        if (toLowerCase(libro.titulo) == toLowerCase(nuevoLibro.titulo) || libro.isbn == nuevoLibro.isbn) {
            cout << "Este libro ya existe en el inventario" << endl;   //Si el libro que se queria agregar ya existe
            return;
        }
    }
    coleccion.push_back(nuevoLibro);
    guardarLibros();
    cout << "Libro registrado " << endl;   //Si no existia y lo agregamos
}

void Biblioteca::mostrarInventario() { //Ensenamos los libros
    if (coleccion.empty()) {    //Chequeamos sino hay
        cout << "No hay libros" << endl;
        return;
    }
    for (const auto& libro : coleccion) {
        libro.mostrarDetallesCompletos();
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

void Biblioteca::mostrarPrestamosPorEstudiante(int idEstudiante) {
    bool estudianteEncontrado = false;
    bool tienePrestamos = false;

    for (const auto& usuario : usuarios) {
        if (usuario.idUsuario == idEstudiante) {
            estudianteEncontrado = true;
            cout << "Estudiante: " << usuario.nombre << " - " << usuario.grado << endl;

            for (const auto& prestamo : prestamos) {
                if (prestamo.idUsuario == idEstudiante) {
                    for (const auto& libro : coleccion) {
                        if (libro.id_libro == prestamo.id_libro) {
                            cout << "Libro: " << libro.titulo << endl;
                            cout << "ID Libro: " << libro.id_libro << endl;
                            cout << "Autor: " << libro.nombreAutor << endl;
                            cout << "Fecha prestamo: " << prestamo.fecha_prestamo << endl;

                            if (prestamo.fecha_devolucion == 0) {
                                cout << "Fecha devolucion: PENDIENTE" << endl;
                                cout << "Estado: PRESTADO ACTIVO" << endl;
                            } else {
                                cout << "Fecha devolucion: " << prestamo.fecha_devolucion << endl;
                                cout << "Estado: DEVUELTO" << endl;
                            }

                            cout << "---------------------------------" << endl;
                            tienePrestamos = true;
                            break;
                        }
                    }
                }
            }
            break;
        }
    }

    if (!estudianteEncontrado) {
        cout << "Error: No se encontro ningun estudiante con ID " << idEstudiante << endl;
        return;
    }

    if (!tienePrestamos) {
        cout << "Este estudiante no tiene prestamos registrados." << endl;
    }
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
    getline(cin, nombreUsuario);

    Estudiante* usuario = buscarusuarios(nombreUsuario);
    if (!usuario) {
        cout << "No lo encontramos" << endl;    //Si no tiene usuario
        return;
    }

    if (usuario->prestamos.size() >= 1) {
        cout << "No puedes tener mas de 1 libro prestado." << endl;     //Limite de libros a prestar
        return;
    }

    string respuesta;
    cout << "El libro esta disponible, quiere prestarlo? (si/no): ";    //Confirmacion
    cin >> respuesta;

    if (!esRespuestaValida(respuesta)) {
        cout << "Respuesta inválida." << endl;    //Validacion
        return;
    }

    if (toLowerCase(respuesta) == "si") {
        Prestamo nuevoPrestamo;
        int nextId = 1;
        for (const auto& p : prestamos) {
            if (p.id_prestamo >= nextId) nextId = p.id_prestamo + 1;
        }
        nuevoPrestamo.id_prestamo = nextId;
        nuevoPrestamo.id_libro = libro->id_libro;
        nuevoPrestamo.idUsuario = usuario->idUsuario;
        nuevoPrestamo.fecha_prestamo = obtenerFechaActual() ;
        nuevoPrestamo.fecha_devolucion = 0;

        prestamos.push_back(nuevoPrestamo);
        libro->estaDisponible = false;
        usuario->prestamos.push_back(nuevoPrestamo);

        guardarPrestamos();
        guardarLibros();
        guardarUsuarios();

        cout << "Disfruta de tu libro!!! " << libro->titulo << endl;   //Finalizacion
    } else
    {
        cout << "Cancelamos su prestamo, regrese pronto" << endl;   //Cancelacion
    }
}

void Biblioteca::devolverLibro(const std::string& tituloDevolucion) {     //Cuando terminaron el libro o ya no lo quieren
    Libro* libro = buscarLibro(tituloDevolucion);
    if (!libro) {
        cout << "Este libro no existe" << endl;    //No existe el libro en nuestro sistema
        return;
    }

    if (libro->estaDisponible) {
        cout << "Este libro si esta en el inventario, no ha sido prestado" << endl;    //Si el libro nunca salio
        return;
    }

    string nombreUsuario;
    cout << "Ingrese su nombre de usuario para devolver el libro: ";    //Datos para poder limpiar el historial
    getline(cin, nombreUsuario);

    Estudiante* usuario = buscarusuarios(nombreUsuario);
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

            auto itg = find_if(prestamos.begin(), prestamos.end(),   //actualiza el registro global
                               [&libro, &usuario](const Prestamo& p) {
                                   return p.id_libro == libro->id_libro && p.idUsuario == usuario->idUsuario && p.fecha_devolucion == 0;
                               });
            if (itg != prestamos.end()) {
                itg->fecha_devolucion = it->fecha_devolucion;
            }
        } else {
            cout << "El libro ya ha sido devuelto" << endl;   //Si el libro ya habia sido devuelto
            return;
        }

        usuario->prestamos.erase(it);
        libro->estaDisponible = true;

        guardarPrestamos();
        guardarLibros();
        guardarUsuarios();

        cout << "Libro devuelto" << endl;    //Confirmacion de proceso hecho
    } else

    {
        cout << "El libro no estaba registrado en este usuario" << endl; //Si se equivoco de usuario
    }
}

void Biblioteca::actualizarLibro(int id_libro) {
    for (auto& libro : coleccion) {
        if (libro.id_libro == id_libro) {
            cout << "Actulizar libro con ID: " << id_libro << endl;
            cout << "Nuevo titulo: ";
            cin.ignore();
            getline(cin, libro.titulo);
            cout << "Nuevo ISBN: ";
            getline(cin, libro.isbn);
            cout << "Nuevo anio de publicacion: ";
            cin >> libro.anioPublicacion;
            cout << "Nuevo nombre del autor: ";
            cin.ignore();
            getline(cin, libro.nombreAutor);
            guardarLibros();
            cout << "Libro actualizado!!!" << endl;
            return;
        }
    }
    cout << "Libro con ID: " << id_libro << " ,no encontrado" << endl;
}

void Biblioteca::eliminarLibro(int id_libro) {
    auto it = remove_if(coleccion.begin(), coleccion.end(),
                        [id_libro](const Libro& l) { return l.id_libro == id_libro; });
    if (it != coleccion.end()) {
        coleccion.erase(it, coleccion.end());
        auto prestamo_it = remove_if(prestamos.begin(), prestamos.end(),
                                    [id_libro](const Prestamo& p) { return p.id_libro == id_libro; });
        prestamos.erase(prestamo_it, prestamos.end());
        guardarLibros();
        guardarPrestamos();
        cout << "Libro con ID: " << id_libro << " ,eliminado" << endl;
    } else {
        cout << "Libro con ID: " << id_libro << " ,no encontrado" << endl;
    }
}

void Biblioteca::guardarLibros() {      //Guarda todo el void en un txt, en diferentes
    ofstream archivo("libros.txt");
    if (archivo.is_open()) {
        for (const auto& libro : coleccion) {
            archivo << libro.id_libro << ","
                    << libro.titulo << ","
                    << libro.isbn << ","
                    << libro.anioPublicacion << ","
                    << libro.nombreAutor << ","
                    << libro.estaDisponible << "\n";
        }
        archivo.close();
        cout << "Libros guardados" << endl;
    } else

    {
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
    } else
    {
        cout << "Error" << endl;
    }
}

void Biblioteca::guardarUsuarios() {           //Guardar los usuarios en txt
    ofstream archivo("estudiantes.txt");
    if (archivo.is_open()) {
        for (const auto& usuario : usuarios) {
            archivo << usuario.idUsuario << ","
                    << usuario.nombre << ","
                    << usuario.grado << "\n";
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
    } else

    {
        cout << "Error" << endl;
    }
}

int main() {
    Biblioteca miBiblioteca;
    miBiblioteca.cargarDatos();

    int opcion;

    Libro libroInicial;
    libroInicial.titulo = "El Hobbit";
    libroInicial.id_libro = 1;
    libroInicial.isbn = "454545454545455";
    libroInicial.nombreAutor = "J.R.R. Tolkien";
    libroInicial.anioPublicacion = 1937;
    libroInicial.estaDisponible = true;
    miBiblioteca.agregarLibro(libroInicial);

    Estudiante usuarioInicial;
    usuarioInicial.nombre = "Diego Carpio";
    usuarioInicial.grado = "Segundo año General";
    usuarioInicial.idUsuario = 11;
    miBiblioteca.agregarUsuario(usuarioInicial);

    Autor autorInicial;
    autorInicial.id_autor = 1;
    autorInicial.nombre = "J.R.R. Tolkien";
    autorInicial.nacionalidad = "Inglaterra";
    miBiblioteca.agregarAutor(autorInicial);

    while (true) {
        cout << "-----------------------------------------------" << endl;
        cout << "1. Agregar libro" << endl;
        cout << "2. Mostrar inventario" << endl;
        cout << "3. Prestar libro" << endl;
        cout << "4. Devolver libro" << endl;
        cout << "5. Buscar prestamo por estudiante" << endl;
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
        cout << "16. Autores con mas libros" << endl;
        cout << "17. Salir" << endl;
        cout << "Seleccione una opcion (1-17): ";

        if (!(cin >> opcion)) {
            cout << "Error: Por favor ingrese un numero valido." << endl;
            cin.clear();
            cin.ignore(10000, '\n');
            continue;
        }

        switch (opcion) {
            case 1: {
                string titulo, isbn, nombreAutor;
                int anioPublicacion;
                Libro nuevo;

                cin.ignore();
                cout << "Titulo del libro: ";
                getline(cin, titulo);
                cout << "ISBN: ";
                getline(cin, isbn);
                cout << "Nombre del Autor: ";
                getline(cin, nombreAutor);
                cout << "Anio de publicacion: ";
                cin >> anioPublicacion;

                nuevo.titulo = titulo;
                nuevo.isbn = isbn;
                nuevo.nombreAutor = nombreAutor;
                nuevo.anioPublicacion = anioPublicacion;
                nuevo.id_libro = miBiblioteca.generarIdLibro();

                miBiblioteca.agregarLibro(nuevo);
                break;
            }

            case 2:
                miBiblioteca.mostrarInventario();
                break;

            case 3: {
                string titulo;
                cin.ignore();
                cout << "Titulo del libro que desea prestar: ";
                getline(cin, titulo);
                miBiblioteca.prestarLibro(titulo);
                break;
            }

            case 4: {
                string titulo;
                cin.ignore();
                cout << "Que libro desea devolver: ";
                getline(cin, titulo);
                miBiblioteca.devolverLibro(titulo);
                break;
            }

            case 5: {
                int idEstudiante;
                cout << "ID del estudiante: ";
                cin >> idEstudiante;
                miBiblioteca.mostrarPrestamosPorEstudiante(idEstudiante);
                break;
            }

            case 6: {
                string nombre, grado;
                Estudiante nuevo;

                cin.ignore();
                cout << "Nombre del estudiante: ";
                getline(cin, nombre);
                cout << "Grado: ";
                getline(cin, grado);

                nuevo.nombre = nombre;
                nuevo.grado = grado;
                nuevo.idUsuario = miBiblioteca.generarIdUsuario();
                miBiblioteca.agregarUsuario(nuevo);
                break;
            }

            case 7:
                miBiblioteca.mostrarUsuarios();
                break;

            case 8: {
                string nombre, nacionalidad;
                Autor nuevo;

                cin.ignore();
                cout << "Nombre del autor: ";
                getline(cin, nombre);
                cout << "Nacionalidad: ";
                getline(cin, nacionalidad);

                nuevo.nombre = nombre;
                nuevo.nacionalidad = nacionalidad;
                nuevo.id_autor = miBiblioteca.generarIdAutor();
                miBiblioteca.agregarAutor(nuevo);
                break;
            }

            case 9:
                miBiblioteca.mostrarAutor();
                break;

            case 10: {
                int id;
                cout << "ID del libro a actualizar: ";
                cin >> id;
                miBiblioteca.actualizarLibro(id);
                break;
            }

            case 11: {
                int id;
                cout << "ID del libro a eliminar: ";
                cin >> id;
                miBiblioteca.eliminarLibro(id);
                break;
            }

            case 12: {
                int id;
                cout << "ID del autor a actualizar: ";
                cin >> id;
                miBiblioteca.actualizarAutor(id);
                break;
            }

            case 13: {
                int id;
                cout << "ID del autor a eliminar: ";
                cin >> id;
                miBiblioteca.eliminarAutor(id);
                break;
            }

            case 14: {
                int id;
                cout << "ID del usuario a actualizar: ";
                cin >> id;
                miBiblioteca.actualizarUsuario(id);
                break;
            }

            case 15: {
                int id;
                cout << "ID del usuario a eliminar: ";
                cin >> id;
                miBiblioteca.eliminarUsuario(id);
                break;
            }

            case 16:
                miBiblioteca.mostrarAutoresConMasLibros();
                break;

            case 17:
                miBiblioteca.guardarLibros();
                miBiblioteca.guardarAutores();
                miBiblioteca.guardarUsuarios();
                miBiblioteca.guardarPrestamos();
                cout << "Gracias por venir" << endl;
                return 0;

            default:
                cout << "Opcion no valida. Intente de nuevo." << endl;
                break;
        }

        cin.ignore(10000, '\n');
    }
    return 0;
}