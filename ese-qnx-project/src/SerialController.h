#ifndef __DUMMY_TEST

#ifndef SRC_SERIALCONTROLLER_H_
#define SRC_SERIALCONTROLLER_H_

#include "Serial.h"
#include "Message.h"
#include <memory>

#include "Channel.h"

/**
 * @brief Controller for SerialReader and SerialWriter
 */
class SerialController {
public:
	/**
	 * @brief Constructor for SerialController
	 *
	 * @param channel Channel for communication
	 * @param serial Serial connection to use
	 */
	explicit SerialController(Channel& channel);

	/**
	 * @brief Destructor for SerialController
	 */
	virtual ~SerialController();

	/**
	 * @brief overload () operator
	 */
	void operator()();
	volatile bool isRunning{true};		/// Running status flag
private:
	Channel& dispatcherChannel;				/// Channel for communication
};

#endif /* SRC_SERIALCONTROLLER_H_ */
#endif
