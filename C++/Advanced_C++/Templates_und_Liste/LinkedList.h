#pragma once

template <typename V> 
class CListElement
{
	public:
		CListElement(V value)
		{
			m_pxValue = value;
			m_pPrev = NULL;
			m_pNext = NULL;
		};

		~CListElement()
		{};

		V m_pxValue;
		CListElement<V>* m_pPrev;
		CListElement<V>* m_pNext;
};

template <typename T> 
class CLinkedList
{
	private:
		CListElement<T>* m_pFirst;
		CListElement<T>* m_pLast;
		int m_iSize;

	public:
		CLinkedList()
		{
			m_pFirst = NULL;
			m_pLast = NULL;
			m_iSize = 0;
		};

		~CLinkedList()
		{};

		CListElement<T>* AddToFront(T xValue)
		{
			m_iSize++;
			CListElement<T>* current = new CListElement<T>( xValue );

			if( m_pFirst == NULL )
			{
				m_pFirst = current;
				m_pLast = current;
				
			}
			else
			{
				//altes erstes zeigt auf neues
				m_pFirst->m_pPrev = current;
				//neues zeigt auf altes
				current->m_pNext = m_pFirst;
				//neues ist das erste
				m_pFirst = current;
			}

			return current;
		};

		CListElement<T>* AddToBack(T xValue)
		{
			m_iSize++;
			CListElement<T>* current = new CListElement<T>( xValue );

			if( m_pLast == NULL )
			{
				m_pLast = current;
				m_pFirst = current;
			}
			else
			{
				m_pLast->m_pNext = current;
				current->m_pPrev = m_pLast;
				m_pLast = current;
			}

			return current;
		};

		CListElement<T>* InsertBefore(CListElement<T>* pBeforeThis, T xValueToInsert)
		{
			CListElement<T>* toInsert = new CListElement<T>( xValueToInsert );
			CListElement<T>* current = this->m_pFirst;
			//das entsprechende Element raussuchen:
			while( current != NULL )
			{
				if( current == pBeforeThis )
				{
					this->m_iSize++;
					//gibt es ein Element davor:
					if( current->m_pPrev == NULL )
					{
						//current ist erstes element
						this->m_pFirst = toInsert;
						current->m_pPrev = toInsert;
						toInsert->m_pNext = current;
					}
					else
					{
						//current hat ein element davor
						CListElement<T>* oldPrev = current->m_pPrev;
						oldPrev->m_pNext = toInsert;
						current->m_pPrev = toInsert;

						toInsert->m_pPrev = oldPrev;
						toInsert->m_pNext = current;
					}
					break;
				}
				current = current->m_pNext;
			}

			return toInsert;
		}

		CListElement<T>* InsertAfter(CListElement<T>* pAfterThis, T xValueToInsert)
		{
			CListElement<T>* toInsert = new CListElement<T>( xValueToInsert );
			CListElement<T>* current = this->m_pFirst;
			//das entsprechende Element raussuchen:
			while( current != NULL )
			{			
				if( current == pAfterThis )
				{
					this->m_iSize++;
					if( current->m_pNext == NULL )
					{
						//current ist das letztes element
						this->m_pLast = toInsert;
						current->m_pNext = toInsert;
						toInsert->m_pPrev = current;
					}
					else
					{
						//current hat ein element nach sich
						this->m_pLast->m_pPrev = toInsert;
						current->m_pNext = toInsert;

						toInsert->m_pPrev = current;
						toInsert->m_pNext = this->m_pLast;

						break;
					}
				}
				current = current->m_pNext;
			}
			return toInsert;
		}

		void DeleteElement(CListElement<T>* pElement)
		{
			CListElement<T>* current = this->m_pFirst;
			while( current != NULL )
			{
				if( current == pElement )
				{
					if( current == this->m_pFirst )
					{
						//am anfang
						CListElement<T>* next = current->m_pNext;
						next->m_pPrev = NULL;
						this->m_pFirst = next;
					}
					else if( current == this->m_pLast )
					{
						//am ende
						CListElement<T>* pref = current->m_pPrev;
						pref->m_pNext = NULL;
						this->m_pLast = pref;
					}
					else
					{
						//in der mitte
						CListElement<T>* pref = current->m_pPrev;
						CListElement<T>* next = current->m_pNext;

						pref->m_pNext = next;
						next->m_pPrev = pref;
					}
					this->m_iSize--;
					delete current;
					current = NULL;
					break;
				}
				current = current->m_pNext;
			}
		};

		void SwapElements(CListElement<T>* pE1, CListElement<T>* pE2)
		{
			//simpel:
			//werte Tauschen
			CListElement<T> tmp = pE1->m_pxValue;
			pE1->m_pxValue = pE2->m_pxValue;
			pE2->m_pxValue = tmp.m_pxValue;

			//besser und cooler: Pointer umbiegen:
/*			//anderer ansatz: (von http://www.cplusplus.com/forum/beginner/102181/ )
			if(pE1->m_pPrev) pE1->m_pPrev->m_pNext = pE2;
			else this->m_pFirst = pE1;

			if(pE2->m_pPrev) pE2->m_pPrev->m_pNext = pE1;
			else this->m_pFirst = pE2;

			if(pE1->m_pNext) pE1->m_pNext->m_pPrev = pE2;
			else this->m_pLast = pE1;
			
			if(pE2->m_pNext) pE2->m_pNext->m_pPrev = pE1;
			else this->m_pLast = pE2;

			CListElement<T>* tmp;

			tmp = pE1->m_pPrev;
			pE1->m_pPrev = pE2->m_pPrev;    
			pE2->m_pPrev = tmp;

			tmp = pE1->m_pNext;
			pE1->m_pNext= pE2->m_pNext;    
			pE2->m_pNext= tmp;
*/

/*			if(pE1 == this->m_pFirst) //pE1 ist m_pFirst
			{
				this->m_pFirst = pE2;
				pE2->m_pNext->m_pPrev = pE1;
			}

			if(pE1 == this->m_pLast)
			{
				this->m_pLast = pE2;
				pE1->m_pPrev->m_pNext = pE2;
			}

			if(pE2 == this->m_pFirst) 
			{
				this->m_pLast = pE1;
				pE1->m_pNext->m_pPrev = pE2;
			}

			if(pE2 == this->m_pLast) 
			{
				this->m_pLast = pE1;
				pE2->m_pPrev->m_pNext = pE1;
			}

			CListElement<T>* tmp;

			tmp = pE1->m_pPrev;
			pE1->m_pPrev = pE2->m_pPrev;    
			pE2->m_pPrev = tmp;

			tmp = pE1->m_pNext;
			pE1->m_pNext = pE2->m_pNext;    
			pE2->m_pNext = tmp;
*/
/*			CListElement<T>* bevor_E1 = pE1->m_pPrev;
			CListElement<T>* after_E1 = pE1->m_pNext;

			CListElement<T>* bevor_E2 = pE2->m_pPrev;
			CListElement<T>* after_E2 = pE2->m_pNext;

			if( pE1->m_pPrev != NULL && pE2->m_pNext != NULL )
			{
				//kein ende, kein anfang
				if( pE1->m_pPrev == pE2 && pE2->m_pNext == pE1 )
				{
					
				}

				if( pE1->m_pNext == pE2 && pE2->m_pPrev == pE1 )
				{
					//mittig - nebeneinander - nicht anfang/ende 
					//es gibt element vor E1 und nach E2 

					pE2->m_pPrev = bevor_E1;
					pE1->m_pNext = pE2->m_pNext;

					pE2->m_pNext = pE1;
					pE1->m_pPrev = pE2;

					bevor_E1->m_pNext = pE2;
					after_E2->m_pPrev = pE1;
				}

			}
*/
		};

		CListElement<T>* GetElementByIndex(int iIndex)
		{
			CListElement<T>* current = this->m_pFirst;
			int i = 0;
			while( i != iIndex )
			{
				i++;
				current = current->m_pNext;
			}
//			std::cout << "GetElementByIndex(" << iIndex << ") = " << current->m_pxValue << std::endl;
			return current;
		};

		CListElement<T>* FindValue(T xValue) const
		{
			CListElement<T>* current = this->m_pFirst;
			CListElement<T>* toReturn = NULL;

			while( current != NULL )
			{
				if( current->m_pxValue == xValue )
				{
					toReturn = current;
					//?
					//break; 
				}
				current = current->m_pNext;
			}

			return toReturn;
		};

		CListElement<T>* GetFirstElement() const
		{
			return this->m_pFirst;
		};

		CListElement<T>* GetLastElement() const
		{
			return this->m_pLast;
		};

		int	GetSize() const
		{
			return this->m_iSize;
		};

		void Sort()
		{
			CListElement<T>* current;

			for( int i = 0; i < this->m_iSize; i++ )
			{
				current = this->GetElementByIndex( i );
				for( int j = i; j < this->m_iSize; j++ )
				{
					CListElement<T>* toCheck = this->GetElementByIndex(j);
					if( toCheck->m_pxValue > current->m_pxValue )
					{
						this->SwapElements( current, toCheck );
					}
				}
			}
		};

		bool CheckIntegrity() const
		{
			try
			{
				CListElement<T>* current = this->m_pFirst;
				int i = 0;
				while( current != NULL )
				{
					current = current->m_pNext;
					i++;
				}
				i = this->m_iSize;
				while( current != NULL )
				{
					i--;
					current = current->m_pPrev;
				}
			}
			catch( ... )
			{
				std::cout << "Exception catched on CheckIntegrity() " << std::endl;
				return false;
			}
			std::cout << "CheckIntegrity() passed " << std::endl;
			return true;
		};

		//TODELETE: 4 DEBUG
		void printASC()
		{
			CListElement<T>* current = this->m_pFirst;
			int i = 0;

			std::cout << "printing ASC:" << std::endl;

			while( current != NULL )
			{
				std::cout << "\t" << i << ") " << current->m_pxValue << std::endl;
				current = current->m_pNext;
				i++;
			}
		};

		void printDESC()
		{
			CListElement<T>* current = this->m_pLast;
			int i = this->m_iSize;
			
			std::cout << "printing DESC:" << std::endl;
			
			while( current != NULL )
			{
				i--;
				std::cout << "\t" << i << ") " << current->m_pxValue << std::endl;
				current = current->m_pPrev;
			}
		};
};
