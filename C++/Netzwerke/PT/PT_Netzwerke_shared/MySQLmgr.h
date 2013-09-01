#include <stdlib.h>
#include <stdio.h>

/*Compiler-Weiche für OS*/
#ifdef _WIN32 //Windows Header
	//MySQL
	#include <my_global.h>
	#include <mysql.h>
#else //Linux Header
	//MySQL
	#include <mysql.h>
#endif

#define DEBUG false

using namespace std;

class MySQLmgr
{
	private:
		MYSQL *con;
		MYSQL_RES *result;
		MYSQL_ROW row;
		int num_fields;
		int i_affactedRows;

	public:
		/* Konstruktor */
		MySQLmgr();
		~MySQLmgr();

		int Querry( char* cp_mysql_querry );

		void querytest( char* cp_mysql_querry );
};
