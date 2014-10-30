#ifndef _MAIN_H_
#define _MAIN_H_

#include "Cube.h"
#include "camera.h"
#include "house.h"
#include <vector>

namespace Globals
{
    extern Cube cube;
	extern Camera camera;
	extern Camera altCamera;
	extern House *house;
};

#endif