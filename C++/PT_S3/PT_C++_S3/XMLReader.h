#pragma once

#include <iostream>
#include <cstdlib>
#include <string>
#include <vector>

using namespace std;

#define XML_READER_DEBUG_MODE false

enum XML_STATE 
{
	XMLREADER_STATE_BEGINN			= 0 ,
	XMLREADER_STATE_IDENTIFY_ELEMENT	,

	XMLREADER_STATE_READ_ELEMENT_BEGINN	,
	XMLREADER_STATE_READ_ELEMENT_END	,

	XMLREADER_STATE_READ_ATTRIBUT_NAME	,
	XMLREADER_STATE_READ_ATTRIBUT_VALUE	,

	XMLREADER_STATE_READ_MASKED_STRING	,
};

enum XML_ELEMENT_TYP
{
	XML_ELEMENT_TYP_INIT			,
	XML_ELEMENT_TYP_EMPTY_ELEMENT	,
	XML_ELEMENT_TYP_BEGINN_ELEMENT	,
	XML_ELEMENT_TYP_END_ELEMENT		,
	XML_ELEMENT_TYP_ATTRIBUT		,
	XML_ELEMENT_TYP_STRING_ELEMENT	,
	XML_ELEMENT_TYP_FINISHED
};

struct XML_element
{
	XML_ELEMENT_TYP typ;

	string name;
	string value;

	XML_element( void )
	{
		this->typ = XML_ELEMENT_TYP_INIT;
		
		this->name.empty();
		this->value.empty();
	};

	XML_element( XML_ELEMENT_TYP typ )
	{
		this->typ = typ;
		
		this->name.empty();
		this->value.empty();
	};

	XML_element( XML_ELEMENT_TYP typ, string name )
	{
		this->typ = typ;
		
		this->name = name;
		this->value.empty();
	};

	XML_element( XML_ELEMENT_TYP typ, string name, string value )
	{
		this->typ = typ;
		
		this->name = name;
		this->value = value;
	};
};

class XMLReader
{
	public:
		XMLReader( const char* filename );
		~XMLReader(void);

		XML_element getNext( void );

	private:
		FILE* xmlfile;
		string str_current_xmlline;
		unsigned int current_line;

		vector<XML_element> xmlElements_in_readed_line;

		void readFile( void );
		void parseLine( string lineToParse );
};
