#include <iostream>
#include <conio.h> //http://stackoverflow.com/questions/8435923/getting-arrow-keys-from-cin

using namespace std;

#define KB_UP 72
#define KB_DOWN 80
#define KB_LEFT 75
#define KB_RIGHT 77
#define KB_ESCAPE 27

int main(void)
{
	int KB_code=0;
	while(KB_code != KB_ESCAPE )
	{ 
		if( _kbhit() ) //http://msdn.microsoft.com/de-de/library/58w7c94c%28v=vs.80%29.aspx
		{
			KB_code = _getch(); //ASCII Code
			printf("KB_code = %i \n",KB_code);

			switch (KB_code)
			{
				case KB_LEFT:
						   //Do something
				break;

				case KB_RIGHT:
						   //Do something                     
				break;

				case KB_UP:
						   //Do something                     
				break;

				case KB_DOWN:
						   //Do something                     
				break;
			}        
		}
	}
	return 0;
}
