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
	RenderMachine();
	~RenderMachine() {};
	void AddTriangle(Vector2f, Vector2f, Vector2f);
	void MoveTriangles(Vector2f);
	void MoveTriangles(float x, float y);
	vector<triangle2f>* GetTriangles();
	void AddModel(Model*);
	void Draw(HDC&);

	/// <summary>
	/// 设置相机变换矩阵
	/// </summary>
	/// <param name="cam_pos">相机位置</param>
	/// <param name="lookat_pos">相机看向的位置</param>
	/// <param name="up">相机的y向量</param>
	void LookAt(Vector3f cam_pos, Vector3f lookat_pos, Vector3f up);

	/// <summary>
	/// 设置相机投影矩阵
	/// </summary>
	/// <param name="_near">相机近平面</param>
	/// <param name="_far">相机远平面</param>
	/// <param name="_ratio">相机宽高比</param>
	/// <param name="_fov">相机视场角，角度制</param>
	void SetupCamera(float _near, float _far, float _ratio, float _fov);

	/// <summary>
	/// 设置视口转换矩阵
	/// </summary>
	/// <param name="x_range">x取值范围</param>
	/// <param name="y_range">y取值范围</param>
	/// <param name="z_range">z取值范围</param>
	void SetupViewport(Vector2f x_range, Vector2f y_range, Vector2f z_range);
private:
	vector<triangle2f> triangles;
	vector<Model*> _model_vector;
	Matrix<float, 4, 4> _view_mat;
	Matrix<float, 4, 4> _proj_mat;
	Matrix<float, 4, 4> _viewport_mat;
	Matrix<float, 4, 4> _GetFinalMat();
};


void RenderMachineDraw(HDC&, RenderMachine*);
