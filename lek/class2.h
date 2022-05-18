#include "bibl.h"
#include "class3.h"
#pragma once

class cmp_files
{
private:
	string patchan,rpath,str;
	file global;
	int nt,nb,result_size,curfileN=0;
	char delim;
	const char* dest;
	float** result;//result matrix w%
	vector<string> names;//file names

	float compareF(const vector <float>&, const vector <float>&);
	void res_table(float, string, string);
	void print_table();
	void cmpAll();
public:
	cmp_files(string,char,int,int);
	void setParams(vector<string>,float**,int);
};