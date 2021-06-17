#pragma once

#include <Windows.h>
#include <Eigen/Dense>
#include <limits>
#include <algorithm>
#include <cmath>

using namespace std;
using namespace Eigen;

extern Eigen::Matrix4f ModelView;
extern Eigen::Matrix4f Viewport;
extern Eigen::Matrix4f Projection;

/*
���������Σ����������㣬����obj�ļ���Ĭ�϶���˳����ʱ��
*/
void drawtriangle(HDC&, Vector2f*);

/*
����������
*/
Vector3f barycentric(Vector2f*, Vector2f);

/*
���ά�㼯�İ�Χ��
Vector4f[0]: x��Сֵ
Vector4f[1]: y��Сֵ
Vector4f[2]: x���ֵ
Vector4f[3]: y���ֵ
*/
Vector4f boundingbox(Vector2f*, int);