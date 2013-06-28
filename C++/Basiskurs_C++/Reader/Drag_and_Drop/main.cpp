#include <iostream>

using namespace std;

int main(int argc, char* argv[])
{
    // argv[0] is not interesting, since it's just your program's path.
    for(int i = 1; i < argc; ++i)
	{
        cout << "argv[" << i << "] is \"" << argv[i] << "\"" << endl;
	}
	
	//Drag & Drop:
	//Datei: [...].exe
	//Ordner: [...]

	system("pause");
    return 0;
}
