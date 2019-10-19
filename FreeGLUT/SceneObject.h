#pragma once
#include "Structures.h"
#include "Texture2D.h"

class SceneObject
{
protected:
	Mesh * _mesh;
	Texture2D* _texture;

public:
	SceneObject(Mesh* mesh, Texture2D* _texture);
	virtual ~SceneObject(void);

	virtual void Update() = 0;
	virtual void Draw() = 0;
	virtual void SetPosition(float positionX, float positionY, float positionZ) = 0;
	virtual void SetRotation(float rotation) = 0;
};

