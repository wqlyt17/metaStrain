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
	ofstream ofs(argv[3]);//matrix_B
	ofstream ofs_1(argv[4]);//matrix_A
	ofstream ofs_2(argv[5]);//analysis_out.txt
	
	string temp_species=argv[6];
	
	ofs<<"*"<<temp_species<<"\n";
	ofs_1<<"*"<<temp_species<<"\n";
	
	string temp;
	string temp_1;
	string temp_2;
	string temp_3;
	string temp_4;
	string temp_5;
	string temp_6;
	string temp_7;
	string temp_cga;

	
	map<string,vector<int> > hash_num;
	map<string,vector<int> >::iterator iter_num;
	vector<int> vec_num;
	int num_up=0;
	int num_noup=0;
	
	map<string,vector<string> > hash_cga_strain;
	map<string,vector<string> >::iterator iter_cga;
	vector<string> vec_temp;
	vector<string>::iterator iter_vec;
	
	
	
	ifs.open(argv[1]);//strain_num.txt
	while(getline(ifs,temp))
	{
		istr.str(temp);
		istr>>temp_1>>temp_2>>temp_3>>temp_4;
		istr.clear();
		if(temp_1=="0")//no up
		{
			num_noup++;
		}
		if(temp_1=="1")//no up
		{
			num_up++;
		}
		
		vec_num.clear();
		vec_num.push_back(atoi(temp_1.c_str()));
		vec_num.push_back(atoi(temp_4.c_str()));
		
		hash_num[temp_3]=vec_num;
		
	}
	ifs.close();

//cout<<"hash_num.size():"<<hash_num.size()<<"\n";		
	
	ifs.open(argv[2]);//com_reference.sam
	while(getline(ifs,temp))
	{
		if(temp[0]!='@')
		{			
			istr.str(temp);
			istr>>temp_1>>temp_2>>temp_3>>temp_4>>temp_5>>temp_6>>temp_7;//temp_2:cga; temp_4: strain genome
			istr.clear();
			if(temp_7!="*")//对每个有mapping结果的read进行遍历
			{	
				iter_cga=hash_cga_strain.find(temp_2);
				if(iter_cga==hash_cga_strain.end())
				{
					vec_temp.clear();
					vec_temp.push_back(temp_4);
					hash_cga_strain[temp_2]=vec_temp;
				}
				if(iter_cga!=hash_cga_strain.end())
				{
					vec_temp=iter_cga->second;
					vec_temp.push_back(temp_4);
					hash_cga_strain[temp_2]=vec_temp;
				}
			}
		}
	}
	ifs.close();
//cout<<"hash_cga_strain.size():"<<hash_cga_strain.size()<<"\n";	
	int i;
	vector<int> vec_time_a;
	vector<int> vec_time_b;
	int flag_1;
	int flag_2;
	int old_size;
	for(iter_cga=hash_cga_strain.begin();iter_cga!=hash_cga_strain.end();iter_cga++)
	{
		temp_cga=iter_cga->first;
		vec_temp=iter_cga->second;
		old_size=vec_temp.size();
		
		
		sort(vec_temp.begin(),vec_temp.end());
		iter_vec=unique(vec_temp.begin(),vec_temp.end());
		vec_temp.erase(iter_vec,vec_temp.end()); //unique

		if(old_size==vec_temp.size())
		{
			vec_time_a.clear();
			for(i=0;i<num_noup;i++)
			{
				vec_time_a.push_back(0);
			}
			
			vec_time_b.clear();
			for(i=0;i<num_up;i++)
			{
				vec_time_b.push_back(0);
			}
			
			flag_1=0;
			flag_2=0;
			
			for(i=0;i<vec_temp.size();i++)
			{
				iter_num=hash_num.find(vec_temp[i]);
				if(iter_num==hash_num.end())
				{
					cout<<"error:"<<vec_temp[i]<<"\n";
				}
				if(iter_num!=hash_num.end())
				{
					vec_num=iter_num->second;
					if(vec_num[0]==0)//no up --> A
					{
						flag_1=1;
						vec_time_a[vec_num[1]-1]=1;
					}
					if(vec_num[0]==1)//up --> B
					{
						flag_2=1;
						vec_time_b[vec_num[1]-1]=1;
					}
				}
			}
			if((flag_1==1)&&(flag_2==1))
			{
				for(i=0;i<vec_time_b.size();i++)
				{
					ofs<<vec_time_b[i]<<"\t";
				}
				ofs<<"\n";
				
				for(i=0;i<vec_time_a.size();i++)
				{
					ofs_1<<vec_time_a[i]<<"\t";
				}
				ofs_1<<"\n";
				
				ofs_2<<temp_cga<<"\n";
			}
		}
		
	}
	
	
	
	hash_cga_strain.clear();
	hash_num.clear();
	vec_num.clear();
	vec_temp.clear();
	vec_time_a.clear();
	vec_time_b.clear();
	

	return 0;
	
}














