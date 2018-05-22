

bool FLAG_tDisplay = true;
bool FLAG_tWiFi = false;



void MyDisplay() {
	if(tDisplay.isFirstIteration())
		Serial.println("Run MyDisplay");
	if (conPIP1.finish == PIP_NOTRUNNING && conPIP2.finish == PIP_NOTRUNNING && conPIP3.finish == PIP_NOTRUNNING) {
		drawLogo();
	}
	else if (FLAG_jobStatus == JOB_UNFINISH) {
		showSerial();
		drawState();
	}
}

void MyWiFi() {
	if (tWiFi.isFirstIteration()) {
		FLAG_tWiFi = true;
	}
	//Serial.print("run MyWiFi...STATUS: ");
	//Serial.println(STATUS);
	if (WIFISTATE.isOpen) {
		if (FLAG_tWiFi && STATUS == SEND_ALLOWED) {
			FLAG_tWiFi = false;
			//Serial.println("recv WiFi data");
			if (Serial1.available() > 2) {
				Serial.println("has Data:....");
				if (recvWifiData() == START) {
					STATUS = SEND_REJECT;	//设置不允许继续发送数据
					startControl();

				}
			}
			FLAG_tWiFi = true;
		}
		else {
			//Serial.println("do not recv WiFi data");
		}
	}
	else {
		//Serial.println("WiFi open failed, try to restart wifi...");
		WIFISTATE.isOpen = init_WIFI();
		tWiFi.enableDelayed(3000);
	}
}

void MyStatus() {
	if (conPIP1.finish == PIP_FINISH && conPIP2.finish == PIP_FINISH && conPIP3.finish == PIP_FINISH) {
		Serial.println("JOB_FINISH");
		FLAG_jobStatus = JOB_FINISH;
		tStatus.disable();
	}
	else if (conPIP1.finish == PIP_UNFINISH || conPIP2.finish == PIP_UNFINISH || conPIP3.finish == PIP_UNFINISH) {
		FLAG_jobStatus = JOB_UNFINISH;
		Serial.print("JOB_UNFINISH:  ");
		Serial.print("  conPIP1:  ");
		Serial.print(conPIP1.finish);
		Serial.print("  conPIP2:  ");
		Serial.print(conPIP2.finish);
		Serial.print("  conPIP3:  ");
		Serial.println(conPIP3.finish);
		tStatus.disable();
	}
}

void disableMyStatus() {
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
	initConInfo();
	STATUS = SEND_ALLOWED;	//允许发送数据
	ts.deleteTask(tStatus);
}

void PIP1() {
	
	if (tPIP1.isFirstIteration()) {
		Serial.println("run PIP1....");
		pip1.state = false;
		pip1.flow = 0.0;
	}
	
	if (pip1.state) {
		
		pip1.flow += 0.1;
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
	}

	if (pip2.state) {

		pip2.flow += 0.1;
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
	}

	if (pip3.state) {

		pip3.flow += 0.1;
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
	conPIP1.nowflow = pip1.flow;
	if (conPIP1.target <= conPIP1.nowflow) {
		pip1.state = false;
		tConPIP1.disable();
	}
}

//机器控制完成，或者超时
void FinishPIP1() {
	
	if (tConPIP1.enableIfNot()) {
		tConPIP1.disable();
	}
	if (tConPIP1.timedOut()) {
		conPIP1.finish = PIP_UNFINISH;
		Serial.println("run controlPIP1 timeout");
	}
	else {
		conPIP1.finish = PIP_FINISH;
		Serial.println("finish controlPIP1");
	}
	ts.deleteTask(tConPIP1);
}

void controlPIP2() {
	if (tConPIP2.isFirstIteration()) {
		Serial.println("begin running controlPIP2");
		pip2.state = true;
		conPIP2.finish = PIP_RUNNING;
	}
	conPIP2.nowflow = pip2.flow;
	if (conPIP2.target <= conPIP2.nowflow) {
		pip2.state = false;
		tConPIP2.disable();
	}
}

//机器控制完成，或者超时
void FinishPIP2() {
	
	if (tConPIP2.enableIfNot()) {
		tConPIP2.disable();
	}
	if (tConPIP2.timedOut()) {
		conPIP2.finish = PIP_UNFINISH;
		Serial.println("controlPIP2 timeout");
	}
	else {
		conPIP2.finish = PIP_FINISH;
		Serial.println("finish controlPIP2");
	}
	ts.deleteTask(tConPIP2);
}

void controlPIP3() {
	if (tConPIP3.isFirstIteration()) {
		conPIP3.finish = PIP_RUNNING;
		pip3.state = true;
		Serial.println("begin running controlPIP3");
	}
	conPIP3.nowflow = pip3.flow;
	if (conPIP3.target <= conPIP3.nowflow) {
		pip3.state = false;
		tConPIP3.disable();
	}
}

//机器控制完成，或者超时
void FinishPIP3() {
	
	if (tConPIP3.enableIfNot()) {
		tConPIP3.disable();
	}
	if (tConPIP3.timedOut()) {
		conPIP3.finish = PIP_UNFINISH;
		Serial.println("controlPIP3 timeout");
	}
	else {
		conPIP3.finish = PIP_FINISH;
		Serial.println("finish controlPIP3");
	}
	ts.deleteTask(tConPIP3);
}