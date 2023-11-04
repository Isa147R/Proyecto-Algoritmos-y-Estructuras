#include <iostream>
#include <vector>
#include <algorithm>
#include <fstream>

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

int main() {
    LibretaContactos libreta;

    // Agregar un nuevo contacto
    libreta.agregarContacto(Contacto("Juan", "123456789", "@juan", "👤", "Calle 123"));
    libreta.agregarContacto(Contacto("María", "987654321", "@maria", "👩", "Avenida XYZ"));

    // Mostrar la cantidad total de contactos en la libreta
    libreta.mostrarCantidadContactos();

    // Buscar un contacto por nombre y mostrar su información completa

    // Eliminar un contacto existente por nombre

    // Mostrar la lista completa de contactos ordenados alfabéticamente por nombre

    // Mostrar los contactos cuyos nombres comienzan con una letra específica
    libreta.mostrarContactosPorLetra('M');

    // Realizar una copia de seguridad de la libreta de contactos en un archivo de texto
    libreta.realizarCopiaDeSeguridad("copia_seguridad.txt");

    return 0;
}
