//#include <linux/fs.h>
//#include <linux/path.h>
//#include <linux/types.h>
//#include <linux/uuid.h>
//#include <linux/list_bl.h>
//#include <linux/dcache.h>
//#include  <linux/module.h>

#define DNAME_INLINE_LEN_MIN 32

struct super_block {
	struct list_head	s_list;		                /* Keep this first */
	unsigned char		s_blocksize_bits;
	unsigned long		s_blocksize;
	loff_t				s_maxbytes;	                /* Max file size -> lon long*/
	const struct super_operations	*s_op;
	unsigned long		s_flags;
	struct dentry		*s_root;    				/* raiz arbol*/
	int					s_count;
	atomic_t			s_active;
	struct list_head	s_mounts;	            	/* list of mounts; _not_ for fs use */
	char				s_id[32];					/* Informational name  -> Super Block*/
	uuid_t				s_uuid;						/* UUID */

};


//-------------------------------------------------------------------------------------------------------


struct inode {
	struct hlist_node	i_hash;				/*hash list*/
	struct list_head	i_io_list;			/*i_list -> list of inodes*/
	struct list_head	i_wb_list;			/* i_dentry -> list of dentries */
	unsigned long		i_node ;			/*num inode*/
	int 				i_count;			/* ref counter*/
	unsigned int		i_nlick;

	long long			i_size;				/*long long -> tam inode*/
	int				i_uid;
	int 			i_gid;
	unsigned int	i_blksbit; 				/* blocks size bits */
	unsigned int	i_blocks;				/* file size blocks*/
	unsigned int	i_bytes;				/* bytes consume */

	const struct inode_operations	*i_op;
	struct 		 super_block		*i_sb;
	const struct file_operations	*i_fop;	/* former ->i_op->default_file_ops */

	struct list_head	i_devices;
	unsigned long 		i_state;			/*state flag*/
	unsigned long 		i_flags;			/*filesystem flags*/

};








///---------------------------------------------------------------------------------------------------------------------

// struct hlist_bl_node
// {
// 	/* data */
// };

// struct qstr{

// };


struct dentry {
	/* Read Copy Upadate (RCU) lookup touched fields */
	//atomic_t 				d_count				/*usage count*/
	unsigned int 			d_flags;			/* protected by d_lock / detry_flags */
	int 					d_mounted;			/* is this a mount point? */
	struct inode 			*d_inode;			/* associated inode */
	struct hlist_bl_node 	d_hash;				/* hlist_node -> lookup hash list  */
	struct dentry 			*d_parent;			/* parent directory */
	struct qstr 			d_name;				/* Dentry name ---> ????*/
	struct list_head 		d_child;			/* list of dentries witin/ */
	struct list_head 		d_subdirs;			/* our children */
	const struct dentry_operations *d_op;		/* Dentry operation table*/
	struct super_block 		*d_sb;				/* The root of the dentry tree */
	unsigned char			d_iname[DNAME_INLINE_LEN_MIN];	/*short name*/
};






//-----------------------------------------------------------------------------------------------------------------------

struct address_space
{
	/* data */
};

struct file {

	struct list_head				fu_list;	/* list of file objects*/
	struct path						f_path;		/* contains dentry*/
	//struct inode		*f_inode;				/* cached value */
	const struct file_operations	*f_op;
	unsigned int				f_count;		/*file object's usage count*/
	unsigned int 				f_flags;		/* flags specified on open*/
	//mode_t						f_mode;			/* file access mode*/
	long long					f_pos;			/* file offset (file pointer)*/
	//struct fown_struct			f_owner;		/*owner data for signals */
	//const struct cred			*f_cred;		/* file credencials*/
	//struct file_ra_state		f_ra;			/*read-ahead state*/
	//u64			f_version;

	struct address_space		*f_mapping;			/* page cache mapping*/
	unsigned long 				f_mnt_write_state;	/*debbuging state*/
	//struct inode		*f_inode;				/* cached value */
	//void			*private_data;				/* tty driver hook*/
	//struct list_head		f_ep_links			/* list of epoll links*/

};


/************************************************************************************/
/*							FUNCIONES Y PROCEDIMIENTOS								*/
/************************************************************************************/


struct file_operations {
	struct module *owner;
	loff_t (*llseek) (struct file *, loff_t, int);
	ssize_t (*read) (struct file *, char __user *, size_t, loff_t *);
	ssize_t (*write) (struct file *, const char __user *, size_t, loff_t *);
	//ssize_t (*read_iter) (struct kiocb *, struct iov_iter *);
	//ssize_t (*write_iter) (struct kiocb *, struct iov_iter *);

	int (*iterate) (struct file *, struct dir_context *);
	//int (*iterate_shared) (struct file *, struct dir_context *);

	//long (*compat_ioctl) (struct file *, unsigned int, unsigned long);
	int (*mmap) (struct file *, struct vm_area_struct *);
	unsigned long mmap_supported_flags;
	int (*open) (struct inode *, struct file *);
	int (*flush) (struct file *, fl_owner_t id);
	int (*release) (struct inode *, struct file *);
	int (*fsync) (struct file *, loff_t, loff_t, int datasync);
	//int (*flock) (struct file *, int, struct file_lock *);
	ssize_t (*sendpage) (struct file *, struct page *, int, size_t, loff_t *, int);
	unsigned long (*get_unmapped_area)(struct file *, unsigned long, unsigned long, unsigned long, unsigned long);
	int (*check_flags)(int);

	int (*setlease)(struct file *, long, struct file_lock **, void **);
	long (*fallocate)(struct file *file, int mode, loff_t offset,loff_t len);
	void (*show_fdinfo)(struct seq_file *m, struct file *f);


	// int (*fadvise)(struct file *, loff_t, loff_t, int);
	// int (*uring_cmd)(struct io_uring_cmd *ioucmd, unsigned int issue_flags);
	// int (*uring_cmd_iopoll)(struct io_uring_cmd *, struct io_comp_batch *,unsigned int poll_flags);


	//int (*iopoll)(struct kiocb *kiocb, struct io_comp_batch *,unsigned int flags);
	//__poll_t (*poll) (struct file *, struct poll_table_struct *);
	//long (*unlocked_ioctl) (struct file *, unsigned int, unsigned long);
	//int (*lock) (struct file *, int, struct file_lock *);
	//int (*fasync) (int, struct file *, int);
	//ssize_t (*splice_write)(struct pipe_inode_info *, struct file *, loff_t *, size_t, unsigned int);
	//ssize_t (*splice_read)(struct file *, loff_t *, struct pipe_inode_info *, size_t, unsigned int);
	//ssize_t (*copy_file_range)(struct file *, loff_t, struct file *,loff_t, size_t, unsigned int);
	//loff_t (*remap_file_range)(struct file *file_in, loff_t pos_in,struct file *file_out, loff_t pos_out,loff_t len, unsigned int remap_flags);
};



struct dentry_operations
{
	int (*d_revalidate)(struct dentry *, unsigned int);
	int (*d_hash)(const struct dentry *, struct qstr *);
	int (*d_compare)(const struct dentry *, unsigned int, const char *, const struct qstr *);
	int (*d_delete)(struct dentry *);
	int (*d_init)(struct dentry *);
	void (*d_release)(struct dentry *);
	void (*d_iput)(struct dentry *, struct inode *);
	char *(*d_dname)(struct dentry *dentry, char *buffer, int buflen);

	//int (*d_weak_revalidate)(struct dentry *, unsigned int);
	//struct vfsmount *(*d_automount)(struct path *path);
	//int (*d_manage)(const struct path *, bool);
	//struct dentry *(*d_real)(struct dentry *, const struct inode *);
};




struct inode_operations {
	int (*create) (struct user_namespace *, struct inode *,struct dentry *,umode_t, bool);
	struct dentry * (*lookup) (struct inode *,struct dentry *, unsigned int);

	int (*link) (struct dentry *,struct inode *,struct dentry *);
	int (*unlink) (struct inode *,struct dentry *);
	int (*mkdir) (struct user_namespace *, struct inode *,struct dentry *,umode_t);
	int (*rmdir) (struct inode *,struct dentry *);
	int (*mknod) (struct user_namespace *, struct inode *,struct dentry *,umode_t,dev_t);
	int (*rename) (struct user_namespace *, struct inode *, struct dentry *,struct inode *, struct dentry *, unsigned int);

	int (*permission) (struct user_namespace *, struct inode *, int);
	int (*setattr) (struct user_namespace *, struct dentry *,struct iattr *);
	int (*getattr) (struct user_namespace *, const struct path *,struct kstat *, u32, unsigned int);
	int (*fiemap)(struct inode *, struct fiemap_extent_info *, u64 start, u64 len);

	//const char * (*get_link) (struct dentry *, struct inode *, struct delayed_call *);
	//ssize_t (*listxattr) (struct dentry *, char *, size_t);
	//struct posix_acl * (*get_inode_acl)(struct inode *, int, bool);
	//int (*readlink) (struct dentry *, char __user *,int);
	//int (*symlink) (struct user_namespace *, struct inode *,struct dentry *,const char *);
	//void (*truncate)	(struct inode*);
	//int (*fileattr_set)(struct user_namespace *mnt_userns,struct dentry *dentry, struct fileattr *fa);
	//int (*fileattr_get)(struct dentry *dentry, struct fileattr *fa);
	//int (*update_time)(struct inode *, struct timespec64 *, int);
	//int (*atomic_open)(struct inode *, struct dentry *,struct file *, unsigned open_flag,umode_t create_mode);
	//int (*tmpfile) (struct user_namespace *, struct inode *,struct file *, umode_t);
	//struct posix_acl *(*get_acl)(struct user_namespace *, struct dentry *,int);
	//int (*set_acl)(struct user_namespace *, struct dentry *,struct posix_acl *, int);
};


/* Eliminamos el: freeze, evict_inode, umount_begin, drop_inode, put_super*/
struct super_operations {
   	struct inode *(*alloc_inode)(struct super_block *sb);					/*inode -> asignar memoria*/
	//void (*destroy_inode)(struct inode *);									/*destruir inode*/
	void (*free_inode)(struct inode *);										/*free_inode*/

   	void (*dirty_inode) (struct inode *, int flags);						/*localizacion memoria*/
	int (*write_inode) (struct inode *, struct writeback_control *wbc);		/*escribir en el inodo*/
	int (*sync_fs)(struct super_block *sb, int wait);						/*update -> disk*/
	int (*statfs) (struct dentry *, struct kstatfs *);						/**/
	int (*remount_fs) (struct super_block *, int *, char *);				/*montaje*/

	//int (*show_options)(struct seq_file *, struct dentry *);
	//int (*show_devname)(struct seq_file *, struct dentry *);
	//int (*show_path)(struct seq_file *, struct dentry *);
	//int (*show_stats)(struct seq_file *, struct dentry *);

};