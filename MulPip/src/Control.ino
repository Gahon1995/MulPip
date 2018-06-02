
void addControlTask() {
	if (conPIP1.needControl==1) {
		Serial.println("add task controlPIP1");
		ts.addTask(tConPIP1);
		tConPIP1.setTimeout(60 * TASK_SECOND);
		tConPIP1.restart();

		
	}
	if (conPIP2.needControl==1) {
		Serial.println("add task controlPIP2");
		ts.addTask(tConPIP2);
		tConPIP2.setTimeout(60 * TASK_SECOND);
		tConPIP2.restartDelayed(345);
	}
	if (conPIP3.needControl==1) {
		Serial.println("add task controlPIP3");
		ts.addTask(tConPIP3);
		tConPIP3.setTimeout(60 * TASK_SECOND);
		tConPIP3.restartDelayed(983);
	}
}

void disableControlTask() {
	if (tConPIP1.isEnabled()) {
		tConPIP1.disable();
	}
	if (tConPIP2.isEnabled()) {
		tConPIP2.disable();
	}
	if (tConPIP3.isEnabled()) {		
		tConPIP3.disable();
	}
	
}
int startControl() {
	//	//TODO-- 目前是一个一个处理，写完以后可以变量传递，实现一个函数搞定
	addControlTask();
	Serial.println("begin running......");
	FLAG_jobStatus = JOB_RUNNING;
	ts.addTask(tStatus);
	Serial.println("");
	tStatus.setTimeout(60 * TASK_SECOND);	
	tStatus.restart();	
	Serial.println("waiting return.....");
}

void openPIP(volatile PIPCONFIG * pip, volatile CONINFO * controlPIP) {
	pip->state = true;
	
	controlPIP->finish = PIP_RUNNING;
}

void closePIP(volatile PIPCONFIG * pip, volatile CONINFO * controlPIP,bool timeout) {
	pip->state = false;
	if (timeout) {
		controlPIP->finish = PIP_UNFINISH;
		Serial.println("run controlPIP timeout");
	}
	else {
		controlPIP->finish = PIP_FINISH;
		Serial.println("finish controlPIP1");
	}
	pip->step = STEP;
}
bool shouldFinish(volatile PIPCONFIG * pip, volatile CONINFO * controlPIP) {
	controlPIP->nowflow = pip->flow;
	if ((controlPIP->target - controlPIP->nowflow) <= STEP * 2) {
		pip->step = 0.1;
	}
	if (controlPIP->target <= controlPIP->nowflow) {
		return true;
	}
	else {
		return false;
	}
}

void simulatePIP(bool isFirst, volatile PIPCONFIG *pip) {
	if (isFirst) {
		Serial.println("init PIP....");
		pip->state = false;
		pip->flow = 0.0;
		pip->step = STEP;
	}

	if (pip->state) {

		pip->flow += pip->step;
	}
	else {
		pip->flow = 0.0;
	}
}