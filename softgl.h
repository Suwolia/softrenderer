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
绘制三角形，至少三个点，按照obj文件的默认顶点顺序，逆时针
*/
void drawtriangle(HDC&, Vector2f*);

/*
求重心坐标
*/
Vector3f barycentric(Vector2f*, Vector2f);

/*
求二维点集的包围盒
Vector4f[0]: x最小值
Vector4f[1]: y最小值
Vector4f[2]: x最大值
Vector4f[3]: y最大值
*/
Vector4f boundingbox(Vector2f*, int);