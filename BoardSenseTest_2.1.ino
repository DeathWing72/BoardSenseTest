//Version 2.1 - Updated 10/26/2018
//Copyright 2019, Tyler Jones, All Rights Reserved

const int buttonPin=2; //blue wires
const int ledPin=3; //green wires
const int pwmPin=9;
const int polarityPin1=10;
const int polarityPin2=11;
const int switchPin=12; //orange wires
boolean polState1 = false;
boolean polState2 = false;
int senseTests = 10;
void setup(){
	pinMode(buttonPin,INPUT_PULLUP);
	pinMode(polarityPin1,OUTPUT);
	pinMode(polarityPin2,OUTPUT);
	pinMode(switchPin,INPUT_PULLUP);
	Serial.begin(9600);
	digitalWrite(polarityPin1,LOW);
	digitalWrite(polarityPin2,LOW);
	analogWrite(pwmPin,0);
	analogWrite(ledPin,0);
	String initStr1 = "Press the button to initiate ";
	String initStr2 = " sensor tests.";
	Serial.println(initStr1+senseTests+initStr2);
}
int sensorTest(){
	analogWrite(ledPin,255);
	for(int x=0;x<=255;x++){
		if(polState1 && !polState2){
			digitalWrite(polarityPin1,LOW);
			polState1=false;
			digitalWrite(polarityPin2,HIGH);
			polState2=true;
		}
		else{
			digitalWrite(polarityPin1,HIGH);
			polState1=true;
			digitalWrite(polarityPin2,LOW);
			polState2=false;
		}
		analogWrite(pwmPin,x);
		delay(4);
		if(digitalRead(switchPin)==LOW){
			return x;
			break;
		}
	}
}
void loop(){
	if(digitalRead(buttonPin)==HIGH){
		Serial.write(27);
		Serial.print("[2J");
		Serial.write(27);
		Serial.print("[H");
		int total = 0;
		for(int x=1;x<=senseTests;x++){
			int tmpTestVal = sensorTest();
			total += tmpTestVal;
			String testStr1 = "Sensor Test ";
			String testStr2 = ": ";
			Serial.println(testStr1+x+testStr2+tmpTestVal);
		}
		String avgStr = "Average: ";
		Serial.println(avgStr+(total/senseTests));
	}
	analogWrite(pwmPin,0);
	analogWrite(ledPin,0);
	digitalWrite(polarityPin1,LOW);
	polState1=false;
	digitalWrite(polarityPin2,LOW);
	polState2=false;
	delay(25);
}