#include "Coleccion.h"
#include "Empresa.h"
#include <iostream>
#include <assert.h>

using namespace std;

//inicializa una coleccion vacia
template <typename T>
Coleccion<T>::Coleccion(){
    cantidad = 0;
    punt = NULL;
};

//dado un elemento, crea un nodo y lo agrega al principio de la lista
//lleva la cuenta de la cantidad de elementos agregados
template <typename T>
void Coleccion<T>::agregar(T elemento){
    Nodo * aAgregar = new Nodo();
    aAgregar->elemento = elemento;
    if (punt == NULL){
        punt = aAgregar;
        aAgregar->sig = NULL;
    } else {
        aAgregar->sig = punt;
        punt = aAgregar;
    }
    cantidad++;
}

//recorre la coleccion, comparando los elementos de los nodos con uno previamente dado
//y determina si el elemento se encuentra o no en ella
//si llega a NULL, no encontro el elemento
template <typename T>
bool Coleccion<T>::perteneceRec(Nodo * actual, T elemento){
    if (actual != NULL){
        if (actual->elemento == elemento){
            return true;
        } else {
            perteneceRec(actual->sig, elemento);
        }
    } else {
        return false;
    }
}

//dado un elemento, determina si se encuentra en la coleccion
template <typename T>
bool Coleccion<T>::pertenece(T elemento){
    return perteneceRec(punt, elemento);
}

//devuelve la cantidad de elementos de la coleccion
template <typename T>
unsigned int Coleccion<T>::cantidadElems() const{
    return cantidad;
}

//determina si la coleccion esta vacia o no
template <typename T>
bool Coleccion<T>::esVacio() const{
    return punt == NULL;
}

//inicializa el cursor en el primer elemento de la Coleccion.
template <typename T>
void Coleccion<T>::inicCursor(){

    cursor = punt;
}

//avanza el cursor al siguiente elemento de la Coleccion.
template <typename T>
void Coleccion<T>::avanzarCursor(){

    assert(!finCursor());
    cursor = cursor->sig;
}

//indica si se llego al último elemento de la Coleccion.
template <typename T>
bool Coleccion<T>:: finCursor() const {

    return(cursor == NULL);
}

//devuelve el elemento que se encuentra en la posición actual del cursor.
template <typename T>
const T & Coleccion<T>::obtenerElemPos() const{

    assert (!finCursor());
    return cursor->elemento;
}

//destructor
template <typename T>
Coleccion<T>::~Coleccion(){
    eliminarColeccionRec(punt);
}

//recorre la lista hasta el final recursivamente y va eliminando los nodos
template <typename T>
void Coleccion<T>::eliminarColeccionRec(Nodo *& actual){

    if (actual != NULL){
        eliminarColeccionRec(actual->sig);
        delete actual;
        actual = NULL;
    }
}


template class Coleccion<Empresa>;
