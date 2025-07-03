// ARBOL BINARIO DE BUSQUEDA

#include <iostream>
using namespace std;

// Estructura que representa un nodo en el Arbol
struct Nodo {
    int dato;        // valor almacenado en el nodo
    Nodo* left;      // puntero al hijo izquierdo
    Nodo* right;     // puntero al hijo derecho

    // Constructor: inicializa el dato y establece hijos en NULL
    Nodo(int dato) {
        this->dato = dato;
        this->left = NULL;
        this->right = NULL;
    }
};

// Clase que implementa un Binary Search Tree (sin valores repetidos)
class BST {
private:
    Nodo* raiz = NULL;  // puntero a la raíz del árbol, inicialmente vacío

    // Inserta recursivamente un nodo con valor x en el subárbol de "nodo"
    Nodo* insertarNodoAux(Nodo* nodo, int x) {
        if (nodo == NULL) {
            // Si el lugar está libre creamos un nuevo nodo
            return new Nodo(x);
        }
        if (x < nodo->dato) {
            // Si x es menor vamos al subarbol izquierdo
            nodo->left = insertarNodoAux(nodo->left, x);
        }
        else if (x > nodo->dato) {
            // Si x es mayor vamos al subarbol derecho
            nodo->right = insertarNodoAux(nodo->right, x);
        }
        // Si x es igual no insertamos duplicados
        return nodo;
    }

    // Busca recursivamente el nodo con valor x en el subarbol de "nodo"
    Nodo* buscarAux(Nodo* nodo, int x) {
        if (nodo == NULL)
            return NULL;            // no encontrado
        else if (x == nodo->dato)
            return nodo;            // encontrado

        // Recorremos segun comparacion
        if (x < nodo->dato)
            return buscarAux(nodo->left, x);
        else
            return buscarAux(nodo->right, x);
    }

    // Recorre el arbol en orden (izquierda, nodo, derecha)
    void imprimirEnOrderAux(Nodo* nodo) {
        if (nodo == NULL)
            return;
        imprimirEnOrderAux(nodo->left);
        cout << nodo->dato << ' ';
        imprimirEnOrderAux(nodo->right);
    }

    // Recorre el arbol en preorden (nodo, izquierda, derecha)
    void imprimirPreOrderAux(Nodo* nodo) {
        if (nodo == NULL)
            return;
        cout << nodo->dato << ' ';
        imprimirPreOrderAux(nodo->left);
        imprimirPreOrderAux(nodo->right);
    }

    // Recorre el arbol en postorden (izquierda, derecha, nodo)
    void imprimirPostOrderAux(Nodo* nodo) {
        if (nodo == NULL)
            return;
        imprimirPostOrderAux(nodo->left);
        imprimirPostOrderAux(nodo->right);
        cout << nodo->dato << ' ';
    }

    // Elimina todos los nodos del subárbol de "nodo" (libera memoria)
    void eliminar(Nodo* nodo) {
        if (nodo == NULL)
            return;
        eliminar(nodo->left);
        eliminar(nodo->right);
        delete nodo;
    }

    // Devuelve el valor minimo del subarbol de "nodo"
    int minimoAux(Nodo* nodo) {
        if (nodo->left == NULL)
            return nodo->dato;       // el mas izquierdo es el menor
        return minimoAux(nodo->left);
    }

    // Devuelve el valor máximo del subárbol de "nodo"
    int maximoAux(Nodo* nodo) {
        if (nodo->right == NULL)
            return nodo->dato;       // el más derecho es el mayor
        return maximoAux(nodo->right);
    }

    // Encuentra el sucesor en orden del nodo dado
    Nodo* sucesorAux(Nodo* nodo) {
        // Caso 1: tiene subarbol derecho → mínimo de ese subarbol
        if (nodo->right != NULL)
            return this->buscar(minimoAux(nodo->right));
        // Caso 2: sin hijo derecho → buscamos ancestro que lo contenga a la izquierda
        Nodo* ancestro = raiz;
        Nodo* sucesor = NULL;
        while (ancestro != nodo) {
            if (nodo->dato < ancestro->dato) {
                sucesor = ancestro;
                ancestro = ancestro->left;
            }
            else {
                ancestro = ancestro->right;
            }
        }
        return sucesor;
    }

    // Devuelve el padre del nodo con valor x en el subárbol de "nodo"
    Nodo* padreAux(Nodo* nodo, int x) {
        if (nodo == NULL || nodo->dato == x)
            return NULL;  // la raíz o nodo inexistente no tienen padre

        // Comprobamos si alguno de los hijos es "x"
        if (nodo->left != NULL && nodo->left->dato == x)
            return nodo;
        if (nodo->right != NULL && nodo->right->dato == x)
            return nodo;

        // Recorremos según comparación
        if (x < nodo->dato)
            return padreAux(nodo->left, x);
        else
            return padreAux(nodo->right, x);
    }

    // Elimina el nodo dado (aplica tres casos: hoja, un hijo, dos hijos)
    void eliminarAux(Nodo* nodo, int x) {
        // Caso 1: hoja (sin hijos)
        if (nodo->left == NULL && nodo->right == NULL) {
            Nodo* padre_x = this->padreAux(raiz, x);
            if (padre_x != NULL) {
                // Desconectamos el puntero del padre
                if (padre_x->left != NULL && padre_x->left->dato == x)
                    padre_x->left = NULL;
                else
                    padre_x->right = NULL;
            }
            delete nodo;
        }
        // Caso 2: un solo hijo izquierdo
        else if (nodo->left != NULL && nodo->right == NULL) {
            Nodo* padre_x = this->padreAux(raiz, x);
            // Reemplazamos el enlace del padre al único hijo
            if (padre_x->left != NULL && padre_x->left->dato == x)
                padre_x->left = nodo->left;
            else
                padre_x->right = nodo->left;
            delete nodo;
        }
        // Caso 2b: un solo hijo derecho
        else if (nodo->left == NULL && nodo->right != NULL) {
            Nodo* padre_x = this->padreAux(raiz, x);
            if (padre_x->left != NULL && padre_x->left->dato == x)
                padre_x->left = nodo->right;
            else
                padre_x->right = nodo->right;
            delete nodo;
        }
        // Caso 3: dos hijos → sustituir por sucesor
        else {
            Nodo* suc = this->sucesorAux(nodo);
            int tmp = suc->dato;
            this->eliminarAux(suc, tmp);  // eliminamos sucesor
            nodo->dato = tmp;             // copiamos su valor aquí
        }
    }

public:
    // Inserta un valor x en el arbol
    void insertarNodo(int x) {
        raiz = insertarNodoAux(raiz, x);
    }

    // Imprime todos los valores en orden ascendente
    void imprimirEnOrder() {
        imprimirEnOrderAux(raiz);
        cout << endl;
    }

    // Imprime en preorden
    void imprimirPreOrder() {
        imprimirPreOrderAux(raiz);
        cout << endl;
    }

    // Imprime en postorden
    void imprimirPostOrder() {
        imprimirPostOrderAux(raiz);
        cout << endl;
    }

    // Destructor: elimina todos los nodos al destruir el árbol
    ~BST() {
        eliminar(raiz);
    }

    // Busca y devuelve el puntero al nodo con valor x
    Nodo* buscar(int x) {
        return buscarAux(raiz, x);
    }

    // Devuelve el valor mínimo del árbol
    int minimo() {
        return minimoAux(raiz);
    }

    // Devuelve el valor maximo del árbol
    int maximo() {
        return maximoAux(raiz);
    }

    // Devuelve el puntero al sucesor de x
    Nodo* sucesor(int x) {
        Nodo* nodo_x = buscarAux(raiz, x);
        if (nodo_x == NULL)
            return NULL;
        return sucesorAux(nodo_x);
    }

    // Elimina el nodo con valor x si existe
    void eliminar(int x) {
        Nodo* nodo = buscar(x);
        if (nodo != NULL)
            eliminarAux(nodo, x);
    }

    // Devuelve el padre del nodo con valor x
    Nodo* padre(int x) {
        Nodo* nodo = buscar(x);
        if (nodo == NULL)
            return NULL;
        return padreAux(raiz, x);
    }
};

int main() {
    BST arbol;

    // Insertamos varios valores en el BST
    arbol.insertarNodo(5);
    arbol.insertarNodo(7);
    arbol.insertarNodo(4);
    arbol.insertarNodo(6);
    arbol.insertarNodo(6);  // no se insertará porque se repite
    arbol.insertarNodo(8);
    arbol.insertarNodo(2);

    // Imprimimos en preorden para ver la estructura
    arbol.imprimirPreOrder();

    // Ejemplo de eliminacion:
    arbol.eliminar(2); // elimina hoja (caso 1)

    // Otros casos de eliminacion:
    // arbol.eliminar(4); // elimina nodo con un solo hijo (caso 2)
    // arbol.eliminar(5); // elimina nodo con dos hijos (caso 3)

    /*
    // Ejemplo de uso de "padre"
    auto nodoPadre = arbol.padre(6);
    if (nodoPadre == NULL)
        cout << "El nodo no tiene padre!\n";
    else
        cout << "Padre de 6: " << nodoPadre->dato << endl;
    */

    /*
    // Ejemplos de mínimo, máximo y sucesor
    cout << "Minimo: " << arbol.minimo() << endl;
    cout << "Maximo: " << arbol.maximo() << endl;
    Nodo* suc = arbol.sucesor(5);
    if (suc) cout << "Sucesor de 5: " << suc->dato << endl;
    */

    /*
    // Ejemplo de impresión en los tres órdenes
    cout << "En Orden: ";
    arbol.imprimirEnOrder();
    cout << "Post Orden: ";
    arbol.imprimirPostOrder();
    */

    return 0;
}