/*
 * dbManager.h
 *
 *  Created on: Sep 17, 2021
 *      Author: elmas
 */

#ifndef INC_DBMANAGER_H_
#define INC_DBMANAGER_H_

int dbInitialize(void);
int dbAddProduct(Product* id);
int dbSaveEvent(Event* event);



#endif /* INC_DBMANAGER_H_ */
