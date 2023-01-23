#include <iostream>
#include <fstream>
#include <stdio_ext.h>
#include "Empresa.h"
#include "Ranking.h"
#include "PST.h"
#include "NodoPST.h"

using namespace std;

void procesar_archivo_entrada(string origen, Ranking & miRanking);
unsigned int leerCantEmpresas(string origen);


int main()
{
    unsigned int cant_empresas = leerCantEmpresas("Ranking.csv");
    Ranking miRanking (cant_empresas);
    procesar_archivo_entrada("Ranking.csv", miRanking);
    PST * miArbol = new PST(miRanking);

    int eleccion = 0;
    cout << "BIENVENIDO AL SISTEMA DE RANKING."<< endl;
    cout << "Seleccione una opcion:" << endl;
    cout << "1- Obtener la posicion en el ranking para una empresa en particular."<<endl;
    cout << "2- Obtener la informacion de la empresa que se encuentra en una posicion determinada."<<endl;
    cout << "3- Listar las empresas, junto a su posicion en el ranking, que cuentan con un numero de empleados dentro de un rango especificado."<<endl;
    cout << "4- Obtener la informacion de las primeras N puestos del ranking y que cuentan con una cantidad de empleados dentro de un rango determinado."<<endl;
    cout << "5- Salir."<<endl<<endl;

    cin >>eleccion;

    while (eleccion != 5){
        switch (eleccion){
            case 1:
            {
                __fpurge(stdin); //limpia el buffer
                cout << "Ingrese la razon social de la empresa: ";
                string empresa;

                getline(cin, empresa);

                unsigned int posEmpresa = miRanking.consultarEmpresaRanking(empresa);
                if (posEmpresa == 0){
                    cout << "La empresa no pertenece al ranking." << endl;
                } else {
                    cout << "La empresa: " << empresa << " se encuentra en la posicion: " << posEmpresa << endl<<endl;
                }
                break;
            }
            case 2:
            {
                cout << "Ingrese la posicion en el ranking: ";
                int posicion;
                cin >> posicion;
                if (posicion > miRanking.longRanking()){
                    cout<<"\nLa posicion no es valida." << endl;
                } else {
                    Empresa empresaInfo = miRanking.consultarPosRanking(posicion);
                    cout << "\nRazon Social: " << empresaInfo.consultarRazonSocialEmpresa() << endl;
                    cout << "Posicion en el ranking: " << empresaInfo.consultarPosRankingEmpresa() << endl;
                    cout << "Pais de origen: " << empresaInfo.consultarPaisEmpresa() << endl;
                    cout << "Cantidad de empleados: " << empresaInfo.consultarCantEmpleadosEmpresa() << endl;
                    cout << "Rubro: " << empresaInfo.consultarRubroEmpresa() << endl<<endl;
                }
                break;
            }
            case 3:
            {
                cout << "Ingrese el rango mínimo: ";
                int rangoMin, rangoMax;
                cin >> rangoMin;
                cout << "Ingrese el rango máximo: ";
                cin >> rangoMax;
                Coleccion<Empresa> empresasRango;
                miRanking.consultarRangoRanking(rangoMin, rangoMax, empresasRango);
                empresasRango.inicCursor();
                while (!empresasRango.finCursor()){
                    Empresa actual = empresasRango.obtenerElemPos();
                    cout << "\n" << actual.consultarPosRankingEmpresa() << endl;
                    cout << actual.consultarRazonSocialEmpresa() << endl;
                    empresasRango.avanzarCursor();

                }
                break;
            }
            case 4:
            {
                cout<<"Ingrese hasta que puesto desea buscar: ";
                int prioridad;
                cin>>prioridad;
                if (prioridad <= cant_empresas){
                    cout << "Ingrese el rango mínimo: ";
                    int rangoMinPST, rangoMaxPST;
                    cin >> rangoMinPST;
                    cout << "Ingrese el rango máximo: ";
                    cin >> rangoMaxPST;
                    Coleccion<Empresa> empresasRangoPST;
                    Empresa * rankingPST = miRanking.obtenerRanking();
                    miArbol->buscarEmpresasPST(rankingPST, prioridad, rangoMinPST, rangoMaxPST, empresasRangoPST);

                    if (empresasRangoPST.cantidadElems() == 0)
                        cout << "\nNo existen empresas con el rango de empleados ingresado.\n" << endl;
                    else
                        cout << "\nLas " << prioridad<< " mejores empresas con cantidad de empleados entre " << rangoMinPST << " y " << rangoMaxPST <<endl;

                    empresasRangoPST.inicCursor();
                    while (!empresasRangoPST.finCursor()){
                        Empresa actualPST = empresasRangoPST.obtenerElemPos();
                        cout << "\n" << actualPST.consultarPosRankingEmpresa() << endl;
                        cout << actualPST.consultarRazonSocialEmpresa() << endl;
                        cout << actualPST.consultarCantEmpleadosEmpresa() << endl;
                        cout << actualPST.consultarPaisEmpresa() << endl;
                        cout << actualPST.consultarRubroEmpresa() <<endl<<endl;
                        empresasRangoPST.avanzarCursor();
                    }
                }
                else
                    cout<<"\nEl ranking solo tiene las "<<cant_empresas<< " mejores empresas."<<endl;

                break;
            }
        }

        cout<< endl;
        cout << "Seleccione una opcion:" << endl;
        cout << "1- Obtener la posicion en el ranking para una empresa en particular."<<endl;
        cout << "2- Obtener la informacion de la empresa que se encuentra en una posicion determinada."<<endl;
        cout << "3- Listar las empresas, junto a su posicion en el ranking, que cuentan con un numero de empleados dentro de un rango especificado."<<endl;
        cout << "4- Obtener la informacion de las primeras N puestos del ranking y que cuentan con una cantidad de empleados dentro de un rango determinado."<<endl;
        cout << "5- Salir."<<endl<<endl;

        cin >> eleccion;
    }
    return 0;
}

unsigned int leerCantEmpresas (string origen){
    ifstream archivo(origen);
    if (!archivo.is_open()){
        cout << "No se pudo abrir el archivo: " << origen << endl;
        return 0;
    }
    else {
        string linea;
        getline(archivo, linea);
        int cantidad_empresas = atoi(linea.c_str());
        return cantidad_empresas;
    }
}

void procesar_archivo_entrada(string origen, Ranking & miRanking)
{
    ifstream archivo(origen);
    if (!archivo.is_open())
        cout << "No se pudo abrir el archivo: " << origen << endl;
    else {
        string linea;
        getline(archivo, linea); //lee la primera linea (cantidad de empresas)
        int posRanking = 1;
        //Leemos de una linea completa por vez (getline).
        while (getline(archivo, linea)) {
            //Primer posición del separador ;
            int pos_inicial = 0;
            int pos_final = linea.find(';');

            //Informacion entre pos_inicial y pos_final
            string razon_social = linea.substr(pos_inicial, pos_final);

            //Segunda posición del separador ;
            pos_inicial = pos_final + 1;
            pos_final = linea.find(';', pos_inicial);
            string pais = linea.substr(pos_inicial, pos_final - pos_inicial);

            //Tercera posición del separador ;
            pos_inicial = pos_final + 1;
            pos_final = linea.find(';', pos_inicial);
            int empleados = atoi(linea.substr(pos_inicial, pos_final - pos_inicial).c_str());

            //Cuarta posición del separador ;
            pos_inicial = pos_final + 1;
            pos_final = linea.find(';', pos_inicial);
            string rubro = linea.substr(pos_inicial, pos_final - pos_inicial);

            if (empleados > 0){ //por la pre-condicion
                Empresa empresaActual (razon_social, pais, empleados, rubro, posRanking);
                miRanking.agregarEmpresaRanking(empresaActual);
                posRanking++;
            } else {
                cout << "La cantidad minima de empleados de una empresa debe ser mayor que 0." << endl;
            }

        }
    }
}

