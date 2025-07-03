// DIJSKTRA EJERCICIOS

#include <iostream>
#include <unordered_map> // para usar unordered_map (mapas hash)
#include <queue> // para usar priority_queue
using namespace std;

// Clase generica para grafo ponderado no dirigido
template<typename T>
class GrafoPonderado {
private:
    // Mapa de adyacencia:
    // clave: nodo T
    // valor: otro mapa cuya clave es vecino y el valor es peso de la arista
    unordered_map<T, unordered_map<T,int>> grafo;

    // Guarda la mejor distancia conocida desde el origen a cada nodo
    unordered_map<T, int> distancia_al_origen;

public:
    // Agrega una arista entre n1 y n2 con el peso dado
    void nueva_arista(char n1, char n2, int peso_arista) {
        // Bidireccional: n1->n2 y n2->n1
        grafo[n1][n2] = peso_arista;
        grafo[n2][n1] = peso_arista;
        // Inicializamos distancias a "infinito" para ambos nodos
        distancia_al_origen[n1] = INT_MAX;
        distancia_al_origen[n2] = INT_MAX;
    }

    // Ejecuta Dijkstra desde 'origen' y devuelve el mapa de padres
    unordered_map<T,T> dijkstra(T origen) {
        // 1. Distancia al origen es 0
        distancia_al_origen[origen] = 0;

        // 2. Cola de prioridad (min-heap invertido)
        //    pair< -distancia , nodo >
        priority_queue<pair<int, T>> no_visitados;
        no_visitados.push(make_pair(0, origen));

        // Mapa para reconstruir caminos: padre de cada nodo
        unordered_map<T,T> padres;

        // 3. Recorremos mientras haya nodos por procesar
        while (!no_visitados.empty()) {
            T nodo = no_visitados.top().second;
            no_visitados.pop();

            // Para cada vecino del nodo actual
            for (auto &par : grafo[nodo]) {
                T vecino      = par.first;   // nodo vecino
                int peso_arista = par.second; // peso hacia el vecino

                // Si encontramos un camino más corto a "vecino"
                if (distancia_al_origen[nodo] + peso_arista <
                    distancia_al_origen[vecino]) {

                    // Actualizamos la distancia más corta
                    distancia_al_origen[vecino] =
                        distancia_al_origen[nodo] + peso_arista;
                    // Volvemos a encolar con distancia negativa
                    no_visitados.push(make_pair(
                        -distancia_al_origen[vecino], vecino));
                    // Guardamos al padre para reconstruir ruta
                    padres[vecino] = nodo;
                }
            }
        }

        // 4. Imprimimos distancias finales desde el origen
        for (auto &par : distancia_al_origen) {
            cout << "d(" << par.first << ")=" << par.second << endl;
        }
        return padres;  // devolvemos el mapa de padres
    }
};

int main() {
    // Creamos un grafo ponderado con nodos char
    GrafoPonderado<char> g;

    // Añadimos aristas con sus pesos
    g.nueva_arista('A','C', 4);
    g.nueva_arista('A','D', 7);
    g.nueva_arista('C','D', 11);
    g.nueva_arista('C','E', 20);
    g.nueva_arista('C','F', 9);
    g.nueva_arista('D','E', 1);
    g.nueva_arista('E','G', 1);
    g.nueva_arista('E','I', 3);
    g.nueva_arista('F','G', 2);
    g.nueva_arista('F','H', 6);
    g.nueva_arista('G','H', 10);
    g.nueva_arista('G','B', 15);
    g.nueva_arista('G','I', 5);
    g.nueva_arista('H','B', 5);
    g.nueva_arista('I','B', 12);

    // Ejecutamos Dijkstra desde "A" y obtenemos mapa de padres
    auto padres = g.dijkstra('A');

    // Mostramos quien fue el padre de cada nodo en el camino mas corto
    for (auto &par : padres) {
        cout << "Nodo: " << par.first
             << ", Padre: " << par.second << endl;
    }

    return 0;
}