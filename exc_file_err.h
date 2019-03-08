#ifndef FILE_ERR_EXCEP_H
#define FILE_ERR_EXCEP_H
#include <exception>
#include <string>

class FileError: public std::exception{
	private:
    	std::string msg;
	public:
		/*Defino el constructor de la excepcion*/
		explicit FileError(const std::string& msg);
		/*Defino el metodo what para mostrar el mensaje*/
		virtual const char* what() const throw();
};

#endif
