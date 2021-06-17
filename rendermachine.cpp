#include "rendermachine.h"
#include "softgl.h"
#include <iostream>

void RenderMachine::AddTriangle(Vector2f p1, Vector2f p2, Vector2f p3)
{
    //cout << p1[0] << ":" << p1[1] << endl;
    //cout << p2[0] << ":" << p2[1] << endl;
    //cout << p3[0] << ":" << p3[1] << endl;


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

vector<triangle2f> RenderMachine::GetTriangles()
{
    return triangles;
}

void RenderMachineDraw(HDC& hdc, RenderMachine* prm)
{
    vector<triangle2f> triangles = prm->GetTriangles();
    for (int i = 0; i < triangles.size(); i++)
    {
        triangle2f tri = triangles[i];
        Vector2f vecs[3] = { tri.p1, tri.p2, tri.p3 };
        drawtriangle(hdc, vecs);
    }
}