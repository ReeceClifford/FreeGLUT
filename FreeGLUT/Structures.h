#pragma once
#include <Windows.h> // Required for OpenGL on windows
#include <gl/GL.h> //OpenGL
#include <gl/GLU.h> // OGL Utilites
#include "GL\freeglut.h" // FreeGlut Library

struct Vector3
{
	float x;
	float y;
	float z;
};

struct Vector4 //For Lighting
{
	float x;
	float y;
	float z;
	float w;
};

struct Camera
{
	Vector3 eye;
	Vector3 center;
	Vector3 up;
};

struct Color
{
	GLfloat r, g, b;
};

struct Vertex
{
	GLfloat x, y, z;
};

struct TexCoord
{
	GLfloat u, v;
};

struct Normals
{
	GLfloat nx, ny, nz;
};
struct Mesh
{
	Vertex* Vertices;
	Color* Colors;
	Normals* indexedNormals;
	TexCoord* TexCoords;
	GLushort* Indices;
	int VertexCount, ColorCount, NormalsCount, IndexCount, TexCoordCount;
};

// Struct for Lighting
struct Lighting
{
	Vector4 Ambient[4]; // Values for RGBA
	Vector4 Diffuse[4]; // Values for RGBA
	Vector4 Specular[4]; // Values for RGBA
};

struct Material
{
	Vector4 Ambient[4]; // Values for RGBA
	Vector4 Diffuse[4]; // Values for RGBA
	Vector4 Specular[4]; // Values for RGBA
	GLfloat Shininess;
};






