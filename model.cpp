
#include <iostream>
#include <fstream>
#include <string>
#include "model.h"

using namespace std;

Model::Model(const char* filename)
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