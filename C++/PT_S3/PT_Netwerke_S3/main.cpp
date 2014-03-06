/*
* Network_Examn_UseCase.cpp
*
* provides a use case for the history class 
* to be written in the examn 
* of the course PR340 - Network Programming
* Solved by: Christopher Jann PRO 2012 26.02.2014
*/

#include <math.h> //< needed for sin() and cos()

#include "History.h"

/*
* use case method
*
* NOTE: This use case stores orientations and button events and calls printDebugInfo. 
* If you choose not to implement these features remove them from the code.
*
* NOTE: to keep the code simple the positions are written first, then the directions and last the button events. 
* That means the direction of timestamp 0 is written directly after the position of timestamp 3000.
* Your history class should work in a network game environment, and that means that you CAN expect the values to be written in order, i.e. sorted by timestamp, not by type.
* If you want to make use of that assumption feel free to change this test method.
*
*/
int main(int argc, char* argv[])
{
	// make instance of the history
    History* history = new History( 10 );

    // generate test positions
    CVector3 position;
    for (int timestamp = 0; timestamp <= 3000; timestamp += 200)
    {
        position.x = (float)abs(timestamp % 1000 - 500);
        position.y = 0;
        position.z = (float)abs((timestamp + 250) % 1000 - 500);

        // store timestamped position in history class
        history->addPosition(timestamp, position);
    }

    // generate test orientations
    CVector3 direction;
    for (int timestamp = 0; timestamp <= 3000; timestamp += 200)
    {
        direction.x = sin(timestamp * 0.001f);
        direction.y = 0;
        direction.z = cos(timestamp * 0.001f);

        // store timestamped orientation in history class
        history->addDirection(timestamp, direction);
    }

    // store test button events
	history->addButtonEvent(100, true);
	history->addButtonEvent(200, false);
	history->addButtonEvent(300, true);
   
	history->addButtonEvent(500, true);
    history->addButtonEvent(1000, false);
    history->addButtonEvent(1250, true);
    history->addButtonEvent(1500, false);
    history->addButtonEvent(2100, true);
    history->addButtonEvent(2400, false);
    history->addButtonEvent(2900, true);

    // print debug info
    history->printDebugInfo();

    // retrieve interpolated values from the history class
    CVector3 positiontest = history->getPosition(2300); // should be (200, 0, 50)
    CVector3 directiontest = history->getDirection(2300); // should be (0.745, 0, -0.66)
    bool buttontest = history->getButtonDown(2300); // should be true

    // retrieve extrapolated values from the history class
    positiontest = history->getPosition(3100); // should be (600, 0, 150)
    directiontest = history->getDirection(3100); // should be (0.04, 0, -0.99)
    buttontest = history->getButtonDown(3100); // should be true

	// custom test timestamps
	int timestampToExtrapolate = 1000;
    positiontest = history->getPosition(timestampToExtrapolate);
    directiontest = history->getDirection(timestampToExtrapolate);
    buttontest = history->getButtonDown(timestampToExtrapolate);

	system("pause");
}
