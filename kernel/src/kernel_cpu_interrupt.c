#include "../include/kernel_cpu_interrupt.h"

void atender_kernel_cpu_interrupt(){
    bool control_key = 1;
    while(control_key){
        int cod_op = recibir_operacion(fd_cpu_interrupt);
        switch (cod_op){
            case MENSAJE:
                //
                break;
            case PAQUETE:
                //
                break;
            case -1:
                log_error(kernel_logger, "Desconexión de CPU - INTERRUPT");
                control_key = 0;
            //exit(EXIT_FAILURE);
            default:
                log_warning(kernel_logger, "Operacion desconocida de CPU - INTERRUPT");
                break;
        }
    }
}