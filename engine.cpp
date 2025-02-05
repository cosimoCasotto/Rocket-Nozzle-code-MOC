#include "engine.h"

//methods: 
	void 
engine::initializePoints(void)
{
	reset();
	//initialize empty array of charaxcteristic points
	m_nPoints = m_nLines + m_nLines*(m_nLines+1)/2;
	int j = 1 + m_nLines;
	int k = 0; 
	for (int i = 1; i <= m_nPoints; i++) {   // LOOP from 1 to m_nPoints
		cPoint point(i); 
		//set wall points
		if (i == j + k){
			point.m_wallLocation = true; 
			k = k + 1; 
			j = j + m_nLines - k; 
		}
		m_charPoints.push_back(point); 
	}
	//set centerline points (0 flow angle and y location)
	for (int i = 0; i < m_nPoints; i++) {    // LOOP from 0 to m_nPoints-1
		cPoint& c = m_charPoints[i]; 
		if (c.m_index == 1){
			c.m_centerlineLocation = true; 
			c.m_flowAngle          = 0; 
			c.m_y                  = 0; 
		}
		if (i >= 1){
			if ( m_charPoints[i-1].m_wallLocation ) {
				c.m_centerlineLocation = true;
				c.m_flowAngle          = 0; 
				c.m_y                  = 0; 
			}
		}
	}
}


	void 
engine::reset(void)
{
	//reset all
	m_charPoints.clear(); 
}
