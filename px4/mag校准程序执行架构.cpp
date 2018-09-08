
//mag校准
if (!strcmp(argv[2], "mag")) {  //commander/cpp
	 calib_ret = do_mag_calibration(mavlink_fd,param_cal_mag_sides); //进入mag_calibration.cpp
	      ->for (unsigned cur_mag = 0; cur_mag < max_mags; cur_mag++) { //遍历所有mag
	      -> int fd = px4_open(str, O_RDONLY); //打开mag0, mag1, mag2
	      -> result = px4_ioctl(fd, MAGIOCSSCALE, (long unsigned int)&mscale_null); //传感器mag0， 清除
	      -> result = px4_ioctl(fd, MAGIOCCALIBRATE, fd); //进入传感器校准 hmc5883.cpp
	          -> int HMC5883::ioctl(struct file *filp, int cmd, unsigned long arg)
	          	 -> case MAGIOCCALIBRATE: return calibrate(filp, arg);
	          	     ->int HMC5883::calibrate(struct file *filp, unsigned enable)
	          	        -> if (OK != ioctl(filp, MAGIOCSRANGE, 3)) { //重新设置mag量程为2.5
	          	        	 -> return set_range(arg);
	          	        	 	-> ret = write_reg(ADDR_CONF_B, (_range_bits << 5));//设置5883寄存器
	          	        -> for (uint8_t i = 0; i < 100 && good_count < 30; i++) {
						-> scaling[0] = sum_excited[0] / good_count; //计算5883平均数，作为scale
						-> scaling[1] = sum_excited[1] / good_count;
						-> scaling[2] = sum_excited[2] / good_count;
     
     //获取校准后的传感器scale
	 ->calibrate_return mag_calibrate_all(int mavlink_fd, int32_t (&device_ids)[max_mags])
		 ->if (px4_ioctl(fd_mag, MAGIOCGSCALE, (long unsigned int)&mscale) != OK) { 
