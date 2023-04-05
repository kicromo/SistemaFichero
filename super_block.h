#ifndef _LINUX_FS_H
#define _LINUX_FS_H

#include <linux/linkage.h>
#include <linux/wait_bit.h>
#include <linux/kdev_t.h>
#include <linux/dcache.h>
#include <linux/path.h>
#include <linux/stat.h>
#include <linux/cache.h>
#include <linux/list.h>
#include <linux/list_lru.h>
#include <linux/llist.h>
#include <linux/radix-tree.h>
#include <linux/xarray.h>
#include <linux/rbtree.h>
#include <linux/init.h>
#include <linux/pid.h>
#include <linux/bug.h>
#include <linux/mutex.h>
#include <linux/rwsem.h>
#include <linux/mm_types.h>
#include <linux/capability.h>
#include <linux/semaphore.h>
#include <linux/fcntl.h>
#include <linux/rculist_bl.h>
#include <linux/atomic.h>
#include <linux/shrinker.h>
#include <linux/migrate_mode.h>
#include <linux/uidgid.h>
#include <linux/lockdep.h>
#include <linux/percpu-rwsem.h>
#include <linux/workqueue.h>
#include <linux/delayed_call.h>
#include <linux/uuid.h>
#include <linux/errseq.h>
#include <linux/ioprio.h>
#include <linux/fs_types.h>
#include <linux/build_bug.h>
#include <linux/stddef.h>
#include <linux/mount.h>
#include <linux/cred.h>
#include <linux/mnt_idmapping.h>
#include <linux/slab.h>

#include <asm/byteorder.h>
//#include <linux/fs.h>

struct file {

	struct list_head				fu_list		/* list of file objects*/ 
	struct path						f_path;		/* contains dentry*/
	//struct inode		*f_inode;				/* cached value */
	const struct file_operations	*f_op;
	atomic_t					f_count;		/*file object's usage count*/
	unsigned int 				f_flags;		/* flags specified on open*/
	mode_t						f_mode;			/* file access mode*/
	loff_t						f_pos;			/* file offset (file pointer)*/
	struct fown_struct			f_owner;		/*owner data for signals */
	const struct cred			*f_cred;		/* file credencials*/
	struct file_ra_state		f_ra;			/*read-ahead state*/
	u64			f_version;

	struct address_space		*f_mapping;			/* page cache mapping*/
	unsigned long 				f_mnt_write_state	/*debbuging state*/
	//struct inode		*f_inode;				/* cached value */
	//void			*private_data;				/* tty driver hook*/
	//struct list_head		f_ep_links			/* list of epoll links*/

};







struct dentry {
	/* Read Copy Upadate (RCU) lookup touched fields */
	atomic_t 				d_count				/*usage count*/
	unsigned int 			d_flags;			/* protected by d_lock / detry_flags */
	int 					d_mounted			/* is this a mount point? */
	struct inode 			*d_inode;			/* associated inode */
	struct hlist_bl_node 	d_hash;				/* hlist_node -> lookup hash list  */
	struct dentry 			*d_parent;			/* parent directory */
	struct qstr 			d_name;				/* Dentry name ---> ????*/
	struct list_head 		d_child;			/* list of dentries witin/ */
	struct list_head 		d_subdirs;			/* our children */
	const struct dentry_operations *d_op;		/* Dentry operation table*/
	struct super_block 		*d_sb;				/* The root of the dentry tree */
	unsigned char			d_iname[DNAME_INLINE_LEN_MIN]	/*short name*/ 		
	
};




struct inode {
	struct hlist_node	i_hash;				/*hash list*/
	struct list_head	i_io_list;			/*i_list -> list of inodes*/
	struct list_head	i_wb_list;			/* i_dentry -> list of dentries */
	unsigned long		i_node ;			/*num inode*/
	int 				i_count;			/* ref counter*/
	unsigned int		i_nlick;

	loff_t			i_size;					/*long long -> tam inode*/
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

	
}


/************************************************************************************/
/*							FUNCIONES Y PROCEDIMIENTOS								*/
/************************************************************************************/




struct dentry_operations
{
	int (*d_revalidate)(struct dentry *, unsigned int);
	int (*d_hash)(const struct dentry *, struct qstr *);
	int (*d_compare)(const struct dentry *, unsigned int, const char *, const struct qstr *);
	int (*d_delete)(struct dentry *);
	int (*d_init)(struct dentry *);
	void (*d_release)(struct dentry *);
	void (*d_iput)(struct dentry *, struct inode *);
	char *(*d_dname)((struct dentry *dentry, char *buffer, int buflen);

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
	int (*fiemap)(struct inode *, struct fiemap_extent_info *, u64 start,u64 len);
	
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