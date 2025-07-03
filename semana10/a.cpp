// Patrones de diseño I

#include <iostream>
#include <vector>
using namespace std;

//EJEMPLO 1 - PATRÓN SINGLETON

// Representa una red con un archivo estático y un método estático para accederlo
struct red {
    static int archivo;  // Variable compartida entre todas las instancias
    string usuario;

    red(string usr) : usuario(usr) {}

    static int get() {
        return archivo;
    }
};

int red::archivo = 3;

// Clase Singleton: solo permite una única instancia
class Singleton {
private:
    static Singleton* instance; // Apuntador a la única instancia

    // Constructor privado
    Singleton() {}

public:
    // Método estático que devuelve la instancia única
    static Singleton* getInstance() {
        if (instance == nullptr) {
            instance = new Singleton();
        }
        return instance;
    }
};

Singleton* Singleton::instance = nullptr;


// EJERCICIO 1 - SINGLETON DE SESIÓN

class Sesion {
public:
    static Sesion* get() {
        if (instancia == nullptr) {
            int pw;
            cout << "Ingrese su contraseña: ";
            cin >> pw;
            instancia = new Sesion(); // Solo se crea una vez
        }
        return instancia;
    }

    void view() {
        cout << "Ingresando a la aplicacion...\n";
    }

private:
    static Sesion* instancia;
    Sesion() {} // Constructor privado
};

Sesion* Sesion::instancia = nullptr;


// EJERCICIO 2 - ABSTRACT FACTORY

// Interfaces de cámaras y botones
class Camara {
public:
    virtual void capturar() = 0;
};

class CamaraWindows : public Camara {
public:
    void capturar() override {
        cout << "Capturando imagen desde Windows..." << endl;
    }
};

class CamaraLinux : public Camara {
public:
    void capturar() override {
        cout << "Capturando imagen desde Linux..." << endl;
    }
};

class Boton {
public:
    virtual void grabar() = 0;
};

class BotonWindows : public Boton {
public:
    void grabar() override {
        cout << "Grabando imagen desde Windows..." << endl;
    }
};

class BotonLinux : public Boton {
public:
    void grabar() override {
        cout << "Grabando imagen desde Linux..." << endl;
    }
};

// Fábrica abstracta
class AppFactory {
public:
    virtual Camara* crearCamara() = 0;
    virtual Boton* crearBoton() = 0;
};

// Fábricas concretas para cada sistema operativo
class WindowsFactory : public AppFactory {
public:
    Camara* crearCamara() override {
        return new CamaraWindows();
    }

    Boton* crearBoton() override {
        return new BotonWindows();
    }
};

class LinuxFactory : public AppFactory {
public:
    Camara* crearCamara() override {
        return new CamaraLinux();
    }

    Boton* crearBoton() override {
        return new BotonLinux();
    }
};

// Aplicación que usa la fábrica
class App {
private:
    AppFactory* factory;

public:
    App(AppFactory* f) : factory(move(f)) {}

    void crearApp() {
        auto camara = factory->crearCamara();
        auto boton = factory->crearBoton();
        camara->capturar();
        boton->grabar();
    }
};


// SQLQueryBuilder - PATRÓN BUILDER

// Builder para construir una consulta SQL paso a paso
class SQLQueryBuilder {
private:
    string query;
    string tabla;
    vector<string> columnas;
    string filtro_columna;
    string filtro_valor;
    string orden;
    int limite = -1;

public:
    SQLQueryBuilder& setTable(string table) {
        tabla = table;
        return *this;
    }

    SQLQueryBuilder& addColumn(string columna) {
        columnas.push_back(columna);
        return *this;
    }

    SQLQueryBuilder& setWhereClause(string columna, string valor) {
        filtro_columna = columna;
        filtro_valor = valor;
        return *this;
    }

    SQLQueryBuilder& setOrderByClause(string orden) {
        this->orden = orden;
        return *this;
    }

    SQLQueryBuilder& setLimit(int limit) {
        this->limite = limit;
        return *this;
    }

    string build() {
        query = "SELECT ";
        for (int i = 0; i < columnas.size(); i++) {
            query += columnas[i];
            if (i != columnas.size() - 1)
                query += ", ";
        }

        query += " FROM " + tabla;

        if (!filtro_columna.empty())
            query += " WHERE " + filtro_columna + " = '" + filtro_valor + "'";

        if (!orden.empty())
            query += " ORDER BY " + orden;

        if (limite != -1)
            query += " LIMIT " + to_string(limite);

        return query;
    }
};


int main() {
    try {
        // Crear consulta usando SQLQueryBuilder (Builder)
        string query = SQLQueryBuilder()
            .setTable("empleados")
            .addColumn("id")
            .addColumn("posicion")
            .setWhereClause("position", "Analista")
            .setOrderByClause("nombre ASC")
            .setLimit(10)
            .addColumn("nombre")
            .build();

        cout << query << std::endl;
    }
    catch (const std::exception& e) {
        cerr << "Error al construir la consulta: " << e.what() << std::endl;
    }

    /*
    // Abstract Factory
    AppFactory* factory;
    #ifdef _WIN32
    factory = new WindowsFactory();
    #else
    factory = new LinuxFactory();
    #endif
    App app(factory);
    app.crearApp();
    */

    /*
    // Sesión (Singleton personalizado)
    Sesion* s1 = Sesion::get();
    s1->view();
    Sesion* s2 = Sesion::get();
    s2->view();
    */

    /*
    // Singleton tradicional
    Singleton* instance1 = Singleton::getInstance();
    Singleton* instance2 = Singleton::getInstance();
    cout << "instance1 = " << instance1 << endl;
    cout << "instance2 = " << instance2 << endl;
    */

    /*
    // Uso de struct red con variable estática
    red user1("usr1");
    red user2("usr2");
    cout << user1.archivo << endl;
    cout << user2.archivo << endl;
    cout << red::get() << endl;
    */

    return 0;
}
