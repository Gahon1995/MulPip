/**
	初始化函数定义
 */

//初始化串口
void initSerial() {
	Serial.begin(115200);
	Serial1.begin(9600);
}



void initTask() {
	
}
//初始化引脚定义
void initPIN() {
	// 中断口
	pinMode(PIP_1, INPUT);
	pinMode(PIP_2, INPUT);
	pinMode(PIP_3, INPUT);
	//开关
	pinMode(SWITCH_1, OUTPUT);
	pinMode(SWITCH_2, OUTPUT);
	pinMode(SWITCH_3, OUTPUT);
	//关闭开关
	digitalWrite(SWITCH_1, LOW);
	digitalWrite(SWITCH_2, LOW);
	digitalWrite(SWITCH_3, LOW);
}

void initWiFiConfig() {
	wifidata.num_1 = 0;
	wifidata.num_2 = 0;
	wifidata.num_3 = 0;
	wifidata.vol_1 = 0.0;
	wifidata.vol_2 = 0.0;
	wifidata.vol_3 = 0.0;
}



void initConInfo() {
	conPIP1.nowflow = 0.0;
	conPIP1.needControl = false;
	conPIP1.pipNum = PIP_1;
	conPIP1.pipOpenKey = SWITCH_1;
	conPIP1.target = 0.0;
	conPIP1.finish = PIP_NOTRUNNING;

	conPIP2.nowflow = 0.0;
	conPIP2.needControl = false;
	conPIP2.pipNum = PIP_2;
	conPIP2.pipOpenKey = SWITCH_3;
	conPIP2.target = 0.0;
	conPIP2.finish = PIP_NOTRUNNING;

	conPIP3.nowflow = 0.0;
	conPIP3.needControl = false;
	conPIP3.pipNum = PIP_3;
	conPIP3.pipOpenKey = SWITCH_3;
	conPIP3.target = 0.0;
	conPIP3.finish = PIP_NOTRUNNING;
}
void initData() {
	//count = 0;
	//precount = count;
	//flow = 0.0;
	//target = 0.0;
}

void initPIP() {
	pip1.state = false;
	pip1.flow = 0.0;
	pip1.step = STEP;
	
	pip2.state = false;
	pip2.flow = 0.0;
	pip2.step = STEP;

	pip3.state = false;
	pip3.flow = 0.0;
	pip3.step = STEP;
}