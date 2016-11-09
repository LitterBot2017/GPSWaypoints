//============================================================================
// Name        : HelloWorld.cpp
// Author      : 
// Version     :
// Copyright   : 
// Description : Hello World in C++, Ansi-style
//============================================================================

#include <iostream>
#include <iomanip>
#include "waypoints.h"

using namespace std;

int main() {

	Waypoint start;
	start.lat_val=40.4440829681405;
	start.long_val=-79.943168275;
	Waypoint end;
	end.lat_val=40.4429870540925;
	end.long_val=-79.942529238;
	Waypoints test=Waypoints(start,end);
	cout<<test.numOfPoints()<<endl;
	for(int i=0;i<test.numOfPoints();i++)
	{
		Waypoint getVal=test.getNextWaypoint();
		cout<<std::fixed<<std::setprecision(12);
		cout<<getVal.lat_val;
		cout<<",";
		cout<<getVal.long_val;
		cout<<endl;
	}
	return 0;
}
