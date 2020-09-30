#ifndef __DUMMY_TEST
#include "SerialController.h"
#include "SerialReader.h"
#include "SerialWriter.h"
#include "Serial.h"
#include <cstddef>
#include <iostream>
#include <thread>

#include "Channel.h"

using namespace std;

SerialController::SerialController(Channel& channel)
: dispatcherChannel(channel),
  isRunning{true} {}

void SerialController::operator()(){
//	Serial serial("/dev/ser4");
	Serial serial("/dev/ser1");		// use this if VM

	/* create channel, pass it to reader/writer
	 * and run reader/writer in thread
	 */
	Channel readChannel(3);
	SerialReader reader(readChannel, serial);
	thread readerThread(ref(reader));

	Channel writeChannel(3);
	SerialWriter writer(writeChannel, serial);
	thread writerThread(ref(writer));

	while(isRunning){
		/* wait for Message from Dispatcher */
		auto toWrite = std::make_unique<Message>(dispatcherChannel.dequeue());

		/* Send to SerialWriter */
		writeChannel.enqueue(*toWrite);

		/* FIXME: how to listen for read and write simultaneously */

		auto received = std::make_unique<Message>(readChannel.dequeue());
		dispatcherChannel.enqueue(*received);
	}

	writerThread.join();
	readerThread.join();
}

SerialController::~SerialController() {
}
#endif
