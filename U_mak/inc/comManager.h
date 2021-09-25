/*
 * comManager.h
 *
 *  Created on: Sep 17, 2021
 *      Author: elmas
 */

#ifndef INC_COMMANAGER_H_
#define INC_COMMANAGER_H_

int comInit(void);
int comSendEvent(Event* event);
int comClose(void);

#endif /* INC_COMMANAGER_H_ */
