//#include "include\mulpip.h"


bool FLAG_tDisplay = true;
bool FLAG_tWiFi = false;


bool justRun=false;
void MyDisplay() {
	if(tDisplay.isFirstIteration())
		Serial.println("Run MyDisplay");
	if (disInfo._1_finish == PIP_NOTRUNNING && disInfo._2_finish == PIP_NOTRUNNING && disInfo._3_finish == PIP_NOTRUNNING) {
		if (WIFISTATE.isConnected) {
			drawCon();
		}
		else
		{
			drawLogo();
		}
		
	}
	else if (FLAG_jobStatus == JOB_FINISH && justRun) {
		drawFinish(true);
		delay(1000);
		drawState();
		tDisplay.delay(3000);
		justRun = false;
		//initConInfo();
	}
	else if (FLAG_jobStatus == JOB_UNFINISH && justRun ) {
		drawFinish(false);
		tDisplay.delay(3000);
		justRun = false;
		//initConInfo();
	}
	else if (FLAG_jobStatus == JOB_RUNNING) {
		justRun = true;
		//showSerial();
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
		tStatus.disable();
	}
	else if (conPIP1.finish == PIP_UNFINISH || conPIP2.finish == PIP_UNFINISH || conPIP3.finish == PIP_UNFINISH) {
		FLAG_jobStatus = JOB_UNFINISH;
		disableControlTask();
		tStatus.disable();
	}
	getDisInfo();
}

void disableMyStatus() {
	initConInfo();
	if (tStatus.timedOut()) {
		FLAG_jobStatus = JOB_UNFINISH;
		Serial.println("startControl timeout:....");
	}
	if (FLAG_jobStatus == JOB_UNFINISH) {
		Serial.println("startControl unfinish:....");
		sendData(JOB_UNFINISH);
	}
	else if (FLAG_jobStatus == JOB_FINISH) {
		sendData(JOB_FINISH);
		Serial.println("startControl finish:....");
	}
	WIFISTATE.isAllowSend = SEND_ALLOWED;	//允许发送数据

}

void PIP1() {
	simulatePIP(tPIP1.isFirstIteration(), &pip1);
	/*if (tPIP1.isFirstIteration()) {
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
	}*/

}
void PIP2() {	
	simulatePIP(tPIP2.isFirstIteration(), &pip2);
}
void PIP3() {	
	simulatePIP(tPIP3.isFirstIteration(), &pip3);
}


void controlPIP1() {
	if (tConPIP1.isFirstIteration()) {
		Serial.println("begin running controlPIP1");
		openPIP(&pip1,&conPIP1);
		/*pip1.state = true;
		conPIP1.finish = PIP_RUNNING;*/
	}
	//---------------以下为实际管道时启用-------------------------
	//getPIP1_Flow();
	//if (conPIP1.target <= conPIP1.nowflow) {
	//	tConPIP1.disable();
	//}
	//---------------以下为模拟管道时启用-------------------------
	if (shouldFinish(&pip1, &conPIP1)) {
		tConPIP1.disable();
	}
	//conPIP1.nowflow = pip1.flow;
	//
	//if (conPIP1.target <= conPIP1.nowflow) {
	//	
	//	tConPIP1.disable();
	//}else if ((conPIP1.target - conPIP1.nowflow)<=STEP * 2) {
	//	pip1.step = 0.1;
	//}
}

//机器控制完成，或者超时
void FinishPIP1() {
	
	closePIP(&pip1,&conPIP1, tConPIP1.timedOut());
	//pip1.state = false;
	//if (tConPIP1.timedOut()) {
	//	conPIP1.finish = PIP_UNFINISH;
	//	Serial.println("run controlPIP1 timeout");
	//}
	//else {
	//	conPIP1.finish = PIP_FINISH;
	//	Serial.println("finish controlPIP1");
	//}
	//pip1.step = STEP;
	////ts.deleteTask(tConPIP1);
	////Serial.println("delete task controlPIP1");
}

void controlPIP2() {
	if (tConPIP2.isFirstIteration()) {
		Serial.println("begin running controlPIP2");
		openPIP(&pip2, &conPIP2);
	}
	//---------------以下为实际管道时启用-------------------------
	//getPIP2_Flow();
	//if (conPIP2.target <= conPIP2.nowflow) {
	//	tConPIP2.disable();
	//}
	//---------------以下为模拟管道时启用-------------------------
	if (shouldFinish(&pip2, &conPIP2)) {
		tConPIP2.disable();
	}
}

//机器控制完成，或者超时
void FinishPIP2() {
	
	closePIP(&pip2, &conPIP2, tConPIP2.timedOut());
}

void controlPIP3() {
	if (tConPIP3.isFirstIteration()) {
		conPIP3.finish = PIP_RUNNING;
		openPIP(&pip3, &conPIP3);
	}
	//---------------以下为实际管道时启用-------------------------
	//getPIP3_Flow();
	//if (conPIP3.target <= conPIP3.nowflow) {
	//	tConPIP3.disable();
	//}
	//---------------以下为模拟管道时启用-------------------------
	if (shouldFinish(&pip3, &conPIP3)) {
		tConPIP3.disable();
	}
}

//机器控制完成，或者超时
void FinishPIP3() {
	closePIP(&pip3, &conPIP3, tConPIP3.timedOut());
}