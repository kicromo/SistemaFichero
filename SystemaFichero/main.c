#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "implementation.h"

int main (){

    printf("Hola esto es una prueba el sistema de fichero\n");
    T_super_block raiz = NULL;
    T_inode inode = NULL;

    // raiz->s_blocksize_bits = 32;
    // raiz->s_blocksize = 1024;
	// raiz->s_maxbytes = 1048576;    // 1Megabyte aprox
	// raiz->s_op = NULL;
    // raiz->s_flags = 0;
	// raiz->s_root = NULL;
	// raiz->s_count = 0;
	// raiz->s_active = 1;
    // strcpy(raiz->s_id, "Super lock");
    create_bloq(&raiz);
    //inode  = alloc_inode(&raiz);
    printf("Hemos creado el primer inodo de nuestra lista :D");

    //Inode
    // inode->i_blksbit = 32;
    // inode->i_blocks = 10;
    // inode->i_bytes = 8;
    // inode->i_count = 0;     // inicializamos la cuenta
    // inode->i_devices.next = NULL;
    // inode->i_flags = 0;
    // inode->i_fop  = NULL;
    // inode->i_gid = strlen("inodos");        // la longitud sera el tamaño de estos
    // inode->i_hash.next = NULL;
    // inode->i_io_list.next = NULL;
    // inode->i_nlick = 0;
    // inode->i_node = 0;


    return EXIT_SUCCESS;


}
