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

using namespace std;

class PyramidFlyingObject : public SceneObject
{
private:

	Mesh * pyramidFlyingObject;

	GLfloat _rotation;
	Vector3 _position;
	GLfloat _zMovement;
	GLfloat _randomRotation;

public:
	PyramidFlyingObject(Mesh* pyramidMesh, Texture2D* texture, float x, float y, float z);
	~PyramidFlyingObject();
	void Draw();
	void Update();
	void SetRotation(float rotation);
	void SetPosition(float positionX, float positionY, float positionZ);
};

