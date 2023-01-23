#ifndef NODOPST_H_INCLUDED
#define NODOPST_H_INCLUDED

class NodoPST{
    private:
        unsigned int prioridad;
        long cantEmple;
        long mediana;
        int index;
        NodoPST * menores;
        NodoPST * mayores;


    public:
        NodoPST(unsigned int p, long cE, long m, int i, NodoPST * men, NodoPST * may);
        unsigned int obtenerPrioridad() const;
        long obtenerCantEmple() const;
        long obtenerMediana() const;
        int obtenerIndex() const;
        NodoPST * obtenerMenores();
        NodoPST * obtenerMayores();
        bool esHoja() const;

};

#endif // NODOPST_H_INCLUDED
