#ifndef SRC_MESSAGE_H_
#define SRC_MESSAGE_H_

#include "enums.h"
#include <cstdint>
#include <cstring>

#ifndef MSG_PAYLOAD_SIZE
#define MSG_PAYLOAD_SIZE	(32)
#endif

struct Message {
	/**
	 * @brief Reconstruct Message from bytes
	 *
	 * @param bytes to reconstruct
	 */
	Message(uint32_t *bytes) {
		/* TODO: test! */
		/* copy sizeof(Message) bytes starting at start address of this message */
		memcpy(this, (const void *)bytes, sizeof(Message));
	}

	/**
	 * @brief Constructor for messages without payload.
	 * 		  Payload will be initialized to {0}
	 *
	 * @param signal 	Signal for the message
	 * @param dest	 	Destination of this message
	 */
	Message(Signal signal, Component dest)
	: signal(signal), dest(dest), payload{0} {}

	/**
	 * @brief Constructor for messages without payload.
	 * 		  Payload will be initialized to {0}
	 *
	 * @param signal 	Signal for the message
	 * @param dest	 	Destination of this message
	 * @param src 		Source of this message
	 */
	Message(Signal signal, Component dest, Component src)
	: signal(signal), dest(dest), src(src), payload{0} {}

	/**
	 * @brief Constructor for messages with payload
	 *
	 * @param signal 	Signal for the message
	 * @param dest	 	Destination of this message
	 * @param payload	Payload of the message
	 */
	Message(Signal signal, Component dest, uint32_t *payload)
	: signal(signal), dest(dest) {
		memcpy(this->payload, (const void *)payload, sizeof(Message));
	}

	/**
	 * @brief Signal for the message
	 */
	Signal signal;

	/**
	 * @brief Destination of the message
	 */
	Component dest;

	/**
	 * @brief source of the message
	 */
	Component src;

	/**
	 * @brief Payload of the message
	 */
	uint32_t payload[MSG_PAYLOAD_SIZE];
};

#endif /* SRC_MESSAGE_H_ */
