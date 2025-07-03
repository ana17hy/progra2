// PATRONES DE DISEÑO I

#include <iostream>
#include <vector>
using namespace std;

// Ejemplo 1: Miembros estaticos y Singleton

// Estructura "red" que muestra uso de un miembro estatico
struct red {
    static int archivo;      // variable compartida por todas las instancias
    string usuario;          // nombre de usuario de cada instancia

    red(string usr)           // constructor guarda el nombre de usuario
        : usuario(usr) {}

    static int get() {        // metodo estatico para acceder a "archivo"
        // no se puede usar "usuario" aqui porque es estatico
        return archivo;
    }
};
int red::archivo = 3;         // inicializacion del miembro estático

// Clase Singleton que solo crea una instancia única
class Singleton {
private:
    static Singleton* instance;  // puntero a la unica instancia

    Singleton() {}               // constructor privado para prevenir instancias externas

public:
    // Devuelve la única instancia; la crea si aún no existe
    static Singleton* getInstance() {
        if (instance == nullptr) {
            // primera vez que se llama: creamos la instancia
            instance = new Singleton();
        }
        return instance;
    }
};
Singleton* Singleton::instance = nullptr;  // inicializacion del puntero a nullptr


// Ejercicio 1: Patrón Singleton para Sesión

class Sesion {
private:
    static Sesion* instancia;   // puntero a la única Sesion

    Sesion() {}                 // constructor privado para forzar uso de get()

public:
    // Crea o devuelve la única instancia de Sesion
    static Sesion* get() {
        if (instancia == nullptr) {
            int pw;
            cout << "Ingrese su contraseña: ";
            cin >> pw;               // simulacion de autenticacion
            instancia = new Sesion();
        }
        return instancia;
    }
    // Muestra mensaje de ingreso
    void view() {
        cout << "Ingresando a la aplicacion...\n";
    }
};
Sesion* Sesion::instancia = nullptr;  // inicializacion del puntero

// Ejercicio 2: Factory Method (camara y boton)

// Interfaz abstracta para Cámara
class Camara {
public:
    virtual void capturar() = 0;  // metodo puro implementado en derivadas
};
class CamaraWindows : public Camara {
public:
    void capturar() override {
        cout << "Capturando imagen desde Windows...\n";
    }
};
class CamaraLinux : public Camara {
public:
    void capturar() override {
        cout << "Capturando imagen desde Linux...\n";
    }
};

// Interfaz abstracta para botón (grabacion)
class Boton {
public:
    virtual void grabar() = 0;    // metodo puro
};
class BotonWindows : public Boton {
public:
    void grabar() override {
        cout << "Grabando imagen desde Windows...\n";
    }
};
class BotonLinux : public Boton {
public:
    void grabar() override {
        cout << "Grabando imagen desde Linux...\n";
    }
};

// Fabrica abstracta que produce objetos camara y boton
class AppFactory {
public:
    virtual Camara* crearCamara() = 0;
    virtual Boton*  crearBoton()  = 0;
};
class WindowsFactory : public AppFactory {
public:
    Camara* crearCamara() override {
        return new CamaraWindows();    // crea camara Windows
    }
    Boton* crearBoton() override {
        return new BotonWindows();     // crea boton Windows
    }
};
class LinuxFactory : public AppFactory {
public:
    Camara* crearCamara() override {
        return new CamaraLinux();      // crea camara Linux
    }
    Boton* crearBoton() override {
        return new BotonLinux();       // crea boton Linux
    }
};

// Clase App que usa la fabrica para obtener y usar los objetos
class App {
private:
    AppFactory* factory;             // fabrica concreta inyectada

public:
    App(AppFactory* f)                // recibe la fábrica
        : factory(move(f)) {}

    void crearApp() {
        auto camara = factory->crearCamara();  // obtiene cámara según SO
        auto boton  = factory->crearBoton();   // obtiene botón según SO
        camara->capturar();                    // llama al método capturar
        boton->grabar();                       // llama al método grabar
    }
};

// SQLQueryBuilder: Construcción fluida de consultas SQL

class SQLQueryBuilder {
private:
    string query;                  // almacena la consulta final
    string tabla;                  // tabla objetivo
    vector<string> columnas;       // columnas a seleccionar
    string filtro_columna;         // columna para WHERE
    string filtro_valor;           // valor para WHERE
    string orden;                  // cláusula ORDER BY
    int limite = -1;               // cláusula LIMIT (-1 = sin límite)

public:
    // Asigna la tabla
    SQLQueryBuilder& setTable(string table) {
        tabla = table;
        return *this;              // devuelve referencia para encadenar
    }

    // Añade una columna al SELECT
    SQLQueryBuilder& addColumn(string columna) {
        columnas.push_back(columna);
        return *this;
    }

    // Define clausula WHERE: columna = 'valor'
    SQLQueryBuilder& setWhereClause(string columna, string valor) {
        filtro_columna = columna;
        filtro_valor  = valor;
        return *this;
    }

    // Define clausula ORDER BY
    SQLQueryBuilder& setOrderByClause(string orden) {
        this->orden = orden;
        return *this;
    }

    // Define clausula LIMIT
    SQLQueryBuilder& setLimit(int limit) {
        limite = limit;
        return *this;
    }

    // Ensambla la consulta y la devuelve
    string build() {
        query = "SELECT ";
        // Agrega las columnas separadas por comas
        for (int i = 0; i < (int)columnas.size(); ++i) {
            query += columnas[i];
            if (i + 1 < (int)columnas.size())
                query += ", ";
        }
        // Agrega la tabla
        query += " FROM " + tabla;
        // Agrega WHERE si se estableció filtro
        if (!filtro_columna.empty()) {
            query += " WHERE " + filtro_columna
                   + " = '" + filtro_valor + "'";
        }
        // Agrega ORDER BY si corresponde
        if (!orden.empty()) {
            query += " ORDER BY " + orden;
        }
        // Agrega LIMIT si es >= 0
        if (limite >= 0) {
            query += " LIMIT " + to_string(limite);
        }
        return query;  // devuelve la consulta completa
    }
};

int main() {
    try {
        // Construcción de ejemplo de una consulta SQL
        string query = SQLQueryBuilder()
            .setTable("empleados")                     // tabla: empleados
            .addColumn("id")                           // columna: id
            .addColumn("posicion")                     // columna: posicion
            .addColumn("nombre")                       // columna: nombre
            .setWhereClause("position", "Analista")    // WHERE position = 'Analista'
            .setOrderByClause("nombre ASC")            // ORDER BY nombre ASC
            .setLimit(10)                              // LIMIT 10
            .build();                                  // arma la consulta

        cout << query << endl;  // imprime la consulta resultante
    }
    catch (const std::exception& e) {
        // Manejo de errores al construir la consulta
        cerr << "Error al construir la consulta: "
             << e.what() << endl;
    }

    // Ejemplo 1: Uso de AppFactory para crear App según sistema operativo
    /*
    AppFactory* factory;
    #ifdef _WIN32
        factory = new WindowsFactory();
    #else
        factory = new LinuxFactory();
    #endif
    App app(factory);
    app.crearApp();
    */

    // Ejercicio 1: uso de Sesion (Singleton)
    /*
    Sesion* s1 = Sesion::get();
    s1->view();
    Sesion* s2 = Sesion::get();
    s2->view();
    */

    // Ejemplo 1: uso de Singleton y red
    /*
    Singleton* instance1 = Singleton::getInstance();
    Singleton* instance2 = Singleton::getInstance();
    cout << "instance1 = " << instance1 << endl;
    cout << "instance2 = " << instance2 << endl;

    red user1("usr1");
    red user2("usr2");
    cout << user1.archivo << endl;
    cout << user2.archivo << endl;
    cout << red::get() << endl;
    */

    return 0;
}
