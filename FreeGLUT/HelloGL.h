#pragma once
#include <Windows.h> // Required for OpenGL on windows
#include <gl/GL.h> //OpenGL
#include <gl/GLU.h> // OGL Utilites
#include "GL\freeglut.h" // FreeGlut Library
#include "GLUTCallbacks.h"
#include "Structures.h"
#include "CubeFlyingObject.h"
#include "PyramidFlyingObject.h"
#include "Texture2D.h"

#define REFRESHRATE 16

class HelloGL
{
public:
	HelloGL(int argc, char* argv[]);
	~HelloGL();

	void Display();
	void Update();
	void Keyboard(unsigned char key, int x, int y);

	void InitObjects();
	void InitGL(int argc, char* argv[]);
	void DrawString(const char* text, const Vector3* position, const Color* color);
	
	Camera* camera;

private:
	SceneObject* objects[100];

	Vector4* _lightPosition;
	Lighting* _lightData;
	Material* _material;
};


	


