#include <iostream>
#include <fstream>
#include <string>
#include <iomanip>
#include <bitset>  
#define SIZE_BUFF 4
#define CERO_H 0x00
#define V_ATASCADO 0xFFFFFFFF
#define BITS_27 27
#define BITS_5 5
#define BITS_10 10
#include "clasificador.h"
#include "Empaquetador.h"
#include <arpa/inet.h>
#include "Sinc_class.h"
#include "exc_file_err.h"

Clasificador::Clasificador(const std::string& nomb_file, Empaquetador &empaq):
	nomb_file(nomb_file), empaq(empaq) {
	myfile.open(nomb_file, std::ifstream::in);
	if(!myfile.is_open()){
		throw FileError((nomb_file+": no se pudo conectar con el dispositivo"));
	}else{
		while(true){
    		char buff;
        	myfile.get(buff);
			if(myfile.eof()){
				throw FileError((nomb_file+": no se pudo conectar con el dispositivo"));
			}
			if(buff==CERO_H) {
				break;
			}
			nomb_clf.push_back(buff);
		}
		std::cout<<nomb_file;
		std::cout<<": se establece conexion con el dispositivo ";
		std::cout<<nomb_clf<<'\n';
	}
	}

Clasificador::Clasificador(Clasificador&& other):
	nomb_file(other.nomb_file), empaq(other.empaq) {
	this->nomb_clf = other.nomb_clf;
	this->nomb_file = other.nomb_file;
	this->myfile = std::move(other.myfile);
	other.nomb_file = nullptr;
	other.nomb_clf = nullptr;
}


    
void Clasificador::run(){
	unsigned int tipo_tornillo;
	unsigned int ancho; 
	unsigned int cantidad;
	while(!myfile.eof()){
		uint32_t little_endian;
		uint32_t big_endian;
		myfile.read((char*)&big_endian, SIZE_BUFF);
		if(myfile.eof()){ //se debe a que repite la ultima lectura...
			break;
		}
		little_endian = ntohl(big_endian);
		if(little_endian==(V_ATASCADO)){
			Sinc_class sincronizar(m);
			std::cerr << nomb_clf << " atascado"<<'\n';
			continue;
		}

		
		tipo_tornillo = little_endian>>BITS_27;
		ancho = (little_endian<<BITS_27)>>BITS_27;
		cantidad = (little_endian<<BITS_5)>>BITS_10;
		empaq.carg_armar_empaq(tipo_tornillo,cantidad,ancho);
    }
	}
        
