#include<iostream>
#include<map>
#include<vector>
#include<fstream>
#include<sstream>
#include<string>
#include<stdlib.h>
#include<cmath>
#include<algorithm>

using namespace std;

int main(int argc,char* argv[])
{
	ifstream ifs;
	istringstream istr;
	ofstream ofs(argv[2]);
	string temp_1;
	string temp_2;
	string temp_3;
	string temp_4;
	string temp_5;
	string temp_6;
	string temp_7;
	string temp_8;
	string temp_9;
	string temp;
	map<string,vector<string> > hash;
	map<string,vector<string> >::iterator iter;
	vector<string> vec_time;
	vector<string>::iterator iter_1;
	int i;

	
	ifs.open(argv[1]);
	while(getline(ifs,temp))
	{
		istr.str(temp);
		istr>>temp_1>>temp_2>>temp_3>>temp_4>>temp_5>>temp_6>>temp_7>>temp_8>>temp_9;
		istr.clear();
		
		if((temp_1=="S")||(temp_1=="H"))
		{
			iter=hash.find(temp_2);
			if(iter==hash.end())//not exist
			{
				vec_time.clear();
				vec_time.push_back(temp_9);
				hash[temp_2]=vec_time;
			}
			if(iter!=hash.end())//exist
			{
				vec_time=iter->second;
				vec_time.push_back(temp_9);
				iter->second=vec_time;
			}
		}
	}
	ifs.close();

	for(iter=hash.begin();iter!=hash.end();iter++)
	{
		ofs<<">cluster_"<<iter->first<<"\n";
		vec_time=iter->second;
//cout<<"vec_time.size():"<<vec_time.size()<<"\n";
		for(i=0;i<vec_time.size();i++)
		{
			ofs<<vec_time[i]<<"\t";
		}
		ofs<<vec_time.size();
		ofs<<"\n";
	}
	
	hash.clear();
	vec_time.clear();
	return 0;
}
		
		
			