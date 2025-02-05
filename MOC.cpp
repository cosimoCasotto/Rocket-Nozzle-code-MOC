#include "MOC.h"
#include "equations.h"



	void
MOC(engine& Engine, equations& eq)
{
	Engine.initializePoints();
	Engine.m_maxWallAngle = eq.getPMAngle(Engine.m_gamma, Engine.m_Mexit) / 2.0;
	std::vector<float> thtDivisions = eq.interpolateAngle(Engine.m_maxWallAngle, Engine.m_nLines);
	std::vector<int>   wallPoints;
	std::vector<int>   centerPoints;
	for (int i = 0; i < Engine.m_nPoints; i++)
	{
		if (Engine.m_charPoints[i].m_wallLocation)
		{
			wallPoints.push_back(Engine.m_charPoints[i].m_index);
		}
		if (Engine.m_charPoints[i].m_centerlineLocation)
		{
			centerPoints.push_back(Engine.m_charPoints[i].m_index);
		}
	}

	// begin method of characteristics

	// conversions
	float r2d = 180 / M_PI;
	float d2r = M_PI / 180;

	// point a (throat)
	float xa = 0; // x location (cm)

	float tht_a = 0.19;     // kickoff angle (deg)
	float pm_a = 0.19;      // same as kickoff angle (deg)
	float M_a = 1.026;      // Mach at a
	float slope_a = -75.23; // slope at a (deg)

	// point 1
	Engine.m_charPoints[0].m_x = Engine.m_Rthroat * tan((90 + slope_a) * d2r);
	Engine.m_charPoints[0].m_pmAngle = tht_a + pm_a;
	Engine.m_charPoints[0].m_Mach = eq.getMachFromPM(M_a, Engine.m_charPoints[0].m_pmAngle, Engine.m_gamma);
	Engine.m_charPoints[0].m_mu = asin(1 / Engine.m_charPoints[0].m_Mach) * r2d;

	// points 2 to n+1, m_charPoints[1] to cP[n] - the first reflection
	for (int i = 1; i <= Engine.m_nLines; i++)
	{
		// assign flow and pm angle (equal for first reflection)
		cPoint &point_i = Engine.m_charPoints[i];
		cPoint &point_i_meno1 = Engine.m_charPoints[i - 1];
		if (!point_i.m_wallLocation)
		{
			point_i.m_flowAngle = thtDivisions[i];
			point_i.m_pmAngle = thtDivisions[i];
			point_i.m_Mach = eq.getMachFromPM(point_i_meno1.m_Mach, point_i.m_pmAngle, Engine.m_gamma);
			point_i.m_mu = asin(1 / point_i.m_Mach) * r2d;
			// find theta_ax = nu_ax and the Mach angle
			float tv_ax = (2 * (thtDivisions[i]) + (point_i_meno1.m_flowAngle - point_i_meno1.m_pmAngle)) / 2;
			float M_ax = eq.getMachFromPM(1.001, tv_ax, Engine.m_gamma);
			float mu_ax = asin(1 / M_ax) * r2d;
			// find left and right running characteristic slopes
			float tht_b = (point_i_meno1.m_flowAngle + point_i_meno1.m_mu + point_i.m_flowAngle + point_i.m_mu) / 2;
			float tht_t = (tv_ax - mu_ax + point_i.m_flowAngle - point_i.m_mu) / 2;
			// find xy location of point i
			std::pair<float, float> xy = eq.returnXYIntersectionPoint(xa, Engine.m_Rthroat, tht_t, point_i_meno1.m_x, point_i_meno1.m_y, tht_b);
			point_i.m_x = xy.first;
			point_i.m_y = xy.second;
		}
		// extend for the wall location
		else
		{
			point_i.m_flowAngle = point_i_meno1.m_flowAngle;
			point_i.m_pmAngle = point_i_meno1.m_pmAngle;
			point_i.m_Mach = point_i_meno1.m_Mach;
			point_i.m_mu = point_i_meno1.m_mu;
			// find left and second left running (both point up), the first left is the interpolated wall angle (max for first reflection)
			float tht_t = Engine.m_maxWallAngle;
			float tht_b = (point_i_meno1.m_flowAngle + point_i_meno1.m_mu + point_i.m_flowAngle + point_i.m_mu) / 2;
			// find xy location of the wall point
			std::pair<float, float> xy = eq.returnXYIntersectionPoint(xa, Engine.m_Rthroat, tht_t, point_i_meno1.m_x, point_i_meno1.m_y, tht_b);
			point_i.m_x = xy.first;
			point_i.m_y = xy.second;
		}
	}

	// remaining points
	int j = 0;
	int k = 1;
	for (int i = Engine.m_nLines + 1; i < Engine.m_nPoints; i++)
	{
		cPoint &point_i = Engine.m_charPoints[i];
		cPoint &point_i_meno1 = Engine.m_charPoints[i - 1];
		cPoint &point_i2 = Engine.m_charPoints[i - (Engine.m_nLines - j)];
		cPoint &point_i3 = Engine.m_charPoints[i - (Engine.m_nLines - j + 1)];
		if (point_i.m_centerlineLocation)
		{
			point_i.m_pmAngle = point_i2.m_flowAngle + point_i2.m_pmAngle;
			point_i.m_Mach = eq.getMachFromPM(point_i2.m_Mach, point_i.m_pmAngle, Engine.m_gamma);
			point_i.m_mu = asin(1 / point_i.m_Mach) * r2d;
			float tht_t = (point_i2.m_flowAngle - point_i2.m_mu + point_i.m_flowAngle - point_i.m_mu) / 2;
			float tht_b = 0;
			// find xy location of centerline point
			std::pair<float, float> xy = eq.returnXYIntersectionPoint(point_i2.m_x, point_i2.m_y, tht_t, point_i3.m_x, point_i3.m_y, tht_b);
			point_i.m_x = xy.first;
			point_i.m_y = xy.second;
		}
		if (!point_i.m_centerlineLocation && !point_i.m_wallLocation)
		{
			point_i.m_flowAngle = thtDivisions[k];
			point_i.m_pmAngle = (point_i2.m_flowAngle + point_i2.m_pmAngle - (point_i_meno1.m_flowAngle - point_i_meno1.m_pmAngle)) / 2;
			point_i.m_Mach = eq.getMachFromPM(point_i_meno1.m_Mach, point_i.m_pmAngle, Engine.m_gamma);
			point_i.m_mu = asin(1 / point_i.m_Mach) * r2d;
			float tht_t = (point_i2.m_flowAngle - point_i2.m_mu + point_i.m_flowAngle - point_i.m_mu) / 2;
			float tht_b = (point_i_meno1.m_flowAngle + point_i_meno1.m_mu + point_i.m_flowAngle + point_i.m_mu) / 2;
			// find xy location of point
			std::pair<float, float> xy = eq.returnXYIntersectionPoint(point_i2.m_x, point_i2.m_y, tht_t, point_i_meno1.m_x, point_i_meno1.m_y, tht_b);
			point_i.m_x = xy.first;
			point_i.m_y = xy.second;
			k += 1;
		}
		if (point_i.m_wallLocation)
		{
			point_i.m_flowAngle = point_i_meno1.m_flowAngle;
			point_i.m_pmAngle = point_i_meno1.m_pmAngle;
			point_i.m_Mach = point_i_meno1.m_Mach;
			point_i.m_mu = point_i_meno1.m_mu;
			float tht_t = point_i_meno1.m_flowAngle;
			float tht_b = (point_i_meno1.m_flowAngle + point_i_meno1.m_mu + point_i.m_flowAngle + point_i.m_mu) / 2;
			// find xy location of the wall point
			std::pair<float, float> xy = eq.returnXYIntersectionPoint(point_i2.m_x, point_i2.m_y, tht_t, point_i_meno1.m_x, point_i_meno1.m_y, tht_b);
			point_i.m_x = xy.first;
			point_i.m_y = xy.second;
			k = 1;
			j += 1;
		}
	}
}

















