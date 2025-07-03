// ejercicio 1

#include <iostream>
using namespace std;

class Sesion {
public:
    static Sesion* get() {
        if (instancia == nullptr) {
            int pw;
            cout << "Ingrese su contraseña: ";
            cin >> pw;
            instancia = new Sesion();
        }
        return instancia;
    }
    void view() {
        cout << "Ingresando a la aplicacion...\n";
    }
private:
    static Sesion* instancia;
    Sesion() {}
};

Sesion* Sesion::instancia = nullptr;

int main() {
    Sesion* s = Sesion::get();
    s->view();
    return 0;
}
