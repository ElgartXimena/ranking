#include "PST.h"
#include "Ranking.h"
#include <iostream>

#include "Empresa.h"

using namespace std;

//crea un arbol a partir del ranking obtenido por parametro
PST::PST(Ranking ranking){
    arbol = construirPST(ranking.obtenerRanking(), ranking.obtenerEmpleados(), 0, ranking.longRanking()-1);
};

//determina si un arbol es vacio
bool PST::vacioPST() const{
    return (arbol == NULL);
}

//calcula la mediana segun la cantidad de empleados en el rango obtenido por incio y fin
long PST::calcularMediana(Empresa * pRanking, unsigned int a[], unsigned int inicio, unsigned int fin){
    //verifico si es impar
    if ((fin-inicio+1) % 2 != 0) // fin-inicio+1 nos da la cantidad de elementos
        return pRanking[a[(inicio + fin) / 2]].consultarCantEmpleadosEmpresa();

    unsigned int cantEmpleMedio1 = pRanking[a[(inicio + fin) / 2]].consultarCantEmpleadosEmpresa();
    unsigned int cantEmpleMedio2 = pRanking[a[((inicio + fin) / 2) + 1]].consultarCantEmpleadosEmpresa();
    return (cantEmpleMedio1 + cantEmpleMedio2) / 2;

}

//busca en pEmpleado, entre el rango definido por incio y fin, el elemento mas chico, que nos indica
//la posicion del arreglo pRanking en la que se encuentra la empresa de menor prioridad
int PST::obtenerIndice(Empresa * pRanking, unsigned int pEmpleado[], unsigned int inicio, unsigned int fin, int &indice) const{
    int pos = pEmpleado[inicio];
    indice = 0;
    unsigned int minimo = pRanking[pEmpleado[inicio]].consultarPosRankingEmpresa();

    for(int i = inicio + 1; i <= fin; i++){
        unsigned int aux = pRanking[pEmpleado[i]].consultarPosRankingEmpresa();
        if (aux < minimo){
            minimo = aux;
            pos = pEmpleado[i];
            indice = i;
        }
    }
    return pos;
}

//realiza un corrimiento a izquierda para eliminar el elemento apuntado por pos y
//agrega un -1 al final
void PST::eliminar(unsigned int pEmpleado[], int pos, unsigned int fin){
    for(int i = pos; i<fin; i++)
        pEmpleado[i] = pEmpleado[i+1];

    pEmpleado[fin] = -1;
}

//contruye un nodo del arbol PST con los datos obtenidos por parametro
NodoPST * PST::construirNodo(Empresa * pRanking, unsigned int indice, long valorMedio, NodoPST * men, NodoPST * may){
    unsigned int prioridad = pRanking[indice].consultarPosRankingEmpresa();
    long cantEmple = pRanking[indice].consultarCantEmpleadosEmpresa();

    NodoPST * aAgregar = new NodoPST(prioridad, cantEmple, valorMedio, indice, men, may);

    return aAgregar;
}

//construye el arbol PST a partir del arreglo pEmpleado obteniendo los datos de pRanking
NodoPST * PST::construirPST(Empresa * pRanking, unsigned int pEmpleado[], unsigned int inicio, unsigned int fin){
    if (inicio > fin)
        return NULL;
    else if (inicio == fin){
        long  valorMedio = -1;
        NodoPST * arbol = construirNodo(pRanking, pEmpleado[inicio], valorMedio, NULL, NULL);

        return arbol;
    }
    else {
        int iEmple;
        int indiceMenorPriori = obtenerIndice (pRanking, pEmpleado, inicio, fin, iEmple);
        eliminar(pEmpleado, iEmple, fin);
        fin--; //resto uno porque elimine un elemento

        long valorMedio;
        if (inicio < fin)
            valorMedio = calcularMediana(pRanking, pEmpleado, inicio, fin);
        else
            valorMedio = -1;

        unsigned int mitad = (inicio + fin) / 2;
        NodoPST * menores;
        NodoPST * mayores;

        //de acuerdo a la cantidad de elementos, elijo distintas mitades para que aquellos que son
        //mayores o iguales a la mediana queden a la derecha
        if (((fin-inicio+1) % 2 != 0) && (mitad != 0)){
            menores = construirPST(pRanking, pEmpleado, inicio, mitad-1);
            mayores = construirPST(pRanking, pEmpleado, mitad, fin);
        }
        else{
            menores = construirPST(pRanking, pEmpleado, inicio, mitad);
            mayores = construirPST(pRanking, pEmpleado, mitad+1, fin);
        }

        NodoPST * arbol = construirNodo(pRanking, indiceMenorPriori, valorMedio, menores, mayores);

        return arbol;
    }
}

//llama a buscarEmpresasPSTRec para resolver el Servicio 4, si los parametros obtenidos cumplen las condiciones
void PST::buscarEmpresasPST(Empresa * pRanking, unsigned int prioridad, long minimo, long maximo, Coleccion<Empresa> &empresas){
    if ((minimo > 0) && (maximo >= minimo))    //verifico que el rango ingresado sea valido
        buscarEmpresasPSTRec(arbol, pRanking, prioridad, minimo, maximo, empresas);
    else if (minimo <= 0)
        cout << "\nLa cantidad minima de empleados de una empresa debe ser mayor que 0." << endl;
    else
        cout << "\nLa cantidad maxima de empleados debe ser mayor que la cantidad minima." << endl;
}

//busca en el arbol PST las primeras N empresas que tienen una cantidad de empleados entre el minimo y maximo
void PST::buscarEmpresasPSTRec(NodoPST * arbol, Empresa * pRanking, unsigned int prioridad, long minimo, long maximo, Coleccion<Empresa> &empresas){
        if (arbol->esHoja()){
            if(((arbol->obtenerPrioridad()) <= prioridad) && (minimo <= (arbol->obtenerCantEmple())) && ((arbol->obtenerCantEmple())<= maximo))
                empresas.agregar(pRanking[arbol->obtenerIndex()]);
        }
        else{
            if (arbol->obtenerPrioridad() <= prioridad){
                if ((minimo <= (arbol->obtenerCantEmple())) && ((arbol->obtenerCantEmple())<= maximo))
                    empresas.agregar(pRanking[arbol->obtenerIndex()]);

                if (minimo < (arbol->obtenerMediana()))
                    buscarEmpresasPSTRec(arbol->obtenerMenores(), pRanking, prioridad, minimo, maximo, empresas);

                if ((arbol->obtenerMediana()) < maximo)
                    buscarEmpresasPSTRec(arbol->obtenerMayores(), pRanking, prioridad, minimo, maximo, empresas);
            }
        }
}

//destructor
PST::~PST(){
    eliminarArbolRec(arbol);
}


void PST::eliminarArbolRec(NodoPST * actual){
    if (actual != NULL){
        eliminarArbolRec(actual->obtenerMenores());
        eliminarArbolRec(actual->obtenerMayores());
        delete actual;
        actual = NULL;
    }
}
