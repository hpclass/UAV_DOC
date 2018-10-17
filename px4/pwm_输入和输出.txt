yangang@ubuntu:~/work/theone_proj/firmware/theone-mc-helicopter/theone-heli/ROMFS/px4fmu_common/init.d$ grep -rn "pwm"
//pwm输入和输出
rc.interface:38:		set OUTPUT_DEV /dev/pwm_output0
rc.interface:74:			pwm rate -c $PWM_OUT -r $PWM_RATE
rc.interface:75:                        # pwm rate -c 4 -r 200
rc.interface:83:			pwm disarmed -c $PWM_OUT -p $PWM_DISARMED
rc.interface:86:			    pwm disarmed -c 678 -p 900
rc.interface:88:			    pwm disarmed -c 78 -p 900
rc.interface:95:			    pwm disarmed -c 5 -p 900
rc.interface:100:			    pwm disarmed -c 4 -p 760
rc.interface:106:			pwm min -c $PWM_OUT -p $PWM_MIN
rc.interface:109:			    pwm min -c 4 -p 460
rc.interface:115:			pwm max -c $PWM_OUT -p $PWM_MAX
rc.interface:118:			    pwm max -c 4 -p 1060
rc.interface:125:		pwm failsafe -d $OUTPUT_DEV $FAILSAFE
rc.interface:127:	pwm failsafe -c 123 -p 1520
rc.interface:128:	pwm failsafe -c 78 -p 900
rc.interface:131:			pwm failsafe -c 4 -p 760
rc.interface:133:			pwm failsafe -c 4 -p 1520
rc.interface:137:			pwm failsafe -c 5 -p 1520
rc.interface:139:			pwm failsafe -c 5 -p 900 
rc.interface:143:			pwm failsafe -c 6 -p 900
rc.interface:147:				pwm failsafe -c 6 -p 920
rc.interface:149:				pwm failsafe -c 6 -p 2120
rc.interface:168:	set OUTPUT_AUX_DEV /dev/pwm_output1
rc.interface:202:			echo "ERROR: Could not start: fmu mode_pwm" >> $LOG_FILE
rc.interface:208:		fmu mode_pwm
rc.interface:218:				pwm rate -c $PWM_AUX_OUT -r $PWM_AUX_RATE -d $OUTPUT_AUX_DEV
rc.interface:226:				pwm disarmed -c $PWM_AUX_OUT -p $PWM_AUX_DISARMED -d $OUTPUT_AUX_DEV
rc.interface:227:                                pwm disarmed -c 2 -p 1520 -d $OUTPUT_AUX_DEV
rc.interface:232:				pwm min -c $PWM_AUX_OUT -p $PWM_AUX_MIN -d $OUTPUT_AUX_DEV
rc.interface:236:				pwm max -c $PWM_AUX_OUT -p $PWM_AUX_MAX -d $OUTPUT_AUX_DEV
rc.interface:242:			pwm failsafe -d $OUTPUT_AUX_DEV $FAILSAFE
rcS:250:	set FMU_MODE pwm
rcS:251:	set AUX_MODE pwm
rcS:504:				if [ $FMU_MODE == pwm -o $FMU_MODE == gpio ]
rcS:508:				if [ $FMU_MODE == pwm_gpio -o $OUTPUT_MODE == ardrone ]
rcS:541:			if pwm_out_sim mode_port2_pwm8
rcS:582:					if [ $FMU_MODE == pwm -o $FMU_MODE == gpio ]
rcS:586:					if [ $FMU_MODE == pwm_gpio -o $OUTPUT_MODE == ardrone ]
rcS:641:			set AUX_MODE pwm4
rcS:883:   pwm_input start

//pwm输出
rcS:890:	if pwm_input start
rcS:892:		if ll40ls start pwm


pwm输入的启动过程： 
int pwm_input_main(int argc, char *argv[])
		-> pwmin_start();

	g_dev = new PWMIN();
	  -> PWMIN::PWMIN() :
	   CDev("pwmin", PWMIN0_DEVICE_PATH) // 注册设备节点
        
        //初始化 ，创建必要的内存空间 
	if (g_dev->init() != OK) {

	exit(0);
}


int
PWMIN::open(struct file *filp)
{
	if (g_dev == nullptr) {
		return -EIO;
	}

	int ret = CDev::open(filp);

	if (ret == OK && !_timer_started) {
		g_dev->_timer_init();
	}

	return ret;
}

//上层去open打开设备节点，进行数据传递

//初始化
drivers/px4fmu/fmu.cpp:1050:		up_pwm_servo_init(_pwm_mask);

int up_pwm_servo_init(uint32_t channel_mask) //pwm_servo.c 
		for (unsigned channel = 0; channel_mask != 0 &&  channel < MAX_TIMER_IO_CHANNELS; channel++) {
		if (channel_mask & (1 << channel)) { //遍历所有的通道 
  -> io_timer_channel_init(channel, IOTimerChanMode_PWMOut, NULL, NULL); //drv_io_time.c文件
   

   pwm.cpp = > 配置pwm的通道，频率
   fmu.cpp =》订阅控制量，进行混控处理
   mix.cpp进行混控处理 

     drv_io_time.c 


   控制量是1个抽象的东西

下面是8个控制量: 
uint8 NUM_ACTUATOR_CONTROLS = 8
uint8 NUM_ACTUATOR_CONTROL_GROUPS = 4
uint8 INDEX_ROLL = 0
uint8 INDEX_PITCH = 1
uint8 INDEX_YAW = 2
uint8 INDEX_THROTTLE = 3
uint8 INDEX_FLAPS = 4
uint8 INDEX_SPOILERS = 5
uint8 INDEX_AIRBRAKES = 6
uint8 INDEX_LANDING_GEAR = 7
uint8 GROUP_INDEX_ATTITUDE = 0
uint8 GROUP_INDEX_ATTITUDE_ALTERNATE = 1
uint64 timestamp
uint64 timestamp_sample	    # the timestamp the data this control response is based on was sampled
float32[8] control



// 至少进行2层callback的调用
//定时器执行的callback，
  -> 执行到输入的callback, 
    -> 然后执行到通道的callback,
static void input_capture_chan_handler(void *context, const io_timers_t *timer, uint32_t chan_index,


static void input_capture_bind(unsigned channel, capture_callback_t callback, void *context)
{
  irqstate_t flags = px4_enter_critical_section();
  channel_handlers[channel].callback = callback;
  channel_handlers[channel].context = context;
  px4_leave_critical_section(flags);
}

static void input_capture_unbind(unsigned channel)
{
  input_capture_bind(channel, NULL, NULL);
}

pwm_input.cpp自己 联动模式的pwm输入捕获程序


void PWMIN::_timer_init(void)
 -> irq_attach(PWMIN_TIMER_VECTOR, pwmin_tim_isr);

