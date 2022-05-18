#include "class3.h"

file::file(string nam)
{
	name = nam;
}
file::file()
{
	name = "null";
}
void file::change_name(string n)
{
	name = n;
}
string file::get_name()
{
	return name;
}
vector<float> file::get_nums()
{
	return nums;
}
void file::split(string s)//vector <float>& res
{
	istringstream iss(s);
	string item;
	while (getline(iss, item, ';'))//delim
	{
		nums.push_back(stof(item));
	}

}
void file::out()
{
	for (int i = 0; i < nums.size(); ++i)
	{
		cout << nums[i];
	}
	cout << endl;
}
void file::clear()
{
	nums.clear();
}