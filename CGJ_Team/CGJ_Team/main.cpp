///////////////////////////////////////////////////////////////////////
//
// TANKS - TEAM ASSIGNMENT 1
//
///////////////////////////////////////////////////////////////////////

#include "engine.h"
#include "Tank.h"
#include "BulletManager.h"
#include "HUD.h"
#include "Explosion.h"
#include "Sandtrail.h"
#include "SceneGraph.h"
#include "StaticObject.h"
// Managersdddo
#include "MeshManager.h"
#include "MaterialManager.h"
#include "TextureManager.h"
#include "ShaderProgramManager.h"
#include "SceneGraphManager.h"
#include "ParticleSystemManager.h"
//using namespace engine;

#define ASSERT_GL_ERROR(string) checkOpenGLError(string)

#define CAPTION "Modern OpenGL Engine"
int WinX = 640, WinY = 480;
int WindowHandle = 0;
unsigned int FrameCount = 0;

GLuint UBO_BP = 0, UBO_BP1 = 1, UBO_BP2 = 2;

const float DistanceStep = 1.5f;
float Distance = 45.0f;

int LastMousePositionX, LastMousePositionY;
float RotationAngleY = 45.0f;
float RotationAngleX = 30.0f;
float yaw = 45.0f, pitch = 30.0f;
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

bool gameOver = false;

// Tank class to encapsulate behaviour
Tank* tankObject;
Tank* tankObject2;
std::vector<StaticObject*> props;
BulletManager * bulletManager;
BulletManager * bulletManager2;
HUD* p1HUD;
HUD* p2HUD;
Explosion * explosion;
Sandtrail * sandtrail;

/////////////////////////////////////////////////////////////////////// Textures

void createTextures()
{
	Texture* texture;

	texture = new Texture("Textures/desert.jpg");
	TextureManager::instance()->add("desert", texture);
	
	texture = new Texture("Textures/particle.tga");
	TextureManager::instance()->add("particle", texture);

	texture = new Texture("Textures/greenMetal.tga");
	TextureManager::instance()->add("greenMetal", texture);

	texture = new Texture("Textures/redMetal.tga");
	TextureManager::instance()->add("redMetal", texture);

	texture = new Texture("Textures/winScreen_1.tga");
	TextureManager::instance()->add("winScreen_1", texture);

	texture = new Texture("Textures/winScreen_2.tga");
	TextureManager::instance()->add("winScreen_2", texture);
}

/////////////////////////////////////////////////////////////////////// Materials

void createMaterials()
{
	Material* material;
	material = new Material("Models/Tank/TankColour.mtl");
	MaterialManager::instance()->add(material->MaterialName(), material);

	material = new Material("Models/Tank/TankColour2.mtl");
	MaterialManager::instance()->add(material->MaterialName(), material);

	material = new Material("Models/Tank/TankGrey.mtl");
	MaterialManager::instance()->add(material->MaterialName(), material);

	material = new Material("Models/Tank/TankLights.mtl");
	MaterialManager::instance()->add(material->MaterialName(), material);

	material = new Material("Models/Bullet.mtl");
	MaterialManager::instance()->add(material->MaterialName(), material);

	material = new Material("Models/Ground.mtl");
	MaterialManager::instance()->add(material->MaterialName(), material);

	material = new Material("Models/Environment/YellowDark.mtl");
	MaterialManager::instance()->add(material->MaterialName(), material);

	material = new Material("Models/Environment/YellowLight.mtl");
	MaterialManager::instance()->add(material->MaterialName(), material);

	material = new Material("Models/Environment/Green.mtl");
	MaterialManager::instance()->add(material->MaterialName(), material);

	material = new Material("Models/Environment/TankGrey.mtl");
	MaterialManager::instance()->add(material->MaterialName(), material);

}

/////////////////////////////////////////////////////////////////////// Meshes

void createMeshes()
{
	Mesh* mesh;
	mesh = new Mesh("Models/cube_vtn.obj");
	mesh->create();
	MeshManager::instance()->add("cube", mesh);

	mesh = new Mesh("Models/Tank/TankBackWheelLeft.obj");
	mesh->create();
	MeshManager::instance()->add("TankBackWheelLeft", mesh);

	mesh = new Mesh("Models/Tank/TankBackWheelRight.obj");
	mesh->create();
	MeshManager::instance()->add("TankBackWheelRight", mesh);

	mesh = new Mesh("Models/Tank/TankCaterpillarLeft.obj");
	mesh->create();
	MeshManager::instance()->add("TankCaterpillarLeft", mesh);

	mesh = new Mesh("Models/Tank/TankCaterpillarRight.obj");
	mesh->create();
	MeshManager::instance()->add("TankCaterpillarRight", mesh);

	mesh = new Mesh("Models/Tank/TankChassis.obj");
	mesh->create();
	MeshManager::instance()->add("TankChassis", mesh);

	mesh = new Mesh("Models/Tank/TankFrontWheelLeft.obj");
	mesh->create();
	MeshManager::instance()->add("TankFrontWheelLeft", mesh);

	mesh = new Mesh("Models/Tank/TankFrontWheelRight.obj");
	mesh->create();
	MeshManager::instance()->add("TankFrontWheelRight", mesh);

	mesh = new Mesh("Models/Tank/TankLights.obj");
	mesh->create();
	MeshManager::instance()->add("TankLights", mesh);

	mesh = new Mesh("Models/Tank/TankProps.obj");
	mesh->create();
	MeshManager::instance()->add("TankProps", mesh);

	mesh = new Mesh("Models/Tank/TankAntenna.obj");
	mesh->create();
	MeshManager::instance()->add("TankAntenna", mesh);

	mesh = new Mesh("Models/Tank/TankTurret.obj");
	mesh->create();
	MeshManager::instance()->add("TankTurret", mesh);

	mesh = new Mesh("Models/Bullet.obj");
	mesh->create();
	MeshManager::instance()->add("Bullet", mesh);

	mesh = new Mesh("Models/quad.obj");
	mesh->create();
	MeshManager::instance()->add("quad", mesh);

	mesh = new Mesh("Models/Environment/terrain.obj");
	mesh->create();
	MeshManager::instance()->add("terrain", mesh);

	mesh = new Mesh("Models/Environment/cliff.obj");
	mesh->create();
	MeshManager::instance()->add("cliff", mesh);

	mesh = new Mesh("Models/Environment/busted_tank.obj");
	mesh->create();
	MeshManager::instance()->add("busted_tank", mesh);

	mesh = new Mesh("Models/Environment/cactus.obj");
	mesh->create();
	MeshManager::instance()->add("cactus", mesh);

	mesh = new Mesh("Models/Environment/rocks1.obj");
	mesh->create();
	MeshManager::instance()->add("rocks1", mesh);

	mesh = new Mesh("Models/Environment/rocks2.obj");
	mesh->create();
	MeshManager::instance()->add("rocks2", mesh);

	mesh = new Mesh("Models/Environment/rocks3.obj");
	mesh->create();
	MeshManager::instance()->add("rocks3", mesh);
}

/////////////////////////////////////////////////////////////////////// Shaders

void createShaderPrograms()
{
	ShaderProgram* program;
	// Main simple shader
	program = new ShaderProgram();
	program->addShader(GL_VERTEX_SHADER, "Shaders/cube_vs.glsl");
	program->addShader(GL_FRAGMENT_SHADER, "Shaders/cube_fs.glsl");
	program->addAttribute("inPosition", VERTICES);
	program->addAttribute("inTexcoord", TEXCOORDS);
	program->addAttribute("inNormal", NORMALS);
	program->create();
	program->addUniform("ModelMatrix");
	program->addUniform("NormalMatrix");
	program->addUniform("DiffuseReflectivity");
	program->addUniform("SpecularReflectivity");
	program->addUniform("SpecularExponent");
	program->addUniform("Texmap");
	program->addUniform("TexMode");
	program->addUniformBlock("Camera", UBO_BP);
	program->addUniformBlock("DirectionalLight", UBO_BP1);
	ShaderProgramManager::instance()->add("Basic", program);
	// Tank shader
	program = new ShaderProgram();
	program->addShader(GL_VERTEX_SHADER, "Shaders/tank_vs.glsl");
	program->addShader(GL_FRAGMENT_SHADER, "Shaders/tank_fs.glsl");
	program->addAttribute("inPosition", VERTICES);
	program->addAttribute("inTexcoord", TEXCOORDS);
	program->addAttribute("inNormal", NORMALS);
	program->create();
	program->addUniform("ModelMatrix");
	program->addUniform("NormalMatrix");
	program->addUniform("DiffuseReflectivity");
	program->addUniform("SpecularReflectivity");
	program->addUniform("SpecularExponent");
	program->addUniform("Texmap");
	program->addUniform("TexMode");
	program->addUniformBlock("Camera", UBO_BP);
	program->addUniformBlock("DirectionalLight", UBO_BP1);
	ShaderProgramManager::instance()->add("tank", program);
	// HUD shader
	program = new ShaderProgram();
	program->addShader(GL_VERTEX_SHADER, "Shaders/hud_vs.glsl");
	program->addShader(GL_FRAGMENT_SHADER, "Shaders/hud_fs.glsl");
	program->addAttribute("inPosition", VERTICES);
	program->addAttribute("inTexcoord", TEXCOORDS);
	program->create();
	program->addUniform("ModelMatrix");
	program->addUniform("Texmap");
	program->addUniform("TexMode");
	program->addUniformBlock("Camera", UBO_BP2);
	ShaderProgramManager::instance()->add("HUD", program);
	// Explosion particles
	program = new ShaderProgram();
	program->addShader(GL_VERTEX_SHADER, "Shaders/explosion_vs.glsl");
	program->addShader(GL_FRAGMENT_SHADER, "Shaders/explosion_fs.glsl");
	program->addAttribute("inPosition", VERTICES);
	program->addAttribute("inTexcoord", TEXCOORDS);
	program->addAttribute("inNormal", NORMALS);
	program->create();
	program->addUniform("ModelMatrix");
	program->addUniform("Texmap");
	program->addUniform("TexMode");
	program->addUniform("Life");
	program->addUniformBlock("Camera", UBO_BP);
	ShaderProgramManager::instance()->add("explosion", program);
	// Sand trail particles
	program = new ShaderProgram();
	program->addShader(GL_VERTEX_SHADER, "Shaders/sandtrail_vs.glsl");
	program->addShader(GL_FRAGMENT_SHADER, "Shaders/sandtrail_fs.glsl");
	program->addAttribute("inPosition", VERTICES);
	program->addAttribute("inTexcoord", TEXCOORDS);
	program->addAttribute("inNormal", NORMALS);
	program->create();
	program->addUniform("ModelMatrix");
	program->addUniform("Texmap");
	program->addUniform("TexMode");
	program->addUniform("Life");
	program->addUniformBlock("Camera", UBO_BP);
	ShaderProgramManager::instance()->add("sandtrail", program);
	// Silhouette shader
	program = new ShaderProgram();
	program->addShader(GL_VERTEX_SHADER, "Shaders/silhouette_vs.glsl");
	program->addShader(GL_FRAGMENT_SHADER, "Shaders/silhouette_fs.glsl");
	program->addAttribute("inPosition", VERTICES);
	program->addAttribute("inTexcoord", TEXCOORDS);
	program->addAttribute("inNormal", NORMALS);
	program->create();
	program->addUniform("ModelMatrix");
	program->addUniformBlock("Camera", UBO_BP);
	ShaderProgramManager::instance()->add("silhouette", program);
}

/////////////////////////////////////////////////////////////////////// SceneGraph

SceneNode *tankBase, *tankAntenna, *frontLeftWheel, *frontRightWheel, *backLeftWheel, *backRightWheel, *tankTurret;
SceneNode *tankBase2, *tankAntenna2, *frontLeftWheel2, *frontRightWheel2, *backLeftWheel2, *backRightWheel2, *tankTurret2;

void createTankSceneGraph(SceneGraph* scenegraph)
{
	Mesh* mesh;
	Material* mat;
	//Texture* tex;

	// Tank
	// Main Color material
	ShaderProgram* shader = ShaderProgramManager::instance()->get("tank");
	mesh = MeshManager::instance()->get("TankChassis");
	mat = MaterialManager::instance()->get("TankColour");
	tankBase = scenegraph->createNode();
	tankBase->setMesh(mesh);
	tankBase->setMaterial(mat);
	tankBase->setShaderProgram(shader);

	mesh = MeshManager::instance()->get("TankBackWheelLeft");
	backLeftWheel = tankBase->createNode();
	backLeftWheel->setMesh(mesh);
	backLeftWheel->setMaterial(mat);

	mesh = MeshManager::instance()->get("TankBackWheelRight");
	backRightWheel = tankBase->createNode();
	backRightWheel->setMesh(mesh);
	backRightWheel->setMaterial(mat);

	mesh = MeshManager::instance()->get("TankFrontWheelLeft");
	frontLeftWheel = tankBase->createNode();
	frontLeftWheel->setMesh(mesh);
	frontLeftWheel->setMaterial(mat);

	mesh = MeshManager::instance()->get("TankFrontWheelRight");
	frontRightWheel = tankBase->createNode();
	frontRightWheel->setMesh(mesh);
	frontRightWheel->setMaterial(mat);

	mesh = MeshManager::instance()->get("TankTurret");
	tankTurret = tankBase->createNode();
	tankTurret->setMesh(mesh);
	tankTurret->setMaterial(mat);

	// Grey material
	mat = MaterialManager::instance()->get("TankGrey");
	mesh = MeshManager::instance()->get("TankCaterpillarLeft");
	SceneNode* othersTank = tankBase->createNode();
	othersTank->setMesh(mesh);
	othersTank->setMaterial(mat);

	mesh = MeshManager::instance()->get("TankCaterpillarRight");
	othersTank = tankBase->createNode();
	othersTank->setMesh(mesh);
	othersTank->setMaterial(mat);

	mesh = MeshManager::instance()->get("TankProps");
	othersTank = tankBase->createNode();
	othersTank->setMesh(mesh);
	othersTank->setMaterial(mat);

	mesh = MeshManager::instance()->get("TankAntenna");
	tankAntenna = tankBase->createNode();
	tankAntenna->setMesh(mesh);
	tankAntenna->setMaterial(mat);
	
	// Lights material
	mat = MaterialManager::instance()->get("TankLights");
	mesh = MeshManager::instance()->get("TankLights");
	othersTank = tankBase->createNode();
	othersTank->setMesh(mesh);
	othersTank->setMaterial(mat);

	// Tank 2
	// Main Color material
	mesh = MeshManager::instance()->get("TankChassis");
	mat = MaterialManager::instance()->get("TankColour2");
	tankBase2 = scenegraph->createNode();
	tankBase2->setMesh(mesh);
	tankBase2->setMaterial(mat);
	tankBase2->setShaderProgram(shader);

	mesh = MeshManager::instance()->get("TankBackWheelLeft");
	backLeftWheel2 = tankBase2->createNode();
	backLeftWheel2->setMesh(mesh);
	backLeftWheel2->setMaterial(mat);

	mesh = MeshManager::instance()->get("TankBackWheelRight");
	backRightWheel2 = tankBase2->createNode();
	backRightWheel2->setMesh(mesh);
	backRightWheel2->setMaterial(mat);

	mesh = MeshManager::instance()->get("TankFrontWheelLeft");
	frontLeftWheel2 = tankBase2->createNode();
	frontLeftWheel2->setMesh(mesh);
	frontLeftWheel2->setMaterial(mat);

	mesh = MeshManager::instance()->get("TankFrontWheelRight");
	frontRightWheel2 = tankBase2->createNode();
	frontRightWheel2->setMesh(mesh);
	frontRightWheel2->setMaterial(mat);

	mesh = MeshManager::instance()->get("TankTurret");
	tankTurret2 = tankBase2->createNode();
	tankTurret2->setMesh(mesh);
	tankTurret2->setMaterial(mat);

	// Grey material
	mat = MaterialManager::instance()->get("TankGrey");
	mesh = MeshManager::instance()->get("TankCaterpillarLeft");
	SceneNode* othersTank2 = tankBase2->createNode();
	othersTank2->setMesh(mesh);
	othersTank2->setMaterial(mat);

	mesh = MeshManager::instance()->get("TankCaterpillarRight");
	othersTank2 = tankBase2->createNode();
	othersTank2->setMesh(mesh);
	othersTank2->setMaterial(mat);

	mesh = MeshManager::instance()->get("TankProps");
	othersTank2 = tankBase2->createNode();
	othersTank2->setMesh(mesh);
	othersTank2->setMaterial(mat);

	mesh = MeshManager::instance()->get("TankAntenna");
	tankAntenna2 = tankBase2->createNode();
	tankAntenna2->setMesh(mesh);
	tankAntenna2->setMaterial(mat);

	// Lights material
	mat = MaterialManager::instance()->get("TankLights");
	mesh = MeshManager::instance()->get("TankLights");
	othersTank2 = tankBase2->createNode();
	othersTank2->setMesh(mesh);
	othersTank2->setMaterial(mat);

	// Bullet Managers
	bulletManager = new BulletManager(scenegraph->getRoot(), 5);
	bulletManager2 = new BulletManager(scenegraph->getRoot(), 5);

	tankObject = new Tank(tankBase, tankTurret, tankAntenna, bulletManager, 1);
	tankObject2 = new Tank(tankBase2, tankTurret2, tankAntenna2, bulletManager2, 2);
}

void createEnvironmentSceneGraph(SceneGraph* scenegraph)
{
	Mesh* mesh;
	Texture* tex;
	Material* mat;
	
	// Ground
	mesh = MeshManager::instance()->get("terrain");
	tex = TextureManager::instance()->get("desert");
	mat = MaterialManager::instance()->get("Ground");

	SceneNode *ground = scenegraph->createNode();
	ground->setMesh(mesh);
	ground->setTexture(tex);
	ground->setMaterial(mat);
	//ground->setMatrix(translation(0.0f, -0.1f, 0.0f));
	ground->setScale(scale(0.6f, 1.0f, 0.6f));

	SceneNode *cliff = scenegraph->createNode();
	cliff->setMesh(MeshManager::instance()->get("cliff"));
	cliff->setMaterial(MaterialManager::instance()->get("YellowDark"));
	cliff->setScale(scale(0.6f, 0.6f, 0.6f));

	cliff = scenegraph->createNode();
	cliff->setMesh(MeshManager::instance()->get("cliff"));
	cliff->setMaterial(MaterialManager::instance()->get("YellowDark"));
	cliff->setMatrix(rotation(90.0f, AXIS3D_Y));
	cliff->setScale(scale(0.6f, 0.6f, 0.6f));

	cliff = scenegraph->createNode();
	cliff->setMesh(MeshManager::instance()->get("cliff"));
	cliff->setMaterial(MaterialManager::instance()->get("YellowDark"));
	cliff->setMatrix(rotation(180.0f, AXIS3D_Y));
	cliff->setScale(scale(0.6f, 0.6f, 0.6f));

	cliff = scenegraph->createNode();
	cliff->setMesh(MeshManager::instance()->get("cliff"));
	cliff->setMaterial(MaterialManager::instance()->get("YellowDark"));
	cliff->setMatrix(rotation(270.0f, AXIS3D_Y));
	cliff->setScale(scale(0.6f, 0.6f, 0.6f));

	Vector3D position = Vector3D(9.0f, 0.0f, -7.0f);
	SceneNode *p = scenegraph->createNode();
	p->setMesh(MeshManager::instance()->get("cactus"));
	p->setMaterial(MaterialManager::instance()->get("TankColour"));
	p->setMatrix(translation(position));
	props.push_back(new StaticObject(position, -1.0f, 1.0, 0.0f, 2.0f, -1.0f, 1.0f)); //Cactus

	position = Vector3D(-17.0f, 0.0f, -19.0f);
	p = scenegraph->createNode();
	p->setMesh(MeshManager::instance()->get("cactus"));
	p->setMaterial(MaterialManager::instance()->get("TankColour"));
	p->setMatrix(translation(position));
	props.push_back(new StaticObject(position, -1.0f, 1.0, 0.0f, 2.0f, -1.0f, 1.0f)); //Cactus

	position = Vector3D(-21.0f, 0.0f, -9.0f);
	p = scenegraph->createNode();
	p->setMesh(MeshManager::instance()->get("cactus"));
	p->setMaterial(MaterialManager::instance()->get("TankColour"));
	p->setMatrix(translation(position));
	props.push_back(new StaticObject(position, -1.0f, 1.0, 0.0f, 2.0f, -1.0f, 1.0f)); //Cactus

	position = Vector3D(-13.0f, 0.0f, 0.0f);
	p = scenegraph->createNode();
	p->setMesh(MeshManager::instance()->get("cactus"));
	p->setMaterial(MaterialManager::instance()->get("TankColour"));
	p->setMatrix(translation(position));
	props.push_back(new StaticObject(position, -1.0f, 1.0, 0.0f, 2.0f, -1.0f, 1.0f)); //Cactus

	position = Vector3D(-8.0f, 0.0f, 6.0f);
	p = scenegraph->createNode();
	p->setMesh(MeshManager::instance()->get("cactus"));
	p->setMaterial(MaterialManager::instance()->get("TankColour"));
	p->setMatrix(translation(position));
	props.push_back(new StaticObject(position, -1.0f, 1.0, 0.0f, 2.0f, -1.0f, 1.0f)); //Cactus

	position = Vector3D(17.0f, 0.0f, 18.0f);
	p = scenegraph->createNode();
	p->setMesh(MeshManager::instance()->get("cactus"));
	p->setMaterial(MaterialManager::instance()->get("TankColour"));
	p->setMatrix(translation(position));
	props.push_back(new StaticObject(position, -1.0f, 1.0, 0.0f, 2.0f, -1.0f, 1.0f)); //Cactus

	position = Vector3D(12.0f, 0.0f, -20.0f);
	p = scenegraph->createNode();
	p->setMesh(MeshManager::instance()->get("cactus"));
	p->setMaterial(MaterialManager::instance()->get("TankColour"));
	p->setMatrix(translation(position));
	props.push_back(new StaticObject(position, -1.0f, 1.0, 0.0f, 2.0f, -1.0f, 1.0f)); //Cactus

	position = Vector3D(-6.0f, 0.0f, -22.0f);
	p = scenegraph->createNode();
	p->setMesh(MeshManager::instance()->get("rocks1"));
	p->setMaterial(MaterialManager::instance()->get("YellowDark"));
	p->setMatrix(translation(position));
	props.push_back(new StaticObject(position, -2.6f, 2.6f, 0.0f, 6.0f, -3.0f, 3.0f)); //Rocks 01

	position = Vector3D(6.0f, 0.0f, -16.0f);
	p = scenegraph->createNode();
	p->setMesh(MeshManager::instance()->get("rocks1"));
	p->setMaterial(MaterialManager::instance()->get("YellowDark"));
	p->setMatrix(translation(position));
	props.push_back(new StaticObject(position, -2.6f, 2.6f, 0.0f, 6.0f, -3.0f, 3.0f)); //Rocks 01

	position = Vector3D(-19.0f, 0.0f, 14.0f);
	p = scenegraph->createNode();
	p->setMesh(MeshManager::instance()->get("rocks2"));
	p->setMaterial(MaterialManager::instance()->get("YellowDark"));
	p->setMatrix(translation(position));
	props.push_back(new StaticObject(position, -2.5f, 1.5f, 0.0f, 6.0f, -1.7f, 1.7f)); //Rocks 02

	position = Vector3D(-10.0f, 0.0f, 21.0f);
	p = scenegraph->createNode();
	p->setMesh(MeshManager::instance()->get("rocks2"));
	p->setMaterial(MaterialManager::instance()->get("YellowDark"));
	p->setMatrix(translation(position));
	props.push_back(new StaticObject(position, -2.5f, 1.5f, 0.0f, 6.0f, -1.7f, 1.7f)); //Rocks 02

	position = Vector3D(5.0f, 0.0f, 12.0f);
	p = scenegraph->createNode();
	p->setMesh(MeshManager::instance()->get("rocks3"));
	p->setMaterial(MaterialManager::instance()->get("YellowDark"));
	p->setMatrix(translation(position));
	props.push_back(new StaticObject(position, -2.2f, 2.1f, 0.0f, 1.0f, -3.5f, 2.3f)); //Rocks 03

	position = Vector3D(19.0f, 0.0f, 6.0f);
	p = scenegraph->createNode();
	p->setMesh(MeshManager::instance()->get("busted_tank"));
	p->setMaterial(MaterialManager::instance()->get("TankGrey"));
	p->setMatrix(translation(position));
	props.push_back(new StaticObject(position, -1.2f, 2.5f, 0.0f, 3.0f, -1.0f, 1.0f)); //BustedTank
}

SceneNode *p1_HUDBar_1, *p1_HUDBar_2, *p1_HUDBar_3, *p2_HUDBar_1, *p2_HUDBar_2, *p2_HUDBar_3;
SceneNode *p1_Win, *p2_Win;

void createHUDSceneGraph(SceneGraph* scenegraph)
{
	Mesh* mesh;
	Texture* tex;

	mesh = MeshManager::instance()->get("cube");
	tex = TextureManager::instance()->get("greenMetal");

	p1_HUDBar_1 = scenegraph->createNode();
	p1_HUDBar_1->setMesh(mesh);
	p1_HUDBar_1->setTexture(tex);
	p1_HUDBar_1->setMatrix(translation(30.0f, 15.0f, -1.0f) * rotation(90.0f, 1.0f, 0.0f, 0.0f));
	p1_HUDBar_1->setScale(scale(25.0f, 0.1f, 10.0f));
	p1_HUDBar_1->setUI();

	p1_HUDBar_2 = scenegraph->createNode();
	p1_HUDBar_2->setMesh(mesh);
	p1_HUDBar_2->setTexture(tex);
	p1_HUDBar_2->setMatrix(translation(90.0f, 15.0f, -1.0f) * rotation(90.0f, 1.0f, 0.0f, 0.0f));
	p1_HUDBar_2->setScale(scale(25.0f, 0.1f, 10.0f));
	p1_HUDBar_2->setUI();

	p1_HUDBar_3 = scenegraph->createNode();
	p1_HUDBar_3->setMesh(mesh);
	p1_HUDBar_3->setTexture(tex);
	p1_HUDBar_3->setMatrix(translation(150.0f, 15.0f, -1.0f) * rotation(90.0f, 1.0f, 0.0f, 0.0f));
	p1_HUDBar_3->setScale(scale(25.0f, 0.1f, 10.0f));
	p1_HUDBar_3->setUI();

	tex = TextureManager::instance()->get("redMetal");

	p2_HUDBar_1 = scenegraph->createNode();
	p2_HUDBar_1->setMesh(mesh);
	p2_HUDBar_1->setTexture(tex);
	p2_HUDBar_1->setMatrix(translation(610.0f, 15.0f, -1.0f) * rotation(90.0f, 1.0f, 0.0f, 0.0f));
	p2_HUDBar_1->setScale(scale(25.0f, 0.1f, 10.0f));
	p2_HUDBar_1->setUI();

	p2_HUDBar_2 = scenegraph->createNode();
	p2_HUDBar_2->setMesh(mesh);
	p2_HUDBar_2->setTexture(tex);
	p2_HUDBar_2->setMatrix(translation(550.0f, 15.0f, -1.0f) * rotation(90.0f, 1.0f, 0.0f, 0.0f));
	p2_HUDBar_2->setScale(scale(25.0f, 0.1f, 10.0f));
	p2_HUDBar_2->setUI();

	p2_HUDBar_3 = scenegraph->createNode();
	p2_HUDBar_3->setMesh(mesh);
	p2_HUDBar_3->setTexture(tex);
	p2_HUDBar_3->setMatrix(translation(490.0f, 15.0f, -1.0f) * rotation(90.0f, 1.0f, 0.0f, 0.0f));
	p2_HUDBar_3->setScale(scale(25.0f, 0.1f, 10.0f));
	p2_HUDBar_3->setUI();

	p1HUD = new HUD(p1_HUDBar_1, p1_HUDBar_2, p1_HUDBar_3, tankObject);
	p2HUD = new HUD(p2_HUDBar_1, p2_HUDBar_2, p2_HUDBar_3, tankObject2);


	tex = TextureManager::instance()->get("winScreen_1");

	p1_Win = scenegraph->createNode();
	p1_Win->setMesh(mesh);
	p1_Win->setTexture(tex);
	p1_Win->setMatrix(translation(320.0f, 240.0f, 0.0f) * rotation(90.0f, 1.0f, 0.0f, 0.0f));
	p1_Win->setScale(scale(320.0f, 0.1f, 240.0f));
	p1_Win->setVisible(false);
	p1_Win->setUI();

	tex = TextureManager::instance()->get("winScreen_2");

	p2_Win = scenegraph->createNode();
	p2_Win->setMesh(mesh);
	p2_Win->setTexture(tex);
	p2_Win->setMatrix(translation(320.0f, 240.0f, 0.0f) * rotation(90.0f, 1.0f, 0.0f, 0.0f));
	p2_Win->setScale(scale(320.0f, 0.1f, 240.0f));
	p2_Win->setVisible(false);
	p2_Win->setUI();
}

void createParticlesEffectsSceneGraph(SceneGraph* scenegraph)
{
	Mesh* mesh = MeshManager::instance()->get("quad");
	Texture* tex = TextureManager::instance()->get("particle");
	ShaderProgram* shader = ShaderProgramManager::instance()->get("explosion");

	int particleCount;

	//Explosions
	particleCount = 250;
	ParticleSceneNode* explosionNode = new ParticleSceneNode();
	explosionNode->setMesh(mesh);
	explosionNode->setTexture(tex);
	explosionNode->setShaderProgram(shader);
	explosionNode->setScale(scale(0.5f, 0.5f, 0.5f));

	// Explosion 1
	scenegraph->getRoot()->addNode(explosionNode);
	explosion = new Explosion(explosionNode, particleCount);
	ParticleSystemManager::instance()->add("Explosion", explosion);
	// Explosion 2
	Explosion* explosion2;
	explosionNode = explosionNode->copyNode();
	scenegraph->getRoot()->addNode(explosionNode);
	explosion2 = new Explosion(explosionNode, particleCount);
	ParticleSystemManager::instance()->add("Explosion", explosion2);
	// Explosion 3
	explosionNode = explosionNode->copyNode();
	scenegraph->getRoot()->addNode(explosionNode);
	explosion2 = new Explosion(explosionNode, particleCount);
	ParticleSystemManager::instance()->add("Explosion", explosion2);
	// Explosion 4
	explosionNode = explosionNode->copyNode();
	scenegraph->getRoot()->addNode(explosionNode);
	explosion2 = new Explosion(explosionNode, particleCount);
	ParticleSystemManager::instance()->add("Explosion", explosion2);
	// Explosion 5
	explosionNode = explosionNode->copyNode();
	scenegraph->getRoot()->addNode(explosionNode);
	explosion2 = new Explosion(explosionNode, particleCount);
	ParticleSystemManager::instance()->add("Explosion", explosion2);
	// Explosion 6
	explosionNode = explosionNode->copyNode();
	scenegraph->getRoot()->addNode(explosionNode);
	explosion2 = new Explosion(explosionNode, particleCount);
	ParticleSystemManager::instance()->add("Explosion", explosion2);

	// Sandtrails
	particleCount = 50;
	shader = ShaderProgramManager::instance()->get("sandtrail");
	ParticleSceneNode* sandtrailNode = explosionNode->copyNode();
	sandtrailNode->setShaderProgram(shader);
	sandtrailNode->setScale(scale(0.25f, 0.25f, 0.25f));
	//Sandtrail* sandtrail;

	// Sandtrail 1
	scenegraph->getRoot()->addNode(sandtrailNode);
	sandtrail = new Sandtrail(sandtrailNode, particleCount);
	ParticleSystemManager::instance()->add("Sandtrail", sandtrail);
	// Sandtrail 2
	sandtrailNode = sandtrailNode->copyNode();
	scenegraph->getRoot()->addNode(sandtrailNode);
	Sandtrail* sandtrail2 = new Sandtrail(sandtrailNode, particleCount);
	ParticleSystemManager::instance()->add("Sandtrail", sandtrail2);

	tankObject->setTrails(sandtrail, sandtrail2);
	tankObject2->setTrails(sandtrail, sandtrail2);
}

void createScene()
{
	SceneGraph* scenegraph = new SceneGraph();
	scenegraph->setCamera(new Camera(UBO_BP));

	scenegraph->getCamera()->setProjectionMatrix(perspectiveMatrix(30.0f, 640.0f / 480.0f, 1.0f, 500.0f));
	scenegraph->getCamera()->setAltProjectionMatrix(orthographicMatrix(-10.0f, 10.0f, -10.0f, 10.0f, 1.0f, 100.0f));

	//scenegraph->setLight(new DirectionalLight(Vector3D(1.0f, 0.6f, 0.25f), Vector3D(0.8f, 0.47f, 0.18f), UBO_BP1));
	scenegraph->setLight(new DirectionalLight(Vector3D(1.0f, 0.6f, 0.25f), Vector3D(0.94f, 0.78f, 0.27f), UBO_BP1));

	SceneNode* groundRoot = scenegraph->getRoot();
	groundRoot->setShaderProgram(ShaderProgramManager::instance()->get("Basic"));

	createEnvironmentSceneGraph(scenegraph);
	createTankSceneGraph(scenegraph);
	createParticlesEffectsSceneGraph(scenegraph);

	SceneGraphManager::instance()->add("main", scenegraph);


	SceneGraph* HUDScenegraph = new SceneGraph();
	HUDScenegraph->setCamera(new Camera(UBO_BP2));

	int vp[4];
	glGetIntegerv(GL_VIEWPORT, vp);
	HUDScenegraph->getCamera()->setProjectionMatrix(orthographicMatrix(0.0f, vp[2], vp[3], 0.0f, -100.0f, 100.0f));
	HUDScenegraph->getCamera()->setViewMatrix(identity());

	SceneNode* HUDRoot = HUDScenegraph->getRoot();
	HUDRoot->setShaderProgram(ShaderProgramManager::instance()->get("HUD"));

	createHUDSceneGraph(HUDScenegraph);
	SceneGraphManager::instance()->add("HUD", HUDScenegraph);
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
	tankObject->move();
	tankObject2->move();
	bulletManager->move();
	bulletManager2->move();
	ParticleSystemManager::instance()->move();
	SceneGraphManager::instance()->get("main")->draw();

	p1HUD->update();
	p2HUD->update();
	SceneGraphManager::instance()->get("HUD")->draw();
}

/////////////////////////////////////////////////////////////////////// Scene

void drawScene()
{
	if (tankObject->getLife() == 0) {
		gameOver = true;
		p2_Win->setVisible(true);
	}
	if (tankObject2->getLife() == 0) {
		gameOver = true;
		p1_Win->setVisible(true);
	}

	drawSceneGraph();
	ASSERT_GL_ERROR("ERROR: Could not draw scene.");
}

/////////////////////////////////////////////////////////////////////// Simulation

void restartGame() {
	tankObject->reset();
	tankObject2->reset();
	p1HUD->reset();
	p2HUD->reset();
	bulletManager->reset();
	bulletManager2->reset();
	ParticleSystemManager::instance()->reset();

	p1_Win->setVisible(false);
	p2_Win->setVisible(false);
}

void update() {

	q = qFromAngleAxis(-RotationAngleY, AXIS3D_Y) * qFromAngleAxis(-RotationAngleX, AXIS3D_X) * q;
	RotationAngleX = RotationAngleY = 0.0f;

	tankObject->update(elapsedTime);
	if (tankObject->collides(tankObject2) ||
		tankObject->getPosition().getX() > 26.0f || tankObject->getPosition().getX() < -26.0f ||
		tankObject->getPosition().getZ() > 26.0f || tankObject->getPosition().getZ() < -26.0f)
	{
		tankObject->hitTank();
	}
	tankObject2->update(elapsedTime);
	if (tankObject2->collides(tankObject) ||
		tankObject2->getPosition().getX() > 26.0f || tankObject2->getPosition().getX() < -26.0f ||
		tankObject2->getPosition().getZ() > 26.0f || tankObject2->getPosition().getZ() < -26.0f)
	{
		tankObject2->hitTank();
	}

	for each(StaticObject * o in props) {
		if (tankObject->collides(o))
		{
			tankObject->hitTank();
		}
		if (tankObject2->collides(o))
		{
			tankObject2->hitTank();
		}
	}

	bulletManager->update(elapsedTime);
	bulletManager->checkCollisions(tankObject2);

	bulletManager2->update(elapsedTime);
	bulletManager2->checkCollisions(tankObject);

	ParticleSystemManager::instance()->update(elapsedTime);
}

/////////////////////////////////////////////////////////////////////// Callbacks

void cleanup()
{
	MeshManager::instance()->destroy();
	TextureManager::instance()->destroy();
	MaterialManager::instance()->destroy();
	ShaderProgramManager::instance()->destroy();
	SceneGraphManager::instance()->destroy();
	ParticleSystemManager::instance()->destroy();
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

	if (!gameOver) {
		update();
		glutPostRedisplay();
	}
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
	case 'e':
		explosion->initParticles(Vector3D(0.0f, 4.0f, 0.0f));
		break;
	case 'f':
		sandtrail->initParticles(Vector3D(0.0f, 4.0f, 0.0f));
		break;
	case 'r':
		if (gameOver) {
			restartGame();
			gameOver = false;
		}
		break;
	}
}

void keyboard_up(unsigned char key, int x, int y)
{
	KeyBuffer::instance()->releaseKey(key);
}

void special_down(int key, int x, int y)
{
	KeyBuffer::instance()->pressSpecialKey(key);
}

void special_up(int key, int x, int y)
{
	KeyBuffer::instance()->releaseSpecialKey(key);
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
	glutSpecialFunc(special_down);
	glutSpecialUpFunc(special_up);
	glutMouseFunc(mouse);
	glutMotionFunc(mouseMotion);
	glutMouseWheelFunc(mouseWheel);
	glutReshapeFunc(reshape);

	glutTimerFunc(0, timer, 0);
}

void setupOpenGL() {
	std::cerr << "CONTEXT: OpenGL v" << glGetString(GL_VERSION) << std::endl;
	glClearColor(0.6f, 0.8f, 0.9f, 1.0f);
	glEnable(GL_DEPTH_TEST);
	glDepthFunc(GL_LEQUAL);
	glDepthMask(GL_TRUE);
	glDepthRange(0.0, 1.0);
	glClearDepth(1.0);
	glEnable(GL_CULL_FACE);
	glCullFace(GL_BACK);
	glFrontFace(GL_CCW);
	//glEnable(GL_MULTISAMPLE);
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
		createMaterials();
	ASSERT_GL_ERROR("ERROR: Material loading.");
		createTextures();
	ASSERT_GL_ERROR("ERROR: Texture loading.");
		createShaderPrograms();
	ASSERT_GL_ERROR("ERROR: Shader creation.");
		createScene();
	ASSERT_GL_ERROR("ERROR: Scene creation.");
}

int main(int argc, char* argv[])
{
	init(argc, argv);
	//system("pause");
	glutMainLoop();
	exit(EXIT_SUCCESS);
}

///////////////////////////////////////////////////////////////////////
