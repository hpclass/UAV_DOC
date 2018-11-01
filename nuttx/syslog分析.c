    1.  用户层去封装流的概念
    2.  内核去封装对应设备驱动的节点
    3.  用层和内核层通道putc进行打通道

    //指定输入流
    syslogstream((FAR struct lib_outstream_s *)&stream);
        stream->put   = syslogstream_putc;  
          ->  ret = syslog_putc(ch); //输入到syslog对应的通道 
          		->  return g_syslog_channel->sc_force(ch);
          		->  return g_syslog_channel->sc_putc(ch);

    int syslog_initialize(enum syslog_init_e phase)
      //dev和console都是基于文件的操作
     ->   ret = syslog_dev_channel(); 
        -> file_write(FAR struct file *filep, FAR const void *buf, size_t nbytes)
        -> syslog_channel(&g_syslog_dev_channel); //设备文件中
            -> (void)file_fsync(&g_syslog_dev.sl_file);
     ->   ramlog_syslog_channel();
         //先注册设备节点
         -> register_driver(CONFIG_SYSLOG_DEVPATH, &g_ramlogfops, 0666, &g_sysdev);//g_sys中缓冲
         -> int ramlog_register(FAR const char *devpath, FAR char *buffer, size_t buflen)
           //读写数据到ram缓冲区
           -> static ssize_t ramlog_write(FAR struct file *filep, FAR const char *buffer, size_t len)
           -> ret = ramlog_addchar(priv, '\r'); 写到缓冲区
               -> g_sysbuffer                    /* rl_buffer */
     ->   syslog_console_channel();
          -> open /dev/console
          -> write console


//如果是中断服务程序，可以把log添加到中断的缓冲中去
int syslog_add_intbuffer(int ch)

//默认借口
//RAMLOG是一个设备节点
#if defined(CONFIG_RAMLOG_SYSLOG) && !defined(CONFIG_SYSLOG_DEVPATH)
#  define CONFIG_SYSLOG_DEVPATH "/dev/ramlog"
#endif


//设置
#if defined(CONFIG_SYSLOG_CHAR) && !defined(CONFIG_SYSLOG_DEVPATH)
#  define CONFIG_SYSLOG_DEVPATH "/dev/ttyS1"
#endif

#ifdef CONFIG_SYSLOG_INTBUFFER
#  ifndef CONFIG_SYSLOG_INTBUFSIZE
#    define CONFIG_SYSLOG_INTBUFSIZE 512
#  endif
#  if CONFIG_SYSLOG_INTBUFSIZE > 65535
#    undef  CONFIG_SYSLOG_INTBUFSIZE
#    define CONFIG_SYSLOG_INTBUFSIZE 65535
#  endif
#endif

总结： 1. printf就是输出数据到stdout的文件句柄中
       2. syslog和printf很像，自己实现c库的流的概念，但是没有做流的缓冲部分，直接通道过通道的概念进行缓冲 
       3. 标准stdin, stdout和/dev/console是一样的，stdin有自己的缓冲机制
        printf(stdin)
        write("/dev/console）是不一样的
