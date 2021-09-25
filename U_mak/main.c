/*
 * main.c
 *
 *  Created on: Sep 17, 2021
 *      Author: elmas
 */
#include "config.h"

#include "ioManager.h"
#include "dbManager.h"
#include "comManager.h"

int main(int argc, char **argv)
{
	State currentState=IO_STATE_PRECHECK;
	State nextState;
	int ret;
	Event event;
	Product currentProduct;

	comInit();

	while(1)
	{
		memset(&event,0,sizeof(Event));
		switch(currentState)
		{
		case IO_STATE_PRECHECK:
			//read prep sensor
			ret=ioReadPrepSensor();

			if(ret == SUCCESS)
			{
				ret = dbAddProduct(&currentProduct);
				event.eventType=EVENT_PRODUCT_IN;
				event.currentState=currentState;
				nextState=IO_STATE_PROCESS;
			}
			else
			{
				event.eventType=EVENT_PRODUCT_TRASH;
				event.currentState=currentState;
				nextState=IO_STATE_PRECHECK;
			}
			break;
		case IO_STATE_PROCESS:
			if(ret== SUCCESS)
			{
				ret = ioProcessProduct(currentProduct);
			}

			if(ret == SUCCESS)
			{
				event.eventType=EVENT_PRODUCT_IN_PROCESS;
				event.currentState=currentState;
				nextState=IO_STATE_QUALTY_CHECK;
			}
			break;
		case IO_STATE_QUALTY_CHECK:
			{
				int quality=0;
				ret=ioReadQualitySensor(&quality);

				if(ret == SUCCESS)
				{
					if(quality>=90)
					{
						event.eventType=EVENT_PRODUCT_OUT;
						event.currentState=currentState;
						event.optionalParam=(unsigned char)quality&0xFF;
					}
					else
					{
						event.eventType=EVENT_PRODUCT_TRASH;
						event.currentState=currentState;
						nextState=IO_STATE_PRECHECK;
					}
				}

				nextState=IO_STATE_PRECHECK;
				break;
			}

		}

		if(currentState!=IO_STATE_QUALTY_CHECK)
		{
			event.optionalParam=0;
		}

		event.product=currentProduct;
		dbSaveEvent(&event);
		comSendEvent(&event);
		currentState=nextState;
	}

	comClose();
}





