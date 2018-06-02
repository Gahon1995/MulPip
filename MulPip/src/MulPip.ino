//头文件包含

# include "./include/mulpip.h"  


//全局变量定义

Scheduler ts;	//任务管理器

//主要运行任务定义
Task tDisplay(0.01 * TASK_SECOND, TASK_FOREVER, MyDisplay, &ts, true);	//显示任务
Task tWiFi(0.5 * TASK_SECOND, TASK_FOREVER, MyWiFi, &ts, true);		//WiFi接收任务
Task tStatus(0.001 * TASK_SECOND, TASK_FOREVER, MyStatus,NULL,false,NULL, disableMyStatus);		//检查机器运行状态任务

//模拟管道运行状态任务												
Task tPIP1(0.001 * TASK_SECOND, TASK_FOREVER, PIP1, &ts, true);
Task tPIP2(0.001 * TASK_SECOND, TASK_FOREVER, PIP2, &ts, true);
Task tPIP3(0.001 * TASK_SECOND, TASK_FOREVER, PIP3, &ts, true);

//机器控制任务，未启用
Task tConPIP1(0.001 * TASK_SECOND, TASK_FOREVER, controlPIP1, NULL, false, NULL, FinishPIP1);
Task tConPIP2(0.001 * TASK_SECOND, TASK_FOREVER, controlPIP2, NULL, false, NULL, FinishPIP2);
Task tConPIP3(0.001 * TASK_SECOND, TASK_FOREVER, controlPIP3, NULL, false, NULL, FinishPIP3);

//显示屏声明
U8G2_SSD1306_128X64_NONAME_F_HW_I2C u8g2(U8G2_R0, /* reset=*/ U8X8_PIN_NONE);
//模拟管道数据声明
volatile PIPCONFIG pip1, pip2, pip3;
//执行控制时用于保存相关管道数据
volatile CONINFO conPIP1, conPIP2, conPIP3;
// 保存wifi信息
volatile WIFIDATA wifidata;



volatile int isFINISHED = JOB_UNFINISH; //标志： 判断当前管道是否完成配置
volatile int FLAG_jobStatus = JOB_FINISH;




void setup()
{
	//初始化串口
	initSerial();
	//初始化引脚
	initPIN();
	//初始化硬件
	WIFISTATE.isOpen=init_WIFI(); //WIFI名称目前写死
	//初始化WIFI出书过来的信息保存目标
	initWiFiConfig();
	//初始化模拟管道的数据
	initPIP();
	//初始化控制的参数
	initConInfo();
	//初始化线程
	//initThread();
	//初始化显示屏
	u8g2.begin();
}

void loop()
{
	ts.execute();	//执行任务
}
