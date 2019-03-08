#ifndef PAQUETE_H
#define PAQUETE_H
#include <iostream>
#include <vector>
#include <fstream>
#include <string>

class Paquete{
    private:
        int tipo;
        std::string tipo_n;
        int cant;
        int lim_paq;
        std::vector<int> vect_anchos;

    public:
        /*Constructor: define la estructura del paquete segun el tipo
        nombre y limite de carga en paquete*/
        Paquete(int tipo,const std::string& tipo_n,int lim_paq);
        /*Devuelve la cantidad que no pudo ser agregada, devuelve 0 si
        pudo agregar todo o -1 en caso que esta lleno*/
        int agregar(int cant,int ancho);
        /*Devuelve la cantidad de tornillos que aun se pueden almacenar*/
        int cant_a_comp() const;
        /*Devuelve la cantidad de tornillos almacenados*/
        int obt_cant() const;
        /*Devuelve el tipo en int segun el archivo clasificador*/
        int obt_tipo() const;
        /*Devuelve la mediana de los anchos de los tonrillos del paquete*/
        int obt_mediana() const;
        /*Devuelve el limite de carga del paquete*/
        int obt_lim() const;
        /*Devuelve un string con el nombre del paquete*/
        const std::string& obt_nombre() const;
        /*Operador menor, devuelve un booleano si es menor a otro Paquete*/
        bool operator < (const Paquete& a) const;
};


#endif

