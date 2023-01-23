#ifndef EMPRESA_H_INCLUDED
#define EMPRESA_H_INCLUDED
#include <string>

using namespace std;

class Empresa{
    private:
        string razonSocial, pais, rubro;
        unsigned int cantEmpleados, posRanking;

    public:
        Empresa();
        Empresa(string razonSocial, string pais, unsigned int cantEmpleados, string rubro, unsigned int posRanking);
        string consultarRazonSocialEmpresa() const;
        string consultarPaisEmpresa() const;
        unsigned int consultarCantEmpleadosEmpresa() const;
        string consultarRubroEmpresa() const;
        unsigned int consultarPosRankingEmpresa() const;
        string toString() const;
        bool operator == (Empresa emp);
};

#endif // EMPRESA_H_INCLUDED
