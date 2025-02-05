#ifndef EQUATIONS_H
#define EQUATIONS_H

#include <vector>
#include <math.h>
#include <string>

class equations {
	public: 
		//constructor: 
		equations(); 

		//methods: 
		std::pair<float,float> returnOutsideTemperatureAndPressure(float h); 
		float validateGam( float gam ) { return (gam<=1.0) ? 1.2 : gam;} //check if gamma is acceptable value
		float getExitMach(float Tc, float Pc, float Pe, float& gam, float R); 
		float getPMAngle(float gam, float M); //degrees
		float getMachFromPM(float Mi, float pmAngle, float gam); 
		std::vector<float> interpolateAngle(float theta, int n); 
		std::string vectorToString(std::vector<float> v); 
		std::string vectorToString(std::vector<int> v); 
		std::pair<float, float> returnXYIntersectionPoint(float xt, float yt, float tht_to, float xb, float yb, float tht_b); 

};

#endif
