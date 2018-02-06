int CAN_DRV::task_main() {

    uint32_t dist_sensor_direction_sel = 0;
    param_get(param_find("MPC_DIS_DIR_SEL"), &dist_sensor_direction_sel);

    struct can_msg_s rxmsg;           
    size_t msgsize;
    ssize_t nbytes;
    

    if (OK != init()) { 
        return -1;
    }           
    usleep(100000);//delay 100ms 
    
    struct filelist *flist = sched_getfiles();
    struct file old;
    memcpy(&old, &(flist->fl_files[1]), sizeof(struct file));
    printf("A\n");
    int fd = open("/dev/null", O_RDWR);
    if (fd > 0) {
        dup2(fd, 1);
        close(fd);
        printf("B\n");
        memcpy(&(flist->fl_files[1]), &old, sizeof(struct file));
        printf("C\n");
    }
