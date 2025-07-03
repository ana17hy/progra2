#include <iostream>
#include <set>
using namespace std;

// PATRON ADAPTER

// Clase base para métodos de pago
class Pago {
public:
    virtual void pagar() = 0; // Método abstracto que se implementará en subclases
};

// Implementación del pago con tarjeta
class PagoTarjeta : public Pago {
public:
    void pagar() override {
        int nt, ccv;
        string fc;
        cout << "#Tarjeta: ";
        cin >> nt;
        cout << "CCV: ";
        cin >> ccv;
        cout << "MM/YY: ";
        cin >> fc;
        cout << "Pago Exitoso!" << endl;
    }
};

// Clase que representa el pago con PayPal (pero no hereda de Pago)
class PagoPayPal {
public:
    void pagodirecto(string user, string pw) {
        cout << "Pago con PayPal: user: " << user << ", pw: " << pw << endl;
    }
};

// Adaptador que permite usar PagoPayPal como si fuera un Pago
class AdaptadorPayPal : public Pago {
private:
    PagoPayPal* pago_paypal = new PagoPayPal(); // Composición con la clase real
public:
    void pagar() override {
        string user, pw;
        cout << "User: ";
        cin >> user;
        cout << "Password: ";
        cin >> pw;
        pago_paypal->pagodirecto(user, pw); // Usa el método de la clase adaptada
    }
};


// PATRON PROXY

// Interfaz común para sitios web
class SitioWeb {
public:
    virtual void visualizar() const = 0;
};

// Sitio web real, sin restricciones
class SitioWebSinProxy : public SitioWeb {
private:
    string url;

    void cargarDesdeServidor() {
        // Simula cargar el sitio desde internet
        cout << "Descargando el sitio web desde el servidor: " << url << endl;
    }

public:
    SitioWebSinProxy(const string& url) : url(url) {
        cargarDesdeServidor(); // Se carga al crearlo
    }

    void visualizar() const override {
        cout << "Visualizando el sitio web: " << url << endl;
    }
};

// Proxy que bloquea ciertos sitios web
class ProxySitioWeb : public SitioWeb {
private:
    // Lista de sitios bloqueados
    set<string> sitiosWebNoPermitidos = {
        "www.sitioprohibido1.com",
        "www.sitioprohibido2.com",
        "www.sitioprohibido3.com"
    };

    string url;
    SitioWebSinProxy sitio; // El objeto real

public:
    ProxySitioWeb(const string& url) : sitio(url), url(url) {}

    void visualizar() const override {
        // Verifica si el sitio está prohibido
        for (string urli : sitiosWebNoPermitidos) {
            if (url == urli)
                return; // No muestra nada si está prohibido
        }
        // Si no está prohibido, lo muestra
        sitio.visualizar();
    }
};


int main() {
    // Prueba del patrón Proxy
    SitioWeb* sitio;

    // Sitio permitido
    sitio = new ProxySitioWeb("www.sitiopermitido1.com");
    sitio->visualizar();

    // Sitio prohibido sin proxy (lo carga igual)
    sitio = new SitioWebSinProxy("www.sitioprohibido1.com");
    sitio->visualizar();

    // Sitio prohibido con proxy (no se muestra)
    sitio = new ProxySitioWeb("www.sitioprohibido1.com");
    sitio->visualizar();

    /*
    // Prueba del patrón Adapter
    Pago* pago;
    int op;
    cout << "¿Como quiere pagar? [Tarjeta:0, Paypal: 1]: ";
    cin >> op;

    if (op == 0)
        pago = new PagoTarjeta();       // Usa tarjeta
    else
        pago = new AdaptadorPayPal();   // Usa PayPal adaptado

    pago->pagar();
    */

    return 0;
}

