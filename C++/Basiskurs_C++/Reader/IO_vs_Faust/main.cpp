// obtaining file size
#include <iostream>
#include <fstream>
#include <string>

#include <iomanip>// std::setw (http://www.cplusplus.com/reference/iomanip/setw/)

#include "Word.h"

#include "Performance.h"

using namespace std;

#define MAX_PERFORMANCE false
#define MAX_WORDS 50000

int main()
{
//Performancetest starten
Performance p;

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

	char file[] = { "faust.txt" };

//	char tmp[256] = {0};
//	cout << "Filename to analyse: ";
//	cin.get(str, 256); // get c-string

	ifstream is( file ); // open file

	unsigned long wordCount_different = 0;
	unsigned long wordCount_every = 0;
	unsigned long charakterCount = 0;
	unsigned long count_space = 0;

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
				case '"':

				case '-':

				case '\n': if( !MAX_PERFORMANCE ) charakterCount++;
				case ' ':
				{
					if( !MAX_PERFORMANCE ) count_space++;

					w->finished();

					if( w->getCharakterCount() > 0)
					{
						if( !MAX_PERFORMANCE ) wordCount_every++;
						
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
						if( !MAX_PERFORMANCE ) charakterCount++;
				break;
			}
		}
	}
	//ende der Datei
	//letztes Word im Speicher verarbeiten
	w->finished();

	if( w->getCharakterCount() > 0)
	{
		if( !MAX_PERFORMANCE ) wordCount_every++;

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
	is.close(); // close file

	if( !MAX_PERFORMANCE )
	{
		cout << "Total 4 file \"" << file << "\":" << endl;
		cout << "---------------------------------" << endl;

		cout << "Total: " << currentWordIndex << " different words. " << endl;
		cout << "Total: " << wordCount_every << " words. " << endl;

		cout << "Charakters: " << charakterCount << endl;
		cout << "With spaces: " << count_space << endl;

		cout << "Writing to file: " ;
	}
///////////////////////////////////////////////////////////
	
	//maximal gelesene Zeichenanzahl pro Wort ermitteln
	unsigned int maxCharakterRead = 0;
	if( !MAX_PERFORMANCE ) 
 	{
		for( int i = 0; i < currentWordIndex; i++)
		{
			if( words[i]->getCharakterCount() > maxCharakterRead )
				maxCharakterRead = words[i]->getCharakterCount();
		}
	}
	else
		maxCharakterRead = 40;

	//sortieren nach Wortanzahl
	if( !MAX_PERFORMANCE )
	{
		for( int i = 0; i < currentWordIndex; i++ )
		{
			//mit allen folgenden vergleichen
			for( int x = i; x < currentWordIndex; x++ )
			{
				if( words[x]->getAppearence() > words[i]->getAppearence() )
				{
					//vertauschen
					Word* tmp = words[i];
					words[i] = words[x];
					words[x] = tmp;
				}
			}
		}
	}

	//words in datei schreiben
	ofstream ofs("output.txt", ofstream::out);

	for( int i = 0; i < currentWordIndex; i++ )
	{	
		//Für schöne ausgabe in der Datei
		ofs << left << std::setw(maxCharakterRead);
		ofs << setfill('.');

		ofs << words[i]->getWord() ;

		//Rechts orientiert: bis zu einer anzahl von "xx.xxx" 
		ofs << right << std::setw(5) << words[i]->getAppearence() << endl;
	}

	if( !MAX_PERFORMANCE )
	{
		ofs << endl;
		ofs << "statistics enabled because MAX_PERFORMANCE mod if OFF!" << endl;
		ofs << endl;

		ofs << "Total 4 file \"" << file << "\":" << endl;
		ofs << "---------------------------------" << endl;

		ofs << "Total: " << currentWordIndex << " different words. " << endl;
		ofs << "Total: " << wordCount_every << " words. " << endl;

		ofs << "Charakters: " << charakterCount << endl;
		ofs << "With spaces: " << count_space << endl;
	}
	else
	{
		ofs << endl;
		ofs << "statistics disabled because MAX_PERFORMANCE mod is ON!" << endl;
	}

	ofs.close();

	cout << "Done!" << endl;

//Performancetest beenden um zeit zu ermitteln
double zeit = p.stop();
cout << "Performance : " << zeit << " sek" << endl;

	system("pause");
	return 0;
}