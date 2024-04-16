#include "../include/kernel_entradasalida.h"

void atender_kernel_entradasalida(){
    bool control_key = 1;
    while(control_key){
        int cod_op = recibir_operacion(fd_entradasalida);
        switch (cod_op){
            case MENSAJE:
                //
                break;
            case PAQUETE:
                //
                break;
            case -1:
                log_error(kernel_logger, "Desconexión de ENTRADA SALIDA");
                control_key = 0;
            //exit(EXIT_FAILURE);
            default:
                log_warning(kernel_logger, "Operacion desconocida de ENTRADA SALIDA");
                break;
        }
    }
}