一. logger的创建
1.1 logger对象的实例化
Logger::Logger(LogWriter::Backend backend, size_t buffer_size, uint32_t log_interval, const char *poll_topic_name,
	       bool log_on_start, bool log_until_shutdown, bool log_name_timestamp, unsigned int queue_size) :
	//找到tooic的名字
	if (strcmp(poll_topic_name, topics[i]->o_name) == 0) {


1.2 logger 整个文件的入口,shi 1个静态函数 
static int main(int argc, char *argv[]) //静态函数
		-> static int start_command_base(int argc, char *argv[]) //静态函数 
			-> 	ret = T::task_spawn(argc, argv);
				-> _task_id = px4_task_spawn_cmd("logger",
					 ->static int run_trampoline(int argc, char *argv[]) //静态函数
					 	-> _object = T::instantiate(argc, argv); //用户的实例入口
					 		//解析输入的参数
					 		->while ((ch = px4_getopt(argc, argv, "r:b:etfm:q:p:", &myoptind, &myoptarg)) != EOF) {
					 	->if (_object) {
					 	//执行周期的处理
					 	->object->run();

1.3 指定logger的周期，使用那个orb进行控制
case 'p':
	poll_topic = myoptarg;
	break;

1.4 启动logger,记录数据
 void Logger::start_log_file()
 	->_writer.start_log_file(file_name);
 		-> void LogWriter::start_log_file(const char *filename)
			if (_log_writer_file) {
				_log_writer_file->start_log(filename);
                -> _fd = ::open(filename, O_CREAT | O_WRONLY, PX4_O_MODE_666); //create log file 

1.5 logger_write_file.cpp中对象的成员
//lock file 
void lock()
{
	if (_log_writer_file) { _log_writer_file->lock(); }
}

void unlock()
{
	if (_log_writer_file) { _log_writer_file->unlock(); }
}

1.6 logger中的文件层次架构很霸气
logger.cpp
 	-> logger_write.cpp
 		->logger_write_file.cpp
 		->logger_write_mavlink.cpp
 	-> watchdog.cpp 

1.7 logger write 重要的系统资源，1个互斥量，1个条件变量
void lock()
{
	pthread_mutex_lock(&_mtx);
}

void unlock()
{
	pthread_mutex_unlock(&_mtx);
}

void notify()
{
	pthread_cond_broadcast(&_cv);
}

2. logger write file 

2.1 创建logwritefile的对象： 最小写入的文件大小是4096字节
modules/sdlog2/sdlog2.c:154:static const int MIN_BYTES_TO_WRITE = 2048;
modules/sdlog2/sdlog2.c:2352:		if (logbuffer_count(&lb) > MIN_BYTES_TO_WRITE) {
//create 
LogWriterFile::LogWriterFile(size_t buffer_size) :
	//循环缓冲区的大小，至少是写个flash的大小4096
	_buffer_size(math::max(buffer_size, _min_write_chunk + 300))
{
	pthread_mutex_init(&_mtx, nullptr);
	pthread_cond_init(&_cv, nullptr);

2.3 写1个message
//buffer overflow, writebuf 
int LogWriterFile::write_message(void *ptr, size_t size, uint64_t dropout_start)
{
	if (_need_reliable_transfer) {
		int ret;

		while ((ret = write(ptr, size, dropout_start)) == -1) {
			unlock(); 
			notify(); //read 

2.3 线程内部等待接收到最大缓冲的数据，就行写入
	while (true) {
		available = get_read_ptr(&read_ptr, &is_part);

		/* if sufficient data available or partial read or terminating, exit this wait loop */
		if ((available >= _min_write_chunk) || is_part || !_should_run) {
			/* GOTO end of block */
			break;
		}
		pthread_cond_wait(&_cv, &_mtx);
	}

	pthread_mutex_unlock(&_mtx);
	written = 0;

	if (available > 0) {
		perf_begin(_perf_write)
	//sdlog2 
	if (logbuffer_count(&lb) > MIN_BYTES_TO_WRITE) {
	-> if (available > 0) {
	perf_begin(_perf_write);
	written = ::write(_fd, read_ptr, available);
	perf_end(_perf_write);
