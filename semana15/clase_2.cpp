// KRUSKAL

#include <iostream>
#include <vector>     // lista de aristas
#include <map>        // para usar map (pertenece y cardinal)
#include <algorithm>  // para usar sort
using namespace std;

/*
 Estructura que representa una arista entre dos nodos con un peso
 T: tipo de los nodos
*/

template<typename T>
struct arista {
    T n1, n2;    // los dos extremos de la arista
    int peso;    // peso de la arista

    // Constructor que inicializa los campos
    arista(T _n1, T _n2, int _peso)
        : n1(_n1), n2(_n2), peso(_peso) {}

    // Operador < para ordenar aristas de menor a mayor peso
    bool operator<(const arista<T> &otro) const {
        return this->peso < otro.peso;
    }
};


// Clase que aplica el algoritmo de Kruskal para obtener el Árbol de Expansión Mínima (AEM) de un grafo no dirigido

template<typename T>
class GrafoAristas {
private:
    vector<arista<T>> aristas;  // lista de todas las aristas del grafo
    map<T,T> pertenece;         // para cada nodo, su representante en conjuntos disjuntos
    map<T,int> cardinal;        // tamaño (cardinalidad) de cada conjunto raíz

public:
    // Agrega una nueva arista al grafo y prepara los conjuntos disjuntos
    void nueva_arista(T n1, T n2, int peso_arista) {
        aristas.push_back(arista<T>(n1, n2, peso_arista));

        // Inicializamos conjuntos: cada nodo pertenece a sí mismo
        pertenece[n1]  = n1;
        pertenece[n2]  = n2;
        // Cada conjunto inicial tiene cardinalidad 1
        cardinal[n1]   = 1;
        cardinal[n2]   = 1;
    }

    // Encuentra el representante (raíz) del conjunto al que pertenece 'nodo'
    T ancestro(T nodo) {
        if (pertenece[nodo] == nodo) {
            // Si el nodo es su propio representante, lo devolvemos
            return nodo;
        }
        // Si no, seguimos subiendo recursivamente
        return ancestro(pertenece[nodo]);
    }

    // Ejecuta el algoritmo de Kruskal y muestra el AEM
    void kruskal() {
        vector<arista<T>> AEM;           // contiene las aristas del Árbol de Expansión Mínima

        // 1. Ordenamos todas las aristas por peso ascendente
        sort(aristas.begin(), aristas.end());

        // 2. Recorremos las aristas más baratas primero
        for (auto &a : aristas) {
            T n1 = a.n1, n2 = a.n2;
            // Encontramos representantes de ambos extremos
            T anc1 = ancestro(n1);
            T anc2 = ancestro(n2);

            // Solo unimos si están en conjuntos distintos (evita ciclos)
            if (anc1 != anc2) {
                AEM.push_back(a);  // agregamos la arista al AEM

                // Union por tamaño: anexamos el conjunto más pequeño al más grande
                if (cardinal[anc1] > cardinal[anc2]) {
                    pertenece[anc2] = anc1;
                    cardinal[anc1] += cardinal[anc2];
                } else {
                    pertenece[anc1] = anc2;
                    cardinal[anc2] += cardinal[anc1];
                }
            }
        }

        // 3. Imprimimos las aristas seleccionadas en el AEM
        cout << "Arbol de Expansion Minima (Kruskal):\n";
        for (auto &a : AEM) {
            cout << a.n1 << " --(" << a.peso << ")-- " << a.n2 << endl;
        }
    }
};

int main() {
    // Creamos un grafo con nodos de tipo char
    GrafoAristas<char> g;

    // Agregamos aristas con sus pesos
    g.nueva_arista('A','B', 5);
    g.nueva_arista('A','C', 7);
    g.nueva_arista('B','C', 9);
    g.nueva_arista('B','E', 15);
    g.nueva_arista('B','F', 6);
    g.nueva_arista('C','D', 8);
    g.nueva_arista('C','E', 7);
    g.nueva_arista('D','E', 5);
    g.nueva_arista('E','F', 8);
    g.nueva_arista('E','G', 9);
    g.nueva_arista('F','G',11);

    // Ejecutamos Kruskal para obtener e imprimir el AEM
    g.kruskal();

    return 0;
}
