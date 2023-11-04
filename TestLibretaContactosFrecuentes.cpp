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
    int consultas;  // Nuevo atributo para contar las consultas

    Contacto(std::string n, std::string t, std::string rs, std::string i, std::string d)
        : nombre(n), telefono(t), redes_sociales(rs), icono(i), direccion(d), consultas(0) {}

    friend std::ostream& operator<<(std::ostream& os, const Contacto& contacto) {
        os << "Nombre: " << contacto.nombre << "\nTeléfono: " << contacto.telefono
           << "\nRedes Sociales: " << contacto.redes_sociales << "\nIcono: " << contacto.icono
           << "\nDirección: " << contacto.direccion << "\nConsultas: " << contacto.consultas << "\n";
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

    // Método para buscar un contacto por nombre en el índice rápido y mostrar su información completa
    void buscarContactoPorNombre(const std::string& nombre) {
        auto it = std::lower_bound(indiceNombre.begin(), indiceNombre.end(), nombre);
        if (it != indiceNombre.end() && *it == nombre) {
            // Encontrado en el índice rápido, obtener el índice y mostrar la información completa
            int indice = std::distance(indiceNombre.begin(), it);
            contactos[indice].consultas++; // Incrementar contador de consultas
            std::cout << contactos[indice];
        } else {
            std::cout << "Contacto no encontrado.\n";
        }
    }

    // Método para mostrar los contactos más consultados
    void mostrarContactosMasConsultados(int numContactos) const {
        // Crear un vector de pares (nombre del contacto, consultas) y ordenarlo por consultas descendente
        std::vector<std::pair<std::string, int>> contactosConsultados;
        for (const auto& contacto : contactos) {
            contactosConsultados.push_back({contacto.nombre, contacto.consultas});
        }
        std::sort(contactosConsultados.begin(), contactosConsultados.end(),
                  [](const auto& a, const auto& b) {
                      return a.second > b.second;
                  });

        // Mostrar los contactos más consultados
        std::cout << "Contactos más consultados:\n";
        for (int i = 0; i < std::min(numContactos, static_cast<int>(contactosConsultados.size())); ++i) {
            std::cout << "Nombre: " << contactosConsultados[i].first << " - Consultas: " << contactosConsultados[i].second << "\n";
        }
    }

};


int main() {
    LibretaContactos libreta;

    // Agregar algunos contactos
    libreta.agregarContacto(Contacto("Juan Perez", "123456789", "@juanperez", "icono1", "Calle 123"));
    libreta.agregarContacto(Contacto("Andres", "987654321", "@andres", "icono2", "Avenida XYZ"));
    libreta.agregarContacto(Contacto("Maria Rodriguez", "987654321", "@mariarodriguez", "icono2", "Avenida XYZ"));


    // Buscar y mostrar un contacto por nombre
    libreta.buscarContactoPorNombre("Juan Perez");
    libreta.buscarContactoPorNombre("Juan Perez");
    libreta.buscarContactoPorNombre("Juan Perez");
    libreta.buscarContactoPorNombre("Andres");
    libreta.buscarContactoPorNombre("Andres");

    // Mostrar la lista completa de contactos
    libreta.mostrarCantidadContactos();

    // Realizar una copia de seguridad (se realizará periódicamente en segundo plano)
    // LibretaContactos destruirá el hilo de copia de seguridad al salir del alcance
    std::this_thread::sleep_for(std::chrono::seconds(5));  // Esperar un tiempo para que se realice la copia de seguridad
    // (Nota: en un entorno real, esto se haría de manera automática en segundo plano)

    // Mostrar los contactos más consultados
    libreta.mostrarContactosMasConsultados(3);

    return 0;
}
