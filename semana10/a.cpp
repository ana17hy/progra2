// Patrones de diseño I

// Ejemplo 1
#include <iostream>
#include <vector>
using namespace std;

// ===== Ejercicio 1: Sesion (Singleton) =====
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

// ===== Ejercicio 3: SQLQueryBuilder (Builder Pattern) =====
class SQLQueryBuilder {
private:
    string query;
    string tabla;
    vector<string> columnas;
    string filtro_columna;
    string filtro_valor;
    string orden;
    int limite = -1;
public:
    SQLQueryBuilder& setTable(string table) {
        tabla = table;
        return *this;
    }
    SQLQueryBuilder& addColumn(string columna) {
        columnas.push_back(columna);
        return *this;
    }
    SQLQueryBuilder& setWhereClause(string columna, string valor) {
        filtro_columna = columna;
        filtro_valor = valor;
        return *this;
    }
    SQLQueryBuilder& setOrderByClause(string orden) {
        this->orden = orden;
        return *this;
    }
    SQLQueryBuilder& setLimit(int limit) {
        this->limite = limit;
        return *this;
    }
    string build() {
        query = "SELECT ";
        for (int i = 0; i < columnas.size(); i++) {
            query += columnas[i];
            if (i != columnas.size() - 1)
                query += ", ";
        }
        query += " FROM " + tabla;
        if (!filtro_columna.empty())
            query += " WHERE " + filtro_columna + " = '" + filtro_valor + "'";
        if (!orden.empty())
            query += " ORDER BY " + orden;
        if (limite != -1)
            query += " LIMIT " + to_string(limite);
        return query;
    }
};

// ===== Función main: Ejecuta ambos ejercicios =====
int main() {
    // 🧪 Ejercicio 1: Singleton
    Sesion* s1 = Sesion::get();
    s1->view();
    Sesion* s2 = Sesion::get();
    s2->view();

    cout << "------------------------------------" << endl;

    // 🧪 Ejercicio 3: SQL Builder
    try {
        string query = SQLQueryBuilder()
            .setTable("empleados")
            .addColumn("id")
            .addColumn("nombre")
            .addColumn("puesto")
            .setWhereClause("puesto", "Analista")
            .setOrderByClause("nombre ASC")
            .setLimit(5)
            .build();

        cout << "Consulta generada:\n" << query << endl;
    } catch (const exception& e) {
        cerr << "Error al construir la consulta: " << e.what() << endl;
    }

    return 0;
}
