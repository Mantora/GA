// obtaining file size
#include <iostream>
#include <fstream>
#include <string>

#include <iomanip>// std::setw (http://www.cplusplus.com/reference/iomanip/setw/)

#include "Word.h"

using namespace std;

#define MAX_WORDS 50000

int main()
{
	Word* words[MAX_WORDS] = { 0 };

	int currentWordIndex = 0;

	Word* w = new Word();

/*	long begin,end;
	ifstream myfile("test.txt");

	begin = myfile.tellg();

	myfile.seekg (0, ios::end);

	end = myfile.tellg();

	myfile.close();
	cout << "size is: " << (end-begin) << " bytes.\n";
*/
//////////////////////////////////////////////////////////////////////
/*	string line;
	ifstream myfile("test.txt");
	if(myfile.is_open())
	{
		while( myfile.good() )
		{
			getline(myfile, line);
			cout << line << endl;
		}
		myfile.close();
	}
	else
		cout << "Unable to open file"; 
*/
//////////////////////////////////////////////////////////////

	char file[] = { "Faust.txt" };

//	char tmp[256] = {0};
//	cout << "Filename to analyse: ";
//	cin.get(str, 256); // get c-string

	ifstream is( file ); // open file

	unsigned long wordCount_different = 0;
	unsigned long wordCount_every = 0;
	unsigned long charakterCount = 0;

	while( is.good() ) // loop while extraction from file is possible
	{
		char c = is.get(); // get character from file
		if( is.good() )
		{
			switch( c )
			{
				case ')': 
				case '(': 
				case '.':
				case ',':
				case ';':
				case ':':
				case '?':
				case '!':

				case '-':

				//klären
				case '\'': charakterCount++;
				case '\n':
				case ' ':
				{
					w->finished();

					if( w->getCharakterCount() > 0)
					{
						wordCount_every++;

						//nach einer Übereinstimmung suchen
						for( int i = 0; i < currentWordIndex+1; i++ )
						{
							Word* currentWord = words[ i ];
							if( currentWord != NULL && currentWord->Equals( w ) )
							{
								//vorkommen erhöhen
								currentWord->increateAppearence();
								//nicht weiter suchen

								//neues Word
								w = new Word();
								break;
							}
							else if( i == currentWordIndex )
							{
								words[ currentWordIndex ] = w;

								w = new Word();
								currentWordIndex++;
								break;
							}
						}
					}
				}
				break;

				default:
					w->addChar( c );

					//statistics
					charakterCount++;
				break;
			}
		}
	}
	//ende der Datei
	//letztes Word im Speicher verarbeiten
	w->finished();

	if( w->getCharakterCount() > 0)
	{
		//nach einer Übereinstimmung suchen
		for( int i = 0; i < currentWordIndex+1; i++ )
		{
			Word* currentWord = words[ i ];
			if( currentWord != NULL && currentWord->Equals( w ) )
			{
				//vorkommen erhöhen
				currentWord->increateAppearence();
				//nicht weiter suchen
				break;
			}
			else if( i == currentWordIndex )
			{
				words[ currentWordIndex ] = w;

				w = new Word();
				currentWordIndex++;
				break;
			}
		}
	}

	cout << "Total 4 file \"" << file << "\":" << endl;
	cout << "---------------------------------" << endl;

	cout << "Total: " << currentWordIndex << " different words. " << endl;
	cout << "Total: " << wordCount_every << " words. " << endl;

	cout << "Charakters: " << charakterCount << endl;
	cout << "With spaces: " << 0 << endl;

	is.close(); // close file
///////////////////////////////////////////////////////////
	cout << "Writing to file: " ;
	
	ofstream ofs("output.txt", ofstream::out);

	//maximal gelesene Zeichenanzahl pro Wort ermitteln
	unsigned int maxCharakterRead = 0;
	for( int i = 0; i < currentWordIndex; i++)
	{
		if( words[i]->getCharakterCount() > maxCharakterRead )
			maxCharakterRead = words[i]->getCharakterCount();
	}

	for( int i = 0; i < currentWordIndex; i++)
	{	
		//Für schöne ausgabe in der Datei
		ofs << left << std::setw(maxCharakterRead);
		ofs << setfill('.');

		ofs << words[i]->getWord() ;

		//Rechts orientiert: bis zu einer anzahl von "xx.xxx" 
		ofs << right << std::setw(5) << words[i]->getAppearence() << endl;
	}
	ofs.close();

	cout << "Done!" << endl;

	system("pause");
	return 0;
}