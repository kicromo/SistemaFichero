#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "implementation.h"

int main (){

    printf("Hola esto es una prueba el sistema de fichero\n");
    T_super_block root = NULL;
    T_inode inode = NULL;
    T_file file = NULL;


    create_super_bloq(&root);
    //inode  = alloc_inode(&raiz);
    printf("super block creado");
    int ok = new_inode(&root, &inode);

    if(ok){
        printf("El inodo se ha creado");
    }else{
        exit(-1);
    }

    //int open_file = open(&file, &inode);
    
    ///---------------------------------------------
    // Pruebas de llamadas
    int *pe;
    int tam = 1024;
    int f;
    pe=malloc(tam*sizeof(char));
    
    char bloque [128];
    char letra = 'a';
    //int ok = 1;
    printf("Contenido del vector dinamico:\n");
    //for(f=0;f<tam && ok;f++);
    
    free(pe);
    //getc();
    return EXIT_SUCCESS;


}
