
void addControlTask() {
	if (conPIP1.needControl==1) {
		Serial.println("add task controlPIP1");
		ts.addTask(tConPIP1);
		tConPIP1.setTimeout(60 * CLOCK_SECOND);
		tConPIP1.enable();
		
	}
	if (conPIP2.needControl==1) {
		Serial.println("add task controlPIP2");
		ts.addTask(tConPIP2);
		tConPIP2.setTimeout(60 * CLOCK_SECOND);
		tConPIP2.enableDelayed(1345);
	}
	if (conPIP3.needControl==1) {
		Serial.println("add task controlPIP3");
		ts.addTask(tConPIP3);
		tConPIP3.setTimeout(60 * CLOCK_SECOND);
		tConPIP3.enableDelayed(1983);
	}
}

int startControl() {
	//	//TODO-- Ŀǰ��һ��һ������д���Ժ���Ա������ݣ�ʵ��һ�������㶨
	addControlTask();
	Serial.println("begin running......waiting return.....");
	FLAG_jobStatus = JOB_UNFINISH;
	ts.addTask(tStatus);
	tStatus.setTimeout(60 * CLOCK_SECOND);
	tStatus.enable();	
}

