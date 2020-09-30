#include "Channel.h"

#ifndef SRC_DISPATCHER_H_
#define SRC_DISPATCHER_H_

class Dispatcher
{
public:
	explicit Dispatcher(Channel& disp2lamp, Channel& disp2main, Channel& toDisp);
	void operator()();
	virtual ~Dispatcher();

	Channel& _2lamp;
	Channel& _2main;
	Channel& _2me;

};

#endif
