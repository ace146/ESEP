#include "Dispatcher.h"
#include <iostream>
#include "enums.h"
#include "Logger.h"

Dispatcher::Dispatcher(Channel& disp2lamp, Channel& disp2main, Channel& toDisp)
: _2lamp(disp2lamp),
  _2main(disp2main),
  _2me(toDisp)
{

}

void Dispatcher::operator ()()
{
	while(true)
	{
		Message rcvMsg = _2me.dequeue();
		LOG_WRITE("Dispatcher hat Message bekommen");
		switch(rcvMsg.dest)
		{
		case Component::MAIN:
			LOG_WRITE("Message ist für Main. Dispatcher leitet weiter...");
			_2main.enqueue(rcvMsg);
			break;
		case Component::LAMP:
			LOG_WRITE("Message ist für Lamp. Dispatcher leitet weiter...");
			_2lamp.enqueue(rcvMsg);
			break;
		default:
			LOG_WRITE("Wrong Signal detected");
			break;
		}
	}
}

Dispatcher::~Dispatcher()
{

}

