/*
 * waypoints.cpp
 *
 *  Created on: Nov 4, 2016
 *      Author: Admin
 */

#include "waypoints.h"
#include "math.h"
#include "tgmath.h"
#include <iostream>
#include <iomanip>
using namespace std;

Waypoints::Waypoints(Waypoint start, Waypoint end)
{
	this->wayStart=start;
	this->wayEnd=end;
	generateWaypoints();
}

void Waypoints::generateWaypoints()
{
	float totalXDist;
	float totalYDist;
	convertToMeter(wayStart,wayEnd,totalXDist, totalYDist);
	int xGrid=fabs(floor(totalXDist/5));
	int yGrid=fabs(floor(totalYDist/5));
	this->uncoveredWaypoint [xGrid*yGrid];
	//this->coveredWaypoint [xGrid*yGrid];
	this->totalPoints=xGrid*yGrid;
	this->coveredPointer=0;
	this->uncoveredPointer=0;
	float oneLatStep=(totalXDist/xGrid)/meterPerLat;
	float oneLongStep=(totalYDist/yGrid)/meterPerLong;
	cout<<"Onelatstep"<<oneLatStep<<endl;
	cout<<"Onelongstep"<<oneLongStep<<endl;
	Waypoint nextWay;
	float lastY=wayStart.long_val;
	bool addOrMinus=false;
	for(int i=0;i<xGrid;i++)
	{
		float newXPoint=(i*oneLatStep)+wayStart.lat_val;
		if(addOrMinus==false)
			addOrMinus=true;
		else
			addOrMinus=false;
		float newYPoint;
		for(int j=0;j<yGrid;j++)
		{

			if(addOrMinus)
				newYPoint=(j*oneLongStep)+lastY;
			else
				newYPoint=-(j*oneLongStep)+lastY;
			nextWay.lat_val=newXPoint;
			nextWay.long_val=newYPoint;
			this->uncoveredWaypoint[(i*yGrid)+j]=nextWay;

		}

		lastY=newYPoint;
	}

}

int Waypoints::numOfPoints()
{
//	cout<<std::fixed<<std::setprecision(12);
//	cout<<this->uncoveredWaypoint[5].lat_val;
//	cout<<",";
//	cout<<this->uncoveredWaypoint[5].long_val;
//	cout<<endl;
	return totalPoints;
}

Waypoint Waypoints::getNextWaypoint()
{

	if(this->uncoveredPointer<numOfPoints())
	{
		Waypoint next=uncoveredWaypoint[this->uncoveredPointer];
		this->uncoveredPointer+=1;
		return next;
	}
	Waypoint error;
	error.lat_val=-1;
	error.long_val=-1;
	return error;
}

void Waypoints::markWaypointDone(Waypoint done)
{
	coveredWaypoint[coveredPointer]=done;
	this->coveredPointer+=1;
}

Waypoint Waypoints::getStartPoint()
{
	return this->wayStart;
}

Waypoint Waypoints::getEndPoint()
{
	return this->wayEnd;
}

void Waypoints::convertToMeter(Waypoint start, Waypoint end, float& xmeter, float& ymeter)
{
	float start_lat=wayStart.lat_val;
	float start_long=wayStart.long_val;
	float end_lat=wayEnd.lat_val;
	float end_long=wayEnd.long_val;
	xmeter=(end_lat-start_lat)*meterPerLat;
    ymeter=(end_long-start_long)*meterPerLong;
}

void Waypoints::pushWaypoint(Waypoint* array,int pointer, Waypoint data)
{
	array[pointer]=data;
}

