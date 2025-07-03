// BFS

#include <iostream>
#include <unordered_map>          // para usar unordered_map (lista de adyacencia)
#include <vector>                 // vecinos de cada nodo
#include <queue>                  // para usar queue (BFS)
#include <unordered_set>          // para usar unordered_set (conjunto de visitados)
using namespace std;

// Clase Grafo<T> que representa un grafo no dirigido usando listas de adyacencia, con inserción de aristas y recorrido en anchura (BFS)

template<typename T>
class Grafo {
private:
    // Mapa de cada nodo a su lista de vecinos
    unordered_map<T, vector<T>> grafo;

public:
    // Inserta una arista bidireccional entre v1 y v2
    void insertar_arista(T v1, T v2) {
        grafo[v1].push_back(v2);   // agrega v2 como vecino de v1
        grafo[v2].push_back(v1);   // agrega v1 como vecino de v2
    }

    // Realiza un recorrido en anchura (BFS) desde el nodo 'origen'
    void BFS(T origen) {
        queue<T> Q;                 // cola de nodos por visitar
        Q.push(origen);             // comenzamos desde 'origen'
        unordered_set<T> visitados; // conjunto de nodos ya visitados

        while (!Q.empty()) {
            T nodo = Q.front();     // obtenemos el siguiente nodo en la cola
            Q.pop();                // lo sacamos de la cola

            // Si no lo hemos visitado todavía
            if (visitados.find(nodo) == visitados.end()) {
                visitados.insert(nodo);    // marcamos como visitado
                cout << nodo << endl;      // mostramos el nodo

                // Añadimos a la cola todos sus vecinos no visitados
                for (T vecino : grafo[nodo]) {
                    if (visitados.find(vecino) == visitados.end()) {
                        Q.push(vecino);
                    }
                }
            }
        }
    }

    // Muestra en pantalla todos los vecinos directos de un nodo dado
    void print_vecinos(T nodo) {
        cout << "El nodo " << nodo << " está conectado a: ";
        for (T vecino : grafo[nodo]) {
            cout << vecino << " ";
        }
        cout << endl;
    }
};

int main() {
    Grafo<char> grafo; // grafo cuyos nodos son caracteres

    // Creamos algunas aristas (no dirigidas)
    grafo.insertar_arista('A', 'B'); // A --- B
    grafo.insertar_arista('A', 'C'); // A --- C
    grafo.insertar_arista('B', 'E'); // B --- E
    grafo.insertar_arista('B', 'D'); // B --- D

    // Realizamos un recorrido BFS comenzando en 'A'
    grafo.BFS('A'); // imprimira los nodos en orden de nivel

    // Si queremos ver los vecinos de 'B'
    // grafo.print_vecinos('B');

    return 0;
}