
#define MAX_WORT_LENGTH 128

class Word
{
	private:
		char data[MAX_WORT_LENGTH];
		int currentIndex;
		int appearance;

	public:
		Word();
		Word( char* initWord );
		~Word();

		//SET
		void addChar( char c );
		void increateAppearence();

		//GET
		char* getWord();
		char getCharakter( int index );
		int getCharakterCount();
		int getAppearence();

		//vergleich
		bool Equals( Word* w );

		void finished();
};
