// DIJSKTRA

#include <iostream>
#include <unordered_map>          // para usar unordered_map (mapa hash)
#include <queue>                  // para usar priority_queue
using namespace std;

// Clase generica para grafo ponderado no dirigido
template<typename T>
class GrafoPonderado {
private:
    // Mapa de adyacencia:
    // clave: nodo T
    // valor: otro mapa cuyas claves son vecinos de 'nodo' y el valor es el peso de la arista
    unordered_map<T, unordered_map<T,int>> grafo;

public:
    // Agrega una arista entre n1 y n2 con peso dado
    void nueva_arista(char n1, char n2, int peso_arista) {
        // Desde n1 hacia n2
        grafo[n1][n2] = peso_arista;
        // Como es no dirigido, también desde n2 hacia n1
        grafo[n2][n1] = peso_arista;
    }

    // Algoritmo de Dijkstra para hallar distancia mínima desde 'origen'
    void dijkstra(T origen) {
        // 1. Inicializar distancias a INFINITO (INT_MAX)
        unordered_map<T, int> distancia_al_origen;
        for (auto& par : grafo) {
            distancia_al_origen[par.first] = INT_MAX;
        }
        // Distancia al origen es 0
        distancia_al_origen[origen] = 0;

        // 2. Cola de prioridad (min-heap invertido con negativos)
        //    pair< -distancia , nodo > para sacar primero el menor peso
        priority_queue<pair<int, T>> no_visitados;
        no_visitados.push(make_pair(0, origen));

        // 3. Mientras queden nodos por procesar
        while (!no_visitados.empty()) {
            // Obtener nodo con distancia mínima conocida
            T nodo = no_visitados.top().second;
            no_visitados.pop();

            // Revisar cada vecino de 'nodo'
            for (auto& par : grafo[nodo]) {
                T vecino      = par.first;   // nodo vecino
                int peso_arista = par.second; // peso de la arista

                // Si pasando por 'nodo' llegamos más barato a 'vecino'
                if (distancia_al_origen[nodo] + peso_arista <
                    distancia_al_origen[vecino]) {
                    // Actualizamos la mejor distancia
                    distancia_al_origen[vecino] =
                        distancia_al_origen[nodo] + peso_arista;
                    // Volvemos a empujar en la cola con distancia negativa
                    no_visitados.push(make_pair(
                        -distancia_al_origen[vecino], vecino));
                }
            }
        }

        // 4. Imprimir resultados: d(nodo)=distancia
        for (auto& par : distancia_al_origen) {
            cout << "d(" << par.first << ")=" << par.second << endl;
        }
    }
};

int main() {
    // Creamos un grafo ponderado de caracteres
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

    // Ejecutamos Dijkstra desde 'A'
    // Esperado: A->0, C->4, D->7, E->8, F->11, G->9, H->17, I->11, B->22
    g.dijkstra('A');

    return 0;
}
