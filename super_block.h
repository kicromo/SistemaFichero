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


struct dentry {
	/* RCU lookup touched fields */
	unsigned int d_flags;		/* protected by d_lock */
	seqcount_spinlock_t d_seq;	/* per dentry seqlock */
	struct hlist_bl_node d_hash;	/* lookup hash list */
	struct dentry *d_parent;	/* parent directory */
	struct qstr d_name;
	struct inode *d_inode;		/* Where the name belongs to - NULL is
					 * negative */
	unsigned char d_iname[DNAME_INLINE_LEN];	/* small names */

	/* Ref lookup also touches following */
	struct lockref d_lockref;	/* per-dentry lock and refcount */
	const struct dentry_operations *d_op;
	struct super_block *d_sb;	/* The root of the dentry tree */
	unsigned long d_time;		/* used by d_revalidate */
	void *d_fsdata;			/* fs-specific data */

	union {
		struct list_head d_lru;		/* LRU list */
		wait_queue_head_t *d_wait;	/* in-lookup ones only */
	};
	struct list_head d_child;	/* child of parent list */
	struct list_head d_subdirs;	/* our children */
	/*
	 * d_alias and d_rcu can share memory
	 */
	union {
		struct hlist_node d_alias;	/* inode alias list */
		struct hlist_bl_node d_in_lookup_hash;	/* only for in-lookup ones */
	 	struct rcu_head d_rcu;
	} d_u;
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

	unsigned int	i_blksbit; 		/* blocks size bits */
	unsigned int	i_blocks;		/* file size blocks*/
	unsigned int	i_bytes;		/* bytes consume */

	const struct inode_operations	*i_op;
	struct 		 super_block		*i_sb;
	const struct file_operations	*i_fop;	/* former ->i_op->default_file_ops */

	struct list_head	i_devices;
	unsigned long 		i_state;
	unsigned long 		i_flags;

};




struct super_block {
	struct list_head	s_list;		                /* Keep this first */
	//dev_t			s_dev;		                    /* search index; _not_ kdev_t */
	unsigned char		s_blocksize_bits;
	unsigned long		s_blocksize;
	loff_t			s_maxbytes;	                    /* Max file size -> lon long*/ 
	//struct file_system_type	*s_type;
	const struct super_operations	*s_op;
	//const struct dquot_operations	*dq_op;
	//const struct quotactl_ops	*s_qcop;
	//const struct export_operations *s_export_op;
	unsigned long		s_flags;
	//unsigned long		s_iflags;	/* internal SB_I_* flags */
	//unsigned long		s_magic;
	struct dentry		*s_root;    /*/ raiz arbol*/
	//struct rw_semaphore	s_umount;
	int			s_count;
	atomic_t		s_active;

	//struct hlist_bl_head	s_roots;	        /* alternate root dentries for NFS */
	struct list_head	s_mounts;	            /* list of mounts; _not_ for fs use */
	//struct block_device	*s_bdev;			*********
	//struct backing_dev_info *s_bdi;
	//struct mtd_info		*s_mtd;             *********
	//struct hlist_node	s_instances;			*********
	//unsigned int		s_quota_types;	        /* Bitmask of supported quota types */
	//struct quota_info	s_dquot;	/* Diskquota specific options */

	//struct sb_writers	s_writers;

	/*
	 * Keep s_fs_info, s_time_gran, s_fsnotify_mask, and
	 * s_fsnotify_marks together for cache efficiency. They are frequently
	 * accessed and rarely modified.
	 */
	//void			*s_fs_info;	/* Filesystem private info */
    /*Clook delete*******/

	char			s_id[32];	/* Informational name  -> Super Block*/
	uuid_t			s_uuid;		/* UUID */

	/*
	 * Filesystem subtype.  If non-empty the filesystem type field
	 * in /proc/mounts will be "type.subtype"
	 */
	//const char *s_subtype;
	//const struct dentry_operations *s_d_op; /* default d_op for dentries */
	/*
	 * Owning user namespace and default context in which to
	 * interpret filesystem uids, gids, quotas, device nodes,
	 * xattrs and security labels.
	 */
	//struct user_namespace *s_user_ns;
	
}



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