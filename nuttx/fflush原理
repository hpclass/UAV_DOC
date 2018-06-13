fflush(stdout);
    -> find -name *.c | xargs grep  "fflush"
    －> ./nuttx/libc/stdio/lib_fflush.c
        -> ./nuttx/libc/stdio/lib_libfflush.c 
            -> if (stream->fs_bufpos  != stream->fs_bufstart)　//文件stream中的数据还没有发送完成，手动把读指针和写指针对其
                {
                /* Make sure that the buffer holds buffered write data.  We do not
                * support concurrent read/write buffer usage.
                */

                if (stream->fs_bufread != stream->fs_bufstart)
                    {
　　　　　　