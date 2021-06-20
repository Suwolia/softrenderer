#include "softgl.h"
#include <limits>
#include <iostream>

/// <summary>
/// ��ָ��hdc�л���������
/// </summary>
/// <param name="hdc">ָ��hdc</param>
/// <param name="pts">�����ε������㣬��������λ����ʱ������</param>
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
/// ���p���������е���������
/// </summary>
/// <param name="pts">Vector2f������</param>
/// <param name="p">��p</param>
/// <returns>��������</returns>
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
/// ������2�������С��Χ��
/// </summary>
/// <param name="pts">Vector2f������</param>
/// <param name="length">������ĳ���</param>
/// <returns>Vector4f�İ�Χ�У�bbox[0]:x��Сֵ, bbox[1]:y��Сֵ, bbox[2]:x���ֵ, bbox[3]:y���ֵ</returns>
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
/// ����������󣬽�ģ���������������ϵתΪ�����Ϊԭ����������
/// </summary>
/// <param name="campos">���λ��</param>
/// <param name="lookatpos">��������λ��</param>
/// <param name="up">�����y����</param>
/// <returns>4 * 4������任����</returns>
Matrix<float, 4, 4> getviewmatrix(Vector3f campos, Vector3f lookatpos, Vector3f up)
{
	// ���z��������������z�����෴
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
/// ����ͶӰ���󣬽�ģ������תΪ[-1, 1]^3�������������ʾ��Ļӳ��
/// </summary>
/// <param name="_near">�����ƽ�����</param>
/// <param name="_far">���Զƽ�����</param>
/// <param name="_ratio">�����߱�</param>
/// <param name="_fov_angle">����ӳ���, �Ƕ���</param>
/// <returns>4 * 4��ͶӰ�任����</returns>
Matrix<float, 4, 4> getprojectionmatrix(float _near, float _far, float _ratio, float _fov_angle)
{
	Matrix<float, 4, 4> _p_to_o_mat; // ����׶��תΪ������
	Matrix<float, 4, 4> _o_mat; // ��������תΪ[-1, 1]^3��С
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
/// �����ӿھ��󣬻�ȡ��[-1, 1]^3������ӳ�䵽[x_range, y_range, z_range]�����귶Χ��ӳ�䵽��Ļ�ռ䣩
/// </summary>
/// <param name="x_range">x��ȡֵ��Χ</param>
/// <param name="y_range">y��ȡֵ��Χ</param>
/// <param name="z_range">z��ȡֵ��Χ</param>
/// <returns>4 * 4��ת������</returns>
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
