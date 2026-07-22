#include<iostream>
#include<vector>
#include<string>
#include<fstream>
#include<sstream>
#include<stdlib.h>
#include<map>
#include<algorithm>

using namespace std;

int main(int argc,char* argv[])
{
	ifstream ifs;
	istringstream istr;
	ofstream ofs(argv[3]);

	
	string temp;
	string temp_1;
	string temp_2;
	string temp_3;
	string temp_pattern;
	string temp_read;
	vector<int> vec_location;
	int read_l;
	int read_r;
	
	map<string,vector<int> > hash;//pattern --> left ; right	
	map<string,vector<int> >::iterator iter;
	

	ifs.open(argv[1]);//UP_location_Strep26.txt
	while(getline(ifs,temp))
	{
		if(temp[0]=='>')
		{
			vec_location.clear();
			istr.str(temp);
			istr>>temp_1>>temp_2>>temp_3;
			istr.clear();
			
			temp_pattern=temp_2;
			
			getline(ifs,temp);
			getline(ifs,temp);
			istr.str(temp);
			istr>>temp_1>>temp_2;
			istr.clear();
			vec_location.push_back(atoi(temp_1.c_str()));
			vec_location.push_back(atoi(temp_2.c_str()));
			hash[temp_pattern]=vec_location;	
		}
	}
	ifs.close();
	//hash completed
	
		
	ifs.open(argv[2]);
	while(getline(ifs,temp))
	{
		if(temp[0]=='>')
		{
			temp_read=temp;
			getline(ifs,temp);
			istr.str(temp);
			istr>>temp_1>>temp_2>>temp_3;
			istr.clear();
			
			temp_pattern=temp_1;
			iter=hash.find(temp_pattern);
			if(iter!=hash.end())
			{
				vec_location=iter->second;//pattern: left, right
				read_l=atoi(temp_2.c_str());
				read_r=atoi(temp_3.c_str());
				if((read_l<=vec_location[0])&&(read_r>=vec_location[1]))//this read is valid
				{
					ofs<<temp_read<<"\t"<<temp_pattern<<"\n";
				}
			}
			if(iter==hash.end())
			{
				cout<<"error:"<<temp_read<<"\n";
			}
		}
	}	
	ifs.close();
		
		
		

	


	hash.clear();
	vec_location.clear();


	return 0;
	
}














