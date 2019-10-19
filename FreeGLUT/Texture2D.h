#pragma once
#include <Windows.h> // Required for OpenGL on windows
#include <gl/GL.h> //OpenGL
#include <gl/GLU.h> // OGL Utilites
#include "GL\freeglut.h" // FreeGlut Library
#include "GLUTCallbacks.h"
#include <fstream>
#include <iostream>

using namespace std;

class Texture2D
{
private:
	GLuint _ID; //Texture ID
	int _width, _height;

public:
	Texture2D();
	~Texture2D();

	bool Load(char* path, int width, int height);

	GLuint GetID() const;
	int GetWidth() const;
	int GetHeight() const;
};

