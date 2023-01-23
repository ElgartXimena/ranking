#ifndef COLECCION_H_INCLUDED
#define COLECCION_H_INCLUDED

template <typename T>
class Coleccion {

    private:
        struct Nodo{
            T elemento;
            Nodo * sig;
        };
        Nodo * punt;
        unsigned int cantidad;
        Nodo * cursor;

        bool perteneceRec(Nodo * actual, T elemento);
        void eliminarColeccionRec(Nodo *& actual);

    public:
        Coleccion();
        ~Coleccion();
        void agregar(T elemento);
        bool pertenece(T elemento) ;
        unsigned int cantidadElems() const;
        bool esVacio() const;
        void inicCursor();
        void avanzarCursor();
        bool finCursor() const;
        const T & obtenerElemPos() const;

};
#endif // COLECCION_H_INCLUDED
