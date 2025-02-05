#include "outputToFile.h"
#include "engine.h"
#include <fstream>
#include <iostream>

// Implementation of outputToFile
void outputToFile(engine& Engine, const char* fileName) {
	std::ofstream stream(fileName);

	if (stream.is_open()) {
		// write header
		stream << "Index"
			<< "\t\t"
			<< "X"
			<< "\t\t"
			<< "Y"
			<< "\t\t"
			<< "Mach"
			<< "\t\t"
			<< "FlowAngle"
			<< "\t\t"
			<< "P-MAngle"
			<< "\n";

		// write data
		for (int p = 0; p < Engine.m_nPoints; p++) {
			cPoint& c = Engine.m_charPoints[p];
			stream << c.m_index << "\t\t" << c.m_x << "\t\t" << c.m_y << "\t\t" << c.m_Mach
				<< "\t\t" << c.m_flowAngle << "\t\t" << c.m_pmAngle << "\n";
		}
		// close file
		stream.close();
		std::cout << "data written to " << fileName << "\n";
	} else {
		std::cerr << "Failed to open file for writing. \n";
	}
}
