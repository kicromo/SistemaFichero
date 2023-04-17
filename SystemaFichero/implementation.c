#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "implementation.h"

#define     BLOCK_SIZE 1024


/*inode -> asignar memoria*/
// solo llama una vez cada que necesite un nuevo nodo, se crea un nuevo bloque
// como paso inicial vamos hacer la prueba con un solo nodo
struct inode * alloc_inode(T_super_block *sb){
    struct list_head * bloqs_next;
    //struct hlist_head *lista_inodos = malloc (sizeof(struct hlist_node));          //
    // inicializamos el inodo en caso de ser primero
    T_inode new_inodo;
    new_inodo = malloc (sizeof(struct inode));
    new_inodo->i_count = 0;                  // numero de inodo
    //new_inodo->i_node = 0;                   // inicial 0
    new_inodo->i_size  = 1024;               // nos puede servir para el futuro??
    new_inodo->i_blksbit = 10;               // 10 bits = 1024 bytes
    new_inodo->i_blocks = 12;                // cada nodo tiene un tamaño de 12 bloques iniciales
    //new_inodo->i_bytes = 1024;               // 1024 bytes
    //new_inodo->i_hash.next = NULL;
    //new_inodo->i_io_list.next = NULL;

    T_super_block   new_bloq;
    new_bloq = malloc (sizeof(struct super_block));
    new_bloq->s_active =    1;          // para saber si se esta usando el bloque i guess
    new_bloq->s_count = 0;              // tras añadir se suma
    strcpy(new_bloq->s_id, "mi primer bloque");
    new_bloq->s_blocksize_bits = 0;     // registrar cuanto valor tiene almacenado el bloque
    new_bloq->s_blocksize_bytes = 0;    // bloques bytes usados
    new_bloq->s_blocksize = 1024;       // tamaño del bloque por defecto
    //new_bloq->s_list = *bloqs_next;

    // si ambos estan a NULL es porque no tienen ningun enlace, por lo tnato es el nuevo nodo
    // if ((&(new_bloq)->s_list.next == NULL) && (&(new_bloq)->s_list.prev == NULL)){
    //     *(sb) = new_bloq;
    //     //new_bloq->s_list.next = *(sb);
    //     //new_bloq->s_list.prev = *(sb);
    // }
    // actualizamos la lista de inodos, como es primera vez no es necesario un if
    printf("El struct inode tiene valores \n");
    return new_inodo;
}
/*destruir inode*/

void create_super_bloq (T_super_block * sb){
    T_super_block   new_bloq;
    new_bloq = malloc (sizeof(struct super_block));
    new_bloq->s_active = 1;          // para saber si se esta usando el bloque i guess
    new_bloq->s_count = 0;              // tras añadir se suma
    strcpy(new_bloq->s_id, "Super Block");
    new_bloq->s_blocksize_bits = 8;     // registrar cuanto valor tiene almacenado el bloque
    new_bloq->s_blocksize_bytes = 256;    // bloques bytes usados
    new_bloq->s_blocksize = 1024;       // tamaño del bloque por defecto
    new_bloq->sig = NULL;

    *(sb) = new_bloq;
}

int new_inode (T_super_block *sb, T_inode *inod){
    int ok;
    T_inode new_inode;
    new_inode = malloc(sizeof(struct inode));
    new_inode->i_node_id = 0;      // 3-7
    new_inode->i_count = 0;     // inodo actual
    new_inode->i_size = 5;      // inodos
    new_inode->i_blocks = BLOCK_SIZE;
    new_inode->i_blksbit = 5;
    new_inode->next_inode = NULL;

    if (*(sb) != NULL){
        ok = 1;
        new_inode->i_sb = (sb); 
        *(inod) = new_inode;
    }else{
        ok =  0;
    }

    return ok;
}










