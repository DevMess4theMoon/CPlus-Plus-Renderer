#include "Rotation.h"
#include <math.h>
constexpr float MY_PI = 3.1415926535897932384626433832795028841971693993751058209749445923078164062862089986280348253421170679f;
constexpr float ONE_DEGREE = 0.01745329251994329576923690768488612713442871888541725456097191440171009114603449443682241569634509482167f;
Matrix Rotation::rotX(double amount) {
	double x = ONE_DEGREE * amount;
	return Matrix(4, 4, {
		{1, 0     , 0	   , 0},
		{0, cos(x), -sin(x), 0},
		{0, sin(x), cos(x) , 0},
		{0, 0     , 0      , 1}
		});
}
Matrix Rotation::rotY(double amount) {
	double y = ONE_DEGREE * amount;
	return Matrix(4, 4, {
		{cos(y) , 0, sin(y), 0},
		{0      , 1, 0     , 0},
		{-sin(y), 0, cos(y), 0},
		{0      , 0, 0     , 1}
		});
}
Matrix Rotation::rotZ(double amount) {
	double z = ONE_DEGREE * amount;
	return Matrix(4, 4, {
		{cos(z), -sin(z), 0, 0},
		{sin(z), cos(z) , 0, 0},
		{0     , 0      , 1, 0},
		{0     , 0      , 0, 1}
		});
}
Mesh Rotation::rotMesh(Mesh mesh, Vector3 rotation, Vector3 center) {
	Matrix m;
	Matrix rotM = rotX(rotation.x) * rotY(rotation.y) * rotZ(rotation.z);
	std::vector<Vector3> temp(mesh.vertices.size());
	for (int i = 0; i < temp.size(); i++) {
		m = (Matrix)mesh.vertices[i];

		Matrix T = (Matrix)Vector3(-center.x, -center.y, -center.z);
		Matrix nT = (Matrix)center;
		m = m + T;
		m = rotM * m;
		m = m + nT;
		temp[i] = Vector3(m.m[0][0], m.m[1][0], m.m[2][0]);

	}

	return Mesh(temp, mesh.triangles);
}