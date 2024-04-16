#ifndef SHARED_H_
#define SHARED_H_

#include <stdlib.h>
#include <stdio.h>
#include <commons/log.h> 
#include <commons/config.h>  // de esta manera agregamos librerías de las commons

typedef enum{
    MENSAJE, 
    PAQUETE,
    HANDSHAKE,
    //KERNEL-MEMORIA,
    RPTA_HANDSHAKE,
    CREAR_PROCESO_KM,
    RPTA_CREAR_PROCESO_MK
    //KERNEL-CPU,
    //KERNEL-ENTRADASALIDA,
    //ENTRADASALIDA-MEMORIA,
    //CPU-MEMORIA
}op_code;

#endif