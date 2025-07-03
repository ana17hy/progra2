// Patrones de diseño I

#include <iostream>
#include <vector>
#include <string>
#include <cstdlib> // para rand()
using namespace std;

// ========== PATRÓN OBSERVER ==========
// Observador base: cualquier clase que quiera "seguir" a un usuario
class Observer {
public:
    virtual void noticar(string historia, string usuario) = 0;
};

// Seguidor real: recibe historias
class Seguidor : public Observer {
private:
    string nombre;
public:
    Seguidor(const string& nombre) : nombre(nombre) {}
    void noticar(string historia, string usuario) override {
        cout << nombre << " - Nueva historia de " << usuario << ": " << historia << endl;
    }
};

// Observador externo: no recibe historias reales
class Externo : public Observer {
private:
    string nombre;
public:
    Externo(const string& nombre) : nombre(nombre) {}
    void noticar(string historia, string usuario) override {
        cout << nombre << " - No hay nueva historia de " << usuario << endl;
    }
};

// Usuario que publica historias
class Usuario {
private:
    string nombre;
    vector<Observer*> observadores;
public:
    Usuario(const string& nombre) : nombre(nombre) {}

    // Agrega seguidores al usuario
    void agregarObservador(Observer* observador) {
        observadores.push_back(observador);
    }

    // Notifica a todos los seguidores
    void notificarSeguidores(const string& historia) {
        for (Observer* obs : observadores)
            obs->noticar(historia, nombre);
    }
};

// ========== PATRÓN MEMENTO ==========
// Guarda un estado anterior del personaje
class Memento {
private:
    int nivel;
    int X;
    int Y;
public:
    Memento(const int& niv, int posicionX, int posicionY)
        : nivel(niv), X(posicionX), Y(posicionY) {}

    int getNivel() const { return nivel; }
    int getPosicionX() const { return X; }
    int getPosicionY() const { return Y; }
};

// Personaje que puede guardar y restaurar estados
class Personaje {
private:
    string nombre;
    int nivel;
    int x, y;
    vector<Memento*> mementos;
public:
    Personaje(const string& nombre) : nombre(nombre), nivel(1), x(0), y(0) {}

    void info() {
        cout << "Nivel actual: " << nivel << ", Posición=(" << x << ", " << y << ")\n";
    }

    void guardarEstado() {
        // Simula subir de nivel y moverse aleatoriamente
        nivel += rand() % 3;
        x += rand() % 3;
        y += rand() % 3;
        cout << "Guardo Estado: Nivel " << nivel << ", Pos=(" << x << ", " << y << ")\n";
        mementos.push_back(new Memento(nivel, x, y));
    }

    void restaurarEstado() {
        cout << "=== Estados guardados ===\n";
        for (int i = 0; i < mementos.size(); i++) {
            cout << "[" << i+1 << "] Nivel: " << mementos[i]->getNivel()
                 << ", Posición: (" << mementos[i]->getPosicionX()
                 << ", " << mementos[i]->getPosicionY() << ")\n";
        }
        int op;
        cout << "Elige un estado para restaurar (1-" << mementos.size() << "): ";
        cin >> op;
        nivel = mementos[op - 1]->getNivel();
        x = mementos[op - 1]->getPosicionX();
        y = mementos[op - 1]->getPosicionY();
    }
};

// ========== PATRÓN ITERATOR ==========
// Una canción cualquiera
struct Cancion {
    string titulo, artista;
    Cancion(string t, string a) : titulo(t), artista(a) {}
};

// Iterador para recorrer canciones
template<typename T>
class Iterador {
private:
    vector<T> db;
    int indice;
public:
    Iterador(vector<T> _db) : db(_db), indice(0) {}

    T operator*() {
        return db[indice];
    }

    void siguiente() {
        indice++;
    }

    bool final() {
        return indice < db.size();
    }
};

// Reproductor de canciones
template<typename T>
class Reproductor {
private:
    vector<T> lista_de_canciones;
public:
    void agregarCancion(T c) {
        lista_de_canciones.push_back(c);
    }

    Iterador<T> inicio() {
        return Iterador<T>(lista_de_canciones);
    }
};


int main() {
    cout << "================ OBSERVER =================\n";
    Usuario usuario("Usuario1");
    Seguidor seguidor1("Seguidor1");
    Seguidor seguidor2("Seguidor2");
    Externo externo1("Externo1");

    usuario.agregarObservador(&seguidor1);
    usuario.agregarObservador(&seguidor2);
    usuario.agregarObservador(&externo1);

    usuario.notificarSeguidores("¡Hoy estoy de viaje!");

    cout << "\n================ MEMENTO =================\n";
    Personaje pj("Heroe");
    pj.guardarEstado();
    pj.guardarEstado();
    pj.guardarEstado();
    pj.guardarEstado();
    pj.restaurarEstado();
    pj.info();

    cout << "\n================ ITERATOR ================\n";
    Reproductor<Cancion> reproductor;
    reproductor.agregarCancion(Cancion("Canción 1", "Artista A"));
    reproductor.agregarCancion(Cancion("Canción 2", "Artista B"));
    reproductor.agregarCancion(Cancion("Canción 3", "Artista C"));

    Iterador<Cancion> it = reproductor.inicio();
    while (it.final()) {
        Cancion c = *it;
        cout << "🎵 Reproduciendo: " << c.titulo << " - " << c.artista << endl;
        it.siguiente();
    }

    return 0;
}
