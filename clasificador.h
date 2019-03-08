#ifndef CLASIFICADOR_H
#define CLASIFICADOR_H
#include <string>
#include <fstream>
#include "Empaquetador.h"
#include "Thread.h"
#include <mutex>


class Clasificador : public Thread {
	private:
		std::string nomb_clf;
		std::string nomb_file;
		std::ifstream myfile;
		Empaquetador &empaq;
		std::mutex m;
	public:
		/*Constructor por copia no permitido*/
		Clasificador(const Clasificador& other)=delete;
		/*Operador = no permitido*/
		Clasificador& operator=(const Clasificador& other)=delete;
		/*Constructor: intenta abrir el archivo nomb_file y obtener el 
		nombre del clasificador, lanza excepcion del tipo FIleError
		 si no puede abrir el archivo*/
		Clasificador(const std::string& nomb_file, Empaquetador &empaq);
		/*Constructor por movimietno*/
		Clasificador(Clasificador&& other);
		/*Re define la funcion run de Thread, donde se realiza la lectura
		del archivo si es que fue abierto con exito y enpaqueta lo 
		leido del archivo*/
		virtual void run() override;
};
#endif
