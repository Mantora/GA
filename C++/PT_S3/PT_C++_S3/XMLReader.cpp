#include "XMLReader.h"

#include "Config.h"

XMLReader::XMLReader( const char* filename )
{
	this->current_line = 0;
	this->xmlfile = fopen( filename, "r" );

	this->readFile();
}
//-------------------------------------------------------------------------------------------------------------
XMLReader::~XMLReader( void )
{
	fclose( this->xmlfile );
}
//-------------------------------------------------------------------------------------------------------------
XML_element 
XMLReader::getNext( void )
{
	//erstes zurückgeben
	XML_element tmp = this->xmlElements_in_readed_line[0];

	if( DEBUG_XML ) cout << "DEBUG_XML: " << "tmp.typ: " << tmp.typ << " tmp.name:" << tmp.name << " tmp.value:" << tmp.value << endl;

	//erstes aus der liste entfernen
	std::vector<XML_element>::iterator it = this->xmlElements_in_readed_line.begin();
	this->xmlElements_in_readed_line.erase( it );

	return tmp;
};
//-------------------------------------------------------------------------------------------------------------
void 
XMLReader::readFile( void )
{
	char c = 0;
	char lastChar = 0;

	string readedLine;

	do
	{
		c = getc( this->xmlfile );

		if( c != '\n' )
		{
			readedLine += c;
		}
		else
		{
			this->parseLine( readedLine );
			readedLine.clear();
		}

		if( c == EOF )
		{
			this->parseLine( readedLine );
		}

	}
	while(c != EOF );

	//end of xml file reached ?
	if( c == EOF )
	{
		//add XML_ELEMENT_TYP_FINISHED
		XML_element readed_element( XML_ELEMENT_TYP_FINISHED );
		this->xmlElements_in_readed_line.push_back( readed_element );
	}
};
//-------------------------------------------------------------------------------------------------------------
void 
XMLReader::parseLine( string lineToParse )
{
	if( XML_READER_DEBUG_MODE ) cout << "parseLine( " << lineToParse << " )" << endl;

	this->current_line++;

	XML_STATE current_state = XMLREADER_STATE_BEGINN;

	string str_elementName;

	string str_name;
	string str_value;

	for( unsigned int i = 0; i < lineToParse.length(); i++ )
	{
		switch( current_state )
		{
			case XMLREADER_STATE_BEGINN:
			{
				//search 4 the first XML statement
				switch( lineToParse[i] )
				{
					case '<':
					{
						//xml statement found
						//switch to state IDENTIFY_ELEMENT
						current_state = XMLREADER_STATE_IDENTIFY_ELEMENT;
					}
					break;

					case '\n':
					{
						//end of statement
					}
					break;

					case ' ':
					{
						//possible attribut beginn, ignore more spaces
						if( (lineToParse[i+1] >= 65			//A
								&& lineToParse[i+1] <= 90)	//Z
							|| (lineToParse[i+1] >= 97		//a
								&& lineToParse[i+1] <= 122 ))	//z
						{
							//attribut beginn
							current_state = XMLREADER_STATE_READ_ATTRIBUT_NAME;
						}
					}
					break;

					case '>':
					{
						//possible end of line
						//read next char to be sure
					}
					break;

					case '/':
					{
						if( lineToParse[i+1] == '>' )
						{
							if( XML_READER_DEBUG_MODE ) cout << "XMLREADER_STATE_READ_ELEMENT_END:" << str_elementName << endl;
						}
					}
					break;


					default:
					{
						//any char readed
						//check 4 a-z or A-Z
						if( (lineToParse[i] >= 65			//A
								&& lineToParse[i] <= 90)	//Z
							|| (lineToParse[i] >= 97		//a
								&& lineToParse[i] <= 122 ))	//z
						{
							//string found
							current_state = XMLREADER_STATE_READ_MASKED_STRING;

							//rewind one position to not lose the char
							i--;
						}
					}
					break;
				}
			}
			break;

			case XMLREADER_STATE_IDENTIFY_ELEMENT:
			{
				//next char decide:
				if( lineToParse[i] == '/' )
				{
					//xml element closed
					current_state = XMLREADER_STATE_READ_ELEMENT_END;
				}
				else
				{
					//element name beginn
					str_elementName += lineToParse[i];
					current_state = XMLREADER_STATE_READ_ELEMENT_BEGINN;
				}
			}
			break;

			case XMLREADER_STATE_READ_ELEMENT_BEGINN:
			{
				switch( lineToParse[i] )
				{
					case '>':
					{
						//xml element end
						if( XML_READER_DEBUG_MODE ) cout << "XMLREADER_STATE_READ_ELEMENT_BEGINN:" << str_elementName << endl;
						current_state = XMLREADER_STATE_BEGINN;

						//add finished readed element to list
						XML_element readed_element( XML_ELEMENT_TYP_EMPTY_ELEMENT, str_elementName );
						this->xmlElements_in_readed_line.push_back( readed_element );
					}
					break;

					case ' ':
					{
						//beginn of attribut
						if( XML_READER_DEBUG_MODE ) cout << "XMLREADER_STATE_READ_ELEMENT_BEGINN:" << str_elementName << endl;
						current_state = XMLREADER_STATE_READ_ATTRIBUT_NAME;

						//add finished readed element to list
						XML_element readed_element( XML_ELEMENT_TYP_BEGINN_ELEMENT, str_elementName );
						this->xmlElements_in_readed_line.push_back( readed_element );
					}
					break;

					default:
					{
						str_elementName += lineToParse[i];
					}
					break;
				}
			}
			break;

			case XMLREADER_STATE_READ_ELEMENT_END:
			{
				if( lineToParse[i] != '>' )
				{
					str_name += lineToParse[i];
				}
				else
				{
					// '>' indictes end of element name
					if( XML_READER_DEBUG_MODE ) cout << "XMLREADER_STATE_READ_ELEMENT_END:" << str_name << endl;
					
					//add finished readed element to list
					XML_element readed_element( XML_ELEMENT_TYP_END_ELEMENT, str_name );
					this->xmlElements_in_readed_line.push_back( readed_element );

					str_name.clear();

					current_state = XMLREADER_STATE_BEGINN;
				}
			}
			break;

			case XMLREADER_STATE_READ_ATTRIBUT_NAME:
			{
				if( lineToParse[i] != '='
					&& lineToParse[i+1] != '"' )
				{
					str_name += lineToParse[i];
				}
				else
				{
					//jump to the beginning of attribut value
					i++;

					if( XML_READER_DEBUG_MODE ) cout << "XMLREADER_STATE_READ_ATTRIBUT_NAME:" << str_name << endl;

					// attribut name will be cleared after attribut value is readed and both are stored

					current_state = XMLREADER_STATE_READ_ATTRIBUT_VALUE;
				}
			}
			break;

			case XMLREADER_STATE_READ_ATTRIBUT_VALUE:
			{
				if( lineToParse[i] != '"' )
				{
					str_value += lineToParse[i];
				}
				else
				{
					if( XML_READER_DEBUG_MODE ) cout << "XMLREADER_STATE_READ_ATTRIBUT_VALUE:" << str_value << endl;

					//add finished readed element to list
					XML_element readed_element( XML_ELEMENT_TYP_ATTRIBUT, str_name, str_value );
					this->xmlElements_in_readed_line.push_back( readed_element );

					str_value.clear();
					str_name.clear();

					current_state = XMLREADER_STATE_BEGINN;
				}
			}
			break;

			case XMLREADER_STATE_READ_MASKED_STRING:
			{
				if( lineToParse[i] != '<' )
				{
					str_name += lineToParse[i];
				}
				else
				{
					//string ends
					//go one step back to be sure the next XML can be identify
					i--;

					if( XML_READER_DEBUG_MODE ) cout << "XMLREADER_STATE_READ_MASKED_STRING:" << str_name << endl;

					//add finished readed element to list
					XML_element readed_element( XML_ELEMENT_TYP_STRING_ELEMENT, str_name );
					this->xmlElements_in_readed_line.push_back( readed_element );

					str_name.clear();

					current_state = XMLREADER_STATE_BEGINN;
				}
			}
			break;
		}
	}

	if( XML_READER_DEBUG_MODE ) cout << " end of XML line " << endl << endl;
};
