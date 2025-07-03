// Pilas

#include <iostream>
#include <stack>      // Para usar la estructura stack (pila)
using namespace std;

// Función que comprueba si los paréntesis en 'operacion' están bien balanceados
string validarParentesis(string operacion) {
    stack<char> parentesis;          // Pila para guardar paréntesis de apertura
    for (char c : operacion) {
        // Si es paréntesis de apertura, lo apilamos
        if (c == '(' || c == '{' || c == '[')
            parentesis.push(c);

        // Si es paréntesis de cierre, validamos contra el tope de la pila
        if (c == ')' || c == '}' || c == ']') {
            // 1) Si no hay apertura que hacer pop, la operación es inválida
            if (parentesis.empty())
                return "Operacion incorrecta!";

            // 2) Verificamos que el tipo coincida
            if ((c == ')' && parentesis.top() != '(') ||
                (c == ']' && parentesis.top() != '[') ||
                (c == '}' && parentesis.top() != '{'))
                return "Operacion incorrecta!";

            // 3) Si coincide, quitamos el paréntesis de apertura de la pila
            parentesis.pop();
        }
    }
    // Si al final queda algún paréntesis sin cerrar, es inválido
    if (!parentesis.empty())
        return "Operacion incorrecta!";

    // Si todo está balanceado, es correcto
    return "Operacion correcta";
}

// Función que convierte un número decimal a cadena binaria usando una pila
string decimalABinario(int decimal) {
    stack<int> binario;  // Pila para los dígitos binarios
    if (decimal == 0)    // Caso base: si es 0, devolvemos "0"
        return "0";

    // Mientras el número sea > 0, obtenemos el bit menos significativo
    while (decimal > 0) {
        int digito = decimal % 2;  // 0 o 1
        binario.push(digito);      // lo apilamos
        decimal /= 2;              // seguimos con el siguiente bit
    }

    // Construimos la cadena sacando los bits de la pila (MSB primero)
    string resultado;
    while (!binario.empty()) {
        resultado += to_string(binario.top());
        binario.pop();
    }
    return resultado;
}

// Clase que simula un editor de texto con historial de deshacer
class EditorTexto {
private:
    string texto;            // Contenido actual
    stack<string> historial; // Pila de estados para deshacer

public:
    // Añade texto al final y guarda el nuevo estado en el historial
    void agregarTexto(string entrada) {
        texto += entrada;       // Concatenamos la nueva entrada
        historial.push(texto);  // Guardamos el estado actualizado
    }

    // Devuelve el texto actual
    string getTexto() {
        return texto;
    }

    // Deshace el último cambio restaurando el estado anterior
    void deshacer() {
        if (historial.size() > 1) {
            historial.pop();           // Quitamos el estado actual
            texto = historial.top();   // Restauramos el anterior
        } else if (!historial.empty()) {
            // Si solo quedaba un estado, lo borramos y dejamos texto vacío
            historial.pop();
            texto = "";
        }
    }

    // Nota: no existe un método 'rehacer' en esta clase
};

int main() {
    // --- Ejemplo de uso del EditorTexto ---
    EditorTexto editor;

    editor.agregarTexto("Hola ");          // Insertamos "Hola "
    cout << editor.getTexto() << endl;     // Salida: Hola

    editor.agregarTexto("Mundo ");         // Ahora "Hola Mundo "
    editor.agregarTexto("en C++");         // Y luego "Hola Mundo en C++"
    cout << editor.getTexto() << endl;     // Salida: Hola Mundo en C++

    editor.deshacer();                     // Deshacemos "en C++"
    cout << editor.getTexto() << endl;     // Salida: Hola Mundo

    editor.deshacer();                     // Deshacemos "Mundo "
    cout << editor.getTexto() << endl;     // Salida: Hola

    // editor.rehacer();                   // ERROR: método no implementado

    // --- Ejemplo de decimalABinario ---
    /*
    int decimal = 42;
    string binario = decimalABinario(decimal);
    cout << decimal << " -> " << binario << endl; // 42 -> 101010
    */

    // --- Ejemplo de validarParentesis ---
    /*
    cout << validarParentesis("[1+(3*5)-3]}") << endl; // Operacion incorrecta!
    cout << validarParentesis("{1+[1-(3*4}/7]") << endl; // Operacion incorrecta!
    cout << validarParentesis("[1+(5*2)]") << endl;      // Operacion correcta
    cout << validarParentesis("[1+(5*2)") << endl;       // Operacion incorrecta
    */

    return 0;
}

