#ifndef RANKING_H_INCLUDED
#define RANKING_H_INCLUDED
#include "Empresa.h"
#include "Coleccion.h"

class Ranking{
    private:
        struct Casillero {
            string razonSocial;
            unsigned int posRanking;
        };
        unsigned int tamanio, indice;

        Empresa * pRanking;
        Casillero * pAcceso;
        unsigned int * pEmpleado;

        void insertarOrdenadoAcceso(string razonSocial, unsigned int posRanking);
        void insertarOrdenadoEmpleado(long empleados, unsigned int dato);
        unsigned int busBinRec(int minimo, int maximo, string razon);

    public:
        Ranking(unsigned int tamanio);
        //~Ranking();
        void agregarEmpresaRanking(Empresa empresa);
        unsigned int longRanking() const;
        Empresa consultarPosRanking(const unsigned int & pos) const;
        unsigned int consultarEmpresaRanking(string razonSocial);
        void consultarRangoRanking(long minimo, long maximo, Coleccion<Empresa> & empresas);
        bool vacioRanking() const;
        bool existeEmpresaRanking(string razonSocial);
        Empresa * obtenerRanking();
        unsigned int * obtenerEmpleados();
};

#endif // RANKING_H_INCLUDED
