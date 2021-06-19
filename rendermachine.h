#pragma once

#include <Eigen/Dense>
#include <vector>
#include <Windows.h>
#include "model.h"

using namespace std;
using namespace Eigen;

struct triangle2f
{
	Vector2f p1;
	Vector2f p2;
	Vector2f p3;
};

class RenderMachine
{
public:
	RenderMachine() {};
	~RenderMachine() {};
	void AddTriangle(Vector2f, Vector2f, Vector2f);
	void MoveTriangles(Vector2f);
	void MoveTriangles(float x, float y);
	vector<triangle2f>* GetTriangles();
	void AddModel(Model*);
	void Draw(HDC&);
private:
	vector<triangle2f> triangles;
	vector<Model*> _model_vector;
};


void RenderMachineDraw(HDC&, RenderMachine*);
