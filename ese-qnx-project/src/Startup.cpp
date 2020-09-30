/**
 * The main Startup-Class. All Controller threads, etc. are invoked here.
 * @author Adem-Can Agdas, Paul Mathia
 */
#ifndef __ACTUATOR_TEST

#ifdef __DUMMY_TEST
#include "Test/DummyHAL.h"
#else
#include "HAL.h"
#endif

#include <iostream>
#include <thread>
#include <chrono>
#include "MainControl.h"
#include "LampControl.h"
#include "Dispatcher.h"
#include "Channel.h"
#include "Message.h"
#include "enums.h"
#include "Logger.h"

int main()
{
	LOG_ENABLE_CONSOLE_OUTPUT
	LOG_WRITE("TRANSMISSION STARTS HERE");
	LOG_WRITE("--------------------------------------------------------------------------------------------");
	LOG_WRITE("--------------------------------------------------------------------------------------------");
	LOG_WRITE("--------------------------------------------------------------------------------------------");

	Channel disp2main(5);
	Channel disp2lamp(5);
	Channel omniChannel(30);

	LOG_WRITE("Erstelle und starte Threads.");

	MainControl mc(omniChannel, disp2main);
	LampControl lc(omniChannel, disp2lamp);
	Dispatcher dc(disp2lamp, disp2main, omniChannel);

	std::thread mct(std::ref(mc));
	std::thread dct(std::ref(dc));
	std::thread lct(std::ref(lc));

	mct.join();
	dct.join();
	lct.join();
}
#endif
