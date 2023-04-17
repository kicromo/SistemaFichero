#define DNAME_INLINE_LEN_MIN 32

typedef struct list_head *pt_list_head;
struct list_head
{
	unsigned int cont;
	pt_list_head sig;
	pt_list_head prev;
};

typedef struct super_block *T_super_block;
struct super_block
{
	pt_list_head s_list;		/* Keep this first */
	//struct list_head s_mounts; 		 /* list of mounts; _not_ for fs use */
	unsigned char s_blocksize_bits; /*  */
	unsigned char s_blocksize_bytes; /*  */
	unsigned long s_blocksize;
	//long long s_maxbytes; 			/* Max file size -> lon long*/
	//const struct super_operations *s_op;
	//unsigned long s_flags;
	//struct dentry *s_root;			 /* raiz arbol*/
	int s_count;
	int s_active;
	char s_id[32];			   		 /* Informational name  -> Super Block*/
							   		// uuid_t s_uuid;			   /* UUID */
};

//-------------------------------------------------------------------------------------------------------
struct hlist_node
{
	struct hlist_node *next, // siguiente inodo
		**pprev;			 // anterior inodo
};

typedef struct inode *T_inode;
struct inode
{
	struct hlist_node 	i_hash;	/*hash list*/
	struct list_head 	i_io_list; /*i_list -> list of inodes*/
	//struct list_head 	i_wb_list; /* i_dentry -> list of dentries */
	unsigned long 		i_node;		/*num inode*/
	int 				i_count;				/* ref counter*/
	//unsigned int 		i_nlick;

	long long 			i_size; /*long long -> tam inode*/
	//int 				i_uid;
	//int 				i_gid;
	unsigned int 		i_blksbit; /* blocks size bits */
	unsigned int	 	i_blocks;	/* file size blocks*/
	unsigned int 		i_bytes;	/* bytes consume */

	//const struct inode_operations *i_op;
	struct super_block *i_sb;
	//const struct file_operations *i_fop; /* former ->i_op->default_file_ops */

	//struct list_head 	i_devices;
	//unsigned long 		i_state; /*state flag*/
	//unsigned long 		i_flags; /*filesystem flags*/
};

///---------------------------------------------------------------------------------------------------------------------

struct qstr
{
	const unsigned char *name;
};

struct hlist_bl_node
{
	struct hlist_bl_node *next, **pprev;
};

typedef struct dentry *T_dentry;
struct dentry
{
	/* Read Copy Upadate (RCU) lookup touched fields */
	// atomic_t 				d_count				/*usage count*/
	unsigned int d_flags;						 /* protected by d_lock / detry_flags */
	int d_mounted;								 /* is this a mount point? */
	struct inode *d_inode;						 /* associated inode */
	struct hlist_bl_node d_hash;				 /* hlist_node -> lookup hash list  */
	struct dentry *d_parent;					 /* parent directory */
	struct qstr d_name;							 /* Dentry name ---> ????*/
	struct list_head d_child;					 /* list of dentries witin/ */
	struct list_head d_subdirs;					 /* our children */
	const struct dentry_operations *d_op;		 /* Dentry operation table*/
	struct super_block *d_sb;					 /* The root of the dentry tree */
	unsigned char d_iname[DNAME_INLINE_LEN_MIN]; /*short name*/
};

//-----------------------------------------------------------------------------------------------------------------------

struct address_space
{
	/* data */
};
typedef struct file *T_file;

struct file
{
	struct list_head fu_list; /* list of file objects*/
	// struct path f_path;		  /* contains dentry*/
	//  struct inode		*f_inode;				/* cached value */
	const struct file_operations *f_op;
	unsigned int f_count; /*file object's usage count*/
	unsigned int f_flags; /* flags specified on open*/
	// mode_t						f_mode;			/* file access mode*/
	long long f_pos; /* file offset (file pointer)*/
	// struct fown_struct			f_owner;		/*owner data for signals */
	// const struct cred			*f_cred;		/* file credencials*/
	// struct file_ra_state		f_ra;			/*read-ahead state*/
	// u64			f_version;

	struct address_space *f_mapping; /* page cache mapping*/
	unsigned long f_mnt_write_state; /*debbuging state*/
									 // struct inode		*f_inode;				/* cached value */
									 // void			*private_data;				/* tty driver hook*/
									 // struct list_head		f_ep_links			/* list of epoll links*/
};

/************************************************************************************/
/*							FUNCIONES Y PROCEDIMIENTOS								*/
/************************************************************************************/

//* FUNCIONES PARA FILE OPERATIONS*/
/* Nombre del administracion*/
char *owner(T_super_block *ptr_block);
/* *modifica el offset, y comprobar manda 1(bien) o 0(no recibido) */
int sllseek(T_file *ptr_file, long long offset, int origin);
/* Lee un numeros de bytes(en count) de un fichero y actualiza el offset */
size_t read(T_file *ptr_file, char *buff, size_t count, long long *offset);
/* Escribe un numero de byres(en count) de un fichero y actualiza el offset */
size_t write(T_file *, char *buff, size_t count, long long *offset);
/* Crea un fichero nuevo y luego lo likea al abjeto inodo correspondiente*/
int open(T_inode *ptr_inode, T_file *ptr_file);
/*	Lo llama el sistema de fichero cada vez que las referencias de un archivo se decrementa (comprueba) */
int flush(T_file *ptr_file);
/*	Elimina el fichero cuando no hay referencias*/
int release(T_inode *ptr_inode, T_file *ptr_file);
/* Manda todos los datos al disco*/
int fsync(T_file *ptr_file, T_dentry *ptr_dentry, int datasync);




/********************  	Funciones para dentry operations  *********************/

int d_delete(T_dentry *ptr_dentry);
int d_init(T_dentry *ptr_dentry);
void d_release(T_dentry *dentry);
void d_iput(T_dentry *dentry,T_inode *inode);
char * d_dname(T_dentry *dentry, char *buffer, int buflen);

// int d_hash(T_dentry *, struct qstr *);
// int d_revalidate(T_dentry * ptr_dentry, struct nameidata *);
// int d_compare(struct dentry *dentry,struct qstr *name1,struct qstr *name2);





/********************   Funciones para inode operations ****************************************/
//*********int (*create)(struct user_namespace *, struct inode *, struct dentry *, umode_t, bool);
struct dentry * lookup(T_inode *dir, T_dentry *dentry);
int link(T_dentry *old_dentry, T_inode *dir, T_dentry *dentry);
//int unlink(T_inode *dir, T_dentry *dentry);
//*********int (*mkdir)(struct user_namespace *, struct inode *, struct dentry *, umode_t);
int rmdir(T_inode *dir, T_dentry *dentry);
//*********int (*mknod)(struct user_namespace *, struct inode *, struct dentry *, umode_t, dev_t);
//*********int (*rename)(struct user_namespace *, struct inode *, struct dentry *, struct inode *, struct dentry *, unsigned int);

int permission(T_inode *inode, int mask);
//int setattr(T_dentry *ptr_dentry,struct iattr *attr);
//int getattr(struct vfsmount *mnt,struct dentry *dentry,struct kstat *stat);




/*************************************************************** */
/********************		SUPER BLOCK OPERATIONS 	************ */
/*inode -> asignar memoria*/
void create_bloq (T_super_block *sb);
struct inode * alloc_inode(T_super_block *sb);
/*destruir inode*/
void destroy_inode(T_inode *inode);
/*free_inode*/
//void (*free_inode)(struct inode *);

/*localizacion memoria*/
void dirty_inode(T_inode *inode);
/*update -> disk*/
int sync_fs(T_super_block *sb, int wait);
//int statfs(struct super_block *sb, struct statfs *statfs);


