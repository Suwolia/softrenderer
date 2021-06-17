#include "softgl.h"
#include <limits>
#include <iostream>

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