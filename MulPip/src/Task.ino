//#include "include\mulpip.h"


bool FLAG_tDisplay = true;
bool FLAG_tWiFi = false;


int last=0;
void MyDisplay() {
	if(tDisplay.isFirstIteration())
		Serial.println("Run MyDisplay");
	if (conPIP1.finish == PIP_NOTRUNNING && conPIP2.finish == PIP_NOTRUNNING && conPIP3.finish == PIP_NOTRUNNING) {
		if (WIFISTATE.isConnected) {
			drawCon();
		}
		else
		{
			drawLogo();
		}
		
	}
	else if (FLAG_jobStatus == JOB_FINISH && last == 1) {
		drawFinish(true);
		delay(1000);
		drawState();
		tDisplay.delay(3000);
		last = 0;
		initConInfo();
	}
	else if (FLAG_jobStatus == JOB_UNFINISH && last == 1) {
		drawFinish(false);
		tDisplay.delay(3000);
		last = 0;
		initConInfo();
	}
	else if (FLAG_jobStatus == JOB_RUNNING) {
		last = 1;
		showSerial();
		drawState();
	}
	
}

void MyWiFi() {
	if (tWiFi.isFirstIteration()) {
		FLAG_tWiFi = true;
	}
	//Serial.print("run MyWiFi...WIFISTATE.isAllowSend: ");
	//Serial.println(WIFISTATE.isAllowSend);
	if (WIFISTATE.isOpen) {
		if (FLAG_tWiFi  && WIFISTATE.isAllowSend == SEND_ALLOWED) {
			FLAG_tWiFi = false;
			//Serial.println("recv WiFi data");
			if (Serial1.available() > 2) {
				//Serial.println("has Data:....");
				//initConInfo();
				if (recvWifiData() == START) {
					WIFISTATE.isAllowSend = SEND_REJECT;	//设置不允许继续发送数据
					
					startControl();

				}
			}
			FLAG_tWiFi = true;
		}
		else {
		//	Serial.println("no connection");
		}
	}
	else {
		//Serial.println("WiFi open failed, try to restart wifi...");
		WIFISTATE.isOpen = init_WIFI();
		tWiFi.enableDelayed(1000);
		//delay(2000);
		tWiFi.delay(2000);
	}
}

void MyStatus() {
	if (tStatus.isFirstIteration()) {
		Serial.println("run MyStatus");
	}
	//Serial.println("run MyStatus");
	if (conPIP1.finish == PIP_FINISH && conPIP2.finish == PIP_FINISH && conPIP3.finish == PIP_FINISH) {
		Serial.println("JOB_FINISH");
		FLAG_jobStatus = JOB_FINISH;
		disableControlTask();
		//
		tStatus.disable();
	}
	else if (conPIP1.finish == PIP_UNFINISH || conPIP2.finish == PIP_UNFINISH || conPIP3.finish == PIP_UNFINISH) {
		FLAG_jobStatus = JOB_UNFINISH;
		disableControlTask();
		//ts.deleteTask(tStatus);
		tStatus.disable();
	}
}

void disableMyStatus() {
	if (tStatus.timedOut()) {
		FLAG_jobStatus = JOB_UNFINISH;
		Serial.println("startControl timeout:....");
	}
	/*pip1.state = false;
	pip2.state = false;
	pip3.state = false;*/
	if (FLAG_jobStatus == JOB_UNFINISH) {
		Serial.println("startControl unfinish:....");
		sendData(JOB_UNFINISH);
	}
	else if (FLAG_jobStatus == JOB_FINISH) {
		sendData(JOB_FINISH);
		Serial.println("startControl finish:....");
	}
	WIFISTATE.isAllowSend = SEND_ALLOWED;	//允许发送数据
	//ts.deleteTask(tStatus);
}

void PIP1() {
	
	if (tPIP1.isFirstIteration()) {
		Serial.println("run PIP1....");
		pip1.state = false;
		pip1.flow = 0.0;
		pip1.step = STEP;
	}
	
	if (pip1.state) {
		
		pip1.flow += pip1.step;
	}
	else {
		pip1.flow = 0.0;
	}

}
void PIP2() {
	
	if (tPIP2.isFirstIteration()) {
		Serial.println("run PIP2....");
		pip2.state = false;
		pip2.flow = 0.0;
		pip2.step = STEP;
	}

	if (pip2.state) {

		pip2.flow += pip2.step;
	}
	else {
		pip2.flow = 0.0;
	}
}
void PIP3() {
	
	if (tPIP3.isFirstIteration()) {
		Serial.println("run PIP3....");
		pip3.state = false;
		pip3.flow = 0.0;
		pip3.step = STEP;
	}

	if (pip3.state) {

		pip3.flow += pip3.step;
	}
	else {
		pip3.flow = 0.0;
	}
}


void controlPIP1() {
	if (tConPIP1.isFirstIteration()) {
		Serial.println("begin running controlPIP1");
		pip1.state = true;
		conPIP1.finish = PIP_RUNNING;
	}
	//Serial.println("running controlPIP1");
	conPIP1.nowflow = pip1.flow;
	
	if (conPIP1.target <= conPIP1.nowflow) {
		
		tConPIP1.disable();
	}else if ((conPIP1.target - conPIP1.nowflow)<=STEP * 2) {
		pip1.step = 0.1;
	}
}

//机器控制完成，或者超时
void FinishPIP1() {
	
	pip1.state = false;
	if (tConPIP1.timedOut()) {
		conPIP1.finish = PIP_UNFINISH;
		Serial.println("run controlPIP1 timeout");
	}
	else {
		conPIP1.finish = PIP_FINISH;
		Serial.println("finish controlPIP1");
	}
	pip1.step = STEP;
	//ts.deleteTask(tConPIP1);
	//Serial.println("delete task controlPIP1");
}

void controlPIP2() {
	if (tConPIP2.isFirstIteration()) {
		Serial.println("begin running controlPIP2");
		pip2.state = true;
		conPIP2.finish = PIP_RUNNING;
	}
	//Serial.println("running controlPIP2");
	conPIP2.nowflow = pip2.flow;
	if (conPIP2.target <= conPIP2.nowflow) {
		
		tConPIP2.disable();
	}
	else if ((conPIP2.target - conPIP2.nowflow) <= STEP * 2) {
		pip2.step = 0.1;
	}
}

//机器控制完成，或者超时
void FinishPIP2() {
	
	pip2.state = false;
	if (tConPIP2.timedOut()) {
		conPIP2.finish = PIP_UNFINISH;
		Serial.println("controlPIP2 timeout");
	}
	else {
		conPIP2.finish = PIP_FINISH;
		Serial.println("finish controlPIP2");
	}
	pip2.step = STEP;
	//ts.deleteTask(tConPIP2);
	//Serial.println("delete task controlPIP2");
}

void controlPIP3() {
	if (tConPIP3.isFirstIteration()) {
		conPIP3.finish = PIP_RUNNING;
		pip3.state = true;
		Serial.println("begin running controlPIP3");
	}
	//Serial.println("running controlPIP3");
	conPIP3.nowflow = pip3.flow;
	if (conPIP3.target <= conPIP3.nowflow) {
		
		tConPIP3.disable();
	}
	else if ((conPIP3.target - conPIP3.nowflow) <= STEP * 2) {
		pip3.step = 0.1;
	}
}


//机器控制完成，或者超时
void FinishPIP3() {
	
	pip3.state = false;
	if (tConPIP3.timedOut()) {
		conPIP3.finish = PIP_UNFINISH;
		Serial.println("controlPIP3 timeout");
	}
	else {
		conPIP3.finish = PIP_FINISH;
		Serial.println("finish controlPIP3");
	}
	pip3.step = STEP;
	//ts.deleteTask(tConPIP3);
	//Serial.println("delete task controlPIP3");
}