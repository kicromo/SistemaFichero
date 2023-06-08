#include <stdio.h> 
#include <string.h> 

#define BLOCK_SIZE 1024

int main () 
{ 
    char buf[BLOCK_SIZE]; 
    memset(buf, '0', BLOCK_SIZE); 
    printf("La cadena después de la operación memset es: %s\n", buf); 
    return 0; 
}