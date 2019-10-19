#include "PyramidFlyingObject.h"

PyramidFlyingObject::PyramidFlyingObject(Mesh* objectMesh, Texture2D* texture, float x, float y, float z) : SceneObject(objectMesh, texture)
{
	//Initialise Pyramid Values
	_rotation = 0.0f; //Set Pyramid rotation to 0
	pyramidFlyingObject = objectMesh; //Assign loaded mesh to Pyramid Flying object
	_randomRotation = (rand() % 100 / 10) + 1; //Randomise Rotation
	_zMovement = 1.0f; //Apply movement to Z axis
}

void PyramidFlyingObject::Update()
{
	_position.z += _zMovement;
	_rotation += _randomRotation;

	//Reset pyramid position once out of view
	if (_position.z > 10.0f)
		_position.z = -100.0f;
}

void PyramidFlyingObject::Draw()
{
	glEnableClientState(GL_VERTEX_ARRAY);
	glEnableClientState(GL_COLOR_ARRAY);
	glVertexPointer(3, GL_FLOAT, 0, pyramidFlyingObject->Vertices);
	glColorPointer(3, GL_FLOAT, 0, pyramidFlyingObject->Colors);

	glPushMatrix();
		glTranslatef(_position.x, _position.y, _position.z);
		glRotatef(_rotation, 1.0f, 0.0f, 0.0f);
		glRotatef(_rotation, 0.0f, 1.0f, 0.0f);
		glRotatef(_rotation, 0.0f, 0.0f, 1.0f);
		glDrawElements(GL_TRIANGLES, pyramidFlyingObject->IndexCount, GL_UNSIGNED_SHORT, pyramidFlyingObject->Indices);
	glPopMatrix();

	glDisableClientState(GL_COLOR_ARRAY);
	glDisableClientState(GL_VERTEX_ARRAY);
}

void PyramidFlyingObject::SetRotation(float rotation)
{
	_rotation += rotation;
}

void PyramidFlyingObject::SetPosition(float positionX, float positionY, float positionZ)
{
	_position.x = positionX;
	_position.y = positionY;
	_position.z = positionZ;
}

PyramidFlyingObject::~PyramidFlyingObject()
{

}
