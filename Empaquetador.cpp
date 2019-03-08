#include "Empaquetador.h"
#include "Sinc_class.h"
#include <algorithm>
#include <string>
#define CERO 0
#define INVAL -1
#define DESPLAZAMIENTO 1
#include "exc_file_err.h"


Empaquetador::Empaquetador(const std::string& nomb_file): nomb_file(nomb_file){
	std::string nombre;
	std::string id;
	std::string lim;
	unsigned int pos = CERO;
	myfile.open(nomb_file,std::ifstream::in);
	if(!myfile.is_open()){
		std::string msg=":no se pudo cargar la configuracion del Empaquetador";
		// no va a estar mal la config ni tampoco los archivos de los clasif
		throw FileError(nomb_file+msg);
	}	
	std::string line;
	while (std::getline(myfile, line)){
		pos = CERO;
		for (unsigned int i = CERO; i < line.size(); i++){
			if((line[i]=='=') && (i!=CERO)){
				id=line.substr(CERO,i-pos);
				pos=i+DESPLAZAMIENTO;
			}
			if( (line[i]==',') && (pos!=CERO) && (pos!=i) ){
				nombre=line.substr(pos,i-pos);
				lim=line.substr(i+DESPLAZAMIENTO,line.size());
				break;
			}		
		}
		int id_aux =std::stoi(id);
		int lim_aux = std::stoi(lim);
		Paquete *paq = new Paquete(id_aux,nombre,lim_aux);
		vect_paqs.push_back(paq);
	}
}


Empaquetador::Empaquetador(Empaquetador&& other): nomb_file(other.nomb_file){
	this->vect_paqs = other.vect_paqs;
	this->myfile = std::move(other.myfile);
}

int Empaquetador::agregar_paq(int tipo,int cantidad,int ancho){
	Sinc_class sincronizar(m);
	int pos=INVAL;
	for (unsigned int i = CERO; i < vect_paqs.size(); i++){
		if(vect_paqs[i]->obt_tipo() == tipo){
			pos = i;
			break;
		}
	}
	if(pos==INVAL){
		std::cerr<<"Tipo de tornillo invalido: "<<tipo<<'\n';
		return CERO;
	}
	return (vect_paqs[pos]->agregar(cantidad,ancho));;
}

void Empaquetador::revisar_completo(int tipo){
	Sinc_class sincronizar(m);
	for (unsigned int i = CERO; i < vect_paqs.size(); i++){
		if(vect_paqs[i]->cant_a_comp() == CERO){
			Paquete *paq_nuevo = new Paquete(vect_paqs[i]->obt_tipo(),
									vect_paqs[i]->obt_nombre(),
									vect_paqs[i]->obt_lim());
			delete vect_paqs[i];
			vect_paqs.erase(vect_paqs.begin() + i); //borre el que se completo
			vect_paqs.push_back(paq_nuevo); //agrego el nuevo
		}
	}
}

void Empaquetador::carg_armar_empaq(int tipo, int cantidad, int ancho){
	int aux=INVAL;
	while(aux==INVAL){
		aux = agregar_paq(tipo,cantidad,ancho);
		this->revisar_completo(tipo);
		if(aux>CERO){
			this->carg_armar_empaq(tipo,aux,ancho);
		}
	}
}



struct {
	bool operator()(Paquete* a, Paquete* b){
		return (*a < *b);
	}
}paq_orden;

void Empaquetador::ordenar_paquete(){
	std::sort(vect_paqs.begin(), vect_paqs.end(),paq_orden);
}

void Empaquetador::imp_restantes() const{
	std::cout<<"# Informe de remanentes"<<'\n';
	for (unsigned int i = CERO; i < vect_paqs.size() ; i++){
		std::cout<<"* "<< vect_paqs[i]->obt_cant() <<" tornillos";
		std::cout<<" de tipo "<< vect_paqs[i]->obt_nombre()<<'\n';
	}
}


Empaquetador::~Empaquetador(){
	for (unsigned int i = CERO; i < vect_paqs.size(); i++){
		delete vect_paqs[i];
	}
	if(myfile.is_open()){
		myfile.close();	
	}
}

