#ifdef __SERIAL_TEST
#include "../Message.h"
#include "../enums.h"
#include "../Channel.h"
#include "../SerialController.h"
#include <memory>
#include <thread>
#include <iostream>

using namespace std;
using namespace std::string_literals;

class SerialTest {
	SerialTest() {
		Channel sc_channel(3);
		SerialController sc(sc_channel);
		thread sc_thread(ref(sc));

		auto sent = make_unique < Message > (Signal::SIGNAL_B, Component::HAL);
		cout << "SENT:" << endl;
		cout
				<< "Signal: "s + to_string(static_cast<int>(sent->signal))
						+ "; Destination: "
						+ to_string(static_cast<int>(sent->dest)) << endl;
		sc_channel.enqueue(*sent);

		auto received = make_unique < Message > (sc_channel.dequeue());
		cout << "RECEIVED:" << endl;
		cout
				<< "Signal: "s + to_string(static_cast<int>(received->signal))
						+ "; Destination: "
						+ to_string(static_cast<int>(received->dest)) << endl;

		sc.isRunning = false;
		sc_thread.join();
	}

	~SerialTest() {
		// TODO Auto-generated destructor stub
	}

};

#endif /* __SERIAL_TEST */
