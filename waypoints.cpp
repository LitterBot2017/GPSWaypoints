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
using namespace std;

Waypoints::Waypoints(Waypoint start, Waypoint end)
{
//	if(num_of_objects!=0)
//	{
//		return;
//	}
	//Waypoints::num_of_objects=1;
	this->wayStart=start;
	this->wayEnd=end;
	generateWaypoints();
}

void Waypoints::generateWaypoints()
{
	float totalXDist;
	float totalYDist;
	convertToMeter(wayStart,wayEnd,totalXDist, totalYDist);
	cout<<totalXDist<<endl;
	cout<<totalYDist<<endl;
	int xGrid=fabs(floor(totalXDist/5));
	int yGrid=fabs(floor(totalYDist/5));
	cout<<"xGrid"<<xGrid<<endl;
	cout<<"yGrid"<<yGrid<<endl;
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
	for(int i=0;i<xGrid;i++)
	{
		float newXPoint=(i*oneLatStep)+wayStart.lat_val;
		//cout<<"newXPoint"<<newXPoint<<endl;
		for(int j=0;j<yGrid;j++)
		{
			float newYPoint=(j*oneLongStep)+wayStart.long_val;
			//cout<<"newYPoint"<<newYPoint<<endl;

			nextWay.lat_val=newXPoint;
			nextWay.long_val=newYPoint;
			this->uncoveredWaypoint[(i*yGrid)+j]=nextWay;
			//pushWaypoint(&this->uncoveredWaypoint[0],uncoveredPointer,nextWay);
			this->uncoveredPointer+=1;
		}
	}
}

int Waypoints::numOfPoints()
{
	return totalPoints;
}

Waypoint Waypoints::getNextWaypoint()
{
	Waypoint next=uncoveredWaypoint[uncoveredPointer-1];
	this->uncoveredPointer-=1;
	return next;
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

