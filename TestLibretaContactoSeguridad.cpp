#include <iostream>
#include <iostream>
#include <vector>
#include <algorithm>
#include <fstream>
#include <queue>
#include <thread>
#include <chrono>

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
    std::vector<std::string> indiceNombre;
    std::queue<std::string> colaCopias; // Cola para almacenar nombres de archivos de copia de seguridad

    std::thread hiloCopiaSeguridad; // Hilo para realizar copias de seguridad

public:
    // Constructor
    LibretaContactos() {
        // Iniciar el hilo para realizar copias de seguridad periódicas
        hiloCopiaSeguridad = std::thread(&LibretaContactos::realizarCopiasPeriodicas, this);
    }

    // Destructor
    ~LibretaContactos() {
        // Esperar a que el hilo termine antes de destruir la instancia
        hiloCopiaSeguridad.join();
    }

    // Mostrar la cantidad total de contactos en la libreta
    void mostrarCantidadContactos() const {
        std::cout << "Total de contactos: " << contactos.size() << "\n";
    }

    // Método para agregar un nuevo contacto al índice y al vector de contactos
    void agregarContacto(const Contacto& nuevoContacto) {
        contactos.emplace_back(nuevoContacto);
        indiceNombre.push_back(nuevoContacto.nombre);
        // Ordenar el índice rápido para mantenerlo actualizado
        std::sort(indiceNombre.begin(), indiceNombre.end());
    }

    // Método para buscar un contacto por nombre en el índice rápido y mostrar su información completa
    void buscarContactoPorNombre(const std::string& nombre) const {
        auto it = std::lower_bound(indiceNombre.begin(), indiceNombre.end(), nombre);
        if (it != indiceNombre.end() && *it == nombre) {
            // Encontrado en el índice rápido, obtener el índice y mostrar la información completa
            int indice = std::distance(indiceNombre.begin(), it);
            std::cout << contactos[indice];
        } else {
            std::cout << "Contacto no encontrado.\n";
        }
    }

    // Buscar un contacto por nombre y mostrar su información completa

    // Eliminar un contacto existente por nombre

    // Mostrar la lista completa de contactos ordenados alfabéticamente por nombre

    // Método para eliminar un contacto por nombre del índice y del vector de contactos
    void eliminarContactoPorNombre(const std::string& nombre) {
        auto it = std::lower_bound(indiceNombre.begin(), indiceNombre.end(), nombre);
        if (it != indiceNombre.end() && *it == nombre) {
            // Encontrado en el índice rápido, obtener el índice y eliminar el contacto
            int indice = std::distance(indiceNombre.begin(), it);
            contactos.erase(contactos.begin() + indice);
            indiceNombre.erase(it);
        } else {
            std::cout << "Contacto no encontrado.\n";
        }
    }

    // Mostrar los contactos cuyos nombres comienzan con una letra específica
    void mostrarContactosPorLetra(char letra) const {
        for (const auto& contacto : contactos) {
            if (contacto.nombre[0] == letra) {
                std::cout << contacto;
            }
        }
    }

    // Método para realizar copias de seguridad periódicas
    void realizarCopiasPeriodicas() {
        while (true) {
            // Esperar 24 horas entre copias de seguridad
            std::this_thread::sleep_for(std::chrono::hours(24));

            // Realizar una copia de seguridad utilizando un nombre de archivo único (puedes personalizar esto)
            std::string nombreArchivo = "copia_seguridad_" + obtenerFechaHoraActual() + ".txt";
            realizarCopiaDeSeguridad(nombreArchivo);
        }
    }

    /// Realizar una copia de seguridad de la libreta de contactos en un archivo de texto
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

    // Método para obtener la fecha y hora actual (puedes personalizar esto según tus necesidades)
    std::string obtenerFechaHoraActual() const {
        // Implementación de ejemplo: obtener la fecha y hora actual como una cadena
        // Puedes usar bibliotecas como <ctime> o <chrono> para obtener la fecha y hora actual con más precisión
        return "fecha_hora_actual";
    }
};

int main() {
    // Crear una instancia de LibretaContactos
    LibretaContactos libreta;

    // Agregar algunos contactos de ejemplo
    Contacto contacto1("Juan", "123456789", "@juanito", "icono1", "Direccion1");
    Contacto contacto2("Maria", "987654321", "@maria", "icono2", "Direccion2");
    Contacto contacto3("Carlos", "555555555", "@carlos", "icono3", "Direccion3");

    // Agregar contactos a la libreta
    libreta.agregarContacto(contacto1);
    libreta.agregarContacto(contacto2);
    libreta.agregarContacto(contacto3);

    // Mostrar la cantidad total de contactos
    libreta.mostrarCantidadContactos();

    // Buscar un contacto por nombre
    libreta.buscarContactoPorNombre("Maria");

    // Realizar una copia de seguridad manual
    std::cout << "Realizando copia de seguridad manual...\n";
    libreta.realizarCopiaDeSeguridad("copia_manual.txt");

    // Eliminar un contacto por nombre
    libreta.eliminarContactoPorNombre("Juan");

    // Mostrar la lista completa de contactos
    // Ordenados alfabéticamente por nombre
    std::cout << "Lista completa de contactos:\n";
    // (Puedes implementar este método en la clase LibretaContactos)
    // libreta.mostrarListaCompleta();

    // Mostrar contactos cuyos nombres comienzan con una letra específica
    std::cout << "Contactos cuyos nombres comienzan con la letra 'C':\n";
    libreta.mostrarContactosPorLetra('C');

    return 0;
}
