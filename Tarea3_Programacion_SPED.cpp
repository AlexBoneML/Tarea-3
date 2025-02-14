#include <iostream>
#include <string>
using namespace std;

const int MAX=100;

class Empleado {
private:
    std::string clave;
    std::string nombre;
    std::string domicilio;
    float sueldo;
    std::string reporteA;

public:
    Empleado() {}
    Empleado(std::string c, std::string n, std::string d, float s, std::string r)
        : clave(c), nombre(n), domicilio(d), sueldo(s), reporteA(r) {}

    bool operator==(const Empleado &e) const { return clave == e.clave; }
    friend ostream &operator<<(ostream &os, const Empleado &e) {
        os << "Clave: " << e.clave << "\nNombre: " << e.nombre << "\nDomicilio: " << e.domicilio
           << "\nSueldo: " << e.sueldo << "\nReporta a: " << e.reporteA << "\n";
        return os;
    }
    friend istream &operator>>(istream &is, Empleado &e) {
        cout <<"\nIngrese clave: "; is >> e.clave;
        cout <<"\nIngrese nombre: "; is.ignore(); getline(is, e.nombre);
        cout <<"\nIngrese domicilio: "; getline(is, e.domicilio);
        cout <<"\nIngrese sueldo: "; is >> e.sueldo;
        cout <<"\nIngrese nombre de la persona a quien reporta: "; is.ignore(); getline(is, e.reporteA);
        return is;
    }
};

class ListaEstatica {
private:
    Empleado datos[MAX];
    int tam;

public:
    ListaEstatica() : tam(0) {}

    int Agrega(Empleado e){
        if (Llena()) return -1;
        datos[tam++]=e;
        return tam-1;
    }

    int Busca(Empleado e) {
        for (int i=0; i<tam; i++) {
            if (datos[i] == e) return i;
        }
        return -1;
    }

    int Elimina(int pos) {
        if (Vacia() || pos<0 || pos>=tam) return -1;
        for (int i = pos; i < tam-1; i++) {
            datos[i] = datos[i+1];
        }
        tam--;
        return 0;
    }

    int Inserta(Empleado e, int pos) {
        if (Llena() || pos<0 || pos > tam) return -1;
        for (int i=tam; i>pos; i--) {
            datos[i] =datos[i-1];
        }
        datos[pos] = e;
        tam++;
        return 0;
    }

    int Vacia(){ return tam==0; }
    int Llena(){ return tam==MAX; }

    void Muestra(){
        if (Vacia()){
            std::cout<<"\nLista vacia."<<endl;
            return;
        }
        for(int i=0; i<tam; i++) {
            std::cout<<datos[i]<<endl;
        }
    }
};

int main() {
    ListaEstatica lista;
    int opcion;
    do {
        std::cout<<"\nMenu:"<<endl;
        std::cout<<"\n 1. Agrega"<<endl;
        std::cout<<"\n 2. Buscar"<<endl;
        std::cout<<"\n 3. Elimina"<<endl;
        std::cout<<"\n 4. Inserta"<<endl;
        std::cout<<"\n 5. Muestra"<<endl;
        std::cout<<"\n 6. Salir"<<endl;
        std::cout<<"\n Seleccione una opcion: ";
        std::cin>>opcion;

        Empleado e;
        int pos;

        switch (opcion){
        case 1:
            std::cin>> e;
            if (lista.Agrega(e) == -1)
                std::cout<<"\nLista llena."<<endl;
            break;
        case 2:
            std::cin>>e;
            pos=lista.Busca(e);
            if(pos == -1)
                std::cout<<"\nEmpleado no encontrado."<<endl;
            else
                std::cout<<"\nEmpleado encontrado en posicion: "<<pos<< endl;
            break;
        case 3:
            std::cout<<"\nIngrese posicion a eliminar: ";
            std::cin>>pos;
            if(lista.Elimina(pos)==-1)
                std::cout<<"\nError al eliminar."<<endl;
            break;
        case 4:
            std::cin>>e;
            std::cout<<"\nIngrese posicion a insertar: ";
            std::cin>>pos;
            if (lista.Inserta(e, pos)==-1)
                std::cout<<"\nNo se puede insertar."<<endl;
            break;
        case 5:
            lista.Muestra();
            break;
        case 6:
            std::cout<<"Saliendo..."<<endl;
            break;
        default:
            std::cout<<"Opcion no valida."<<endl;
        }
    } while (opcion!=6);

    return 0;
}

