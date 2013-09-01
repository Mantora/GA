#include "MySQLmgr.h"

MySQLmgr::MySQLmgr()
{
	this->i_affactedRows = 0;
	this->num_fields = 0;

	if( DEBUG )
		printf("MySQLmgr: MySQL client version: %s\n", mysql_get_client_info());

	con = mysql_init(NULL);
	if(con == NULL)
	{
		if( DEBUG )
			printf("MySQLmgr: Error %u: %s\n", mysql_errno(con), mysql_error(con));
	    exit(1);
	}

	if( mysql_real_connect(con, "127.0.0.1", "root", "2011#myroot!", "titan_dev", 0, NULL, 0) == NULL)
	{
		if( DEBUG )
			printf("MySQLmgr Error %u: %s\n", mysql_errno(con), mysql_error(con));
		exit(1);
	}

	if( DEBUG )
	{
		printf("MySQLmgr: Verbindung zur Datenbank hergestelt.\n");
		printf("MySQLmgr: MySQL Server info: %s\n", mysql_get_server_info(con));
		printf("MySQLmgr: bereit\n");
	}
};

MySQLmgr::~MySQLmgr()
{

};

int MySQLmgr::Querry( char* cp_mysql_querry )
{
	mysql_query(con, cp_mysql_querry);
	
	result = mysql_store_result(con);

	this->num_fields = mysql_num_fields(result);
//	printf("Anzahl Spalten: %d\n",num_fields);

	this->i_affactedRows = mysql_num_rows( result );
//	printf("Anzahl Zeilen: %d\n",i_affactedRows);

	return this->i_affactedRows;
}


//zum testen
void MySQLmgr::querytest( char* cp_mysql_querry)
{
	mysql_query(con, cp_mysql_querry);

	result = mysql_store_result(con);

	num_fields = mysql_num_fields(result);
	printf("Anzahl Spalten: %d\n",num_fields);

	i_affactedRows = mysql_num_rows( result );
	printf("Anzahl Zeilen: %d\n",i_affactedRows);

	//Datensätze anzeigen
	while( (row = mysql_fetch_row( result )) )
	{
			for(int i = 0; i < num_fields; i++)
			{
				printf("%s ", row[i] ? row[i] : "NULL");
			}
			printf("\n");
	}
	
	/* close connection */
	mysql_free_result(result);
	mysql_close(con);
};
