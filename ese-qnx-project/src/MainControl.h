#ifndef MAINCONTROL_H_
#define MAINCONTROL_H_

#include "Channel.h"

class MainControl
{
public:
	explicit MainControl(Channel& main2disp, Channel& disp2main);
	void operator()();
	virtual ~MainControl();

	Channel& _2disp;
	Channel& _2me;
};

#endif
