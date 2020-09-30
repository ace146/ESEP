#ifdef __DUMMY_TEST
#include "Test/DummyHAL.h"
#else
#include "HAL.h"
#endif

#include <thread>
#include <iostream>
#include "enums.h"
#include "LampControl.h"
#include "Channel.h"
#include "Logger.h"

LampControl::LampControl(Channel& lamp2disp, Channel& disp2lamp)
: _2disp(lamp2disp),
  _2me(disp2lamp),
  _isGreenBlinking(false),
  _isYellowBlinking(false),
  _isRedBlinking(false),
  _delay(1000)

{
	_thread = std::thread(&LampControl::blinkingLoop, this);
}

LampControl::~LampControl()
{
	_thread.join();
}

void LampControl::blinkingLoop()
{
	while(true)
	{
		if(_isGreenBlinking){LampControl::lampOn(COLOR::GREEN);}
		if(_isYellowBlinking){LampControl::lampOn(COLOR::YELLOW);}
		if(_isRedBlinking){LampControl::lampOn(COLOR::RED);}
		std::this_thread::sleep_for(std::chrono::milliseconds(_delay));
		if(_isGreenBlinking){LampControl::lampOff(COLOR::GREEN);}
		if(_isYellowBlinking){LampControl::lampOff(COLOR::YELLOW);}
		if(_isRedBlinking){LampControl::lampOff(COLOR::RED);}
		std::this_thread::sleep_for(std::chrono::milliseconds(_delay));
	}
}

void LampControl::operator ()()
{
	while(true)
	{
		Message rcvMsg = _2me.dequeue();
		LOG_WRITE("Lampe hat message bekommmen");
		switch(rcvMsg.signal)
		{
		case Signal::GREENLIGHT_ON:
			LOG_WRITE("um Lampe einzuschalten");
			lampOn(COLOR::GREEN);
			LOG_WRITE("Lampe wurde eingeschaltet. Lampe sendet ACK...");
			_2disp.enqueue(*(new Message(Signal::ACKNOWLEDGED, rcvMsg.src, Component::LAMP)));
			break;
		case Signal::GREENLIGHT_OFF:
			LOG_WRITE("um Lampe auszuschalten");
			lampOff(COLOR::GREEN);
			LOG_WRITE("Lampe wurde ausgeschaltet. Lampe sendet ACK...");
			_2disp.enqueue(*(new Message(Signal::ACKNOWLEDGED, rcvMsg.src, Component::LAMP)));
			break;
		default:
			LOG_WRITE("Cryptic Signal in Layer 8 detected");
			break;
		}
	}
}

void LampControl::lampOn(COLOR c)
{
	switch(c)
	{
	case COLOR::GREEN:
		HALINSTANCE.greenLightOn();
		break;
	case COLOR::YELLOW:
		HALINSTANCE.yellowLightOn();
		break;
	case COLOR::RED:
		HALINSTANCE.redLightOn();
		break;
	}
}

void LampControl::lampOff(COLOR c)
{
	switch(c)
	{
	case COLOR::GREEN:
		HALINSTANCE.greenLightOff();
		break;
	case COLOR::YELLOW:
		HALINSTANCE.yellowLightOff();
		break;
	case COLOR::RED:
		HALINSTANCE.redLightOff();
		break;
	}
}

void LampControl::lampBlinking(COLOR c, SPEED s)
{
	if(s == SPEED::FAST)
	{
		_delay = 1000;
	}
	else // s == SLOW
	{
		_delay = 2000;
	}

	switch(c)
	{
	case COLOR::GREEN:
		_isGreenBlinking = true;
		break;
	case COLOR::YELLOW:
		_isYellowBlinking = true;
		break;
	case COLOR::RED:
		_isRedBlinking = true;
		break;
	}
}
