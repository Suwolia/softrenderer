#include "rendermachine.h"
#include "softgl.h"
#include <iostream>

RenderMachine::RenderMachine()
{
    _view_mat.Identity();
    _proj_mat.Identity();
    _viewport_mat.Identity();
}

void RenderMachine::AddTriangle(Vector2f p1, Vector2f p2, Vector2f p3)
{
    triangle2f tri = { p1, p2, p3 };
    triangles.push_back(tri);
}

void RenderMachine::MoveTriangles(Vector2f vec)
{
    for (auto tri = begin(triangles); tri != end(triangles); tri++)
    {
        (*tri).p1 += vec;
        (*tri).p2 += vec;
        (*tri).p3 += vec;
    }
}

void RenderMachine::MoveTriangles(float x, float y)
{
    for (auto tri = begin(triangles); tri != end(triangles); tri++)
    {
        (*tri).p1[0] += x;
        (*tri).p1[1] += y;

        (*tri).p2[0] += x;
        (*tri).p2[1] += y;

        (*tri).p3[0] += x;
        (*tri).p3[1] += y;
    }
}

vector<triangle2f>* RenderMachine::GetTriangles()
{
    return &triangles;
}

void RenderMachine::Draw(HDC& hdc)
{
    Matrix<float, 4, 4> _final_mat = _GetFinalMat();
    cout << _final_mat << endl;

    for (auto pmodel = begin(_model_vector); pmodel != end(_model_vector); pmodel++)
    {
        Matrix<float, 4, 4> _mat = _final_mat * (*pmodel)->GetModelMatrix();
        vector<vector<int>>* _indexes = (*pmodel)->GetFaceIndexes();
        for (auto p_index_vec = begin(*_indexes); p_index_vec != end(*_indexes); p_index_vec++)
        {
            int v1_index = (*p_index_vec)[0] - 1;
            int v2_index = (*p_index_vec)[3] - 1;
            int v3_index = (*p_index_vec)[6] - 1;

            cout << v1_index << " " << v2_index << " " << v3_index << endl;
            Vector3f v1 = (*pmodel)->GetVertic(v1_index);
            Vector3f v2 = (*pmodel)->GetVertic(v2_index);
            Vector3f v3 = (*pmodel)->GetVertic(v3_index);
            Vector4f _v1(v1[0], v1[1], v1[2], 1);
            Vector4f _v2(v2[0], v2[1], v2[2], 1);
            Vector4f _v3(v3[0], v3[1], v3[2], 1);

            _v1 = _mat * _v1;
            _v2 = _mat * _v2;
            _v3 = _mat * _v3;

            //Vector2f __v1(_v1[0] / _v1[3], _v1[1] / _v1[3]);
            //Vector2f __v2(_v2[0] / _v2[3], _v2[1] / _v2[3]);
            //Vector2f __v3(_v3[0] / _v3[3], _v3[1] / _v3[3]);

            Vector2f __v1(_v1[0], _v1[1]);
            Vector2f __v2(_v2[0], _v2[1]);
            Vector2f __v3(_v3[0], _v3[1]);


            cout << __v1[0] << "/" << __v1[1] << "/" << " "
                 << __v2[0] << "/" << __v2[1] << "/" << " "
                 << __v3[0] << "/" << __v3[1] << "/" << endl;

            //Vector2f vecs[3] = { v1, v2, v3 };
            //drawtriangle(hdc, vecs);
        }
    }
}

/// <summary>
/// 设置相机变换矩阵
/// </summary>
/// <param name="cam_pos">相机位置</param>
/// <param name="lookat_pos">相机看向的位置</param>
/// <param name="up">相机的y向量</param>
void RenderMachine::LookAt(Vector3f cam_pos, Vector3f lookat_pos, Vector3f up)
{
    _view_mat = getviewmatrix(cam_pos, lookat_pos, up);
}

/// <summary>
/// 设置相机投影矩阵
/// </summary>
/// <param name="_near">相机近平面</param>
/// <param name="_far">相机远平面</param>
/// <param name="_ratio">相机宽高比</param>
/// <param name="_fov">相机视场角，角度制</param>
void RenderMachine::SetupCamera(float _near, float _far, float _ratio, float _fov_angle)
{
    _proj_mat = getprojectionmatrix(_near, _far, _ratio, _fov_angle);
}

/// <summary>
/// 设置视口转换矩阵
/// </summary>
/// <param name="x_range">x取值范围</param>
/// <param name="y_range">y取值范围</param>
/// <param name="z_range">z取值范围</param>
void RenderMachine::SetupViewport(Vector2f x_range, Vector2f y_range, Vector2f z_range)
{
    _viewport_mat = getviewportmatrix(x_range, y_range, z_range);
}

Matrix<float, 4, 4> RenderMachine::_GetFinalMat()
{
    return _viewport_mat * _proj_mat * _view_mat;
}

void RenderMachine::AddModel(Model* p_model)
{
    _model_vector.push_back(p_model);
}