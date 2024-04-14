#include "../include/cpu.h"

// SERVIDOR DE: KERNEL
// CLIENTE DE:  MEMORIA

int main(int argc, char* argv[]) {
    char* mensaje = "Hola mundo";
    prueba_de_shared(mensaje);
    prueba_de_shared("Como estas?");
    return 0;
}
