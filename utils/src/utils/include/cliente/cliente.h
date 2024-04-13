#ifndef CLIENTE_H_
#define CLIENTE_H_

#include <stdlib.h>
#include <stdio.h>
#include<signal.h>
#include<unistd.h>
#include<sys/socket.h>
#include<netdb.h>
#include<string.h>
#include<commons/log.h>

int crear_conexion(char *ip, char* puerto);

#endif
