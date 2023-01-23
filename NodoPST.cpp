#include "NodoPST.h"
#include <iostream>

//crea un nodo del arbol PST a partir de los datos obtenidos por parametro
NodoPST::NodoPST(unsigned int p, long cE, long m, int i, NodoPST * men, NodoPST * may){
    prioridad = p;
    cantEmple = cE;
    mediana = m;
    index = i;
    menores = men;
    mayores = may;
}

//obtiene la prioridad del nodo
unsigned int NodoPST::obtenerPrioridad() const{
    return prioridad;
}

//obtiene la cantidad de empleados del nodo
long NodoPST::obtenerCantEmple() const{
    return cantEmple;
}

//obtiene la mediana del nodo
long NodoPST::obtenerMediana() const{
    return mediana;
}

//obtiene el indice correspondiente a la posicion de pRanking donde se encuentran
//los datos de la empresa
int NodoPST::obtenerIndex() const{
    return index;
}

//obtiene el subarbol izquierdo del nodo
NodoPST * NodoPST::obtenerMenores(){
    return menores;
}

//obtiene el subarbol derecho del nodo
NodoPST * NodoPST::obtenerMayores(){
    return mayores;
}

//determina si un nodo es hoja o no
bool NodoPST::esHoja() const{
    if ((menores == NULL) && (mayores == NULL))
        return true;

    return false;
}
