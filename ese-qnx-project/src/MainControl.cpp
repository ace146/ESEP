#include "MainControl.h"

#ifdef __DUMMY_TEST
#include "Test/DummyHAL.h"
#else
#include "HAL.h"
#endif

#include <iostream>
#include "enums.h"
#include "Logger.h"

using namespace std;

//		this_thread::sleep_for(chrono::milliseconds(5000));

MainControl::MainControl(Channel& main2disp, Channel& disp2main)
: _2disp(main2disp),
  _2me(disp2main)
{

}

void MainControl::operator()()
{
	LOG_WRITE("Nachricht Lampe An versenden");
	_2disp.enqueue(*(new Message(Signal::GREENLIGHT_ON, Component::LAMP, Component::MAIN)));
	LOG_WRITE("Main wartet auf ACK");
	Message rcvMsg = _2me.dequeue();
	if(rcvMsg.signal == Signal::ACKNOWLEDGED && rcvMsg.src == Component::LAMP)
	{
		LOG_WRITE("ACK ist da, Lampe an");
	}

	LOG_WRITE("5 Sekunden warten");
	this_thread::sleep_for(chrono::milliseconds(5000));

	LOG_WRITE("Nachricht Lampe Aus versenden");
	_2disp.enqueue(*(new Message(Signal::GREENLIGHT_OFF, Component::LAMP, Component::MAIN)));
	LOG_WRITE("Main wartet auf ACK");
	rcvMsg = _2me.dequeue();
	if(rcvMsg.signal == Signal::ACKNOWLEDGED && rcvMsg.src == Component::LAMP)
	{
		LOG_WRITE("ACK ist da, Lampe aus");
	}
}

MainControl::~MainControl()
{
	//NULL;
}

