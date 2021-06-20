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
	/// ��������任����
	/// </summary>
	/// <param name="cam_pos">���λ��</param>
	/// <param name="lookat_pos">��������λ��</param>
	/// <param name="up">�����y����</param>
	void LookAt(Vector3f cam_pos, Vector3f lookat_pos, Vector3f up);

	/// <summary>
	/// �������ͶӰ����
	/// </summary>
	/// <param name="_near">�����ƽ��</param>
	/// <param name="_far">���Զƽ��</param>
	/// <param name="_ratio">�����߱�</param>
	/// <param name="_fov">����ӳ��ǣ��Ƕ���</param>
	void SetupCamera(float _near, float _far, float _ratio, float _fov);

	/// <summary>
	/// �����ӿ�ת������
	/// </summary>
	/// <param name="x_range">xȡֵ��Χ</param>
	/// <param name="y_range">yȡֵ��Χ</param>
	/// <param name="z_range">zȡֵ��Χ</param>
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
