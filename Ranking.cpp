#include "Ranking.h"
#include "Empresa.h"
#include <iostream>

using namespace std;

//crea los arreglos pRanking, pAcceso y pEmpleado
Ranking::Ranking(unsigned int tamanio){
    if (tamanio > 0){
        pRanking = new Empresa[tamanio];
        pAcceso = new Casillero[tamanio];
        pEmpleado = new unsigned int[tamanio];
        this->tamanio = tamanio;
        this->indice = 0;
    } else {
        cout << "No se puede crear un ranking si no existen empresas." << endl;
    }
}

//agrega un elemento al arreglo pAcceso de manera ordenada por razon social
void Ranking::agregarEmpresaRanking(Empresa empresa){
    pRanking[indice] = empresa;
    insertarOrdenadoAcceso(empresa.consultarRazonSocialEmpresa(), indice + 1);
    insertarOrdenadoEmpleado(empresa.consultarCantEmpleadosEmpresa(), indice);
    indice++;
}

//inserta de forma ordenada un elemento en el arreglo pEmpleado
void Ranking::insertarOrdenadoEmpleado(long empleados, unsigned int dato){

    if (indice == 0){   //si es la primera empresa a agregar
        pEmpleado[indice] = dato;
    } else {
        int i ;
        for (i= indice - 1; (i >= 0 && pRanking[pEmpleado[i]].consultarCantEmpleadosEmpresa() > empleados); i--){
            pEmpleado[i + 1] = pEmpleado[i];
        }
        pEmpleado[i + 1] = dato;
    }
}

//inserta de forma ordenada un elemento en el arreglo pAcceso
void Ranking::insertarOrdenadoAcceso(string razon, unsigned int posRanking){
    Casillero aAgregar;
    aAgregar.razonSocial = razon;
    aAgregar.posRanking = posRanking;

    if (indice == 0){   //si es la primera empresa a agregar
        pAcceso[indice] = aAgregar;
    } else {
        int i ;
        for (i= indice - 1; (i >= 0 && pAcceso[i].razonSocial > razon); i--){
            pAcceso[i + 1] = pAcceso[i];
        }
        pAcceso[i + 1] = aAgregar;
    }
}

//retorna la longitud del ranking
unsigned int Ranking::longRanking() const{
    return tamanio;
}

//retorna la empresa que se encuentra en una posicion determinada del ranking
Empresa Ranking::consultarPosRanking(const unsigned int & pos) const{
    return pRanking[pos-1];
}

//realiza una busqueda binaria en el arreglo para encontrar la razon buscada,
//si lo hace, retorna su posicion en el arreglo pAcceso donde se encuentra
unsigned int Ranking::busBinRec(int minimo, int maximo, string razon){
    if (maximo < minimo) // no encontro la razon buscada
        return -1;
    int mitad = (minimo + maximo) / 2;
    if (razon == pAcceso[mitad].razonSocial)
        return mitad;
    if (razon > pAcceso[mitad].razonSocial)
        return busBinRec((mitad + 1), maximo, razon);
    return busBinRec(minimo, (mitad - 1), razon);
}

//dada una razon social, retorna la posicion en el ranking donde se encuentra la misma
unsigned int Ranking::consultarEmpresaRanking(string razonSocial){
    unsigned int posRazon = busBinRec(0, tamanio - 1, razonSocial);
    if (posRazon == -1 ){
       return 0;
    }
    return pAcceso[posRazon].posRanking;
}

//carga dentro de la variable empresas, las empresas que cuentan con un numero de empleados
//dentro del rango pasado por parametro
void Ranking::consultarRangoRanking(long minimo, long maximo, Coleccion<Empresa> & empresas){
    Empresa empresaActual;

    if ((minimo > 0) && (maximo >= minimo)){    //verifico que el rango ingresado sea valido
        cout << "Empresas con cantidad de empleados entre " << minimo << " y " << maximo << endl;
        for (unsigned int i=0; i<tamanio; i++){
            empresaActual = pRanking[i];
            if ((empresaActual.consultarCantEmpleadosEmpresa() >= minimo) && (empresaActual.consultarCantEmpleadosEmpresa() <= maximo)){
                empresas.agregar(empresaActual);
            }
        }
        if (empresas.cantidadElems() == 0){
            cout << "No existen empresas con el rango de empleados ingresado." << endl;
        }
    } else if (minimo <= 0)
        cout << "La cantidad minima de empleados de una empresa debe ser mayor que 0." << endl;
    else
        cout << "La cantidad maxima de empleados debe ser mayor que la cantidad minima." << endl;
}

//determina si el ranking esta vacio o no
bool Ranking::vacioRanking() const{
    return (indice == 0);
}

//dada la razon social de una empresa, determina si esta ya se encuentra
//en el ranking o no
bool Ranking::existeEmpresaRanking(string razonSocial){
    if (consultarEmpresaRanking(razonSocial) == 0){
        return false;
    }
    return true;
}

//devuelve un puntero al arreglo pRanking
Empresa* Ranking::obtenerRanking(){
    return pRanking;
}

//devuelve un puntero al arreglo pEmpleado
unsigned int * Ranking::obtenerEmpleados(){
    return pEmpleado;
}

//destructor
/*
Ranking::~Ranking(){
    delete[] pRanking;
    delete[] pAcceso;
}
*/
