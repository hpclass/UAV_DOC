
1 .pwm orb
==================
uint64 timestamp	# Microseconds since system boot
uint64 error_count
uint32 pulse_width	# Pulse width, timer counts 
uint32 period		# Period, timer counts


2 .pwm 输入采集
==================

使用CCR1和CCR2采集宽度和周期
#define rCCR_PWMIN_A		rCCR1			/* compare register for PWMIN */
#define DIER_PWMIN_A		(GTIM_DIER_CC1IE) 	/* interrupt enable for PWMIN */
#define SR_INT_PWMIN_A		GTIM_SR_CC1IF		/* interrupt status for PWMIN */
#define rCCR_PWMIN_B		rCCR2 			/* compare register for PWMIN */
#define SR_INT_PWMIN_B		GTIM_SR_CC2IF		/* interrupt status for PWMIN */


static int pwmin_tim_isr(int irq, void *context)
	uint32_t period = rCCR_PWMIN_A;
	uint32_t pulse_width = rCCR_PWMIN_B;

	/* ack the interrupts we just read */
	rSR = 0;

	if (g_dev != nullptr) {
		g_dev->publish(status, period, pulse_width);
	}

3.直升机姿态控制中
======================================
modules/heli_att_control/heli_att_control_main.cpp:1457:		orb_copy(ORB_ID(pwm_input), _Engine_RPM_sub, &_engine_rpm);

3.1 拷贝orb  【r_c 实时转速】
==========
orb_copy(ORB_ID(pwm_input), _Engine_RPM_sub, &_engine_rpm);

3.2 计算转算
 				
if (_engine_rpm.period > 3000 && _engine_rpm.period < 100000 && (hrt_absolute_time() - _engine_rpm.timestamp) < 500000) {
		r_c = 60000000.0f / _engine_rpm.period;
	}
	else {
		r_c = r_c_lasttime;
	}

3.3 进行低通滤波 【#define SPEED_LBXS 0.6f//低通滤波系数】
m_rc=SPEED_LBXS*m_rc+(1-SPEED_LBXS)*r_c;//低通滤波处理

