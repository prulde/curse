#include "bibl.h"
#include "class2.h"

class getInfo
{
private:
	string pat;
	char delim;
	const char* dest;
	int numtop, numbot, result_size;
	float** result;//result matrix w%
	vector<string> names;//file names
	cmp_files obj;

	void getNames();
	void set_size(int, vector <string>&);

public:
	getInfo(string, char, int, int);
};
