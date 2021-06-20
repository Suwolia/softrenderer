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
/// 往指定hdc中绘制三角形
/// </summary>
/// <param name="hdc">指定hdc</param>
/// <param name="pts">三角形的三个点，三个点以位置逆时针排序</param>
void drawtriangle(HDC& hdc, Vector2f* pts);


/// <summary>
/// 求点p在三个点中的重心坐标
/// </summary>
/// <param name="pts">Vector2f点数组</param>
/// <param name="p">点p</param>
/// <returns>重心坐标</returns>
Vector3f barycentric(Vector2f* pts, Vector2f p);


/// <summary>
/// 求至少2个点的最小包围盒
/// </summary>
/// <param name="pts">Vector2f点数组</param>
/// <param name="length">点数组的长度</param>
/// <returns>Vector4f的包围盒，bbox[0]:x最小值, bbox[1]:y最小值, bbox[2]:x最大值, bbox[3]:y最大值</returns>
Vector4f boundingbox(Vector2f* pts, int length);

/// <summary>
/// 计算相机矩阵，将模型坐标从世界坐标系转为以相机为原点的相机坐标
/// </summary>
/// <param name="campos">相机位置</param>
/// <param name="lookatpos">相机看向的位置</param>
/// <param name="up">相机的y向量</param>
/// <returns>4 * 4的相机变换矩阵</returns>
Matrix<float, 4, 4> getviewmatrix(Vector3f campos, Vector3f lookatpos, Vector3f up);


/// <summary>
/// 计算投影矩阵，将模型坐标转为[-1, 1]^3，方便后面往显示屏幕映射
/// </summary>
/// <param name="_near">相机近平面距离</param>
/// <param name="_far">相机远平面距离</param>
/// <param name="_ratio">相机宽高比</param>
/// <param name="_fov_angle">相机视场角, 角度制</param>
/// <returns>4 * 4的投影变换矩阵</returns>
Matrix<float, 4, 4> getprojectionmatrix(float _near, float _far, float _ratio, float _fov_angle);


/// <summary>
/// 计算视口矩阵，获取将[-1, 1]^3的坐标映射到[x_range, y_range, z_range]的坐标范围（映射到屏幕空间）
/// </summary>
/// <param name="x_range">x的取值范围</param>
/// <param name="y_range">y的取值范围</param>
/// <param name="z_range">z的取值范围</param>
/// <returns>4 * 4的转换矩阵</returns>
Matrix<float, 4, 4> getviewportmatrix(Vector2f x_range, Vector2f y_range, Vector2f z_range);