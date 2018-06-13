uart_dev_t

union inode_ops_u
{
  FAR const struct file_operations      *i_ops;    /* Driver operations for inode */
#ifndef CONFIG_DISABLE_MOUNTPOINT
  FAR const struct block_operations     *i_bops;   /* Block driver operations */
  FAR const struct mountpt_operations   *i_mops;   /* Operations on a mountpoint */
#endif
#ifdef CONFIG_FS_NAMED_SEMAPHORES
  FAR struct nsem_inode_s               *i_nsem;   /* Named semaphore */
#endif
#ifndef CONFIG_DISABLE_MQUEUE
  FAR struct mqueue_inode_s             *i_mqueue; /* POSIX message queue */
#endif
};

//节点的数据结构
struct inode
{
  FAR struct inode *i_peer;     /* Link to same level inode */
  FAR struct inode *i_child;    /* Link to lower level inode */
  int16_t           i_crefs;    /* References to inode */
  uint16_t          i_flags;    /* Flags for inode */
  union inode_ops_u u;          /* Inode operations */
#ifdef CONFIG_FILE_MODE
  mode_t            i_mode;     /* Access mode flags */
#endif
  FAR void         *i_private;  /* Per inode driver private data */
  char              i_name[1];  /* Name of inode (variable) */
};

//注册驱动， 把file_opreations挂载到路径上，同时吧dev挂载到路径上
return register_driver(path, &g_serialops, 0666, dev);  
 
open
	-> path
		-> static const struct file_operations
			->  uart_open
        		-> FAR struct inode *inode    = filep->f_inode;
				-> FAR uart_dev_t   *dev      = inode->i_private;//设备驱动层


