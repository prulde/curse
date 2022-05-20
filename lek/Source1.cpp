#include "class1.h"

getInfo::getInfo(string path, char deli, int nt, int nb) :obj(path, deli, nt, nb)
{
	delim = deli;
	pat = path;
	dest = pat.c_str();
	numbot = nb;
	numtop = nt;
	getInfo::getNames();
}

void getInfo::getNames()
{
	vector<string> ring;
	ofstream log("log.txt");
	log.clear();
	log << "dir: " << pat << endl<<delim<<endl<<numbot<<" "<<numtop<<endl;
	int unic=0;
	if (auto dir = opendir(dest))
	{

		while (auto f = readdir(dir))
		{
			if (!f->d_name || f->d_name[0] == '.')
				continue; // Skip everything that starts with a dot

			ring.push_back(f->d_name);
			log << "File: " << f->d_name << endl;
			//printf("File: %s\n", f->d_name);
			unic++;
		}
		closedir(dir);
	}
	else
	{
		log << "error: incorrect path";
		return;
	}
	
	log << endl << "Number of files:" << unic << endl << endl;
	set_size(unic, ring);//кол-во файлов
	ring.clear();
	log.close();
	obj.setParams(names,result,result_size);
}
void getInfo::set_size(int a, vector <string>& files)
{
	result = new float* [a];//строки
	result_size = a;
	names = files;
	for (int i = 0; i < a; ++i)
	{
		result[i] = new float[a];//столбцы
		for (int j = 0; j < a; ++j)
		{
			result[i][j] = 0;
		}
	}
}

int main()
{
	string path;//"C:/Users/PC/Desktop/well/"
	char delim;//
	int nt, nb;
	cin >> path >> delim >> nb >> nt;
	getInfo obj(path,delim,nt,nb);
}