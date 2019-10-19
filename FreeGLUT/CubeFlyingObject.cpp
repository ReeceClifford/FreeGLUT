#include "CubeFlyingObject.h"

CubeFlyingObject::CubeFlyingObject(Mesh* objectMesh, Texture2D* texture, float x, float y, float z) : SceneObject(objectMesh, texture)
{
	_rotation = 0.0f;
	cubeFlyingObject = objectMesh;
	_randomRotation = (rand() % 100 / 10) + 1;
	_zMovement = 1.0f;
}

void CubeFlyingObject::Update()
{
	_position.z += _zMovement;
	_rotation += _randomRotation;

	if (_position.z > 10.0f)
		_position.z = -100.0f;
}

void CubeFlyingObject::Draw()
{
	
	glBindTexture(GL_TEXTURE_2D, _texture->GetID());
	glEnable(GL_TEXTURE_2D);

	glEnableClientState(GL_VERTEX_ARRAY);
	glEnableClientState(GL_NORMAL_ARRAY);
	glEnableClientState(GL_TEXTURE_COORD_ARRAY);
	glVertexPointer(3, GL_FLOAT, 0, cubeFlyingObject->Vertices);
	glNormalPointer(GL_FLOAT, 0, cubeFlyingObject->indexedNormals);
	glTexCoordPointer(2, GL_FLOAT, 0, cubeFlyingObject->TexCoords);

	glPushMatrix();
		glTranslatef(_position.x, _position.y, _position.z);
		glRotatef(_rotation, 1.0f, 0.0f, 0.0f);
		glRotatef(_rotation, 0.0f, 1.0f, 0.0f); 
		glRotatef(_rotation, 0.0f, 0.0f, 1.0f); 
		glDrawElements(GL_TRIANGLES, cubeFlyingObject->IndexCount, GL_UNSIGNED_SHORT, cubeFlyingObject->Indices);
	glPopMatrix();
	
	glDisableClientState(GL_TEXTURE_COORD_ARRAY);
	glDisableClientState(GL_VERTEX_ARRAY);
	glDisable(GL_TEXTURE_2D);

}

void CubeFlyingObject::SetRotation(float rotation)
{
	_rotation += rotation;
}

void CubeFlyingObject::SetPosition(float positionX, float positionY, float positionZ)
{
	_position.x = positionX;
	_position.y = positionY;
	_position.z = positionZ;
}

CubeFlyingObject::~CubeFlyingObject()
{

}
