#pragma once

#include <vector>
#include <Eigen/Dense>

using namespace Eigen;
using namespace std;

class Model
{
public:
	Model(const char*);
	~Model() {};
	int nface(){ return _faceindex.size(); }
private:
	vector<Vector3f> _vertics;
	vector<Vector3f> _texvertics;
	vector<Vector3f> _normvertics;
	vector<vector<int>> _faceindex;
};