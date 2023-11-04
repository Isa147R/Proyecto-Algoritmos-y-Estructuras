#include <iostream>
#include "Contacto.h"

using namespace std;

#ifndef ARBOLCONTACTOS_H
#define ARBOLCONTACTOS_H

class NodoContacto {
public:
    Contacto contacto;
    NodoContacto* siguiente; // Puntero al siguiente nodo

    NodoContacto(const Contacto& c) : contacto(c), siguiente(nullptr) {}
};

class ArbolContactos {
private:
    NodoContacto* raiz; // Puntero a la raíz del árbol

    // Función auxiliar para insertar un nuevo nodo en el árbol
    NodoContacto* insertar(NodoContacto* nodo, const Contacto& nuevoContacto) {
        if (nodo == nullptr) {
            return new NodoContacto(nuevoContacto);
        }

        // Comparar los nombres y decidir la posición en el árbol
        if (nuevoContacto.nombre < nodo->contacto.nombre) {
            nodo->siguiente = insertar(nodo->siguiente, nuevoContacto);
        } else if (nuevoContacto.nombre > nodo->contacto.nombre) {
            nodo->siguiente = insertar(nodo->siguiente, nuevoContacto);
        } else {
            // Si los nombres son iguales, agregar a una lista enlazada
            NodoContacto* nuevoNodo = new NodoContacto(nuevoContacto);
            nuevoNodo->siguiente = nodo->siguiente;
            nodo->siguiente = nuevoNodo;
        }

        return nodo;
    }

    // Función auxiliar para realizar un recorrido inorden del árbol
    void inOrden(NodoContacto* nodo) const {
        if (nodo != nullptr) {
            inOrden(nodo->siguiente);  // Recorrer el subárbol izquierdo
            std::cout << nodo->contacto;
            // No hay subárbol derecho en tu implementación
        }
    }

public:
    // Constructor
    ArbolContactos() : raiz(nullptr) {}

    // Método para agregar un nuevo contacto al árbol
    void agregarContacto(const Contacto& nuevoContacto) {
        raiz = insertar(raiz, nuevoContacto);
    }

    // Método para mostrar la lista completa de contactos ordenados alfabéticamente por nombre
    void mostrarContactosOrdenados() const {
        inOrden(raiz);
    }
};

#endif
