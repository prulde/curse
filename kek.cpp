#include <iostream>
#include <fstream>
#include "dirent.h"
#include <string>
#include <vector>
#include <sstream>

using namespace std;

class par
{
protected:
	int numbot, numtop,result_size;
	char delim;
	float** result;//result matrix w%
	vector<string> names;
public:
	par()
	{
		numbot = -1;
		numtop = 1;
		delim = ';';
	}
	par(int a, int b, char c)
	{
		numbot = a;
		numtop = b;
		delim = c;
	}
	void set_size(int a, vector <string>& files)
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
	void res_table(float a,string main,string notmain)
	{
		int i, j;
		for (i = 0; i < result_size; ++i)
		{
			if (names[i] == main)
			{
				for (j = 0; j < result_size; ++j)
				{
					if (names[j] == notmain)
					{
						result[i][j] = a/result_size;
						result[j][i] = a/result_size;
					}
				}
			}
		}
	}

	void print_table()
	{
		int i, j;
		for (i = 0; i < result_size; ++i)
		{
			if (i == 0)
			{
				cout << '\t';
				for (int k = 0; k < result_size; ++k)
				{
					cout << names[k] << '\t';
				}
				cout << endl;
			}
			cout << names[i]<< '\t';
			for (j = 0; j < result_size; ++j)
			{
				if (i == j)
					cout<< '-' << '\t';
				else
				{
					if (result[i][j] == 1)
						cout << result[i][j] * 100 << '%' << '\t';
					else
						cout << result[i][j] << '%' << '\t';
				}
					
			}
			cout << endl;
		}
	}
};

class file:protected par
{
private:
	vector<float> nums;
	string Fname;
public:
	file(string a)
	{
		Fname = a;
	}
	void change_name(string a)
	{
		Fname = a;
	}
	string get_name()
	{
		return Fname;
	}
	void split(string s)//vector <float>& res
	{
		istringstream iss(s);
		string item;
		while (getline(iss, item, delim))
		{
			nums.push_back(stof(item));
			
		}
	}
	float compareF(class file& notmain)//сравнение файлов
	{
		int persent = 0;
		for (int i = 0; i < nums.size(); ++i)
		{
			if ((notmain.nums[i]+numbot) <= nums[i] && nums[i]<=(notmain.nums[i]+numtop))
			{
				persent++;
			}
		}
		return persent;
	}
	void out()
	{
		for (int i = 0; i < nums.size(); ++i)
		{
			cout << nums[i] << " ";
		}
	}
	void clear()
	{
		nums.clear();
	}
	~file()
	{
		
	}
};


int main()
{
	int k = 0, j, i;
	int unic = 0, curfileN = 0, curfile = 0;
	vector<string> ring;//считывание
	string str;
	string pat = "C:/Users/PC/Desktop/well/";//cin pat
	string patchan = pat;
	const char* to = pat.c_str();
	//cin delim,pat,range

	par obj(-2, 2, ';');

	if (auto dir = opendir(to))
	{

		while (auto f = readdir(dir))
		{
			if (!f->d_name || f->d_name[0] == '.')
				continue; // Skip everything that starts with a dot

			ring.push_back(f->d_name);
			printf("File: %s\n", f->d_name);
			unic++;
		}
		closedir(dir);
	}
	cout << endl << "Number of files:" << unic << endl << endl;
	obj.set_size(unic, ring);//кол-во файлов
	file global(ring[0]);
	ring.clear();

	//'\n'

	for (i = 0; i < unic - 1; ++i)//cm pic(последний файл нисчем не сравниваем)
	{
		curfileN = 0;
		if (auto dir = opendir(to))
		{
			while (auto f = readdir(dir))
			{
				if (!f->d_name || f->d_name[0] == '.')
				{
					continue; // Skip everything that starts with a dot
				}
				patchan = pat;
				patchan += f->d_name;
				//cout << patchan << endl;
				if (curfileN == i)
				{
					global.clear();
					global.change_name(f->d_name);

					ifstream fs(patchan);

					while (getline(fs, str, '\n'))//while(!fs.eof())
					{
						if (!cin.eof())
						{
							str += ';';
							global.split(str);
						}
					}
					//cout << f->d_name << " - main" << endl;
					fs.close();
				}
				else if (curfileN > i)
				{
					curfile++;
					file Fobj(f->d_name);
					ifstream fs(patchan);

					while (getline(fs, str, '\n'))//while(!fs.eof())
					{
						if (!cin.eof())
						{
							str += ';';
							Fobj.split(str);
							ring.push_back(str);
							k++;
						}
					}
					//Fobj.out();
					obj.res_table(global.compareF(Fobj), global.get_name(), Fobj.get_name());//заполнение таблицы над диагональю
					//cout << f->d_name << " - notmain" << endl;
					fs.close();
				}
				curfileN++;

			}
			closedir(dir);
		}
	}
	obj.print_table();
}