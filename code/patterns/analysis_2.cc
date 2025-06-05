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

	string temp;
	string temp_1;
	string temp_2;
	string temp_3;
	vector<string> vec_time;
	int i;
	
	
	map<string,vector<string> > hash;//genome --> pattern
	map<string,vector<string> >::iterator iter;
	
	ifs.open(argv[1]); 
	while(getline(ifs,temp))
	{
				
		istr.str(temp);
		istr>>temp_1>>temp_2>>temp_3;
		istr.clear();
		
		if(temp_1==temp_3)//the read map to its corresonding genome
		{
			iter=hash.find(temp_3);
			if(iter==hash.end())
			{
				vec_time.clear();
				vec_time.push_back(temp_2);
				hash[temp_3]=vec_time;
			}
			if(iter!=hash.end())
			{
				vec_time=iter->second;
				vec_time.push_back(temp_2);
				hash[temp_3]=vec_time;
			}	
		}
	}
	ifs.close();

	int sum=0;
	for(iter=hash.begin();iter!=hash.end();iter++)
	{
		vec_time=iter->second;
		sum++;
		ofs<<iter->first<<"\t"<<vec_time.size()<<"\n";
		for(i=0;i<vec_time.size();i++)
		{
			//ofs<<iter->first<<"_"<<vec_time[i]<<"\t";
			ofs<<vec_time[i]<<"\t";
		}
		ofs<<"\n";
	}

	//cout<<"sum:"<<sum<<"\n";
	hash.clear();
	return 0;
}



