#pragma once

#include <stdlib.h>
#include <stdio.h>
#include <sstream>	//ostringstream

#include <cstring> //memset

/*Compiler-Weiche für OS*/
#ifdef _WIN32 //Windows Header
	//MySQL
	#include <my_global.h>
	#include <mysql.h>
#else //Linux Header
	//MySQL
	#include <mysql.h>
#endif

#define DEBUG_BUFFERQUERRYSIZE 128

using namespace std;

class MySQLmgr
{
	private:
		MYSQL *con;
		MYSQL_RES *result;
		MYSQL_ROW row;
		int num_fields;
		int num_rows;
		int i_affactedRows;

		char user[64];
		bool printQueryToConsol;

		void check4Connection();

	public:
		/* Konstruktor */
		MySQLmgr(const char* server, const char* user, const char* password, const char* database);
		~MySQLmgr();

		bool Query( const char* cp_mysql_query );
		int getSingleDataFromQuerry( const char* cp_mysql_query, int indexRow );

		bool storeOrderedResult( const char* cp_mysql_query );
		int getOrderedResult( int index );
		char* getOrderedResultAsString( int index );
		float getOrderedResultAsFloat( int index );

		void setUser( const char* user );
		char* getUser( void );

		void setPrintQueryToConsol( bool b );

		void logFailedQuery( const char* query );
		char* getLastQuery( void );

		int getRowsCountFromQuerry();
		void getNextRow( void );
		//zum testen
		void querytest( char* cp_mysql_query );
};
