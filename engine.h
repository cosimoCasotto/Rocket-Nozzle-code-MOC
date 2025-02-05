#ifndef ENGINE_H
#define ENGINE_H

#include "cPoint.h"
#include <vector>


class engine {
	public: 
		//constructors
		engine()
			: m_gamma(1.2)
			  , m_nLines( 45 )
			  , m_Mexit( 3.0 )
			  , m_Rthroat( 20 )   // 20 cm
	{
		initializePoints();
	}

		//methods 
		void initializePoints( void );
		void reset( void );

		//variables: user defined 
		float m_Pchamb;
		float m_Tchamb; 
		float m_gamma;
		float m_Rgas;
		float m_Rthroat; 
		int   m_nPoints; 
		int   m_nLines; 

		//variables: calculated
		float m_Pexit; 
		float m_Texit; 
		float m_SOSexit;
		float m_Mexit;
		float m_maxWallAngle;
		std::vector<cPoint> m_charPoints; 
};


#endif
