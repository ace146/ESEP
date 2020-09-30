#ifndef SRC_ENUMS_H_
#define SRC_ENUMS_H_

enum class COLOR
{
	GREEN,
	YELLOW,
	RED,
};

enum class SPEED
{
	SLOW,
	FAST,
};

enum class Component
{
	NULL_COMPONENT,
	MAIN,
	HAL,
	SERIAL,
	REMOTE,
	DISPATCHER,
	LAMP,
};

enum class Signal
{
	NULL_SIGNAL,

	SIGNAL_A,
	SIGNAL_B,

	GREENLIGHT_ON,
	GREENLIGHT_OFF,

	ACKNOWLEDGED,
};


#endif
