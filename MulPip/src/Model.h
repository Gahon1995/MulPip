
//Wi-Fi信息保存
typedef struct INFO
{
	int num_1;
	int num_2;
	int num_3;
	int vol_1;
	int vol_2;
	int vol_3;
}INFO;


typedef struct CONINFO
{
	bool needControl;		//是否进行控制
	volatile double target;		//控制的目标值
	volatile double nowflow;		//实时目标值
	int pipNum;			//控制目标的管道，用于打开中断
	int pipOpenKey;		//控制目标开关引脚号
	volatile int finish;		//控制是否结束
};


typedef struct CONFIG
{
	int num;
	double flow;
	int pip;
	int switchKey;
};

typedef struct PIPCONFIG
{
	//int control;	//是否进行控制标志
	volatile double flow;	//实时流量
	volatile bool state;	//开关状态
};