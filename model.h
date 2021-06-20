#pragma once

#include <Eigen/Dense>
#include <Eigen/StdVector>

using namespace Eigen;
using namespace std;

class Model
{
public:
	EIGEN_MAKE_ALIGNED_OPERATOR_NEW
	Model(const char*);
	~Model() {};

	/// <summary>
	/// ��ȡģ������������
	/// </summary>
	/// <returns>ģ������������</returns>
	int nface(){ return _faceindex.size(); }

	vector<vector<int>>* GetFaceIndexes() { return &_faceindex; };

	/// <summary>
	/// ��ȡģ�;�����������������µ�Ψһ������
	/// TODO: rotation
	/// </summary>
	/// <returns>4 * 4ģ�;���</returns>
	Matrix<float, 4, 4> GetModelMatrix();

	/// <summary>
	/// ����ģ��λ��
	/// </summary>
	/// <param name="_x">x����</param>
	/// <param name="_y">y����</param>
	/// <param name="_z">z����</param>
	void SetPosition(float _x, float _y, float _z);

	/// <summary>
	/// ����ģ�ͱ���
	/// </summary>
	/// <param name="_x">x�����</param>
	/// <param name="_y">y�����</param>
	/// <param name="_z">z�����</param>
	void SetScale(float _x, float _y, float _z);

	Vector3f GetVertic(int index) { return _vertics[index]; };

private:
	/// <summary>
	/// ģ���ļ��а��������еĶ�������
	/// </summary>
	//vector<Vector3f> _vertics;
	vector<Vector3f, aligned_allocator<Vector3f>> _vertics;

	/// <summary>
	/// ģ���ļ��а��������е�������������
	/// </summary>
	//vector<Vector3f> _texvertics;
	vector<Vector3f, aligned_allocator<Vector3f>> _texvertics;

	/// <summary>
	/// ģ���ļ��а��������еķ�������
	/// </summary>
	//vector<Vector3f> _normvertics;
	vector<Vector3f, aligned_allocator<Vector3f>> _normvertics;

	/// <summary>
	/// ģ�����е��������е����� ����/����/���� ������
	/// </summary>
	vector<vector<int>> _faceindex;
	Vector3f _position;
	Vector3f _scale;
};