// ALGORITMO DFS

#include <iostream>
#include <vector>
#include <stack>                 // para usar stack (DFS)
#include <unordered_map>         // para mapas hash
#include <unordered_set>         // para conjuntos hash
#include <map>                   // para map ordenado (padres en DFS de grafo)
using namespace std;

// Clase genérica Grafo<T> usando lista de adyacencia
// y DFS (Depth-First Search) para recorrer nodos y detectar bucles.

template<typename T>
class Grafo {
private:
    // grafo: para cada nodo T guarda vector de vecinos
    unordered_map<T, vector<T>> grafo;
    // padres: cuenta cuantas aristas apuntan a cada nodo
    unordered_map<T,int> padres;

public:
    // Inserta una arista no dirigida u---v
    void insertar_arista(T u, T v) {
        grafo[u].push_back(v);   // agrega v como vecino de u
        grafo[v].push_back(u);   // agrega u como vecino de v
        padres[v]++;             // incrementa contador de "padres" de v
        // si quieres contar padres de u
        // padres[u]++;
    }

    // Recorre el grafo desde "inicial" usando DFS
    void DFS(T inicial) {
        stack<T> s;                    // pila para nodos pendientes
        s.push(inicial);
        unordered_set<T> visitados;    // conjunto de nodos ya visitados
        map<T,T> mapa_padres;          // mapea cada nodo con el nodo desde el que se llegó

        while (!s.empty()) {
            T top = s.top();
            s.pop();

            // Si no lo habíamos visitado lo procesamos
            if (visitados.find(top) == visitados.end()) {
                visitados.insert(top);
                cout << "Visitando: " << top << endl;

                // Recorremos vecinos
                for (T vecino_top : grafo[top]) {
                    // Si el vecino no ha sido visitado
                    if (visitados.find(vecino_top) == visitados.end()) {
                        // Si ya existe en mapa_padres detectamos un ciclo
                        if (mapa_padres.find(vecino_top) != mapa_padres.end()) {
                            cout << "Se detecto BUCLE! en el nodo: "
                                 << vecino_top << endl;
                        }
                        // guardamos quién es el padre de este vecino
                        mapa_padres[vecino_top] = top;
                        s.push(vecino_top);
                    }
                }
            }
        }

        // Al finalizar DFS, mostramos cuántos "padres" tiene cada nodo
        for (auto &p : padres) {
            cout << "nodo: " << p.first
                 << ", padres: " << p.second << endl;
        }
    }
};

/*
 DFS sobre matriz de '1'/'0' para contar islas:
 - '1' representa tierra no visitada
 - '0' representa agua o tierra ya visitada
*/
void DFS(vector<vector<char>>& mapa, int i0, int j0) {
    stack<pair<int,int>> s;
    s.push(make_pair(i0, j0));

    while (!s.empty()) {
        auto top = s.top();
        int i = top.first, j = top.second;
        s.pop();

        // Solo procesamos si es '1' (tierra sin visitar)
        if (mapa[i][j] == '1') {
            mapa[i][j] = '0';  // marcamos como visitado

            // Empujamos vecinos válidos en 4 direcciones
            if (i+1 < (int)mapa.size() && mapa[i+1][j] == '1')
                s.push(make_pair(i+1, j));
            if (i-1 >= 0 && mapa[i-1][j] == '1')
                s.push(make_pair(i-1, j));
            if (j+1 < (int)mapa[i].size() && mapa[i][j+1] == '1')
                s.push(make_pair(i, j+1));
            if (j-1 >= 0 && mapa[i][j-1] == '1')
                s.push(make_pair(i, j-1));
        }
    }
}

// Cuenta cuantas islas hay: recorre matriz y lanza DFS donde encuentra '1'
int contar_islas(vector<vector<char>> mapa) {
    int contador = 0;
    for (int i = 0; i < (int)mapa.size(); i++) {
        for (int j = 0; j < (int)mapa[i].size(); j++) {
            // Si encontramos tierra no visitada
            if (mapa[i][j] == '1') {
                DFS(mapa, i, j);  // sumergimos en esa isla
                contador++;       // contamos una isla
            }
        }
    }
    return contador;
}

int main() {
    // Definimos un mapa de islas (1=tierra, 0=agua)
    vector<vector<char>> islas = {
        {'1','1','0','1','1'},
        {'1','1','0','1','1'},
        {'1','0','1','0','0'},
        {'0','0','0','1','1'}
    };
    // Debe imprimir 4 islas
    cout << "Número de islas: " << contar_islas(islas) << endl;

    /*
     Ejemplo de uso de Grafo<T>

     Grafo<char> g;
     g.insertar_arista('A', 'B');
     g.insertar_arista('C', 'A');
     // g.insertar_arista('B', 'C');  // crea ciclo
     g.insertar_arista('B', 'D');
     g.insertar_arista('C', 'E');
     g.insertar_arista('F', 'C');
     g.insertar_arista('E', 'F');    // crea ciclo adicional
     g.DFS('A');                     // recorre desde "A"
     */

    return 0;
}
