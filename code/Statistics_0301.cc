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
	istringstream istr_1;
	ofstream ofs(argv[6]);

	string temp;
	string temp_1;
	string temp_2;
	
	string temp_genome;

	vector<string> vec_time;

	
	map<string,vector<string> > hash;//genome -> Num of unique patterns+Num of mapping reads+Num of unique patters mapped by reads+Abundance

	map<string,vector<string> >::iterator iter;
	
	ifs.open(argv[1]); //Strep26_mus_noreverse.txt
	while(getline(ifs,temp))
	{
		istr.str(temp);
		istr>>temp_1>>temp_2;
		istr.clear();
		
		vec_time.clear();
		vec_time.push_back(temp_2);
		vec_time.push_back("0");
		vec_time.push_back("0");
		vec_time.push_back("0");
		vec_time.push_back("0");
		hash[temp_1]=vec_time;
		getline(ifs,temp);	
	}
	ifs.close();
	
	
	
	
	
	ifs.open(argv[2]); //Strep26_mus_reduced.txt
	while(getline(ifs,temp))
	{
		istr.str(temp);
		istr>>temp_1>>temp_2;
		istr.clear();
		
		iter=hash.find(temp_1);
		if(iter==hash.end())
		{
			vec_time.clear();
			vec_time.push_back("0");
			vec_time.push_back(temp_2);
			vec_time.push_back("0");
			vec_time.push_back("0");
			vec_time.push_back("0");
			hash[temp_1]=vec_time;
		}
		if(iter!=hash.end())
		{
			vec_time=iter->second;
			vec_time[1]=temp_2;
			hash[temp_1]=vec_time;
		}	
		
		getline(ifs,temp);	
	}
	ifs.close();

	
	ifs.open(argv[3]); //output_genome_nomulti_SP3.txt
	while(getline(ifs,temp))
	{
		
		istr.str(temp);
		istr>>temp_1>>temp_2;
		istr.clear();
		
		iter=hash.find(temp_1);
		if(iter==hash.end())
		{
			vec_time.clear();
			vec_time.push_back("0");
			vec_time.push_back("0");
			vec_time.push_back(temp_2);
			vec_time.push_back("0");
			vec_time.push_back("0");
			hash[temp_1]=vec_time;
		}
		if(iter!=hash.end())
		{
			vec_time=iter->second;
			vec_time[2]=temp_2;
			hash[temp_1]=vec_time;
		}		
	}	
	ifs.close();
	
	
	ifs.open(argv[4]); //output_pattern_read_SP3.txt
	while(getline(ifs,temp))
	{
		
		istr.str(temp);
		istr>>temp_1>>temp_2;
		istr.clear();
		
		iter=hash.find(temp_1);
		if(iter==hash.end())
		{
			vec_time.clear();
			vec_time.push_back("0");
			vec_time.push_back("0");
			vec_time.push_back("0");
			vec_time.push_back(temp_2);
			vec_time.push_back("0");
			hash[temp_1]=vec_time;
		}
		if(iter!=hash.end())
		{
			vec_time=iter->second;
			vec_time[3]=temp_2;
			hash[temp_1]=vec_time;
		}	

		getline(ifs,temp);
	}	
	ifs.close();
	
	
	ifs.open(argv[5]); //output_pattern_read_SP3.txt
	while(getline(ifs,temp))
	{
		
		istr.str(temp);
		istr>>temp_1>>temp_2;
		istr.clear();
		
		iter=hash.find(temp_1);
		if(iter==hash.end())
		{
//cout<<"1:"<<temp_2<<"\n";
			vec_time.clear();
			vec_time.push_back("0");
			vec_time.push_back("0");
			vec_time.push_back("0");
			vec_time.push_back("0");
			vec_time.push_back(temp_2);
			hash[temp_1]=vec_time;
		}
		if(iter!=hash.end())
		{
//cout<<"2:"<<temp_2<<"\n";
			vec_time=iter->second;
			vec_time[4]=temp_2;
			hash[temp_1]=vec_time;
		}	

	}	
	ifs.close();
	
	int i;
	float abundance_2;
	float pattern_num;
	float read_num;
	for(iter=hash.begin();iter!=hash.end();iter++)
	{
		vec_time=iter->second;
		ofs<<iter->first;
		for(i=0;i<vec_time.size();i++)
		{
			ofs<<"\t"<<vec_time[i];
		}
		//ofs<<"\n";
		
		pattern_num=atof(vec_time[1].c_str());
		read_num=atof(vec_time[2].c_str());
		if(pattern_num==0)
		{
			ofs<<"\t"<<"0"<<"\n";
		}
		if(pattern_num!=0)
		{
			abundance_2=read_num/pattern_num;
			ofs<<"\t"<<abundance_2<<"\n";
		}
	}
	

	
	hash.clear();
	vec_time.clear();
	
	return 0;
}



