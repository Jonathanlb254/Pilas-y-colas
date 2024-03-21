#include <iostream>
using namespace std;

// Definición de la estructura para los nodos de la pila y la cola
struct Nodo {
    int dato;
    Nodo* siguiente;
};

// Implementación de la pila
class Pila {
private:
    Nodo* cima;
public:
    Pila() {
        cima = NULL;
    }

    ~Pila() {
        while (!estaVacia()) {
            desapilar();
        }
    }

    void apilar(int dato) {
        Nodo* nuevo = new Nodo;
        nuevo->dato = dato;
        nuevo->siguiente = cima;
        cima = nuevo;
    }

    bool estaVacia() {
        return cima == NULL;
    }

    int desapilar() {
        if (!estaVacia()) {
            int dato = cima->dato;
            Nodo* temp = cima;
            cima = cima->siguiente;
            delete temp;
            return dato;
        }
        return -1; // Si la pila está vacía, retorna -1 (considera manejar esto según tu aplicación)
    }

    int obtenerCima() {
        if (!estaVacia()) {
            return cima->dato;
        }
        return -1; // Si la pila está vacía, retorna -1 (considera manejar esto según tu aplicación)
    }
};

// Implementación de la cola
class Cola {
private:
    Nodo* frente;
    Nodo* fin;
public:
    Cola() {
        frente = NULL;
        fin = NULL;
    }

    ~Cola() {
        while (!estaVacia()) {
            desencolar();
        }
    }

    void encolar(int dato) {
        Nodo* nuevo = new Nodo;
        nuevo->dato = dato;
        nuevo->siguiente = NULL;
        if (estaVacia()) {
            frente = nuevo;
            fin = nuevo;
        } else {
            fin->siguiente = nuevo;
            fin = nuevo;
        }
    }

    bool estaVacia() {
        return frente == NULL;
    }

    int desencolar() {
        if (!estaVacia()) {
            int dato = frente->dato;
            Nodo* temp = frente;
            frente = frente->siguiente;
            delete temp;
            return dato;
        }
        return -1; // Si la cola está vacía, retorna -1 (considera manejar esto según tu aplicación)
    }

    int obtenerFrente() {
        if (!estaVacia()) {
            return frente->dato;
        }
        return -1; // Si la cola está vacía, retorna -1 (considera manejar esto según tu aplicación)
    }
};

int main() {
    Pila pila_prioridades[5]; // Creamos un array de 5 pilas para manejar 5 niveles de prioridad (de 0 a 4)
    Cola cola_global; // Cola que almacenará todos los datos

    int dato, prioridad;
    char opcion;

    do {
        cout << "Ingrese un dato: ";
        cin >> dato;
        cout << "Ingrese el nivel de prioridad (de 0 a 4): ";
        cin >> prioridad;

        if (prioridad < 0 || prioridad > 4) {
            cout << "Prioridad inválida. Debe estar entre 0 y 4." << endl;
            continue;
        }

        pila_prioridades[prioridad].apilar(dato); // Apilamos el dato en la pila correspondiente al nivel de prioridad
        cola_global.encolar(prioridad); // Encolamos la prioridad en la cola global

        cout << "¿Desea ingresar otro dato? (s/n): ";
        cin >> opcion;
    } while (opcion == 's' || opcion == 'S');

    // Proceso de eliminación de datos según prioridad
    for (int i = 4; i >= 0; i--) { // Empezamos desde la prioridad más alta (4)
        while (!pila_prioridades[i].estaVacia()) {
            int dato_eliminar = pila_prioridades[i].desapilar();
            cout << "Eliminando dato con prioridad " << i << ": " << dato_eliminar << endl;
            // Eliminar el elemento de la cola global
            while (!cola_global.estaVacia() && cola_global.obtenerFrente() != i) {
                cola_global.desencolar();
            }
            if (!cola_global.estaVacia()) {
                cola_global.desencolar();
            }
        }
    }

    return 0;
}

