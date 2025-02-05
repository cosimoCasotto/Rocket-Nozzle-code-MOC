#include <fstream>
#include <iostream>
#include <vector>
#include <stdlib.h>
#include <string.h>
#include "outputToFile.h"
#include "MOC.h"

#define _USE_MATH_DEFINES
#include <cmath>

#include "engine.h"
#include "equations.h"


	int
main(int argc, char *argv[])
{
	engine    Engine;
	equations eq;

	const char* outputFileName = "output.txt";

	for ( int i = 1; i < argc; i++ ) {
		if ( strcmp(argv[i], "-nlines"   ) == 0 ) { Engine.m_nLines  = atoi( argv[i+1] ); i++; }
		if ( strcmp(argv[i], "-gamma"    ) == 0 ) { Engine.m_gamma   = atof( argv[i+1] ); i++; }
		if ( strcmp(argv[i], "-exitmach" ) == 0 ) { Engine.m_Mexit   = atof( argv[i+1] ); i++; }
		if ( strcmp(argv[i], "-rthroat"  ) == 0 ) { Engine.m_Rthroat = atof( argv[i+1] ); i++; }
		if ( strcmp(argv[i], "-out"      ) == 0 ) { outputFileName = argv[i+1]; i++; }
	}
	// perform calculations
	MOC(Engine, eq); 


	outputToFile(Engine, outputFileName ); 
	return 0;
}
