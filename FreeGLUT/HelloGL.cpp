#include "HelloGL.h"
#include "MeshLoader.h"
#include <time.h>

HelloGL::HelloGL(int argc, char* argv[])
{
	InitGL(argc, argv);
	InitObjects();
	
	glutMainLoop();
}

void HelloGL::InitGL(int argc, char* argv[])
{
	GLUTCallbacks::Init(this);
	glutInit(&argc, argv);
	glutInitDisplayMode(GLUT_DOUBLE | GLUT_DEPTH);
	glutInitWindowSize(800, 800);
	glutInitWindowPosition(0, 0);
	glutCreateWindow("Simple OpenGL Program");
	glutDisplayFunc(GLUTCallbacks::Display);
	glutTimerFunc(REFRESHRATE, GLUTCallbacks::Timer, REFRESHRATE);
	glutKeyboardFunc(GLUTCallbacks::Keyboard);//Intialise Keyboard
	glMatrixMode(GL_PROJECTION);
	glLoadIdentity(); //Rest Matrix
	glViewport(0, 0, 800, 800); // Set the viewport to be the entire window
	gluPerspective(45, 1, 0.1, 1000); // Set the Perspecive, Type of Camera used

	glEnable(GL_LIGHTING); // Enable Lighting
	glEnable(GL_LIGHT0); // Enable Light to 0
	glMatrixMode(GL_MODELVIEW);
	glEnable(GL_DEPTH_TEST);
	glEnable(GL_CULL_FACE);
	glCullFace(GL_BACK);
}

void HelloGL::InitObjects()
{
	srand(time(NULL));

	camera = new Camera();

	camera->eye.x = 0.0f; camera->eye.y = 0.0f; camera->eye.z = 10.0f;
	camera->center.x = 0.0f; camera->center.y = 0.0f; camera->center.z = 0.0f;
	camera->up.x = 0.0f; camera->up.y = 1.0f; camera->up.z = 0.0f;

	Mesh* cubeMesh = MeshLoader::LoadTextured((char*)"Cube.txt");
	Mesh* pyramidMesh = MeshLoader::Load((char*)"Pyramid.txt");

	_lightPosition = new Vector4();
	_lightPosition->x = 0.0; 
	_lightPosition->y = 0.0; 
	_lightPosition->z = 1.0; 
	_lightPosition->w = 0.0;

	_lightData = new Lighting();
	_lightData->Ambient->x = 0.5; 
	_lightData->Ambient->y = 0.5;
	_lightData->Ambient->z = 0.5;
	_lightData->Ambient->w = 1.0;
	_lightData->Diffuse->x = 1.0;
	_lightData->Diffuse->y = 1.0;
	_lightData->Diffuse->z = 1.0;
	_lightData->Diffuse->w = 1.0;
	_lightData->Specular->x = 1.0;
	_lightData->Specular->y = 1.0;
	_lightData->Specular->z = 1.0;
	_lightData->Specular->w = 1.0;

	_material = new Material(); 
	_material->Ambient->x = 1.0; 
	_material->Ambient->y = 0.0;
	_material->Ambient->z = 0.0;
	_material->Ambient->w = 1.0;

	_material->Diffuse->x = 1.0;
	_material->Diffuse->y = 0.0;
	_material->Diffuse->z = 0.0;
	_material->Diffuse->w = 1.0;

	_material->Specular->x = 1.0;
	_material->Specular->y = 1.0;
	_material->Specular->z = 1.0;
	_material->Specular->w = 1.0; 

	_material->Shininess = 100.0f;

	Texture2D* cubeTexture = new Texture2D();
	cubeTexture->Load((char*)"Penguins.raw", 512, 512);

	Texture2D* pyramidTexture = new Texture2D();
	pyramidTexture->Load((char*)"Penguins.raw", 512, 512);
	
	for (int i = 0; i < 100; i++)
	{
		objects[i] = new CubeFlyingObject(cubeMesh, cubeTexture, 1.0f, 2.0f, 3.0f);
		objects[i]->SetPosition(((rand() % 400) / 10.0f) - 20.0f, ((rand() % 200) / 10.0f) - 10.0f, -(rand() % 1000) / 10.0f);
	}
	for (int i = 50; i < 100; i++)
	{
		objects[i] = new PyramidFlyingObject(pyramidMesh, cubeTexture, 1.0f, 2.0f, 3.0f);
		objects[i]->SetPosition(((rand() % 400) / 10.0f) - 20.0f, ((rand() % 200) / 10.0f) - 10.0f, -(rand() % 1000) / 10.0f);
	}
}

void HelloGL::Display()
{
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

	glMaterialfv(GL_FRONT, GL_AMBIENT, &(_material->Ambient->x));
	glMaterialfv(GL_FRONT, GL_DIFFUSE, &(_material->Diffuse->x));
	glMaterialfv(GL_FRONT, GL_SPECULAR, &(_material->Specular->x));
	glMaterialf(GL_FRONT, GL_SHININESS, _material->Shininess); 

	for (int i = 0; i < 100; i++)
	{
		objects[i]->Draw();
	}
	Vector3 v = { -3.5f, 3.8f, 0.0f };

	Color c = { 5.0f, 6.0f, 0.0f };

	DrawString("Use: W, A, S, D, X, Z to move the camera", &v, &c);
	glFlush();
	glutSwapBuffers();
}

void HelloGL::Update()
{
	glLoadIdentity(); //Reset so old matrix aren't reused.
	
	//Intialise the lighting
	
	glLightfv(GL_LIGHT0, GL_AMBIENT, &(_lightData->Ambient->x));
	glLightfv(GL_LIGHT0, GL_DIFFUSE, &(_lightData->Diffuse->x));
	glLightfv(GL_LIGHT0, GL_SPECULAR, &(_lightData->Specular->x));

	glLightfv(GL_LIGHT0, GL_POSITION, &(_lightPosition->x));

	gluLookAt(camera->eye.x, camera->eye.y, camera->eye.z, camera->center.x, camera->center.y, camera->center.z, camera->up.x, camera->up.y, camera->up.z);
	
	for (int i = 0; i < 100; i++)
	{
		objects[i]->Update();
	}
	glutPostRedisplay();
}

void HelloGL::Keyboard(unsigned char key, int x, int y)
{
	if (key == 'w')
		camera->eye.y += 0.5f;
	if (key == 's')
		camera->eye.y -= 0.5f;
	if(key == 'd')
		camera->eye.x += 0.5f;
	if (key == 'a')
		camera->eye.x -= 0.5f;
	if (key == 'x')
		camera->eye.z += 0.5f;
	if (key == 'z')
		camera->eye.z -= 0.5f;
	if (key == 'o')
	{
		for (int i = 0; i < 100; i++)
		{
			objects[i]->SetPosition(((rand() % 400) / 10.0f) - 20.0f, ((rand() % 200) / 10.0f) - 10.0f, -(rand() % 1000) / 10.0f);
		}
	}
	if (key == 'r')
	{
		camera->eye.x = 0.0f; camera->eye.y = 0.0f; camera->eye.z = 10.0f;
		camera->center.x = 0.0f; camera->center.y = 0.0f; camera->center.z = 0.0f;
		camera->up.x = 0.0f; camera->up.y = 1.0f; camera->up.z = 0.0f;
	}
}
void HelloGL::DrawString(const char* text, const Vector3* position, const Color* color)

{
	glPushMatrix();

	glDisable(GL_TEXTURE);

	glDisable(GL_LIGHTING);

	glColor3f(1.0f, 0.0f, 0.0f);

	glTranslatef(position->x, position->y, position->z);

	glRasterPos2f(0.0f, 0.0f);

	glutBitmapString(GLUT_BITMAP_TIMES_ROMAN_24, (unsigned char*)text);

	glEnable(GL_LIGHTING);

	glEnable(GL_TEXTURE);

	glPopMatrix();

}
HelloGL::~HelloGL()
{

}
