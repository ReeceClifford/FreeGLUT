#pragma once 
#include <Windows.h> //Required for OpenGL on Windows 
#include <gl/GL.h> //OpenGL 
#include <gl/GLU.h> //OpenGL Utilities 
#include "GL\freeglut.h" //freeglut library
#include "Structures.h"
#include <fstream> //Allows for Loading from File
#include <iostream>
#include "MeshLoader.h"
#include "SceneObject.h"
#include "Texture2D.h"

using namespace std;

class CubeFlyingObject : public SceneObject
{
private:

	Mesh* cubeFlyingObject;
	
	GLfloat _rotation;
	Vector3 _position;
	GLfloat _zMovement;
	GLfloat _randomRotation;

public: 
	CubeFlyingObject(Mesh* cubeMesh, Texture2D* texture, float x, float y, float z);
	~CubeFlyingObject();
	void Draw(); 
	void Update();
	void SetRotation(float rotation);
	void SetPosition(float positionX, float positionY, float positionZ);
};

