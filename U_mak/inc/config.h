/*
 * config.h
 *
 *  Created on: Sep 17, 2021
 *      Author: elmas
 */

#ifndef INC_CONFIG_H_
#define INC_CONFIG_H_

#define SUCCESS 0
#define ERROR	-1

typedef int Product;

typedef enum _State
{
	IO_STATE_PRECHECK,
	IO_STATE_PROCESS,
	IO_STATE_QUALTY_CHECK,
}State;

typedef enum _EventType
{
	EVENT_PRODUCT_IN,
	EVENT_PRODUCT_IN_PROCESS,
	EVENT_PRODUCT_OUT,
	EVENT_PRODUCT_TRASH
}EventType;

typedef struct _Event
{
	Product product;
	EventType eventType;
	State currentState;
	unsigned char optionalParam;
}Event;

#endif /* INC_CONFIG_H_ */
