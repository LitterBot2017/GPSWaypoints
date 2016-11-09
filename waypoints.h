/*
 * Waypoints.h
 *
 *  Created on: Nov 4, 2016
 *      Author: Admin
 */

#ifndef WAYPOINTS_H_
#define WAYPOINTS_H_

struct Waypoint{
	float lat_val;
	float long_val;
};

class Waypoints {

	public:
		Waypoints(Waypoint start, Waypoint end);
		Waypoint getStartPoint();
		Waypoint getEndPoint();
		Waypoint getNextWaypoint();
		void markWaypointDone(Waypoint done);
		void convertToMeter(Waypoint start, Waypoint end, float& xmeter, float& ymeter);
		int numOfPoints();
	private:
		int totalPoints;
		const float meterPerLat=111034.60528834906;
		const float meterPerLong=85393.82609037454;
		static int num_of_objects;
		Waypoint wayStart;
		Waypoint wayEnd;
		int uncoveredPointer;
		int coveredPointer;
		Waypoint uncoveredWaypoint[];
		Waypoint coveredWaypoint[];
		void generateWaypoints();
		void pushWaypoint(Waypoint*  arrayToPush, int pointer, Waypoint data);
};

#endif /* WAYPOINTS_H_ */
