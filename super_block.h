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
#include <uapi/linux/fs.h>



struct super_block {
	struct list_head	s_list;		                /* Keep this first */
	//dev_t			s_dev;		                    /* search index; _not_ kdev_t */
	unsigned char		s_blocksize_bits;
	unsigned long		s_blocksize;
	loff_t			s_maxbytes;	                    /* Max file size */
	struct file_system_type	*s_type;
	//const struct super_operations	*s_op;
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
	struct block_device	*s_bdev;
	//struct backing_dev_info *s_bdi;
	//struct mtd_info		*s_mtd;             *********
	struct hlist_node	s_instances;
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