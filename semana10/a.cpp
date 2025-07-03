// Patrones de diseño I

// Ejemplo 1

#include <iostream>
#include <vector>
using namespace std;

struct red {
static int archivo;
string usuario;
red(string usr): usuario(usr) {}
static int get() {
//usuario = "nuevo";
return archivo;
}
};
int red::archivo = 3;
class Singleton {
private:
static Singleton* instance;
// Constructor privado
Singleton() {}
public:
static Singleton* getInstance() {
if (instance == nullptr) { // Si es la primera vez que se llama al metodo
instance = new Singleton();
}
return instance;
}
};

Singleton* Singleton::instance = nullptr;