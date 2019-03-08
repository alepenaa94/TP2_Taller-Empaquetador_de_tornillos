#include <iostream>
#include <vector>
#include <thread>
#include <mutex>
#include "Sinc_class.h"

Sinc_class::Sinc_class(std::mutex &m) : m(m) {
    m.lock();
}

Sinc_class::~Sinc_class() {
    m.unlock();
}
