#include "Utility.h"

#include <pthread.h>
//mutexes
pthread_mutex_t mutex_utility = PTHREAD_MUTEX_INITIALIZER;

int Utility::runningGUID = 0;

Utility::Utility(void)
{
	time_t t;
	srand((unsigned) time(&t));
}

Utility::~Utility(void)
{

}

int Utility::getNewGUID()
{
//	pthread_mutex_lock( &mutex_utility );
		Utility::runningGUID++;
//	pthread_mutex_unlock( &mutex_utility );
	return Utility::runningGUID;
};

void Utility::resetGUIDs()
{
//	pthread_mutex_lock( &mutex_utility );
		Utility::runningGUID = 0;
//	pthread_mutex_unlock( &mutex_utility );
};
