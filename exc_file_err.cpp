#include "exc_file_err.h"
#include <string>


FileError::FileError(const std::string& msg): msg(msg){}

const char* FileError::what() const throw() {
	return msg.c_str();
}

