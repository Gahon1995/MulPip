struct 
{
	volatile bool isOpen=false;
	bool isConnected = false;
	int connectedId = -1;
	volatile int isAllowSend= 200;	//SEND_REJECT
}WIFISTATE;


//Wi-Fi信息保存
struct WIFIDATA
{
	
	int num_1;
	int num_2;
	int num_3;
	int vol_1;
	int vol_2;
	int vol_3;
};


struct CONINFO
{
	bool needControl;		//是否进行控制
	volatile double target;		//控制的目标值
	volatile double nowflow;		//实时目标值
	int pipNum;			//控制目标的管道，用于打开中断
	int pipOpenKey;		//控制目标开关引脚号
	volatile int finish;		//控制是否结束
	void (*countFunction)(void);
	volatile long lastCount;
};


//typedef struct CONFIG
//{
//	int num;
//	double flow;
//	int pip;
//	int switchKey;
//};

struct PIPCONFIG
{
	//int control;	//是否进行控制标志
	volatile double flow;	//实时流量
	volatile bool state;	//开关状态
	volatile double step;
};

