/*
* Pure virtual class that illustrates a possible interface for a history class
* Feel free to improve the interface in any way you think is appropriate.
*/

#include "CVector3.h"

class HistoryInterface
{
	public:
		virtual void addPosition(int timestamp, CVector3 position) = 0;
		virtual void addDirection(int timestamp, CVector3 direction) = 0;
		virtual void addButtonEvent(int timestamp, bool buttonDown) = 0;

		virtual CVector3 getPosition(int timestamp) = 0;
		virtual CVector3 getDirection(int timestamp) = 0;
		virtual bool getButtonDown(int timestamp) = 0;

		virtual void printDebugInfo() = 0;
};
