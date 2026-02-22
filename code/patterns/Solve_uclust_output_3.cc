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
	ifstream ifs_1;
	istringstream istr;
	ofstream ofs(argv[4]);
	string temp_1;
	string temp_2;
	string strain_name;
	string temp;
	string gene_name;
	string direction;
	map<string,vector<int> > hash;
	map<string,vector<int> >::iterator iter;
	map<string,int> hash_name;
	vector<int> vec_time;

	
	
	ifs.open(argv[1]);
	while(getline(ifs,temp))
	{
		istr.str(temp);
		istr>>temp_1>>temp_2;
		istr.clear();	
		hash_name[temp_1]=atoi(temp_2.c_str());
	}
	ifs.close();
	
//cout<<"hash_name.size():"<<hash_name.size()<<"\n";
	
	ifs_1.open(argv[3]);
	ifs.open(argv[2]);
	while(getline(ifs,temp))
	{
		vec_time.clear();
		direction="+";
		
		istr.str(temp);
		istr>>temp_1;//strain name
		strain_name=temp_1;
//cout<<"strain_name:"<<strain_name<<"\n";
		iter=hash.find(strain_name);
		if(iter!=hash.end())//exist
		{
			vec_time=iter->second;
		}
		if(iter==hash.end())//not exist
		{
			vec_time.clear();
			hash[strain_name]=vec_time;
		}
		while(istr>>temp_1)
		{
			if(temp_1=="complement")
			{
				direction="-";
			}
			
		}
		istr.clear();
		
		getline(ifs_1,temp);
//cout<<"hash_name[temp]:"<<hash_name[temp]<<"\n";
		if(direction=="+")
		{
			vec_time.push_back(hash_name[temp]);
		}
		if(direction=="-")
		{
			vec_time.push_back(-1*hash_name[temp]);
		}
		hash[strain_name]=vec_time;
	}
	ifs.close();
	ifs_1.close();

//cout<<"hash.size():"<<hash.size()<<"\n";


	for(iter=hash.begin();iter!=hash.end();iter++)
	{
		ofs<<">"<<iter->first<<"\n";
		vec_time=iter->second;
		for(int i=0;i<vec_time.size();i++)
		{
			ofs<<vec_time[i]<<"\t";
		}
		ofs<<"\n";
	}

	ofs.close();	
	hash.clear();
	vec_time.clear();
	return 0;
}
		
		
			