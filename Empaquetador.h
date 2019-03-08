#ifndef EMPAQUETADOR_H
#define EMPAQUETADOR_H
#include <iostream>
#include <vector>
#include <fstream>
#include <thread>
#include <mutex>
#include "Paquete.h"
#include <string>

class Empaquetador{
	public:
 		/*Ordena los paquetes*/
		void ordenar_paquete();
		/*Constructor por copia no permitido*/
		Empaquetador(const Empaquetador& other)=delete;
		/*Operador = no permitido*/
		Empaquetador& operator=(const Empaquetador& other)=delete;
		/*Constructor: intenta cargar el archivo configuracion y
		segun lo leido armar los paquetes, si no puede cargar el archivo
		lanza una excepcion del tipo FileError*/
		explicit Empaquetador(const std::string& nomb_file);
		/*Constructor por movimiento*/	
		Empaquetador(Empaquetador&& other);
		/*Destructor: se elimina de memoria los paquetes*/
		~Empaquetador();
		/*Carga en el paquete la cantidad pasada y ancho segun el tipo*/
		void carg_armar_empaq(int tipo, int cantidad, int ancho);
		/*Imprime los paquetes segun su tipo*/
		void imp_restantes() const;
		//Fin public  
    private:  
    	/*Atributos privados*/ 
		std::string nomb_file;
		std::ifstream myfile;
		std::vector<Paquete*> vect_paqs;
		std::mutex m;
		/*Devuelve -1 si no pudo agregar al paquete, 0 si pudo todo y sino 
		devuelve la cantidad que no pudo agregar*/
		int agregar_paq(int tipo,int cantidad,int ancho);
		/*Revisa si hay algun paquete completado para quitarlo y agregar uno 
		del mismo tipo vacio*/
		void revisar_completo(int tipo);
};
#endif
