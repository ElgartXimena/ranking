#include "Empresa.h"
#include <string>

using namespace std;

Empresa::Empresa(){
};

//crea una empresa a partir de los datos pasados por parametro
Empresa::Empresa(string razonSocial, string pais, unsigned int cantEmpleados, string rubro, unsigned int posRanking){
    this->razonSocial = razonSocial;
    this->pais = pais;
    this->cantEmpleados = cantEmpleados;
    this->rubro = rubro;
    this->posRanking = posRanking;
}

//devuelve la razon social de una empresa
string Empresa::consultarRazonSocialEmpresa() const{
    return razonSocial;
}

//devuelve el pais de origen de una empresa
string Empresa::consultarPaisEmpresa() const{
    return pais;
}

//devuelve la cantidad de empleados de una empresa
unsigned int Empresa::consultarCantEmpleadosEmpresa() const{
    return cantEmpleados;
}

//devuelve el rubro al que pertenece una empresa
string Empresa::consultarRubroEmpresa() const{
    return rubro;
}

//devuelve la posicion en el ranking de una empresa
unsigned int Empresa::consultarPosRankingEmpresa() const{
    return posRanking;
}

//determina si dos empresas son iguales o no
//esto lo hace a partir de su Razon Social ya que se considera que es unica e identificatoria
bool Empresa::operator==(Empresa emp){
    if (razonSocial == emp.consultarRazonSocialEmpresa()){
        return true;
    }
    return false;
}
