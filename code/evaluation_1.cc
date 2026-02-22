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
	ofstream ofs(argv[4]);//abundance

	string temp;
	string temp_1;
	string temp_2;
	string temp_3;
	string temp_4;
	string temp_5;
	string temp_6;
	string temp_7;
	
	int i;
	map<string,double> hash_strain_abundance;
	map<string,double>::iterator iter_sb;
	
	map<string,vector<string> > hash_strain_num;
	map<string,vector<string> >::iterator iter_num;
	vector<string> vec_time;
	
	
	ifs.open(argv[1]);//statistics_sort.txt
	while(getline(ifs,temp))
	{
		istr.str(temp);
		istr>>temp_1>>temp_2>>temp_3>>temp_4>>temp_5>>temp_6>>temp_7;
		istr.clear();
		
		iter_sb=hash_strain_abundance.find(temp_1);
		if(iter_sb==hash_strain_abundance.end())
		{	
			hash_strain_abundance[temp_1]=atof(temp_7.c_str());	
		}
		if(iter_sb!=hash_strain_abundance.end())
		{
			cout<<"error3:"<<temp_1<<"\n";
		}	
	}
	ifs.close();
	
	
	ifs.open(argv[2]);//strain_num.txt
	while(getline(ifs,temp))
	{
		istr.str(temp);
		istr>>temp_1>>temp_2>>temp_3>>temp_4;//1 0/1; 2 speies; 3 genome; 4 num
		istr.clear();
		if(temp_1=="0")//strain without UPs;if this species has no CP;then hash_strain_num has not its strain genome names
		{
			iter_num=hash_strain_num.find(temp_2);
			if(iter_num==hash_strain_num.end())
			{
				vec_time.clear();
				vec_time.push_back(temp_3);
				hash_strain_num[temp_2]=vec_time;
			}
			if(iter_num!=hash_strain_num.end())
			{
				vec_time=iter_num->second;
				vec_time.push_back(temp_3);
				hash_strain_num[temp_2]=vec_time;
			}	
		}
	}
	ifs.close();
	
	string temp_name;
	int tag;
	ifs.open(argv[3]);//QuadProg_output.txt
	while(getline(ifs,temp))
	{
		if(temp[0]=='*')
		{
			iter_num=hash_strain_num.find(temp);
			if(iter_num==hash_strain_num.end())//these species has not UP; that is all strains of this species are strains with UPs
			{
				//cout<<"error1:"<<temp<<"\n";
			}
			if(iter_num!=hash_strain_num.end())
			{
				vec_time=iter_num->second;
				
				getline(ifs,temp);//f
		    	getline(ifs,temp);//x
		    	getline(ifs,temp);
		    	tag=0;
		    	istr.str(temp);
			    while(istr>>temp_1)
		        {
				    temp_name=vec_time[tag];
				    iter_sb=hash_strain_abundance.find(temp_name);
				    if(iter_sb!=hash_strain_abundance.end())
			    	{
				    	cout<<"error2:"<<temp_name;
			    	}
			    	if(iter_sb==hash_strain_abundance.end())
			    	{
				    	if(temp_1.find("e")!=string::npos)
					    {
					    	hash_strain_abundance[temp_name]=0;
				    	}
				    	if(temp_1.find("e")==string::npos)
				    	{
			    		    hash_strain_abundance[temp_name]=atof(temp_1.c_str());
					    }
			    	}
			    	tag++;
			    }
		    	istr.clear();
			}
			
		}
	}
	ifs.close();
	
	
	for(iter_sb=hash_strain_abundance.begin();iter_sb!=hash_strain_abundance.end();iter_sb++)
	{
		ofs<<iter_sb->first<<"\t"<<iter_sb->second<<"\n";
	}

	

	hash_strain_abundance.clear();
	hash_strain_num.clear();
	vec_time.clear();
	return 0;
	
}














