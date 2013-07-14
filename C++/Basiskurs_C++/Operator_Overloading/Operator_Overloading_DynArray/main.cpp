#include <iostream>

#include "CDynArray.h"

using namespace std;

int main()
{
	CDynArray a;
	a.Print();
	a.AddElement(0);
	a.AddElement(8);
	a.AddElement(2);
	a.AddElement(6);
	a.AddElement(4);
	a.AddElement(5);
	a.AddElement(3);
	a.AddElement(7);
	a.AddElement(1);
	a.AddElement(9);
	cout << a[2] << endl;

	CDynArray b(a);
	b.AddElement(88);

	a.Print();
	a.DeleteElement(1);
	a.Print();

	b.Print();
	b.DeleteRange( 0, b.GetSize());
	b.Print();

	CDynArray c(5);
	c.Print();

	CDynArray d(a);
	CDynArray e(a);

	if( d == e ) cout << "==" << endl;
	if( d != e ) cout << "!=" << endl;

	a.Sort_ASC();
	a.Sort_DSC();

	a.Print();
	a.InsertBeforElement(0, 4);
	a.Print();
	a.InsertAfterElement(0, 5);
	a.Print();

	system("pause");
	return 0;
}