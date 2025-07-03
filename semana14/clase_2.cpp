// ALGORITMO BFS

#include <iostream>
#include <map>                    // para usar map ordenado (distancias en BFS)
#include <unordered_map>          // para usar unordered_map (lista de adyacencia)
#include <vector>                 // para usar vecinos de cada nodo
#include <queue>                  // para usar queue (BFS)
#include <unordered_set>          // para usar unordered_set (conjunto de visitados)
using namespace std;

/*
    Clase genérica Grafo<T> que representa un grafo no dirigido usando listas de adyacencia.
    Incluye recorridos BFS y funciones para distancia mínima y BFS limitada por profundidad
*/

template<typename T>
class Grafo {
private:
    // Para cada nodo T guardamos un vector de vecinos
    unordered_map<T, vector<T>> grafo;

public:
    // Inserta una arista entre v1 y v2 (no dirigido)
    void insertar_arista(T v1, T v2) {
        grafo[v1].push_back(v2);  // v2 es vecino de v1
        grafo[v2].push_back(v1);  // v1 es vecino de v2
    }

    // Recorrido BFS desde el nodo "origen", imprime nodos en orden de visita
    void BFS(T origen) {
        queue<T> Q;                     // cola para el recorrido
        Q.push(origen);                 // empezamos por el origen
        unordered_set<T> visitados;     // para marcar los ya visitados

        while (!Q.empty()) {
            T nodo = Q.front();         // sacamos el frente de la cola
            Q.pop();

            // Si no lo hemos visitado aún
            if (visitados.find(nodo) == visitados.end()) {
                visitados.insert(nodo);     // marcamos como visitado
                cout << nodo << endl;       // imprimimos el nodo

                // Añadimos todos sus vecinos no visitados a la cola
                for (T vecino : grafo[nodo]) {
                    if (visitados.find(vecino) == visitados.end()) {
                        Q.push(vecino);
                    }
                }
            }
        }
    }

    // Calcula la distancia (número de aristas) más corta entre origen y destino
    int aristas(T origen, T destino) {
        queue<T> Q;
        Q.push(origen);
        unordered_set<T> visitados;
        map<T, int> distancias;         // distancia de cada nodo al origen
        distancias[origen] = 0;         // origen está a distancia 0

        while (!Q.empty()) {
            T nodo = Q.front();
            Q.pop();

            if (visitados.find(nodo) == visitados.end()) {
                visitados.insert(nodo);

                for (T vecino : grafo[nodo]) {
                    if (visitados.find(vecino) == visitados.end()) {
                        Q.push(vecino);
                        // Si no hemos asignado distancia al vecino, la calculamos
                        if (distancias.find(vecino) == distancias.end()) {
                            distancias[vecino] = distancias[nodo] + 1;
                            // Si llegamos al destino, devolvemos la distancia
                            if (vecino == destino)
                                return distancias[vecino];
                        }
                    }
                }
            }
        }

        // Si no llegamos al destino mostramos todas las distancias
        for (auto &par : distancias) {
            cout << par.first << ": " << par.second << endl;
        }
        return -1;  // destino no alcanzable
    }

    // BFS limitado por profundidad: solo visita nodos hasta esa profundidad
    void BFS2(T origen, int profundidad) {
        queue<T> Q;
        Q.push(origen);
        unordered_set<T> visitados;
        map<T, int> distancias;
        distancias[origen] = 0;         // origen a distancia 0

        while (!Q.empty()) {
            T nodo = Q.front();
            Q.pop();

            if (visitados.find(nodo) == visitados.end()) {
                // Si la distancia supera la profundidad deseada, detenemos
                if (distancias[nodo] > profundidad)
                    break;

                visitados.insert(nodo);
                cout << nodo << endl;    // imprimimos nodo valido

                // Procesamos vecinos
                for (T vecino : grafo[nodo]) {
                    if (visitados.find(vecino) == visitados.end()) {
                        Q.push(vecino);
                        // Asignamos distancia al vecino si no tiene
                        if (distancias.find(vecino) == distancias.end()) {
                            distancias[vecino] = distancias[nodo] + 1;
                        }
                    }
                }
            }
        }
    }

    // Muestra en pantalla los vecinos directos del nodo dado
    void print_vecinos(T nodo) {
        cout << "El nodo " << nodo << " está conectado a: ";
        for (T vecino : grafo[nodo]) {
            cout << vecino << " ";
        }
        cout << endl;
    }
};

int main() {
    // Creamos un grafo de URLs (string)
    Grafo<string> g;

    // Insertamos aristas (vínculos) entre páginas
    g.insertar_arista("http://www.google.com", "http://www.google.com/finance");
    g.insertar_arista("http://www.google.com", "http://www.google.com/maps");
    g.insertar_arista("http://www.google.com", "http://www.google.com/translate");
    g.insertar_arista("http://www.google.com", "http://www.facebook.com");
    g.insertar_arista("http://www.facebook.com", "http://www.facebook.com/MarkZuckerberg");
    g.insertar_arista("http://www.facebook.com/MarkZuckerberg",
                      "http://www.facebook.com/MarkZuckerberg/photos");
    g.insertar_arista("http://www.google.com", "http://www.twitter.com");
    g.insertar_arista("http://www.twitter.com",
                      "http://www.twitter.com/ElonMusk");
    g.insertar_arista("http://www.twitter.com/ElonMusk",
                      "http://www.twitter.com/ElonMusk/last_tweet");
    g.insertar_arista("http://www.google.com", "http://www.youtube.com");
    g.insertar_arista("http://www.google.com", "http://utec.edu.pe");

    // Realizamos un BFS hasta profundidad 2 desde google.com
    g.BFS2("http://www.google.com", 2);

    /*
    // Ejemplo de uso de otras funciones
    cout << "Distancia Google->YouTube: " << g.aristas("http://www.google.com", "http://www.youtube.com") << endl;
    g.print_vecinos("http://www.google.com");
    */

    return 0;
}
