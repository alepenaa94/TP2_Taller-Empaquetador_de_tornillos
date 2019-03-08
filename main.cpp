#include "clasificador.h"
#include "Empaquetador.h"
#include "exc_file_err.h"
#include <vector>
#define ARCH_CONFIG 1
#define ARCHS_CLASIF 2
#define CERO 0

int main(int argc, char *argv[]){
	Empaquetador empaq(argv[ARCH_CONFIG]);	
	std::vector<Thread*> threads;
	for (int i = ARCHS_CLASIF; i < argc; i++) {
        try{
        	threads.push_back(new Clasificador(argv[i],empaq));  
        }
        catch(FileError& ex){
        	std::cerr << ex.what() << std::endl;
        }	
        catch(const std::exception &e) {
		std::cerr << e.what() << std::endl;
		}  
    }
    for (unsigned int i = CERO; i < threads.size(); i++){
        threads[i]->start();
    }
    for (unsigned int i = CERO; i < threads.size(); i++){
        threads[i]->join();
        delete threads[i];
    }
    empaq.ordenar_paquete();
	empaq.imp_restantes();
	return CERO;
}
