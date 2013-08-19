#pragma once

#include <my_global.h>
#include <mysql.h>
#include <string>

#define LOGERROR this->logError(__FUNCTION__);

class MySqlResult
{
public:
	MySqlResult(void);
	~MySqlResult(void);

	void setup(MYSQL_RES* mysqlResult);

	const std::string& getResult(int rowIdx, int colIdx) const;
	int getNumberOfRows() const;
	int getNumberOfColumns() const;

protected:
	std::string** resultTable;
	int numRows;
	int numCols;
};

class MySqlConnector
{
public:
	MySqlConnector(void);
	~MySqlConnector(void);

	// initialise the underlying MYSQL-pointer
	bool init();
	// deinitialise the underlying MYSQL-pointer
	void shutdown();

	// connect to a database
	bool connect(	const char* address, 
					const char* username, 
					const char* password, 
					const char* database = NULL);
	// send a query
	bool sendQuery(const char* query, MySqlResult* outResult);

	// print an error message describing the last mysql error
	void logError(const char* functionname);
protected:
	// true if init has been called
	bool valid;

	// the underlying mysql-pointer
	MYSQL* connection;
};

