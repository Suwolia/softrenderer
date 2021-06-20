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
	/// 获取模型三角面总数
	/// </summary>
	/// <returns>模型三角面总数</returns>
	int nface(){ return _faceindex.size(); }

	vector<vector<int>>* GetFaceIndexes() { return &_faceindex; };

	/// <summary>
	/// 获取模型矩阵，相对于世界坐标下的唯一和缩放
	/// TODO: rotation
	/// </summary>
	/// <returns>4 * 4模型矩阵</returns>
	Matrix<float, 4, 4> GetModelMatrix();

	/// <summary>
	/// 设置模型位置
	/// </summary>
	/// <param name="_x">x坐标</param>
	/// <param name="_y">y坐标</param>
	/// <param name="_z">z坐标</param>
	void SetPosition(float _x, float _y, float _z);

	/// <summary>
	/// 设置模型比例
	/// </summary>
	/// <param name="_x">x轴比例</param>
	/// <param name="_y">y轴比例</param>
	/// <param name="_z">z轴比例</param>
	void SetScale(float _x, float _y, float _z);

	Vector3f GetVertic(int index) { return _vertics[index]; };

private:
	/// <summary>
	/// 模型文件中包含的所有的顶点数据
	/// </summary>
	//vector<Vector3f> _vertics;
	vector<Vector3f, aligned_allocator<Vector3f>> _vertics;

	/// <summary>
	/// 模型文件中包含的所有的纹理坐标数据
	/// </summary>
	//vector<Vector3f> _texvertics;
	vector<Vector3f, aligned_allocator<Vector3f>> _texvertics;

	/// <summary>
	/// 模型文件中包含的所有的法线数据
	/// </summary>
	//vector<Vector3f> _normvertics;
	vector<Vector3f, aligned_allocator<Vector3f>> _normvertics;

	/// <summary>
	/// 模型所有的三角面中的三个 顶点/纹理/法线 的索引
	/// </summary>
	vector<vector<int>> _faceindex;
	Vector3f _position;
	Vector3f _scale;
};