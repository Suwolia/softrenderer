#pragma once

#include <Windows.h>
#include <Eigen/Dense>
#include <limits>
#include <algorithm>
#include <cmath>

using namespace std;
using namespace Eigen;

#define PI 3.1415926

extern Eigen::Matrix4f ModelView;
extern Eigen::Matrix4f Viewport;
extern Eigen::Matrix4f Projection;


/// <summary>
/// ��ָ��hdc�л���������
/// </summary>
/// <param name="hdc">ָ��hdc</param>
/// <param name="pts">�����ε������㣬��������λ����ʱ������</param>
void drawtriangle(HDC& hdc, Vector2f* pts);


/// <summary>
/// ���p���������е���������
/// </summary>
/// <param name="pts">Vector2f������</param>
/// <param name="p">��p</param>
/// <returns>��������</returns>
Vector3f barycentric(Vector2f* pts, Vector2f p);


/// <summary>
/// ������2�������С��Χ��
/// </summary>
/// <param name="pts">Vector2f������</param>
/// <param name="length">������ĳ���</param>
/// <returns>Vector4f�İ�Χ�У�bbox[0]:x��Сֵ, bbox[1]:y��Сֵ, bbox[2]:x���ֵ, bbox[3]:y���ֵ</returns>
Vector4f boundingbox(Vector2f* pts, int length);

/// <summary>
/// ����������󣬽�ģ���������������ϵתΪ�����Ϊԭ����������
/// </summary>
/// <param name="campos">���λ��</param>
/// <param name="lookatpos">��������λ��</param>
/// <param name="up">�����y����</param>
/// <returns>4 * 4������任����</returns>
Matrix<float, 4, 4> getviewmatrix(Vector3f campos, Vector3f lookatpos, Vector3f up);


/// <summary>
/// ����ͶӰ���󣬽�ģ������תΪ[-1, 1]^3�������������ʾ��Ļӳ��
/// </summary>
/// <param name="_near">�����ƽ�����</param>
/// <param name="_far">���Զƽ�����</param>
/// <param name="_ratio">�����߱�</param>
/// <param name="_fov_angle">����ӳ���, �Ƕ���</param>
/// <returns>4 * 4��ͶӰ�任����</returns>
Matrix<float, 4, 4> getprojectionmatrix(float _near, float _far, float _ratio, float _fov_angle);


/// <summary>
/// �����ӿھ��󣬻�ȡ��[-1, 1]^3������ӳ�䵽[x_range, y_range, z_range]�����귶Χ��ӳ�䵽��Ļ�ռ䣩
/// </summary>
/// <param name="x_range">x��ȡֵ��Χ</param>
/// <param name="y_range">y��ȡֵ��Χ</param>
/// <param name="z_range">z��ȡֵ��Χ</param>
/// <returns>4 * 4��ת������</returns>
Matrix<float, 4, 4> getviewportmatrix(Vector2f x_range, Vector2f y_range, Vector2f z_range);