#ifndef SRC_LAMPCONTROL_H_
#define SRC_LAMPCONTROL_H_

#include "enums.h"
#include <thread>
#include "Channel.h"

class LampControl
{
public:
	explicit LampControl(Channel& lamp2disp, Channel& disp2lamp);
	virtual ~LampControl();
	void operator()();
	void lampOn(COLOR c);
	void lampOff(COLOR c);
	void lampBlinking(COLOR c, SPEED s);

	std::thread _thread;
private:
	void blinkingLoop();

	int _delay;

	bool _isGreenBlinking;
	bool _isYellowBlinking;
	bool _isRedBlinking;

	Channel& _2disp;
	Channel& _2me;
};

#endif
