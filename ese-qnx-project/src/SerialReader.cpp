#ifndef __DUMMY_TEST
#include "SerialReader.h"

#include <cstring> // for std::strerror
#include <cerrno> // for errno

SerialReader::SerialReader(Channel& channel, Serial& serial) : channel_(channel), serial_(serial) {}

void SerialReader::operator()(){
	while(isRunning){
		int res = serial_.recv(buffer_, sizeof(Message));
		if (res != sizeof(Message)) {
			throw std::logic_error("The length of receive Messages smaller than sizeof(Message)");
		}
		auto msg = std::make_unique<Message>(static_cast<Message>(buffer_));
		channel_.enqueue(*msg);
	}
}

SerialReader::~SerialReader() {

}
#endif
