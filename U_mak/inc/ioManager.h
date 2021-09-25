/*
 * ioManager.h
 *
 *  Created on: Sep 17, 2021
 *      Author: elmas
 */

#ifndef INC_IOMANAGER_H_
#define INC_IOMANAGER_H_

#include "config.h"

int ioReadPrepSensor(void);
int ioProcessProduct(Product product);
int ioReadQualitySensor(int* quality);

#endif /* INC_IOMANAGER_H_ */
