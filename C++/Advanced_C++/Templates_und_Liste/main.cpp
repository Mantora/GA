// function template
#include <iostream>

#include "LinkedList.h"

using namespace std;

template <class T> T GetMax (T a, T b)
{
	if( a > b )
		return a;
	else
		return b;
}



int main()
{
//	cout << GetMax<int>(5,6) << endl;
//	cout << GetMax<float>(10.4f,5.2f) << endl;

	CLinkedList<int>* LL = new CLinkedList<int>();
	LL->AddToBack( -1 );
	CListElement<int>* toInsertBevor_mid = LL->AddToFront( 3 );
	CListElement<int>* toDelete_mid = LL->AddToFront( 2 );
	LL->AddToFront( 1 );
	CListElement<int>* toInsertAfter_mid = LL->AddToBack( 4 );
	CListElement<int>* toInsertBevor_front = LL->AddToFront( 0 );
	CListElement<int>* toInsertAfter_end = LL->AddToBack( 5 );

	cout << "4 = " << LL->GetElementByIndex(4)->m_pxValue << endl;

	cout << "Listenelement mit wert 0 hat adresse " << LL->FindValue(0) << endl;

	cout << "Liste enthält " << LL->GetSize() << " elemente " << endl;

	LL->InsertBefore( toInsertBevor_mid, 20 );
	LL->InsertBefore( toInsertBevor_front, 40 );

	LL->InsertAfter( toInsertAfter_mid, 11 );
	LL->InsertAfter( toInsertAfter_end, 22 );


/*
	cout << LL->GetFirstElement()->m_pxValue << endl;
	cout << LL->GetFirstElement()->m_pNext->m_pxValue << endl;
	cout << LL->GetFirstElement()->m_pNext->m_pNext->m_pxValue << endl;
	cout << "--" << endl;
	cout << LL->GetLastElement()->m_pxValue << endl;
	cout << LL->GetLastElement()->m_pPrev->m_pxValue << endl;
	cout << LL->GetLastElement()->m_pPrev->m_pPrev->m_pxValue << endl;
*/

	//TODELETE: 4 DEBUG
	LL->printASC();
//	LL->printDESC();

	LL->DeleteElement( LL->GetFirstElement() );
	LL->DeleteElement( toDelete_mid );
	LL->DeleteElement( LL->GetLastElement() );

	LL->printASC();
//	LL->printDESC();

	LL->SwapElements( LL->GetElementByIndex(3), LL->GetElementByIndex(2) );

	LL->printASC();
//	LL->printDESC();

	system("pause");
	return 0;
}