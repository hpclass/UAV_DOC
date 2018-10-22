
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


