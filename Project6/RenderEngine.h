#pragma once
#include "Matrix.h"
#include "Mesh.h"
#include "Vector2.h"
#include "Vector3.h"
#include <vector>
#include "Rotation.h"

class MainWindow;

class RenderEngine
{
public:
	Vector3 cameraAngle = Vector3(0,0,0);
	Vector3 cameraPosition = Vector3(20,0,0);
	Matrix currentTransformationMatrix;
	Matrix currentProjectionMatrix;
	std::vector<Mesh> renderQueue;
	void AddToRenderQueue(Mesh object);
	void AddListToRenderQueue(std::vector<Mesh> objects);
	static std::vector<std::vector<Vector2>> ConvertMeshToRenderObjects(Mesh mesh, RenderEngine rE, int sW, int sH);
	Vector3 TransformPoint(Vector3 point);
	void UpdateTransformationMatrix();
	void UpdateProjectionMatrix();
	Vector2 ProjectPoint(Vector3 point, int screenWidth, int screenHeight);
	double nearPlane = 1;
	double farPlane = 1000;
	double fov = 70;
	double aspectRatio;
};

