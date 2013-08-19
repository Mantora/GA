#include "stdafx.h"
#include "vld.h"
#include <assert.h>

#include "DynArray.h"

//-----------------------------------------------------------------------------------	
bool	testsort(const CDynArray& xArray)
{
	for (int i = 0; i < xArray.GetSize()-2; i++)
	{
		if ( xArray[i] > xArray[i+1] )
			return false;
	}
	return true;
};

//-----------------------------------------------------------------------------------
int _tmain(int argc, _TCHAR* argv[])
{
	CDynArray ai_test;
	assert(ai_test.GetSize() == 0);
	
	CDynArray ai_test2 = CDynArray(3);
	assert(ai_test2.GetSize() == 3);
			
	ai_test.AddElement(7);
	ai_test.AddElement(3);
	assert(ai_test.GetSize() == 2);
	ai_test.Print();
	
	ai_test2 = ai_test;
	assert(ai_test2.GetSize() == 2);
	ai_test2.Print();
	assert(ai_test2[0] == 7);
	assert(ai_test2[1] == 3);

	CDynArray ai_test3(ai_test);
	assert(ai_test3.GetSize() == 2);
	ai_test3.Print();
	assert(ai_test3[0] == 7);
	assert(ai_test3[1] == 3);
	
	ai_test.AddElement(7);
	ai_test.AddElement(3);
	assert(ai_test.GetSize() == 4);
	assert(ai_test2.GetSize() == 2);
	assert(ai_test3.GetSize() == 2);
				
	ai_test[0] = 4;
	ai_test[1] = 2;
	assert(ai_test.GetSize() == 4);
	assert(ai_test[0] == 4);
	assert(ai_test[1] == 2);
	assert(ai_test[2] == 7);
	assert(ai_test[3] == 3);
	ai_test.Print();
	ai_test2.Print();
	ai_test3.Print();
	
	assert(ai_test2[0] == 7);
	assert(ai_test2[1] == 3);
	assert(ai_test3[0] == 7);
	assert(ai_test3[1] == 3);
	
	ai_test.InsertBeforeElement(42, 3);
	assert(ai_test[3] == 42);
	
	ai_test.InsertAfterElement(43, 3);
	assert(ai_test[4] == 43);
	assert(ai_test.GetSize() == 6);
	
	ai_test3 = ai_test;
	assert(ai_test3.GetSize() == 6);
	ai_test2 = ai_test;
	assert(ai_test2.GetSize() == 6);
	
	ai_test.DeleteElement(3);
	assert(ai_test[3] == 43);
	assert(ai_test.GetSize() == 5);
	
	ai_test.DeleteRange(1,2);
	assert(ai_test[1] == 43);
	assert(ai_test.GetSize() == 3);

	ai_test.DeleteRange(0, 0);
	assert(ai_test[0] == 43);
	assert(ai_test.GetSize() == 2);

	ai_test.Clear();
	assert(ai_test.GetSize() == 0);

	// ab hier Zusatz
	ai_test2.Print();
	ai_test2.selectSort();
	ai_test2.Print();
	testsort(ai_test2);
	
	ai_test3.Print();
	ai_test3.quickSort();
	ai_test3.Print();
	testsort(ai_test3);
	
	assert(ai_test2 == ai_test3);
	assert((ai_test2 != ai_test3) == false);
	ai_test2[2] = 666;
	assert((ai_test2 == ai_test3) == false);
	assert(ai_test2 != ai_test3);

	return 0;
}

