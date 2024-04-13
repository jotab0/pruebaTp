#include "../include/cpu.h"

int main(int argc, char* argv[]) {
    char* mensaje = "Hola mundo";
    prueba_de_shared(mensaje);
    prueba_de_shared("Como estas?");
    return 0;
}
