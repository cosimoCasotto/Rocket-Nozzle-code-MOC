#ifndef CPOINT_H
#define CPOINT_H   //inclde guard to prevent cPoint class from being inclued more than once


class cPoint {
	public: 
		//blank construtor
		cPoint();
		//constructor
		cPoint(int i); 

		//variables
		int   m_index;
		float m_flowAngle;
		float m_pmAngle; //deg
		float m_Mach; 
		float m_mu; 
		float m_x; 
		float m_y; 
		bool  m_wallLocation; 
		bool  m_centerlineLocation; 
};

#endif 
