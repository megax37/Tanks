#ifndef _ENGINE_
#define _ENGINE_

#define DEGREES_TO_RADIANS 0.01745329251994329547
#define RADIANS_TO_DEGREES 57.29577951308232185913
#define M_UNITE 0.7071067811865475244f
#define PI 3.141592653589793238462643383

#include "Dependencies\glew\glew.h"
#include "Dependencies\freeglut\freeglut.h"
#include "Dependencies\SOIL\SOIL.h"

#include <iostream>
#include <sstream>
#include <fstream>
#include <string>
#include <vector>
#include <map>
#include <math.h>
#include <assert.h>

#include "VectorFactory.h"
#include "MatrixFactory.h"
#include "Quaternion.h"
#include "ShaderProgram.h"
#include "Mesh.h"
#include "Camera.h"
#include "DirectionalLight.h"
#include "Texture.h"
#include "Material.h"
//#include "SceneGraph.h"

#include "KeyBuffer.h"
#include "ErrorHandler.h"

#endif