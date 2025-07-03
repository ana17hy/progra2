// PATRONES DE DISEÑO II

#include <iostream>
#include <vector>
using namespace std;


// PATRON ITERADOR

// Representa una canción con título y artista
struct Cancion {
    string titulo, artista;
    Cancion(string t, string a): titulo(t), artista(a) {}
};

// Iterador para recorrer una lista de cualquier tipo T
template<typename T>
class Iterador {
private:
    vector<T> db;   // Lista de elementos
    int indice;     // Índice actual del iterador
public:
    Iterador(vector<T> _db) : db(_db), indice(0) {}

    // Devuelve el elemento actual
    T operator*() {
        return db[indice];
    }

    // Pasa al siguiente elemento
    void siguiente() {
        indice++;
    }

    // Verifica si aún no llega al final
    bool final() {
        return indice < db.size();
    }
};

// Iterador inverso (declarado pero no implementado por el profe)
template<typename T>
class IteradorInv {};

// Reproductor que guarda canciones y crea iteradores para recorrerlas
template<typename T>
class Reproductor {
private:
    vector<T> lista_de_canciones;
public:
    // Agrega una canción a la lista
    void agregarCancion(T c) {
        lista_de_canciones.push_back(c);
    }

    // Crea un iterador para recorrer desde el inicio
    Iterador<T> inicio() {
        return Iterador<T>(lista_de_canciones);
    }

    // (Futuro) Crea un iterador inverso
    IteradorInv<T> inicioInv() {
        return IteradorInv<T>(lista_de_canciones);
    }
};


// PATRON MEMENTO

// Clase que guarda un estado del personaje (nivel, x, y)
class Memento {
private:
    int nivel;
    int X;
    int Y;
public:
    Memento (const int& niv, int posicionX, int posicionY)
        : nivel(niv), X(posicionX), Y(posicionY) {}

    // Métodos para acceder a los datos guardados
    int getNivel() const { return nivel; }
    int getPosicionX() const { return X; }
    int getPosicionY() const { return Y; }
};

// Clase principal que usa el patrón Memento
class Personaje {
private:
    string nombre;
    int nivel;
    int x, y;
    vector<Memento*> mementos; // Guarda todos los estados anteriores
public:
    Personaje(const string& nombre) : nombre(nombre), nivel(1), x(0), y(0) {}

    // Muestra el estado actual del personaje
    void info(){
        cout << "Nivel: " << nivel << ", Pos=(" << x << ", " << y << ")" << endl;
    }

    // Permite elegir un estado anterior guardado
    void restaurarEstado() {
        cout << "--------------------------------\n";
        for (int i = 0; i < mementos.size(); i++) {
            cout << "----------- Estado " << i + 1 << " ----------\n";
            cout << "-Nivel: " << mementos[i]->getNivel() << endl;
            cout << "-Posicion: (" << mementos[i]->getPosicionX()
                 << ", " << mementos[i]->getPosicionY() << ")\n";
        }
        int op;
        cout << "Elige un estado: ";
        cin >> op;
        // Restaurar el estado elegido
        nivel = mementos[op - 1]->getNivel();
        x = mementos[op - 1]->getPosicionX();
        y = mementos[op - 1]->getPosicionY();
    }

    // Guarda el estado actual (nivel, x, y)
    void guardarEstado() {
        cout << "Guardo Estado: Nivel " << nivel << ", Pos=(" << x << ", " << y << ")\n";
        mementos.push_back(new Memento(nivel, x, y));
    }
};


// PATRON OBSERVER

// Clase base para cualquier observador
class Observer {
public:
    virtual void noticar(string historia, string usuario) = 0;
};

// Observador tipo Seguidor: recibe historias nuevas
class Seguidor : public Observer {
private:
    string nombre;
public:
    Seguidor(const string& nombre) : nombre(nombre) {}

    void noticar(string historia, string usuario) override {
        cout << nombre << " - Nueva historia de " << usuario << ": " << historia << endl;
    }
};

// Observador tipo Externo: no recibe historias
class Externo: public Observer {
private:
    string nombre;
public:
    Externo(const string& nombre) : nombre(nombre) {}

    void noticar(string historia, string usuario) override {
        cout << nombre << " - No hay nueva historia de " << usuario << endl;
    }
};

// Clase principal observada: Usuario que puede publicar historias
class Usuario {
private:
    string nombre;
    vector<Observer*> observadores;
public:
    Usuario(const string& nombre) : nombre(nombre) {}

    // Agrega un observador a la lista
    void agregarObservador(Observer* observador) {
        observadores.push_back(observador);
    }

    // Notifica a todos los observadores una nueva historia
    void notificarSeguidores(const string& historia) {
        for (Observer* obs: observadores)
            obs->noticar(historia, nombre);
    }

    // Método futuro para eliminar observadores
    void eliminarObservador(Observer* observador) {
        // (Pendiente de implementar)
    }
};


int main() {
    // ---------- OBSERVER ----------
    Usuario usuario("Usuario1");
    Seguidor seguidor1("Seguidor1");
    Seguidor seguidor2("Seguidor2");
    Externo externo1("Externo1");

    // Agregamos los observadores (seguidores)
    usuario.agregarObservador(&seguidor1);
    usuario.agregarObservador(&seguidor2);
    usuario.agregarObservador(&externo1);

    // Enviamos una historia a todos
    string nuevaHistoria = "Hoy estoy de viaje!";
    usuario.notificarSeguidores(nuevaHistoria);

    /*
    // ---------- MEMENTO ----------
    Personaje pj("Heroe");
    pj.guardarEstado();
    pj.guardarEstado();
    pj.guardarEstado();
    pj.guardarEstado();
    pj.restaurarEstado(); // Elegimos uno
    pj.info(); // Muestra el estado restaurado
    */

    /*
    // ---------- ITERATOR ----------
    Reproductor<Cancion> reproductor;
    Cancion cancion1("Cancion 1", "Artista 1");
    Cancion cancion2("Cancion 2", "Artista 2");
    Cancion cancion3("Cancion 3", "Artista 3");

    // Agregamos canciones al reproductor
    reproductor.agregarCancion(cancion1);
    reproductor.agregarCancion(cancion2);
    reproductor.agregarCancion(cancion3);

    // Creamos un iterador y reproducimos las canciones
    Iterador<Cancion> iterador = reproductor.inicio();
    while (iterador.final()) {
        Cancion cancion = *iterador;
        cout << "Reproduciendo: " << cancion.titulo << " - " << cancion.artista << endl;
        iterador.siguiente();
    }
    */

    return 0;
}