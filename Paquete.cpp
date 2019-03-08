#include "Paquete.h"
#include <algorithm>
#include <string>
#include <vector>
#define CERO 0
#define DOS 2

Paquete::Paquete(int tipo,const std::string& tipo_n,int lim_paq): 
	tipo(tipo),tipo_n(tipo_n),lim_paq(lim_paq){
	this->cant = CERO;
}

int Paquete::obt_cant() const{
	return cant;
}

int Paquete::obt_tipo() const{
	return tipo;
}

const std::string& Paquete::obt_nombre() const{
	return tipo_n;
}

int Paquete::obt_lim() const{
	return lim_paq;
}

int Paquete::obt_mediana() const{
	std::vector<int> auxiliar(vect_anchos); //para asegurar el const
	unsigned int aux = auxiliar.size();
	sort(auxiliar.begin(), auxiliar.end());
	if(aux%DOS==CERO){//par
		return ((auxiliar[(aux/DOS)-1] + auxiliar[aux/DOS])/DOS);
	}
	return  auxiliar[aux/DOS];
}

int Paquete::agregar(int cant,int ancho){
	if(this->cant_a_comp()==CERO){
		return -1;
	}
	if(this->cant_a_comp() <= cant){
		int aux = cant-this->cant_a_comp();
		for (int i = CERO; i < this->cant_a_comp(); i++){
			vect_anchos.push_back(ancho);
		}
		
		this->cant = this->lim_paq;
		std::cout << "Paquete listo: "<<this->obt_cant()<<" tornillos";
		std::cout << " de tipo "<<this->obt_nombre();
		std::cout << " (mediana: "<<this->obt_mediana()<<")"<<'\n';
		
		return  aux;
	}
	this->cant += cant;
	for (int i = CERO; i < cant; i++){
		vect_anchos.push_back(ancho);
	}
	return CERO;
}

int Paquete::cant_a_comp() const{
	return (this->lim_paq - this->cant);
}

bool Paquete::operator < (const Paquete& a) const{
    return (tipo < (a.obt_tipo()));
}





