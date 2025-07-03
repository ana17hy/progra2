// PATRONES DE DISEÑO II

#include <iostream>
#include <set>       // conjunto ordenado
using namespace std;

/*
// Ejemplo de Adapter

// Interfaz de pago genérico
 class Pago {
public:
    virtual void pagar() = 0;  // método puro para pagar
};

// Implementación de Pago con tarjeta
class PagoTarjeta : public Pago {
public:
    void pagar() override {
        int nt, ccv;
        string fc;
        cout << "#Tarjeta: ";
        cin >> nt;           // lee número de tarjeta
        cout << "CCV: ";
        cin >> ccv;          // lee código CCV
        cout << "MM/YY: ";
        cin >> fc;           // lee fecha de expiración
        cout << "Pago Exitoso!" << endl;
    }
};

// Clase PayPal que no implementa la interfaz Pago
class PagoPayPal {
public:
    void pagodirecto(string user, string pw){
        // método específico de PayPal
        cout << "Pago con PayPal: user: " << user
             << ", pw: " << pw << endl;
    }
};

// Adaptador para usar PagoPayPal como Pago
class AdaptadorPayPal: public Pago {
private:
    PagoPayPal* pago_paypal;   // instancia interna de PayPal
public:
    void pagar() override {
        string user, pw;
        cout << "User: ";
        cin >> user;           // lee usuario PayPal
        cout << "Password: ";
        cin >> pw;             // lee contraseña PayPal
        pago_paypal->pagodirecto(user, pw);
    }
};
*/

// Ejemplo de Proxy para controlar acceso

// Interfaz común para visualizar un sitio web
class SitioWeb {
public:
    virtual void visualizar() const = 0;  // método puro
};

// Implementación que descarga y muestra la página directamente
class SitioWebSinProxy : public SitioWeb {
private:
    string url;  // URL del sitio

    // Simula la descarga inicial desde el servidor
    void cargarDesdeServidor() {
        cout << "Descargando el sitio web desde el servidor: "
             << url << endl;
    }

public:
    // Constructor: recibe la URL y descarga la página
    SitioWebSinProxy(const string& url)
        : url(url) {
        cargarDesdeServidor();
    }

    // Muestra el sitio descargado
    void visualizar() const override {
        cout << "Visualizando el sitio web: "
             << url << endl;
    }
};

// Proxy que filtra sitios prohibidos antes de mostrar
class ProxySitioWeb : public SitioWeb {
private:
    // Lista de URLs no permitidas
    set<string> sitiosWebNoPermitidos = {
        "www.sitioprohibido1.com",
        "www.sitioprohibido2.com",
        "www.sitioprohibido3.com"
    };
    string url;                   // URL solicitada
    SitioWebSinProxy sitio;       // objeto real sin proxy

public:
    // Constructor crea el objeto real con la misma URL
    ProxySitioWeb(const string& url)
        : sitio(url), url(url) {}

    // Antes de visualizar revisa si la URL está en la lista negra
    void visualizar() const override {
        // Si está prohibida simplemente no hace nada
        if (sitiosWebNoPermitidos.count(url)) {
            return;
        }
        // Si no está prohibida delega al objeto real
        sitio.visualizar();
    }
};

int main() {
    // Usamos el Proxy para un sitio permitido
    SitioWeb* sitio = new ProxySitioWeb("www.sitiopermitido1.com");
    sitio->visualizar();
    // Salida: descarga + visualización

    // Creamos directamente sin proxy (descarga siempre)
    sitio = new SitioWebSinProxy("www.sitioprohibido1.com");
    sitio->visualizar();
    // Salida: descarga + visualización (no pasa por el Proxy)

    // Usamos Proxy para un sitio prohibido
    sitio = new ProxySitioWeb("www.sitioprohibido1.com");
    sitio->visualizar();
    // Sin salida pues la URL está en la lista negra

    /*
    // Ejemplo de uso de Adapter de Pago

    Pago* pago;
    int op;
    cout << "¿Como quiere pagar? [Tarjeta:0, Paypal: 1]: ";
    cin >> op;
    if (op == 0)
        pago = new PagoTarjeta();
    else
        pago = new AdaptadorPayPal();
    pago->pagar();
     */

    return 0;
}
