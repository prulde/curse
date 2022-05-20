#include "class2.h"

cmp_files::cmp_files(string pat, char del, int numt,int numb)
{
	patchan = pat;
	rpath = pat;
	delim = del;
	dest = rpath.c_str();
	nt = numt;
	nb = numb;
}
void cmp_files::setParams(vector<string> fnames,float** res,int res_size)
{
	global.change_name(fnames[0]);
	names = fnames;
	result = res;
	result_size = res_size;
	cmpAll();
}
void cmp_files::cmpAll()
{

	int i, k = 0;
	for (i = 0; i < result_size - 1; ++i)//(последний файл нисчем не сравниваем)
	{
		curfileN = 0;
		if (auto dir = opendir(dest))
		{
			while (auto f = readdir(dir))
			{
				if (!f->d_name || f->d_name[0] == '.')
				{
					continue; // Skip everything that starts with a dot
				}
				patchan = rpath;
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
					//curfile++;
					file Fobj(f->d_name);
					ifstream fs(patchan);

					while (getline(fs, str, '\n'))//while(!fs.eof())
					{
						if (!cin.eof())
						{
							str += ';';
							Fobj.split(str);
							k++;
						}
					}
					//Fobj.out();
					res_table(compareF(global.get_nums(), Fobj.get_nums()), global.get_name(), Fobj.get_name());//заполнение таблицы над диагональю 

					//cout << f->d_name << " - notmain" << endl;
					fs.close();
				}
				curfileN++;

			}
			closedir(dir);
		}
	}

	print_table();
}
float cmp_files::compareF(const vector <float>& main, const vector <float>& notmain)//сравнение файлов file& main, const file& notmain
{
	float persent = 0;
	for (int i = 0; i < main.size(); ++i)
	{

		if ((notmain[i] + nb) <= main[i] && main[i] <= (notmain[i] + nt))
		{
			persent++;
		}
	}
	return persent;
}
void cmp_files::res_table(float a, string main, string notmain)
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
					result[i][j] = a / result_size;
					result[j][i] = a / result_size;
				}
			}
		}
	}
	//log
	ofstream log("log.txt", std::ios::binary | std::ios::app);
	log<< "current file: " << main << endl;
	log << "comparing with: " << notmain << endl << endl;
	log.close();
	print_table();
	//log << endl;
	/*cout << "current file: " << main << endl;
	cout << "comparing with: " << notmain << endl << endl;
	print_table();
	cout << endl;*/
	
}

void cmp_files::print_table()
{
	int i, j;
	ofstream log("log.txt",std::ios::binary | std::ios::app);
	for (i = 0; i < result_size; ++i)
	{
		if (i == 0)
		{
			log << '\t';
			for (int k = 0; k < result_size; ++k)
			{
				log << names[k] << '\t';
			}
			log << endl;
		}
		log << names[i] << '\t';
		for (j = 0; j < result_size; ++j)
		{
			if (i == j)
				log << '-' << '\t';
			else
			{
				if (result[i][j] == 1)
					log << result[i][j] * 100 << '%' << '\t';
				else
					log << result[i][j] << '%' << '\t';
			}

		}
		log << endl;
	}
	//log
	for (i = 0; i < result_size * 10; ++i)
	{
		log << "-";
	}
	log << endl;
	log.close();
}