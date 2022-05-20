#include "bibl.h"

class file
{
private:
	string name;
	vector<float> nums;
public:
	file(string);
	file();
	void change_name(string);
	string get_name();
	vector<float> get_nums();
	void split(string);
	void clear();
}; 