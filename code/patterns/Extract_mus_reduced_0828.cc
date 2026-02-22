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
	ofstream ofs(argv[3]);
	int up_threshold=atoi(argv[4]);

	string temp;
	string temp_1;
	string temp_2;
	string temp_genome;
	vector<string> vec_time;
	int flag;
	
	
	map<string,vector<string> > hash;//genome --> pattern
	map<string,vector<string> >::iterator iter;
	
	ifs.open(argv[1]); 
	while(getline(ifs,temp))
	{		
		istr.str(temp);
		istr>>temp_1>>temp_2;
		istr.clear();
		temp_genome=temp_1;
//cout<<"temp_genome1:"<<temp_genome<<"\n";		
		vec_time.clear();
		getline(ifs,temp);
		istr.str(temp);
		while(istr>>temp_1)
		{
			vec_time.push_back(temp_1);
		}
		istr.clear();
		
		iter=hash.find(temp_genome);
		if(iter==hash.end())
		{
			hash[temp_genome]=vec_time;
		}
		if(iter!=hash.end())
		{
			cout<<"error1:"<<temp_genome<<"\n";//this genome show up twice
		}	
	}
	ifs.close();

	int up_num;
	ifs.open(argv[2]);
	while(getline(ifs,temp))
	{
		//ofs<<temp<<"\n";
		istr.str(temp);
		istr>>temp_1>>temp_2;
		istr.clear();
		
		up_num=atoi(temp_2.c_str());
		if(up_num>up_threshold)
		{
			ofs<<temp<<"\n";
			temp_genome=temp_1;
	//cout<<"temp_genome2:"<<temp_genome<<"\n";
			iter=hash.find(temp_genome);
			if(iter!=hash.end())
			{
				vec_time=iter->second;
			}
			if(iter==hash.end())
			{
				cout<<"error2:"<<temp_genome<<"\n";//this genome not show up in reduced patterns
			}	
			
			
			getline(ifs,temp);
			istr.str(temp);
			while(istr>>temp_1)
			{
				flag=atoi(temp_1.c_str());
				ofs<<vec_time[flag-1]<<"\t";
				
			}
			istr.clear();
			ofs<<"\n";
		}
		if(up_num<=up_threshold)
		{
			getline(ifs,temp);
		}
	}
	ifs.close();
	

	hash.clear();
	return 0;
}



