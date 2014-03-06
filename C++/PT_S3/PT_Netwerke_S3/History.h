#pragma once

#include "Historyinterface.h"
#include "HistoryData.h"

#include <vector>

class History
: public HistoryInterface
{
	public:
		History( int maxHistoryDataCount );
		~History(void);

		void addPosition(int timestamp, CVector3 position);
		void addDirection(int timestamp, CVector3 direction);
		void addButtonEvent(int timestamp, bool buttonDown);

		CVector3 getPosition(int timestamp);
		CVector3 getDirection(int timestamp);
		bool getButtonDown(int timestamp);

		void printDebugInfo();
		
		static bool sortFunction( HistoryData h1, HistoryData h2 );

	private:
		int maxHistoryDataCount;
		int currentHistoryDataCount;
		std::vector<HistoryData> data;

		HistoryData getLastKnownData( int timestamp );
		HistoryData getFirstDataAfter( int timestamp );
		int getMaxTimestamp( void );

		//interpolation functions
		CVector3 interpolate_pos( HistoryData h1, HistoryData h2, int timestampToInterpolate );
		CVector3 interpolate_dir( HistoryData h1, HistoryData h2, int timestampToInterpolate );
		bool interpolate_buttonDown( int timestampToInterpolate );

		//extrapolate functions
		CVector3 extrapolate_pos( HistoryData h1, int timestampToExtrapolate );
		CVector3 extrapolate_dir( HistoryData h1, int timestampToExtrapolate );
		bool extrapolate_buttonDown( int timestampToExtrapolate );

		//function to manage max elements in history
		void checkForDataSize( void );
};
