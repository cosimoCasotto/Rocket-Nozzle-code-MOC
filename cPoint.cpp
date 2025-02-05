#include "cPoint.h"


cPoint::cPoint(void)
	: m_index(-1)
	, m_centerlineLocation(false)
	  , m_wallLocation(false)
{}

cPoint::cPoint(int i) //constructor of cPoint class. 
	: m_index(i)
	, m_centerlineLocation(false)
	  , m_wallLocation(false)
{}
