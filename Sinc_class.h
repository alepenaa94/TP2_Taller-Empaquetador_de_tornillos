#ifndef SINC_CLASS_H
#define SINC_CLASS_H
#include <iostream>
#include <vector>
#include <thread>
#include <mutex>

/*Clase para realizar la sincronizacion de metodos, para que no se 
produzca race condition*/

class Sinc_class {
    private:
        std::mutex &m;
        /*Constructor por copia no permitido*/
        Sinc_class(const Sinc_class&) = delete;
        /*Operador = no permitido*/
        Sinc_class& operator=(const Sinc_class&) = delete;
        /*Constructor por movimiento no permitido*/
        Sinc_class(Sinc_class&&) = delete;
        /*Operador = no permitido*/
        Sinc_class& operator=(Sinc_class&&) = delete;
    public:
        /*Constructor que crea un mutex en memoria*/
        explicit Sinc_class(std::mutex &m);
        /*Destructor que destruye en memoria el mutex almacenado*/
        ~Sinc_class();
};
#endif

