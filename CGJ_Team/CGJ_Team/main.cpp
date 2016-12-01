///////////////////////////////////////////////////////////////////////
//
// TANKS - TEAM ASSIGNMENT 1
//
///////////////////////////////////////////////////////////////////////

#include "engine.h"
#include "KeyBuffer.h"
#include "SceneGraph.h"
#include "MeshManager.h"
#include "TextureManager.h"
#include "ShaderProgramManager.h"
#include "SceneGraphManager.h"
//using namespace engine;

#define ASSERT_GL_ERROR(string) checkOpenGLError(string)

#define CAPTION "Modern OpenGL Engine"
int WinX = 640, WinY = 480;
int WindowHandle = 0;
unsigned int FrameCount = 0;

//GLuint UBO_BP = 0;

const float DistanceStep = 1.5f;
float Distance = 19.0f;
Vector3D Position(0.0f, 0.0f, 0.0f);

int LastMousePositionX, LastMousePositionY;
float RotationAngleY = 0.0f;
float RotationAngleX = 55.0f;
float yaw = 0.0f, pitch = 55.0f;
float startYaw, startPitch;

Quaternion q;
Vector3D AXIS3D_X = Vector3D(1.0f, 0.0f, 0.0f);
Vector3D AXIS3D_Y = Vector3D(0.0f, 1.0f, 0.0f);
Vector3D AXIS3D_Z = Vector3D(0.0f, 0.0f, 1.0f);

// Camera modes
bool gimbal_lock_mode = true; // T - Euler angles, F - Quaternions
// Animation
bool animating = false;
int animationDirection = 1; // 1 - flow from initial square to final shape, -1 - backward flow
float t = 0.0f;
// Time update
int lastTime = 0, elapsedTime = 0;

/////////////////////////////////////////////////////////////////////// Textures

void createTextures()
{
	Texture* texture;
	//texture = new Texture("Textures/wood-texture.jpg");
	texture = new Texture("Textures/lightwood.tga");
	//texture = new Texture("Textures/stone.tga");
	TextureManager::instance()->add("wood", texture);
}

/////////////////////////////////////////////////////////////////////// Mesh

void createMeshes()
{
	Mesh* mesh;
	mesh = new Mesh("Models/cube_vtn.obj");
	mesh->create();
	MeshManager::instance()->add("cube", mesh);
	mesh = new Mesh("Models/cube2_vtn.obj");
	mesh->create();
	MeshManager::instance()->add("cube2", mesh);
	mesh = new Mesh("Models/triangle3d_vn.obj");
	mesh->create();
	MeshManager::instance()->add("triangle3D", mesh);
	mesh = new Mesh("Models/parallelogram3d_vn.obj");
	mesh->create();
	MeshManager::instance()->add("parallelogram3D", mesh);
}

/////////////////////////////////////////////////////////////////////// Shaders

void createShaderPrograms()
{
	ShaderProgram* program = new ShaderProgram();
	program->addShader(GL_VERTEX_SHADER, "Shaders/cube_vs.glsl");
	program->addShader(GL_FRAGMENT_SHADER, "Shaders/cube_fs.glsl");
	program->addAttribute("inPosition", VERTICES);
	program->addAttribute("inTexcoord", TEXCOORDS);
	program->addAttribute("inNormal", NORMALS);
	//program->addUniformBlock("Camera", UBO_BP);
	program->create();
	program->addUniform("Color");
	program->addUniform("ModelMatrix");
	program->addUniform("ViewMatrix");
	program->addUniform("ProjectionMatrix");
	program->addUniform("Texmap");
	program->addUniform("TexMode");
	ShaderProgramManager::instance()->add("stack", program);
}

/////////////////////////////////////////////////////////////////////// Animation positions & rotations
// INITIAL
Vector3D initialPosTriangleR(4.0f * M_UNITE, 0.0f, 4.0f * M_UNITE);
Vector3D initialPosTriangleG(0.0f, 0.0f, 0.0f);
Vector3D initialPosTriangleB(0.0f, 0.0f, 0.0f);
Vector3D initialPosTriangleO(0.0f, 0.0f, 0.0f);
Vector3D initialPosTriangleP(2.0f * M_UNITE, 0.0f, -2.0f * M_UNITE);
Vector3D initialPosCube(0.0f, 0.0f, 0.0f);
Vector3D initialPosParallelogram(-4.0f * M_UNITE, 0.0f, 4.0f * M_UNITE);

Quaternion initialRotTriangleR(180.0f, AXIS3D_Y);
Quaternion initialRotTriangleG(-135.0f, AXIS3D_Y);
Quaternion initialRotTriangleB(45.0f, AXIS3D_Y);
Quaternion initialRotTriangleO(135.0f, AXIS3D_Y);
Quaternion initialRotTriangleP(-45.0f, AXIS3D_Y);
Quaternion initialRotCube(-45.0f, AXIS3D_Y);
Quaternion initialRotParallelogram(-90.0f, AXIS3D_Y);
// FINAL
Vector3D finalPosTriangleR(2.0f , 0.0f, -1.0f);
Vector3D finalPosTriangleG(0.0f, 0.0f, 0.0f);
Vector3D finalPosTriangleB(0.0f, 0.0f, 3.0f);
Vector3D finalPosTriangleO(0.0f, 0.0f, 0.0f);
Vector3D finalPosTriangleP(0.0f, 0.0f, -3.0f);
Vector3D finalPosCube(4.0f * M_UNITE * M_UNITE, 0.0f, 0.0f);
Vector3D finalPosParallelogram(0.0f, 0.0f, 3.0f);

Quaternion finalRotTriangleR(135.0f, AXIS3D_Y);
Quaternion finalRotTriangleG(-180.0f, AXIS3D_Y);
Quaternion finalRotTriangleB(-45.0f, AXIS3D_Y);
Quaternion finalRotTriangleO(90.0f, AXIS3D_Y);
Quaternion finalRotTriangleP(-45.0f, AXIS3D_Y);
Quaternion finalRotCube(-45.0f, AXIS3D_Y);
Quaternion finalRotParallelogram(-135.0f, AXIS3D_Y);
// CURRENT
Vector3D currentPosTriangleR = initialPosTriangleR;
Vector3D currentPosTriangleG = initialPosTriangleG;
Vector3D currentPosTriangleB = initialPosTriangleB;
Vector3D currentPosTriangleO = initialPosTriangleO;
Vector3D currentPosTriangleP = initialPosTriangleP;
Vector3D currentPosCube = initialPosCube;
Vector3D currentPosParallelogram = initialPosParallelogram;

Quaternion currentRotTriangleR = initialRotTriangleR;
Quaternion currentRotTriangleG = initialRotTriangleG;
Quaternion currentRotTriangleB = initialRotTriangleB;
Quaternion currentRotTriangleO = initialRotTriangleO;
Quaternion currentRotTriangleP = initialRotTriangleP;
Quaternion currentRotCube = initialRotCube;
Quaternion currentRotParallelogram = initialRotParallelogram;

/////////////////////////////////////////////////////////////////////// SceneGraph

SceneNode* groundRoot, *triangleR, *triangleG, *triangleB, *triangleO, *triangleP, *cube, *parallelogram;

void createEnvironmentSceneGraph(SceneGraph* scenegraph)
{
	Mesh* mesh;
	Texture* tex;
	
	// Ground
	mesh = MeshManager::instance()->get("cube");
	SceneNode *ground = scenegraph->createNode();
	ground->setMesh(mesh);
	ground->setColor(Vector4D(0.7f, 0.5f, 0.3f, 1.0f));
	ground->setMatrix(translation(0.0f, -0.25f, 0.0f));
	ground->setScale(scale(5.0f, 0.25f, 5.0f));

	mesh = MeshManager::instance()->get("cube2");
	tex = TextureManager::instance()->get("wood");
	cube = scenegraph->createNode();
	cube->setMesh(mesh);
	cube->setTexture(tex);
	cube->setColor(Vector4D(1.0f, 1.0f, 0.0f, 1.0f));

	// Triangles
	//mesh = MeshManager::instance()->get("triangle3D");
	/** /
	// Red triangle
	triangleR = scenegraph->createNode();
	triangleR->setMesh(mesh);
	triangleR->setColor(Vector4D(1.0f, 0.0f, 0.0f, 1.0f));
	triangleR->setMatrix(translation(currentPosTriangleR) * rotation(currentRotTriangleR));
	triangleR->setScale(scale(2.0f * M_UNITE, 0.7f, 2.0f * M_UNITE));
	/** /
	// Green triangle
	triangleG = scenegraph->createNode();
	triangleG->setMesh(mesh);
	triangleG->setColor(Vector4D(0.0f, 1.0f, 0.0f, 1.0f));
	triangleG->setMatrix(translation(currentPosTriangleG) * rotation(currentRotTriangleG));
	triangleG->setScale(scale(2.0f, 0.9f, 2.0f));
	/** /
	// Blue triangle
	triangleB = scenegraph->createNode();
	triangleB->setMesh(mesh);
	triangleB->setColor(Vector4D(0.0f, 0.0f, 1.0f, 1.0f));
	triangleB->setMatrix(translation(currentPosTriangleB) * rotation(currentRotTriangleB));
	triangleB->setScale(scale(1.0f, 0.5f, 1.0f));
	/** /
	// Orange triangle
	triangleO = scenegraph->createNode();
	triangleO->setMesh(mesh);
	triangleO->setColor(Vector4D(1.0f, 0.5f, 0.0f, 1.0f));
	triangleO->setMatrix(translation(currentPosTriangleO) * rotation(currentRotTriangleO));
	triangleO->setScale(scale(2.0f, 0.8f, 2.0f));
	/** /
	// Pink triangle
	triangleP = scenegraph->createNode();
	triangleP->setMesh(mesh);
	triangleP->setColor(Vector4D(1.0f, 0.0f, 0.5f, 1.0f));
	triangleP->setMatrix(translation(currentPosTriangleP) * rotation(currentRotTriangleP));
	triangleP->setScale(scale(1.0f, 0.5f, 1.0f));
	/** /
	// Yellow square
	mesh = MeshManager::instance()->get("cube2");
	cube = scenegraph->createNode();
	cube->setMesh(mesh);
	cube->setColor(Vector4D(1.0f, 1.0f, 0.0f, 1.0f));
	cube->setMatrix(translation(currentPosCube) * rotation(currentRotCube) * translation(1.0f, 0.0f, 1.0f));
	cube->setScale(scale(1.0f, 0.95f, 1.0f));
	/** /
	// Purple parallelogram 
	mesh = MeshManager::instance()->get("parallelogram3D");
	parallelogram = scenegraph->createNode();
	parallelogram->setMesh(mesh);
	parallelogram->setColor(Vector4D(0.5f, 0.0f, 1.0f, 1.0f));
	parallelogram->setMatrix(translation(currentPosParallelogram) * rotation(currentRotParallelogram));
	parallelogram->setScale(scale(1.0f, 0.6f, 1.0f));
	/**/
}

void createScene()
{
	GLint ProjectionMatrix_UId = ShaderProgramManager::instance()->get("stack")->getUniform("ProjectionMatrix");
	GLint ViewMatrix_UId = ShaderProgramManager::instance()->get("stack")->getUniform("ViewMatrix");

	SceneGraph* scenegraph = new SceneGraph();
	scenegraph->setCamera(new Camera(ProjectionMatrix_UId, ViewMatrix_UId));

	scenegraph->getCamera()->setProjectionMatrix(perspectiveMatrix(30.0f, 640.0f / 480.0f, 1.0f, 100.0f));
	scenegraph->getCamera()->setAltProjectionMatrix(orthographicMatrix(-10.0f, 10.0f, -10.0f, 10.0f, 1.0f, 100.0f));

	groundRoot = scenegraph->getRoot();
	groundRoot->setShaderProgram(ShaderProgramManager::instance()->get("stack"));

	createEnvironmentSceneGraph(scenegraph);

	SceneGraphManager::instance()->add("main", scenegraph);
}

void setViewProjectionMatrix()
{
	// View Matrix
	Matrix4D t;
	Matrix4D r;

	if (gimbal_lock_mode) {
		t = translation(0.0f, 0.0f, -Distance);
		r = rotation(pitch, 1.0f, 0.0f, 0.0f) * rotation(yaw, 0, 1.0f, 0.0f);
		SceneGraphManager::instance()->get("main")->getCamera()->setViewMatrix(t * r);
	} else {
		t = translation(0.0f, 0.0f, -Distance);
		r = qGLMatrix(q);
		SceneGraphManager::instance()->get("main")->getCamera()->setViewMatrix(t * r);
	}
}

void drawSceneGraph()
{
	setViewProjectionMatrix();
	groundRoot->setMatrix(translation(Position));
	/*triangleR->setMatrix(translation(currentPosTriangleR) * rotation(currentRotTriangleR));
	triangleG->setMatrix(translation(currentPosTriangleG) * rotation(currentRotTriangleG));
	triangleB->setMatrix(translation(currentPosTriangleB) * rotation(currentRotTriangleB));
	triangleO->setMatrix(translation(currentPosTriangleO) * rotation(currentRotTriangleO));
	triangleP->setMatrix(translation(currentPosTriangleP) * rotation(currentRotTriangleP));
	cube->setMatrix(translation(currentPosCube) * rotation(currentRotCube) * translation(1.0f, 0.0f, 1.0f));
	parallelogram->setMatrix(translation(currentPosParallelogram) * rotation(currentRotParallelogram));*/

	ShaderProgramManager::instance()->get("stack")->BeginShader();
	SceneGraphManager::instance()->get("main")->draw();
	ShaderProgramManager::instance()->get("stack")->EndShader();
}

/////////////////////////////////////////////////////////////////////// Scene

void drawScene()
{
	drawSceneGraph();
	ASSERT_GL_ERROR("ERROR: Could not draw scene.");
}

/////////////////////////////////////////////////////////////////////// Simulation
void updateAnimation()
{
	float vstep = 0.001f * elapsedTime;

	t += animationDirection * vstep;

	if (t > 1.0f) {
		t = 1.0f;
		animationDirection = -1;
		animating = false;
	}
	else if(t < 0.0f) {
		t = 0.0f;
		animationDirection = 1;
		animating = false;
	}

	currentPosTriangleR = vLerp(initialPosTriangleR, finalPosTriangleR, t);
	currentPosTriangleG = vLerp(initialPosTriangleG, finalPosTriangleG, t);
	currentPosTriangleB = vLerp(initialPosTriangleB, finalPosTriangleB, t);
	currentPosTriangleO = vLerp(initialPosTriangleO, finalPosTriangleO, t);
	currentPosTriangleP = vLerp(initialPosTriangleP, finalPosTriangleP, t);
	currentPosCube = vLerp(initialPosCube, finalPosCube, t);
	currentPosParallelogram = vLerp(initialPosParallelogram, finalPosParallelogram, t);

	currentRotTriangleR = qSlerp(initialRotTriangleR, finalRotTriangleR, t);
	currentRotTriangleG = qSlerp(initialRotTriangleG, finalRotTriangleG, t);
	currentRotTriangleB = qSlerp(initialRotTriangleB, finalRotTriangleB, t);
	currentRotTriangleO = qSlerp(initialRotTriangleO, finalRotTriangleO, t);
	currentRotTriangleP = qSlerp(initialRotTriangleP, finalRotTriangleP, t);
	currentRotCube = qSlerp(initialRotCube, finalRotCube, t);
	currentRotParallelogram = qSlerp(initialRotParallelogram, finalRotParallelogram, t);
}

void update() {
	float vstep = 0.002f * elapsedTime;

	if (KeyBuffer::instance()->isKeyDown('w')) Position.z -= vstep;
	if (KeyBuffer::instance()->isKeyDown('s')) Position.z += vstep;
	if (KeyBuffer::instance()->isKeyDown('a')) Position.x -= vstep;
	if (KeyBuffer::instance()->isKeyDown('d')) Position.x += vstep;
	q = qFromAngleAxis(-RotationAngleY, AXIS3D_Y) * qFromAngleAxis(-RotationAngleX, AXIS3D_X) * q;
	RotationAngleX = RotationAngleY = 0.0f;

	if (animating) updateAnimation();
}

/////////////////////////////////////////////////////////////////////// Callbacks

void cleanup()
{
	MeshManager::instance()->destroy();
	ShaderProgramManager::instance()->destroy();
	SceneGraphManager::instance()->destroy();
	TextureManager::instance()->destroy();
}

void display()
{
	++FrameCount;
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
	drawScene();
	glutSwapBuffers();
}

void idle()
{
	int currentTime = glutGet(GLUT_ELAPSED_TIME);
	elapsedTime = currentTime - lastTime;
	lastTime = currentTime;
	update();

	glutPostRedisplay();
}

void keyboard_down(unsigned char key, int x, int y)
{
	KeyBuffer::instance()->pressKey(key);

	switch (key) {

	case 27:
		glutLeaveMainLoop();
	case 'g':
		gimbal_lock_mode = !gimbal_lock_mode;
		break;
	case 'p':
		SceneGraphManager::instance()->get("main")->getCamera()->changeProjectionMode();
		break;
	case 'm':
		if (!animating) animating = true;
		break;
	case 'c':
		printf("Camera Spherical Coordinates (%f, %f, %f)\n", pitch, yaw, Distance);
		qPrint("Quaternion", q);
		break;
	}
}

void keyboard_up(unsigned char key, int x, int y)
{
	KeyBuffer::instance()->releaseKey(key);
}

void mouse(int button, int state, int x, int y)
{
	LastMousePositionX = x;
	LastMousePositionY = y;
	startYaw = yaw;
	startPitch = pitch;
	if (state == GLUT_UP)
		RotationAngleX = RotationAngleY = 0.0f;
}

void mouseMotion(int x, int y)
{
	RotationAngleX = (float)(y - LastMousePositionY) * 0.5f;
	LastMousePositionY = y;
	RotationAngleY = (float)(x - LastMousePositionX) * 0.5f;
	LastMousePositionX = x;

	yaw += RotationAngleY;
	pitch += RotationAngleX;
}

void mouseWheel(int button, int dir, int x, int y)
{
	if (dir > 0) {
		Distance -= DistanceStep;
	}
	else {
		Distance += DistanceStep;
	}
}
void reshape(int w, int h)
{
	WinX = w;
	WinY = h;
	glViewport(0, 0, WinX, WinY);
}

void timer(int value)
{
	std::ostringstream oss;
	oss << CAPTION << ": " << FrameCount << " FPS @ (" << WinX << "x" << WinY << ")";
	std::string s = oss.str();
	glutSetWindow(WindowHandle);
	glutSetWindowTitle(s.c_str());
	FrameCount = 0;
	glutTimerFunc(1000, timer, 0);
}

/////////////////////////////////////////////////////////////////////// Setup

void setupCallbacks()
{
	glutCloseFunc(cleanup);
	glutDisplayFunc(display);
	glutIdleFunc(idle);
	glutKeyboardFunc(keyboard_down);
	glutKeyboardUpFunc(keyboard_up);
	glutMouseFunc(mouse);
	glutMotionFunc(mouseMotion);
	glutMouseWheelFunc(mouseWheel);
	glutReshapeFunc(reshape);

	glutTimerFunc(0, timer, 0);
}

void setupOpenGL() {
	std::cerr << "CONTEXT: OpenGL v" << glGetString(GL_VERSION) << std::endl;
	glClearColor(0.1f, 0.1f, 0.1f, 1.0f);
	glEnable(GL_DEPTH_TEST);
	glDepthFunc(GL_LEQUAL);
	glDepthMask(GL_TRUE);
	glDepthRange(0.0, 1.0);
	glClearDepth(1.0);
	glEnable(GL_CULL_FACE);
	glCullFace(GL_BACK);
	glFrontFace(GL_CCW);
}

void setupGLEW() {
	glewExperimental = GL_TRUE;
	GLenum result = glewInit();
	if (result != GLEW_OK) {
		std::cerr << "ERROR glewInit: " << glewGetString(result) << std::endl;
		exit(EXIT_FAILURE);
	}
	GLenum err_code = glGetError();
}

void setupGLUT(int argc, char* argv[])
{
	glutInit(&argc, argv);

	glutInitContextVersion(3, 3);
	glutInitContextFlags(GLUT_FORWARD_COMPATIBLE);
	glutInitContextProfile(GLUT_CORE_PROFILE);

	glutSetOption(GLUT_ACTION_ON_WINDOW_CLOSE, GLUT_ACTION_GLUTMAINLOOP_RETURNS);

	glutInitWindowSize(WinX, WinY);
	glutInitDisplayMode(GLUT_DEPTH | GLUT_DOUBLE | GLUT_RGBA);
	WindowHandle = glutCreateWindow(CAPTION);
	if (WindowHandle < 1) {
		std::cerr << "ERROR: Could not create a new rendering window." << std::endl;
		exit(EXIT_FAILURE);
	}
}

void init(int argc, char* argv[])
{
	setupGLUT(argc, argv);
	setupGLEW();
	setupOpenGL();
	setupCallbacks();

	ASSERT_GL_ERROR("ERROR: General setup.");
		createMeshes();
	ASSERT_GL_ERROR("ERROR: Mesh creation.");
		createTextures();
	ASSERT_GL_ERROR("ERROR: Texture creation.");
		createShaderPrograms();
	ASSERT_GL_ERROR("ERROR: Shader creation.");
		createScene();
	ASSERT_GL_ERROR("ERROR: Scene creation.");
}

int main(int argc, char* argv[])
{
	init(argc, argv);
	glutMainLoop();
	exit(EXIT_SUCCESS);
}

///////////////////////////////////////////////////////////////////////
