#include <iostream>
#include <string>
#include <algorithm>
#include <fstream>
#include <vector>


class Contacto {
  public:
      std::string nombre;
      std::string telefono;
      std::string redes_sociales;
      std::string icono;
      std::string direccion;
  
      Contacto(std::string n, std::string t, std::string rs, std::string i, std::string d){
        nombre = n;
        telefono = t;
        redes_sociales = rs;
        icono = i;
        direccion = d;
  
      }

      friend std::ostream& operator<<(std::ostream& os, const Contacto& contacto) {
        os << "Nombre: " << contacto.nombre << "\nTeléfono: " << contacto.telefono
           << "\nRedes Sociales: " << contacto.redes_sociales << "\nIcono: " << contacto.icono
           << "\nDirección: " << contacto.direccion << "\n";
        return os;
    } 
          
};


class LibretaContactos {
private:

    std::vector<Contacto> contactos;

public:
    // Agregar un nuevo contacto
    void agregarContacto(const Contacto& nuevoContacto) {
        contactos.emplace_back(nuevoContacto);
    }

    // Mostrar la cantidad total de contactos en la libreta
    void mostrarCantidadContactos() const {
        std::cout << "Total de contactos: " << contactos.size() << "\n";
    }

    // Buscar un contacto por nombre y mostrar su información completa

    // Eliminar un contacto existente por nombre

    // Mostrar la lista completa de contactos ordenados alfabéticamente por nombre

    

    // Mostrar los contactos cuyos nombres comienzan con una letra específica
    void mostrarContactosPorLetra(char letra) const {
        for (const auto& contacto : contactos) {
            if (contacto.nombre[0] == letra) {
                std::cout << contacto;
            }
        }
    }

    // Realizar una copia de seguridad de la libreta de contactos en un archivo de texto
    void realizarCopiaDeSeguridad(const std::string& nombreArchivo) const {
        std::ofstream archivo(nombreArchivo);
        if (archivo.is_open()) {
            for (const auto& contacto : contactos) {
                archivo << contacto.nombre << "," << contacto.telefono << "," << contacto.redes_sociales << ","
                        << contacto.icono << "," << contacto.direccion << "\n";
            }
            archivo.close();
            std::cout << "Copia de seguridad realizada con éxito.\n";
        } else {
            std::cerr << "Error al abrir el archivo para copia de seguridad: " << nombreArchivo << '\n';
        }
    }
};

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

int main() {
    // Crear instancias de la clase Contacto
    Contacto contacto1("Juan Perez", "123456789", "@juanperez", "👤", "Calle A");
    Contacto contacto2("Maria Lopez", "987654321", "@marialopez", "👩", "Calle B");
    Contacto contacto3("Carlos Gomez", "555555555", "@carlosgomez", "👨", "Calle C");
    Contacto contacto4("Ana Perez", "123456789", "@juanperez", "👤", "Calle A");

    // Crear una instancia de la clase ArbolContactos
    ArbolContactos arbol;

    // Agregar contactos al árbol
    arbol.agregarContacto(contacto1);
    arbol.agregarContacto(contacto2);
    arbol.agregarContacto(contacto3);
    arbol.agregarContacto(contacto4);

    // Mostrar la lista de contactos ordenados alfabéticamente por nombre
    std::cout << "Lista de contactos ordenados:\n";
    arbol.mostrarContactosOrdenados();

    return 0;
}
