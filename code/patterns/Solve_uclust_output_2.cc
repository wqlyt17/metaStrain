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
	string temp;
	string temp_cluster;
	map<string,string> hash;
	map<string,string>::iterator iter;
	vector<string> vec_time;
	int i;
	
	ifs.open(argv[1]);
	while(getline(ifs,temp))
	{
		temp_cluster=temp;
		
		getline(ifs,temp);
		vec_time.clear();
		istr.str(temp);
		while(istr>>temp_1)
		{
			vec_time.push_back(temp_1);
//cout<<temp_1<<"\n";
		}
		istr.clear();
		
		for(i=0;i<vec_time.size()-1;i++)
		{
			iter=hash.find(vec_time[i]);
			if(iter!=hash.end())
			{
				cout<<"error:"<<vec_time[i]<<"\n";
			}
			if(iter==hash.end())
			{
				hash[vec_time[i]]=temp_cluster;
			}
		}	
	}
	ifs.close();

//cout<<"hash.size():"<<hash.size()<<"\n";	
	for(iter=hash.begin();iter!=hash.end();iter++)
	{
		ofs<<iter->first<<"\t"<<iter->second<<"\n";
	}
	
	hash.clear();
	vec_time.clear();
	return 0;
}
		
		
			