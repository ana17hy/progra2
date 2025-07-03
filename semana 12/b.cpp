// Colas

#include <iostream>
#include <queue>      // para usar colas (queue y priority_queue)
#include <thread>     // para pausas con sleep_for
using namespace std;

// Clase que simula un banco con dos colas: normal y de prioridad
class Banco {
private:
    queue<string> lista_clientes;    // clientes sin prioridad
    queue<string> lista_prioridad;   // clientes con prioridad

public:
    // El cliente saca un ticket normal
    void sacarticket(string nombre) {
        lista_clientes.push(nombre);
    }

    // El cliente saca un ticket de prioridad
    void sacarticket_con_prioridad(string nombre) {
        lista_prioridad.push(nombre);
    }

    // Muestra quiénes están esperando en ambas colas
    void mostrarClientesEnEspera() {
        // Usamos copias para no vaciar las colas originales
        queue<string> copia = lista_clientes;
        cout << "Lista de clientes:" << endl;
        int i = 1;
        while (!copia.empty()) {
            cout << i << ": " << copia.front() << endl; // muestra el cliente al frente
            copia.pop();                                  // quita de la copia
            i++;
        }

        queue<string> copia2 = lista_prioridad;
        cout << "Lista de prioridad:" << endl;
        int j = 1;
        while (!copia2.empty()) {
            cout << j << ": " << copia2.front() << endl;
            copia2.pop();
            j++;
        }
    }

    // Atiende al siguiente cliente: primero prioridad, luego normal
    void atenderCliente() {
        if (!lista_prioridad.empty()) {
            cout << "Atender cliente: " << lista_prioridad.front() << endl;
            lista_prioridad.pop();  // quita de la cola de prioridad
        }
        else if (!lista_clientes.empty()) {
            cout << "Atendiendo cliente: " << lista_clientes.front() << endl;
            lista_clientes.pop();   // quita de la cola normal
        }
    }
};

// Representa un documento para una cola de impresión (nombre y fecha)
struct Documento {
    string nombre, fecha;
    Documento(string n, string f): nombre(n), fecha(f) {}
};

// Representa una tarea con una prioridad (para priority_queue)
struct Tarea {
    string nombre;
    int prioridad;

    // Definimos el operador < para que las de mayor prioridad salgan primero
    bool operator<(const Tarea& t) const {
        return prioridad < t.prioridad;
    }
};

// Permite imprimir una Tarea con cout << tarea;
ostream& operator<<(ostream& os, const Tarea& d) {
    os << "Tarea " << d.nombre << ", Prioridad " << d.prioridad;
    return os;
}

// Gestor de tareas que utiliza una cola de prioridad
class Gestor {
private:
    priority_queue<Tarea> pq; // la tarea con mayor prioridad está arriba

public:
    // Agrega una tarea a la cola
    void agregar(Tarea t) {
        pq.push(t);
    }

    // Devuelve cuántas tareas hay pendientes
    int size() {
        return pq.size();
    }

    // Atiende (procesa) la tarea con mayor prioridad
    void atender_tarea() {
        if (!pq.empty()) {
            Tarea t = pq.top();
            cout << t << endl;  // muestra la tarea que se atiende
            pq.pop();           // la elimina de la cola
        }
    }
};

int main() {
    // Ejemplo de uso del Gestor de tareas
    Gestor gestor;

    // Agregamos tres tareas con distintas prioridades
    gestor.agregar(Tarea("A", 2));
    gestor.agregar(Tarea("B", 1));
    gestor.agregar(Tarea("C", 3));

    // Mientras queden tareas, las atendemos en orden de prioridad
    while (gestor.size() != 0) {
        gestor.atender_tarea();
    }

    /*
    // Ejercicio con priority_queue<int>
    priority_queue<int> pq;
    pq.push(2);
    pq.push(1);
    pq.push(3);
    cout << pq.top() << endl; pq.pop();
    cout << pq.top() << endl; pq.pop();
    cout << pq.top() << endl;

    // Ejercicio con cola de impresión
    queue<Documento> colaImpresion;
    colaImpresion.push(Documento("nota.txt",       "01/06/2025"));
    colaImpresion.push(Documento("sibalo.pdf",     "02/06/2025"));
    colaImpresion.push(Documento("practica_3.pdf", "03/06/2025"));
    colaImpresion.push(Documento("slide_10.ppt",   "04/06/2025"));
    // ... (muestra y procesa la cola de impresión)

    // Ejercicio con Banco y tickets
    this_thread::sleep_for(chrono::seconds(1)); // pausa 1 segundo
    Banco banco;
    banco.sacarticket("Juan");
    banco.sacarticket("Maria");
    banco.sacarticket("Pedro");
    banco.sacarticket_con_prioridad("Jose");
    banco.mostrarClientesEnEspera();
    banco.atenderCliente();
    banco.mostrarClientesEnEspera();
    // ...
    */

    return 0;
}
