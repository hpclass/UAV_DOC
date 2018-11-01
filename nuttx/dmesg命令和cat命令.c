demsg命令
======================

int cmd_dmesg(FAR struct nsh_vtbl_s *vtbl, int argc, char **argv)
 //这里很像cat命令
 nt nsh_catfile(FAR struct nsh_vtbl_s *vtbl, FAR const char *cmd,
                FAR const char *filepath)
   -> fd = open(filepath, O_RDONLY);
      ->    int nbytesread = read(fd, buffer, IOBUFFERSIZE); 
        -> nsh_output(vtbl, g_fmtsignalrecvd, cmd);

cat命令
=======================
int cmd_cat(FAR struct nsh_vtbl_s *vtbl, int argc, char **argv)
  ret = nsh_catfile(vtbl, argv[0], fullpath);