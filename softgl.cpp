#include "softgl.h"
#include <limits>
#include <iostream>

/// <summary>
/// 往指定hdc中绘制三角形
/// </summary>
/// <param name="hdc">指定hdc</param>
/// <param name="pts">三角形的三个点，三个点以位置逆时针排序</param>
void drawtriangle(HDC& hdc, Vector2f* pts)
{
	Vector4f bbox = boundingbox(pts, 3);
	Vector2i P;
	COLORREF color = RGB(255, 0, 0);
	for (P[0] = bbox[0]; P[0] < bbox[2]; P[0]++)
	{
		for (P[1] = bbox[1]; P[1] < bbox[3]; P[1]++)
		{
			Vector2f p(P[0], P[1]);
			Vector3f v = barycentric(pts, p);
			if (v[0] < 0 || v[1] < 0 || v[2] < 0) continue;
			SetPixel(hdc, p[0], p[1], color);
		}
	}
}

/// <summary>
/// 求点p在三个点中的重心坐标
/// </summary>
/// <param name="pts">Vector2f点数组</param>
/// <param name="p">点p</param>
/// <returns>重心坐标</returns>
Vector3f barycentric(Vector2f* pts, Vector2f p)
{
	Vector3f vecs[2];
	for (int i = 0; i < 2; i++)
	{
		vecs[i][0] = (pts[1] - pts[0])[i];
		vecs[i][1] = (pts[2] - pts[0])[i];
		vecs[i][2] = (pts[0] - p)[i];
	}
	Vector3f res = vecs[0].cross(vecs[1]);
	if (std::abs(res[2]) > 1e-2)
		return Vector3f(res[0] / res[2], res[1] / res[2], 1 - res[0] / res[2] - res[1] / res[2]);
	return Vector3f(-1, 0, 0);
}

/// <summary>
/// 求至少2个点的最小包围盒
/// </summary>
/// <param name="pts">Vector2f点数组</param>
/// <param name="length">点数组的长度</param>
/// <returns>Vector4f的包围盒，bbox[0]:x最小值, bbox[1]:y最小值, bbox[2]:x最大值, bbox[3]:y最大值</returns>
Vector4f boundingbox(Vector2f* pts, int length)
{
	Vector4f bbox;
	bbox[0] =  (numeric_limits<float>::max)(); // x min
	bbox[1] =  (numeric_limits<float>::max)(); // y min
	bbox[2] = -(numeric_limits<float>::max)(); // x max
	bbox[3] = -(numeric_limits<float>::max)(); // y max
	for (int i = 0; i < length; i++)
	{
		bbox[0] = min(bbox[0], pts[i][0]);
		bbox[1] = min(bbox[1], pts[i][1]);
		bbox[2] = max(bbox[2], pts[i][0]);
		bbox[3] = max(bbox[3], pts[i][1]);
	}
	return bbox;
}

/// <summary>
/// 计算相机矩阵，将模型坐标从世界坐标系转为以相机为原点的相机坐标
/// </summary>
/// <param name="campos">相机位置</param>
/// <param name="lookatpos">相机看向的位置</param>
/// <param name="up">相机的y向量</param>
/// <returns>4 * 4的相机变换矩阵</returns>
Matrix<float, 4, 4> getviewmatrix(Vector3f campos, Vector3f lookatpos, Vector3f up)
{
	// 相机z向量与世界坐标z向量相反
	Vector3f forward = -(lookatpos - campos).normalized();
	Vector3f right = up.cross(forward).normalized();
	Matrix<float, 4, 4> viewmat;
	viewmat.Identity();

	viewmat.row(0)[0] = right[0];
	viewmat.row(0)[1] = right[1];
	viewmat.row(0)[2] = right[2];
	viewmat.row(0)[3] = -campos[0];

	viewmat.row(1)[0] = up[0];
	viewmat.row(1)[1] = up[1];
	viewmat.row(1)[2] = up[2];
	viewmat.row(1)[3] = -campos[1];

	viewmat.row(2)[0] = forward[0];
	viewmat.row(2)[1] = forward[1];
	viewmat.row(2)[2] = forward[2];
	viewmat.row(2)[3] = -campos[2];
	return viewmat;
}

/// <summary>
/// 计算投影矩阵，将模型坐标转为[-1, 1]^3，方便后面往显示屏幕映射
/// </summary>
/// <param name="_near">相机近平面距离</param>
/// <param name="_far">相机远平面距离</param>
/// <param name="_ratio">相机宽高比</param>
/// <param name="_fov_angle">相机视场角, 角度制</param>
/// <returns>4 * 4的投影变换矩阵</returns>
Matrix<float, 4, 4> getprojectionmatrix(float _near, float _far, float _ratio, float _fov_angle)
{
	Matrix<float, 4, 4> _p_to_o_mat; // 将视锥体转为正交体
	Matrix<float, 4, 4> _o_mat; // 将正交体转为[-1, 1]^3大小
	float fov_radian = _fov_angle / 180 * PI;
	_o_mat.Identity();
	float top = tan(fov_radian / 2) * _near;
	float right = top * _ratio;

	_p_to_o_mat.row(0)[0] = _near;
	_p_to_o_mat.row(1)[1] = _near;
	_p_to_o_mat.row(2)[2] = _far + _near;
	_p_to_o_mat.row(2)[3] = -(_near * _far);
	_p_to_o_mat.row(3)[2] = 1;

	_o_mat.row(2)[3] = -(_near + _far) / 2;
	_o_mat.row(0)[0] = 1 / right;
	_o_mat.row(1)[1] = 1 / top;
	_o_mat.row(2)[2] = 2 / (_far - _near);

	return _o_mat * _p_to_o_mat;
}

/// <summary>
/// 计算视口矩阵，获取将[-1, 1]^3的坐标映射到[x_range, y_range, z_range]的坐标范围（映射到屏幕空间）
/// </summary>
/// <param name="x_range">x的取值范围</param>
/// <param name="y_range">y的取值范围</param>
/// <param name="z_range">z的取值范围</param>
/// <returns>4 * 4的转换矩阵</returns>
Matrix<float, 4, 4> getviewportmatrix(Vector2f x_range, Vector2f y_range, Vector2f z_range)
{
	Matrix<float, 4, 4> _viewportmat;
	
	_viewportmat.row(0)[0] = (x_range[1] - x_range[0]) / 2;
	_viewportmat.row(0)[3] = (x_range[1] - x_range[0]) / 2;
	_viewportmat.row(1)[1] = (y_range[1] - y_range[0]) / 2;
	_viewportmat.row(1)[3] = (y_range[1] - y_range[0]) / 2;
	_viewportmat.row(2)[2] = (z_range[1] - z_range[0]) / 2;
	_viewportmat.row(2)[3] = (z_range[1] - z_range[0]) / 2;

	return _viewportmat;
}
