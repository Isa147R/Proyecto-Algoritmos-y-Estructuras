#include <iostream>
#include <string>

using namespace std;

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
          
};

int main() {
    // Crear instancias de la clase Contacto
    Contacto contacto1("Juan Perez", "123456789", "juanperez", "icono1", "123 Main St");
    Contacto contacto2("Maria Garcia", "987654321", "mariagarcia", "icono2", "456 Elm St");

    // Mostrar la información de los contactos
    cout << "Contacto 1:\n";
    cout << "Nombre: " << contacto1.nombre << "\nTeléfono: " << contacto1.telefono << "\nRedes Sociales: "
         << contacto1.redes_sociales << "\nIcono: " << contacto1.icono << "\nDirección: " << contacto1.direccion << "\n\n";

    cout << "Contacto 2:\n";
    cout << "Nombre: " << contacto2.nombre << "\nTeléfono: " << contacto2.telefono << "\nRedes Sociales: "
         << contacto2.redes_sociales << "\nIcono: " << contacto2.icono << "\nDirección: " << contacto2.direccion << "\n";

    return 0;
}
