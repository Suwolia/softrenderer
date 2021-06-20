
#include <iostream>
#include <fstream>
#include <string>
#include "model.h"

using namespace std;

Model::Model(const char* filename):_scale(Vector3f(1, 1, 1))
{
	ifstream ifs;
	ifs.open(filename, ios::in);
	string line;
	string flag;
	string index_str;
	string trash;
	Vector3f temp;
	while (!ifs.eof())
	{
		getline(ifs, line);
		istringstream iss(line);
		while (!iss.eof())
		{
			if (flag.compare("") == 0)
			{
				iss >> flag;
			}
			else if(flag.compare("v") == 0)
			{
				iss >> temp[0] >> temp[1] >> temp[2];
				_vertics.push_back(temp);
			}
			else if (flag.compare("vt") == 0)
			{
				iss >> temp[0] >> temp[1] >> temp[2];
				_texvertics.push_back(temp);
			}
			else if (flag.compare("vn") == 0)
			{
				iss >> temp[0] >> temp[1] >> temp[2];
				_normvertics.push_back(temp);
			}
			else if (flag.compare("f") == 0)
			{
				vector<int> indexes;
				for (int i = 0; i < 3; i++)
				{
					char slash;
					int vindex;
					int vtindex;
					int vnindex;
					iss >> vindex >> slash >> vtindex >> slash >> vnindex;
					indexes.push_back(vindex);
					indexes.push_back(vtindex);
					indexes.push_back(vnindex);
				}
				_faceindex.push_back(indexes);
			}
			else
			{
				iss >> trash;
			}
		}
		flag = "";
	}
	cout << "Read file " << filename << " Succeed" << endl;
	cout << "Vertics: " << _vertics.size() << endl;
	cout << "Texture Vertics: " << _texvertics.size() << endl;
	cout << "Normal Vertics: " << _normvertics.size() << endl;
	cout << "Face: " << _faceindex.size() << endl;
	ifs.close();
}


void Model::SetPosition(float x, float y, float z)
{
	_position[0] = x;
	_position[1] = y;
	_position[2] = z;
}


void Model::SetScale(float x, float y, float z)
{
	_scale[0] = x;
	_scale[1] = y;
	_scale[2] = z;
}


Matrix<float, 4, 4> Model::GetModelMatrix()
{
	Matrix<float, 4, 4> _mat;
	_mat.setIdentity();
	_mat.row(0)[0] = _scale[0];
	_mat.row(1)[1] = _scale[1];
	_mat.row(2)[2] = _scale[2];
	_mat.row(0)[3] = _position[0];
	_mat.row(1)[3] = _position[1];
	_mat.row(2)[3] = _position[2];
	return _mat;
}