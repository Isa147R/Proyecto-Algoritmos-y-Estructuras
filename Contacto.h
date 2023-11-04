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
