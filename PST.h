#ifndef PST_H_INCLUDED
#define PST_H_INCLUDED
#include "Ranking.h"
#include "NodoPST.h"
#include "Coleccion.h"

class PST{

    private:

        NodoPST * arbol;

        long calcularMediana(Empresa * pRanking,unsigned int a[], unsigned int inicio, unsigned int fin);
        int obtenerIndice(Empresa * pRanking, unsigned int pEmpleado[], unsigned int inicio, unsigned int fin, int &indice) const;
        void eliminar(unsigned int pEmpleado[], int iEmple, unsigned int fin);
        NodoPST * construirNodo(Empresa * pRanking, unsigned int indice, long valorMedio, NodoPST * men, NodoPST * may);
        void buscarEmpresasPSTRec(NodoPST * arbol, Empresa * pRanking, unsigned int prioridad, long minimo, long maximo, Coleccion<Empresa> & empresas);

        void eliminarArbolRec(NodoPST * actual);

    public:
        PST(Ranking ranking);
        ~PST();
        bool vacioPST() const;
        NodoPST * construirPST(Empresa * pRanking, unsigned int pEmpleado [], unsigned int inicio, unsigned int fin);
        void imprimirArbol();
        void buscarEmpresasPST(Empresa * pRanking, unsigned int prioridad, long minimo, long maximo, Coleccion<Empresa> & empresas);
};

#endif // PST_H_INCLUDED
