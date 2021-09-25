/*
 * dbManager.c
 *
 *  Created on: Sep 17, 2021
 *      Author: elmas
 */
#include <string.h>
#include <sqlite3.h>

#include "config.h"
#include "dbManager.h"

/************************************************************************/
#define QUERY_GET_LAST_PRODUCT_ID 	0
#define QUERY_ADD_PRODUCT 			1
#define DB_FILENAME 				"database.db"


/************************************************************************/

static int isInitialized=0;
static int queryType;
static sqlite3 *db;
static char* errMsg;
char *sql;

static int lastProductID;

/************************************************************************/

static int callback(void* nan,int argc,char **argv,char **key)
{
	switch(queryType)
	{
	case QUERY_ADD_PRODUCT:
		break;
	case QUERY_GET_LAST_PRODUCT_ID:
		lastProductID=atoi(argv[0]);
		break;

	}
}

static int getLastProductId(sqlite3** db)
{
	queryType=QUERY_GET_LAST_PRODUCT_ID;
	sql="SELECT COUNT(*) FROM Product";
	sqlite3_exec(*db,sql,callback,NULL, errMsg);

	return lastProductID;
}

/************************************************************************/

int dbInitialize(void)
{
	int ret;

	ret=sqlite3_open(DB_FILENAME, &db);

	if(ret==SUCCESS)
	{
		sql="CREATE TABLE Product(ID INTEGER PRIMARY KEY)";

		sqlite3_exec(db,sql,callback,NULL, errMsg);
	}

	if(ret==SUCCESS)
	{
		sql="CREATE TABLE Event(ID INTEGER PRIMARY KEY AUTOINCREMENT, PID INTEGER, EventType INTEGER, State INTEGER, Optional INTEGER)";

		sqlite3_exec(db,sql,callback,NULL, errMsg);
	}

	if(ret == SUCCESS)
	{
		isInitialized=1;
	}

	ret = sqlite3_close(db);

	return ret;
}

int dbAddProduct(Product* id)
{
	int ret;

	if(!isInitialized)
	{
		ret = dbInitialize();
	}

	ret=sqlite3_open(DB_FILENAME, &db);

	if(ret==SUCCESS)
	{
		char query[128]={0};

		getLastProductId(&db);
		*id=lastProductID+1;
		sprintf(query,"INSERT INTO Product VALUES(%d)",*id);
		sql=query;
		sqlite3_exec(db,sql,callback,NULL, errMsg);
	}

	sqlite3_close(db);

	return 0;

}

int dbSaveEvent(Event* event)
{
	int ret;

		if(!isInitialized)
		{
			ret = dbInitialize();
		}

		ret=sqlite3_open(DB_FILENAME, &db);

		if(ret==SUCCESS)
		{
			char query[128];

			sprintf(query,"INSERT INTO Event VALUES(NULL, %d, %d, %d, %d)",event->product,event->eventType,event->currentState,event->optionalParam);
			sql=query;
			sqlite3_exec(db,sql,callback,NULL, errMsg);
		}

		sqlite3_close(db);

		return 0;
}
