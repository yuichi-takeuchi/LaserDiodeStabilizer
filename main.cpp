#include "mbed.h"
#include <cmath>
////////////////////////////////////////////////////////////////////////////////////////////
// This code is for feedback voltage control with a microcomputer, STM32L152RE.
// Latest version is available at Github (https://github.com/yuichi-takeuchi/LaserDiodeStabilizer).
//
//
// Author:
// Yuichi Takeuchi PhD
// Department of Physiology, University of Szeged, Hungary
// Email: yuichi-takeuchi@umin.net
// 
// Lisence:
// MIT License
////////////////////////////////////////////////////////////////////////////////////////////

Ticker toggle_led_ticker; // led timer
Ticker toggle_readandwrite_ticker; // sampling timer
AnalogIn analog_value1(PA_0);	// (A0: Arduino, PA_0: Morpho)
AnalogIn analog_value2(PA_1);	// (A1: Arduino, PA_1: Morpho)
AnalogOut my_output1(PA_4);	//	(A2: Arduino, PA_4: Morpho)
AnalogOut my_output2(PA_5);	//	(D13: Arduion, PA_5: Morpho)
DigitalOut myled(PC_3);	// (Morpho)
InterruptIn callback(USER_BUTTON); // (PC13: Morpho)

int RANGE = 65535; // 16 bit DAC in software though it is 12 bit DAC
int CYCLE = 200; // in microsecond: 5 kHz
float VRANGE = 3.3;
int TWO = 2;
int ZERO = 0;
float BUFFER = 0.25; // 0-1
//int PMPDGAIN = 240; // PD1: 440 * 60 / 110
float PMPDGAIN = 16.5; // PD2 16
int CMDGAIN = 50; // 50 mA/V
float SLOPE = 1.252; // PL450B-1: mW/mA
int THRESHOLD = 35; // mA
float THETARATIO = 1; // 0-1
/*
p-wave:
(0 + 90*n) = 1
(15 + 90*n) = 0.75
(30 + 90*n) = 0.25
(45 + 90*n) = 0.0001
(60 + 90*n) = 0.25
(75 + 90*n) = 0.75
s-wave:
(0 + 90*n) = 0.0001
(15 + 90*n) = 0.25
(30 + 90*n) = 0.75
(45 + 90*n) = 1
(60 + 90*n) = 0.75
(75 + 90*n) = 0.25
*/

bool status = true;

void toggle_led() {
	myled = !myled;
}

// read and write function
float Vcmd, Vpd, Vnp, Vnn, diff;
void toggle_readandwrite(){

	Vcmd = VRANGE * analog_value1.read(); // (volt)
	Vpd = VRANGE * analog_value2.read(); // (volt)
	if ((TWO * Vcmd * CMDGAIN - THRESHOLD) > ZERO){
		diff = TWO * Vcmd - (((Vpd * PMPDGAIN / (SLOPE * THETARATIO)) + THRESHOLD) / CMDGAIN);
	}
	else{
		diff = ZERO;
	}

	if (diff > ZERO){
		Vnp = BUFFER * fabs(diff * RANGE / VRANGE);
		Vnn = ZERO;
	}
	else{
		Vnp = ZERO;
		Vnn = BUFFER * fabs(diff * RANGE / VRANGE) / TWO; // output range of DAC1 equal 0-1.65 V
	}

	my_output1.write_u16(Vnp);
	my_output2.write_u16(Vnn);
}

// button control
void pressed(){
	status = !status;

	if (status){
		// rean and write cycle on
		toggle_readandwrite_ticker.attach_us(&toggle_readandwrite, CYCLE);

		// led on
		toggle_led_ticker.attach(&toggle_led, 0.1);
	}
	else{
		// read and write cycle off
		toggle_readandwrite_ticker.detach();
		my_output1.write_u16(0);
		my_output2.write_u16(0);

		// led off
		toggle_led_ticker.detach();
		myled = 0;
	}
}

int main() {
	// set button
	callback.fall(&pressed);

	while (1) {
	}
}