// PATRONES DE DISEÑO II

#include <iostream>
#include <vector>
using namespace std;

// Patrón Iterator

// Representa una canción con titulo y artista
struct Cancion {
    string titulo, artista;
    Cancion(string t, string a)
        : titulo(t), artista(a) {}
};

// Iterador generico para recorrer un vector<T>
template<typename T>
class Iterador {
private:
    vector<T> db;   // copia del contenedor a iterar
    int indice;     // posición actual del iterador

public:
    Iterador(vector<T> _db)
        : db(_db), indice(0) {}       // inicializa con índice 0

    T operator*() {                   // devuelve el elemento actual
        return db[indice];
    }

    void siguiente() {                // avanza al siguiente elemento
        indice++;
    }

    bool final() {                    // indica si aún quedan elementos
        return indice < (int)db.size();
    }
};

// Iterador inverso (no implementado aqui D:)
template<typename T>
class IteradorInv {};


/*
// Clase Reproductor que usa el patrón Iterator

template<typename T>
class Reproductor {
private:
    vector<T> lista_de_canciones;    // almacena las canciones

public:
    void agregarCancion(T c) {        // añade canción al final
        lista_de_canciones.push_back(c);
    }

    Iterador<T> inicio() {            // crea iterador al inicio
        return Iterador<T>(lista_de_canciones);
    }

    IteradorInv<T> inicioInv() {      // crea iterador inverso (no implementado D:)
        return IteradorInv<T>(lista_de_canciones);
    }
};
*/


/*
// Patrón Memento

// Guarda el estado de un objeto (nivel y posicion)
class Memento {
private:
    int nivel, X, Y;

public:
    Memento(const int& niv, int posicionX, int posicionY)
        : nivel(niv), X(posicionX), Y(posicionY) {}

    int getNivel() const        { return nivel; }
    int getPosicionX() const    { return X; }
    int getPosicionY() const    { return Y; }
};

// Personaje que puede guardar y restaurar estados
class Personaje {
private:
    string nombre;
    int nivel, x, y;
    vector<Memento*> mementos;  // historial de estados

public:
    Personaje(const string& nombre)
        : nombre(nombre), nivel(1), x(0), y(0) {}

    // Muestra el estado actual
    void info() {
        cout << "Nivel: " << nivel
             << ", Pos=(" << x << ", " << y << ")" << endl;
    }

    // Lista todos los estados guardados y permite elegir uno
    void restaurarEstado() {
        cout << "--------------------------------\n";
        for (int i = 0; i < (int)mementos.size(); i++) {
            cout << "Estado " << i+1 << ":\n"
                 << " - Nivel: " << mementos[i]->getNivel() << "\n"
                 << " - Pos: (" << mementos[i]->getPosicionX()
                 << ", " << mementos[i]->getPosicionY() << ")\n";
        }
        int op;
        cout << "Elige un estado: ";
        cin >> op;
        nivel = mementos[op-1]->getNivel();
        x     = mementos[op-1]->getPosicionX();
        y     = mementos[op-1]->getPosicionY();
    }

    // Genera un nuevo estado aleatorio y lo guarda
    void guardarEstado() {
        nivel += rand() % 3;
        x     += rand() % 3;
        y     += rand() % 3;
        cout << "Guardo Estado: Nivel " << nivel
             << ", Pos=(" << x << ", " << y << ")\n";
        mementos.push_back(new Memento(nivel, x, y));
    }
};
*/


// Patrón Observer: usuarios y seguidores

// Interfaz común para observadores
class Observer {
public:
    virtual void noticar(const string& historia,
                         const string& usuario) = 0;
};

// Observador concreto: Seguidor que ve las historias
class Seguidor : public Observer {
private:
    string nombre;  // nombre del seguidor

public:
    Seguidor(const string& nombre)
        : nombre(nombre) {}

    // Recibe notificaciones con la historia y el usuario origen
    void noticar(const string& historia,
                 const string& usuario) override {
        cout << nombre << " - Nueva historia de "
             << usuario << ": " << historia << endl;
    }
};

// Observador concreto: Externo que no ve historias
class Externo : public Observer {
private:
    string nombre;  // nombre del externo

public:
    Externo(const string& nombre)
        : nombre(nombre) {}

    // Se notifica pero indica que no hay nueva historia
    void noticar(const string& historia,
                 const string& usuario) override {
        cout << nombre
             << " - No hay nueva historia de " << usuario
             << endl;
    }
};

// Sujeto observado: Usuario que publica historias
class Usuario {
private:
    string nombre;                     // nombre del usuario
    vector<Observer*> observadores;    // lista de sus observadores

public:
    Usuario(const string& nombre)
        : nombre(nombre) {}

    // Añade un observador (seguidores o externos)
    void agregarObservador(Observer* observador) {
        observadores.push_back(observador);
    }

    // Notifica a todos los observadores con la nueva historia
    void notificarSeguidores(const string& historia) {
        for (Observer* obs : observadores) {
            obs->noticar(historia, nombre);
        }
    }

    // Elimina un observador de la lista (opcional)
    void eliminarObservador(Observer* observador) {
        // Buscar y quitar de "observadores" (no implementado aquí D:)
    }
};

int main() {
    // Creamos un usuario que publicara historias
    Usuario usuario("Usuario1");

    // Creamos observadores de distintos tipos
    Seguidor seguidor1("Seguidor1");
    Seguidor seguidor2("Seguidor2");
    Externo externo1("Externo1");

    // Registramos a los observadores en el usuario
    usuario.agregarObservador(&seguidor1);
    usuario.agregarObservador(&seguidor2);
    usuario.agregarObservador(&externo1);

    // Publicamos una nueva historia y notificamos
    string nuevaHistoria = "Hoy estoy de viaje!";
    usuario.notificarSeguidores(nuevaHistoria);

    /*
    Ejemplo de uso del Patrón Memento
    Personaje pj("Heroe");
    pj.guardarEstado();
    pj.guardarEstado();
    pj.restaurarEstado();
    pj.info();
    */

    /*
    Ejemplo de uso del Patrón Iterator
    Reproductor<Cancion> reproductor;
    reproductor.agregarCancion(Cancion("C1","A1"));
    reproductor.agregarCancion(Cancion("C2","A2"));
    Iterador<Cancion> it = reproductor.inicio();
    while (it.final()) {
        Cancion c = *it;
        cout << "Reproduciendo: " << c.titulo
             << " - " << c.artista << endl;
        it.siguiente();
    }
    */

    return 0;
}