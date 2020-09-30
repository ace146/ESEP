/*
 * @author Ömer Kirdas, Adem-Can Agdas
 * @version 0.2
 */
#ifdef __ACTUATOR_TEST

#include "HALTest.h"
#include "../HAL.h"
#include <iostream>
#include <chrono>

/*
 *
 */
int main(){
	HALINSTANCE.motorRight();
	this_thread::sleep_for(chrono::milliseconds(5000));

	HALINSTANCE.motorSlow();
	this_thread::sleep_for(chrono::milliseconds(5000));

	HALINSTANCE.motorStop();
	this_thread::sleep_for(chrono::milliseconds(5000));

	HALINSTANCE.motorLeft();
	this_thread::sleep_for(chrono::milliseconds(5000));

	HALINSTANCE.motorFast();
	this_thread::sleep_for(chrono::milliseconds(5000));

	HALINSTANCE.motorStop();
	this_thread::sleep_for(chrono::milliseconds(1000));
	HALINSTANCE.gateOpen();
	this_thread::sleep_for(chrono::milliseconds(2000));

	HALINSTANCE.gateClose();
	this_thread::sleep_for(chrono::milliseconds(1000));

	HALINSTANCE.redLightOn();
	this_thread::sleep_for(chrono::milliseconds(3000));

	HALINSTANCE.redLightOff();
	HALINSTANCE.yellowLightOn();
	this_thread::sleep_for(chrono::milliseconds(3000));

	HALINSTANCE.yellowLightOff();
	HALINSTANCE.greenLightOn();
	this_thread::sleep_for(chrono::milliseconds(3000));

	HALINSTANCE.greenLightOff();
	this_thread::sleep_for(chrono::milliseconds(2000));

	HALINSTANCE.greenLightOn();
	HALINSTANCE.redLightOn();
	HALINSTANCE.yellowLightOn();
	this_thread::sleep_for(chrono::milliseconds(3000));

	HALINSTANCE.greenLightOff();
	HALINSTANCE.redLightOff();
	HALINSTANCE.yellowLightOff();
}

#endif
