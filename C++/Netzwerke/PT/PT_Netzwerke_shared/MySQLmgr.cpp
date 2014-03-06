#include "MySQLmgr.h"

MySQLmgr::MySQLmgr(const char* server, const char* user, const char* password, const char* database)
{
	memset( this->user, 0, sizeof( this->user ) );
	printQueryToConsol = false;

	this->i_affactedRows = 0;
	this->num_fields = 0;

	if( printQueryToConsol )
		printf("MySQLmgr: MySQL client version: %s\n", mysql_get_client_info());

	con = mysql_init(NULL);
	if(con == NULL)
	{
		//if( DEBUG )
			printf("MySQLmgr: Error %u: %s\n", mysql_errno(con), mysql_error(con));
		//Compilerweiche für OS
		#ifdef _WIN32 //Windows Header
			system("pause");
		#else //Linux Header
			system("read");
		#endif
	    exit(1);
	}

	if( mysql_real_connect(con, server, user, password, database, 0, NULL, 0) == NULL)
	{
		//if( DEBUG )
			printf("MySQLmgr Error %u: %s\n", mysql_errno(con), mysql_error(con));
		//Compilerweiche für OS
		#ifdef _WIN32 //Windows Header
			system("pause");
		#else //Linux Header
			system("read");
		#endif
		exit(1);
	}

	my_bool reconnect = 1;
	mysql_options( con, MYSQL_OPT_RECONNECT, &reconnect );

	if( printQueryToConsol )
	{
		printf("MySQLmgr: Verbindung zur Datenbank hergestelt.\n");
		printf("MySQLmgr: MySQL Server info: %s\n", mysql_get_server_info(con));
		printf("MySQLmgr: bereit\n");
	}
}

MySQLmgr::~MySQLmgr()
{

}

void MySQLmgr::check4Connection()
{
	mysql_ping( this->con );
}

bool MySQLmgr::Query( const char* cp_mysql_query )
{
	check4Connection();

	if( printQueryToConsol )
		printf( "\t%s\n", cp_mysql_query);

	int result = mysql_query( this->con, cp_mysql_query);

	if( result != 0 )
	{
		logFailedQuery( cp_mysql_query );
		return false;
	}
	this->result = mysql_store_result( this->con );

	this->num_rows = (int)mysql_num_rows( this->result );

	return true;
}

//fehlerhaften SQL befehl speichern
void MySQLmgr::logFailedQuery( const char* query )
{
	check4Connection();

	char* maskQuery = new char[ strlen( query ) * 2 + 1 ];
	mysql_real_escape_string( con, maskQuery, query, strlen( query ) );

	ostringstream oss;
	oss << "INSERT INTO log(ENTRY, TIME, FROMSQLUSER) VALUES('FAIL QUERRY: " << maskQuery << "', NOW(),'" << this->user << "' );";

	mysql_query( this->con, oss.str().c_str() );

	delete maskQuery;
}

int MySQLmgr::getSingleDataFromQuerry( const char* cp_mysql_query, int indexRow )
{
	if( printQueryToConsol )
		printf( "\t%s\n", cp_mysql_query);

	int i_tmp_data = 0;

	if( mysql_query(con, cp_mysql_query) )
	{
		//Fehler im query
		printf( "MySQLmgr: ERROR bei mysql_query(\"%s\")\n", cp_mysql_query );

		ostringstream oss;
		oss << "mysql_query() on " << cp_mysql_query;
		this->logFailedQuery( oss.str().c_str() );

		return -1;
	}
	else //Anfrage erfolgreich, Rückgabedaten können verarbeitet werden
	{
		result = mysql_store_result( con );
		if( result ) //es sind Zeilen vorhanden
		{
			//Hole Zeilen ab und rufe dann mysql_free_result(result) auf
			my_ulonglong num_rows = mysql_num_rows( result );
			if( num_rows > 0 )
			{
				row = mysql_fetch_row( result );
				i_tmp_data = atoi( row[indexRow] );
				return i_tmp_data;
			}
			else
			{
				//Query ok, es gibt aber keine zeilen
				return -1;
			}
		}
		else //es gab nichts zurück
		{
			printf( "MySQLmgr: ERROR bei mysql_store_result(\"%s\")\n", cp_mysql_query );

			ostringstream oss;
			oss << "mysql_store_result() on " << cp_mysql_query;
			this->logFailedQuery( oss.str().c_str() );

			return -1;
		}
	}
}

bool MySQLmgr::storeOrderedResult( const char* cp_mysql_query )
{
	check4Connection();

	if( printQueryToConsol )
		printf( "\t%s\n", cp_mysql_query);

	if( mysql_query(con, cp_mysql_query) )
	{
		//Fehler im Query
		printf( "MySQLmgr: ERROR bei mysql_query(\"%s\")\n", cp_mysql_query );

		ostringstream oss;
		oss << "mysql_query() on " << cp_mysql_query;
		this->logFailedQuery( oss.str().c_str() );

		return false;
	}

	//Anfrage erfolgreich, Rückgabedaten können verarbeitet werden
	this->result = mysql_store_result( con );

	if( this->result->row_count == 0 )
	{
		//es gab kein ergebniss
		//Fehlerbehandlung notwendig da querry auch richtig sein können, 
		//aber keine ergebnisse zurückgeben

/*		printf( "MySQLmgr: ERROR bei mysql_store_result(\"%s\")\n", cp_mysql_query );

		ostringstream oss;
		oss << "mysql_store_result() on " << cp_mysql_query;
		this->logFailedQuery( oss.str().c_str() );
*/		return false;
	}

	this->row = mysql_fetch_row( this->result );
	if( this->row == 0)
	{
		//es gibt keine zeilen mehr
		//Fehlerbehandlung notwendig da querry auch richtig sein können, 
		//aber keine ergebnisse zurückgeben
/*		printf( "MySQLmgr: ERROR bei mysql_fetch_row(\"%s\")\n", cp_mysql_query );

		ostringstream oss;
		oss << "mysql_fetch_row() on " << cp_mysql_query;
		this->logFailedQuery( oss.str().c_str() );
*/
		return false;
	}

	this->num_rows = (int)mysql_num_rows( this->result );

	return true;
}

float MySQLmgr::getOrderedResultAsFloat( int index )
{
	return atof( this->row[index] );
}

char* MySQLmgr::getOrderedResultAsString( int index )
{
	return this->row[index];
}

int MySQLmgr::getOrderedResult( int index )
{
	return atoi( this->row[index] );
}

void MySQLmgr::setUser( const char* user )
{
	memcpy( this->user, user, sizeof( this->user ) );
}

char* MySQLmgr::getUser( void )
{
	return this->user;
}

void MySQLmgr::getNextRow( void )
{
	this->row = mysql_fetch_row( this->result );
}

void MySQLmgr::setPrintQueryToConsol( bool b )
{
	this->printQueryToConsol = b;
}

//zum testen
void MySQLmgr::querytest( char* cp_mysql_querry )
{
	check4Connection();

	mysql_query(con, cp_mysql_querry);

	result = mysql_store_result(con);

	num_fields = mysql_num_fields(result);
	printf("Anzahl Spalten: %d\n",num_fields);

	i_affactedRows = (int)mysql_num_rows( result );
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
}

int MySQLmgr::getRowsCountFromQuerry()
{
	return this->num_rows;
}
