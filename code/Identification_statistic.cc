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
	ofstream ofs(argv[2]);//read
	ofstream ofs_1(argv[3]);//genome, with multi-reads
	ofstream ofs_2(argv[4]);//genome, without multi-reads

	
	string temp;
	string temp_1;
	string temp_2;
	string temp_3;
	int i;
	map<string,vector<string> > hash_RtoG;
	map<string,vector<string> > hash_RtoP;
	map<string,vector<string> >::iterator iter_1;
	map<string,vector<string> >::iterator iter_2;
	vector<string> vec_time;
	vector<string> vec_time_1;
	vector<string>::iterator iter;
	map<string,int> hash_multi_read;
	map<string,int>::iterator iter_m;
	
	map<string,vector<string> > hash_GtoR;
	map<string,vector<string> > hash_GtoR_nomulti;
	
	
	ifs.open(argv[1]);
	while(getline(ifs,temp))
	{
		istr.str(temp);
		istr>>temp_1>>temp_2>>temp_3;//1 read; 2 genome; 3 pattern
		istr.clear();
		
		iter_1=hash_RtoG.find(temp_1);
		if(iter_1==hash_RtoG.end())
		{
			vec_time.clear();
			vec_time.push_back(temp_2);
			hash_RtoG[temp_1]=vec_time;
		}
		if(iter_1!=hash_RtoG.end())
		{
			vec_time=iter_1->second;
			vec_time.push_back(temp_2);
			hash_RtoG[temp_1]=vec_time;
		}	
		iter_2=hash_RtoP.find(temp_1);
		if(iter_2==hash_RtoP.end())
		{
			vec_time.clear();
			vec_time.push_back(temp_3);
			hash_RtoP[temp_1]=vec_time;
		}
		if(iter_2!=hash_RtoP.end())
		{
			vec_time=iter_2->second;
			vec_time.push_back(temp_3);
			hash_RtoP[temp_1]=vec_time;
		}		
	}
	ifs.close();
	
	for(iter_1=hash_RtoG.begin();iter_1!=hash_RtoG.end();iter_1++)
	{
		vec_time=iter_1->second;
		sort(vec_time.begin(),vec_time.end());
		iter=unique(vec_time.begin(),vec_time.end());
		vec_time.erase(iter,vec_time.end()); //unique
		iter_1->second=vec_time;
	}

	for(iter_2=hash_RtoP.begin();iter_2!=hash_RtoP.end();iter_2++)
	{
		vec_time=iter_2->second;
		sort(vec_time.begin(),vec_time.end());
		iter=unique(vec_time.begin(),vec_time.end());
		vec_time.erase(iter,vec_time.end()); //unique
		iter_2->second=vec_time;
	}
//hash_RtoG;hash_RtoP completed
//next: find multi read

	for(iter_1=hash_RtoG.begin();iter_1!=hash_RtoG.end();iter_1++)
	{
		vec_time=iter_1->second;
		if(vec_time.size()==1)
		{
			iter_2=hash_RtoP.find(iter_1->first);
			if(iter_2!=hash_RtoP.end())
			{
				vec_time_1=iter_2->second;
				if(vec_time_1.size()==1)//type a
				{
					ofs<<iter_1->first<<"\t"<<"a"<<"\t"<<vec_time[0]<<"\t"<<vec_time_1[0]<<"\n";
				}
				if(vec_time_1.size()>1)//type b
				{
					ofs<<iter_1->first<<"\t"<<"b"<<"\t"<<vec_time[0]<<"\t";
					for(i=0;i<vec_time_1.size();i++)
					{
						ofs<<vec_time_1[i]<<"/";
					}
					ofs<<"\n";
				}
			}
			if(iter_2==hash_RtoP.end())
			{
				cout<<"error:"<<iter_1->first<<"\n";
			}
		}
		if(vec_time.size()>1)//type c
		{
			ofs<<iter_1->first<<"\t"<<"c"<<"\t";
			for(i=0;i<vec_time.size();i++)
			{
				ofs<<vec_time[i]<<"/";
			}
			ofs<<"\t"<<"*"<<"\n";
			hash_multi_read[iter_1->first]=1;
		}
	}

//hash_multi_read completed; output file1 completed

	ifs.open(argv[1]);
	while(getline(ifs,temp))
	{
		istr.str(temp);
		istr>>temp_1>>temp_2>>temp_3;//1 read; 2 genome; 3 pattern
		istr.clear();
		
		iter_1=hash_GtoR.find(temp_2);
		if(iter_1==hash_GtoR.end())
		{
			vec_time.clear();
			vec_time.push_back(temp_1);
			hash_GtoR[temp_2]=vec_time;
		}
		if(iter_1!=hash_GtoR.end())
		{
			vec_time=iter_1->second;
			vec_time.push_back(temp_1);
			hash_GtoR[temp_2]=vec_time;
		}	
		
		iter_m=hash_multi_read.find(temp_1);
		if(iter_m==hash_multi_read.end())
		{
			iter_2=hash_GtoR_nomulti.find(temp_2);
			if(iter_2==hash_GtoR_nomulti.end())
			{
				vec_time.clear();
				vec_time.push_back(temp_1);
				hash_GtoR_nomulti[temp_2]=vec_time;
			}
			if(iter_2!=hash_GtoR_nomulti.end())
			{
				vec_time=iter_2->second;
				vec_time.push_back(temp_1);
				hash_GtoR_nomulti[temp_2]=vec_time;
			}	
		}
		
	}
	ifs.close();
//cout<<"hash_GtoR:"<<hash_GtoR.size()<<"\n";
//cout<<"hash_GtoR_nomulti:"<<hash_GtoR_nomulti.size()<<"\n";	
	for(iter_1=hash_GtoR.begin();iter_1!=hash_GtoR.end();iter_1++)
	{
		vec_time=iter_1->second;
		sort(vec_time.begin(),vec_time.end());
		iter=unique(vec_time.begin(),vec_time.end());
		vec_time.erase(iter,vec_time.end()); //unique
		iter_1->second=vec_time;
		ofs_1<<iter_1->first<<"\t"<<vec_time.size()<<"\n";
	}

	for(iter_2=hash_GtoR_nomulti.begin();iter_2!=hash_GtoR_nomulti.end();iter_2++)
	{
		vec_time=iter_2->second;
		sort(vec_time.begin(),vec_time.end());
		iter=unique(vec_time.begin(),vec_time.end());
		vec_time.erase(iter,vec_time.end()); //unique
		iter_2->second=vec_time;
		ofs_2<<iter_2->first<<"\t"<<vec_time.size()<<"\n";
//cout<<iter_2->first<<"\t"<<vec_time.size()<<"\n";
	}

	

	return 0;
	
}














