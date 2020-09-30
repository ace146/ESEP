#ifndef __DUMMY_TEST

#include "SerialWriter.h"

#include <cstring> // for std::strerror
#include <cerrno> // for errno
#include <memory>

SerialWriter::SerialWriter(Channel& channel, Serial& serial) : channel_(channel), serial_(serial), isRunning{true} {}

void SerialWriter::operator()(){
	while(isRunning){
		/* wait for message from SerialController */
		auto msg = std::make_unique<Message>(channel_.dequeue());

		memcpy(buffer_,(const void*) msg.get(), sizeof(Message));
		int res = serial_.send(buffer_, sizeof(Message));
		if (res != sizeof(Message)) {
			throw std::logic_error("The length of sent Messages smaller than sizeof(Message)");
		}
	}
}

SerialWriter::~SerialWriter() {
	// TODO Auto-generated destructor stub
}

#endif
