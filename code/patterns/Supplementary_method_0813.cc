#include <bits/stdc++.h>
using namespace std;


int main(int argc,char* argv[])
{
    
	ifstream ifs;
	istringstream istr;
	ofstream ofs(argv[3]);
	ofstream ofs_1(argv[4]);
	ofstream ofs_2(argv[5]);
	ofstream ofs_3(argv[6]);
	int L=atoi(argv[7]);//length threshold
	string species=argv[8]; //0725
	int cga_num=atoi(argv[9]);
	int flag;
	string temp_genome;
	string temp;
	string temp_1;
	vector<string> vec_temp;//element is gene
	map<string,int> hash_strain;//strains with unique patterns
	map<string,int>::iterator iter_s;
	
	stringstream ss;
	string temp_arrangement;
	
	map<string,vector<string> > hash_strain_with_up;
	map<string,vector<string> > hash_strain_without_up;
	vector<string> vec_time;
	vector<string> vec_time_no;
//0724
	vector<int> vec_tag;
	vector<int> vec_tag_no;
	int tag;
//0724
	map<string,vector<string> >::iterator iter_up;
	map<string,vector<string> >::iterator iter_no_up;
	int occurrence;
	
	map<int,vector<string> > hash_occurrence;//the occurrence in strains without unique patterns; occurrence --> gene arrangment 
	map<int,vector<string> >::iterator iter_o;
	vector<string> vec_o;
	
//0724	
	map<string,int> hash_strain_num;//strain_name (no UP) --> num
	map<string,int>::iterator iter_num;
	int num=0;
	int num_up=0;
	
	ofs<<"*"<<species<<"\n";
	ofs_1<<"*"<<species<<"\n";
//0724		
	ifs.open(argv[1]);//record strains with up -> num
	while(getline(ifs,temp))
	{
		istr.str(temp);
		istr>>temp_1;
		istr.clear();
		num_up++;
		iter_s=hash_strain.find(temp_1);
		if(iter_s==hash_strain.end())
		{
			hash_strain[temp_1]=num_up;
		}
		if(iter_s!=hash_strain.end())
		{
			cout<<"error:"<<temp_1<<"\n";
		}
		getline(ifs,temp);
	}
	ifs.close();
	
//cout<<"Strain_withUP_size:"<<hash_strain.size()<<"\n";	

	int strain_num=0;
	int i,j,k;
	int length;
	//add	
	map<string,string> hash_reverse;//substring (_1_2_) -> reverse of this substring (_-2_-1_)
	map<string,string>::iterator iter_r;
	map<string,string>::iterator iter_r_1;
	string temp_reverse;
	string temp_time;
	stringstream ss_r;
	//add
	ifs.open(argv[2]);//genome_arrangement.txt
	while(getline(ifs,temp))
	{
		temp_genome=temp;
		strain_num++;
		getline(ifs,temp);
		vec_temp.clear();
		istr.str(temp);
		while(istr>>temp_1)
		{
			vec_temp.push_back(temp_1);
		}
		istr.clear();
		
		iter_s=hash_strain.find(temp_genome);
		if(iter_s!=hash_strain.end())//strain with unique pattern
		{
			for(length=2;length<=L;length++)
			{
				flag=vec_temp.size()-length+1;
				for(i=0;i<flag;i++)
				{
					ss.clear();
					temp_arrangement.clear();
	
					ss<<"_";
					for(j=0;j<length;j++)
					{
						ss<<vec_temp[i+j]<<"_";
					}
				
					ss>>temp_arrangement;
					
					//add
					ss_r.clear();
					temp_reverse.clear();
					ss_r<<"_";
					for(j=length-1;j>=0;j--)
					{
						temp_time=vec_temp[i+j];
						if(temp_time[0]!='-')
						{
							ss_r<<"-"<<temp_time<<"_";
						}
						if(temp_time[0]=='-')//solve:  _-2_-1_ --> _--1_--2_
						{
							temp_time.erase(0,1);
							ss_r<<temp_time<<"_";
						}
					}
					ss_r>>temp_reverse;
					
					iter_r=hash_reverse.find(temp_arrangement);
					if(iter_r==hash_reverse.end())
					{
						hash_reverse[temp_arrangement]=temp_reverse;
					}
	
					//add
					iter_up=hash_strain_with_up.find(temp_arrangement);
					if(iter_up==hash_strain_with_up.end())
					{
						vec_time.clear();
						vec_time.push_back(temp_genome);
						hash_strain_with_up[temp_arrangement]=vec_time;
					}
					if(iter_up!=hash_strain_with_up.end())
					{
						vec_time=iter_up->second;
						vec_time.push_back(temp_genome);
						hash_strain_with_up[temp_arrangement]=vec_time;
					}
				}
			}
		}
		if(iter_s==hash_strain.end())//strain without unique pattern
		{
			iter_num=hash_strain_num.find(temp_genome);
			if(iter_num==hash_strain_num.end())
			{
				num++;
				hash_strain_num[temp_genome]=num;
			}
			if(iter_num!=hash_strain_num.end())
			{
				cout<<"error:"<<temp_genome<<"\n";
			}
			
			for(length=2;length<=L;length++)
			{
				flag=vec_temp.size()-length+1;
				for(i=0;i<flag;i++)
				{
					ss.clear();
					ss<<"_";
					for(j=0;j<length;j++)
					{
						ss<<vec_temp[i+j]<<"_";
					}
				
					ss>>temp_arrangement;
					
					//add
					ss_r.clear();
					temp_reverse.clear();
					ss_r<<"_";
					for(j=length-1;j>=0;j--)
					{
						temp_time=vec_temp[i+j];
						if(temp_time[0]!='-')
						{
							ss_r<<"-"<<temp_time<<"_";
						}
						if(temp_time[0]=='-')//solve:  _-2_-1_ --> _--1_--2_
						{
							temp_time.erase(0,1);
							ss_r<<temp_time<<"_";
						}
					}
					ss_r>>temp_reverse;
					
					iter_r=hash_reverse.find(temp_arrangement);
					if(iter_r==hash_reverse.end())
					{
						hash_reverse[temp_arrangement]=temp_reverse;
					}
	
					//add
					iter_no_up=hash_strain_without_up.find(temp_arrangement);
					if(iter_no_up==hash_strain_without_up.end())
					{
						vec_time.clear();
						vec_time.push_back(temp_genome);
						hash_strain_without_up[temp_arrangement]=vec_time;
					}
					if(iter_no_up!=hash_strain_without_up.end())
					{
						vec_time=iter_no_up->second;
						vec_time.push_back(temp_genome);
						hash_strain_without_up[temp_arrangement]=vec_time;
					}
				}
			}
		}	
	}
	ifs.close();
	//complete hash_strain_with_up, hash_strain_without_up
	//complete hash_strain_num;0615
	//complete hash_reverse

//cout<<"Strain_withoutUP_size:"<<hash_strain_num.size()<<"\n";
//cout<<"Strain_size:"<<strain_num<<"\n";
//cout<<"hash_strain_with_up.size():"<<hash_strain_with_up.size()<<"\n";
//cout<<"hash_strain_without_up.size():"<<hash_strain_without_up.size()<<"\n";
//cout<<"hash_reverse.size():"<<hash_reverse.size()<<"\n";
//cout<<"num:"<<num<<"\n";

//ofs_3<<"//NO_UP"<<"\n";
for(iter_num=hash_strain_num.begin();iter_num!=hash_strain_num.end();iter_num++)
{
	ofs_3<<"0"<<"\t"<<"*"<<species<<"\t"<<iter_num->first<<"\t"<<iter_num->second<<"\n";
}
//ofs_3<<"//UP"<<"\n";
for(iter_s=hash_strain.begin();iter_s!=hash_strain.end();iter_s++)
{
	ofs_3<<"1"<<"\t"<<"*"<<species<<"\t"<<iter_s->first<<"\t"<<iter_s->second<<"\n";
}

	for(iter_up=hash_strain_with_up.begin();iter_up!=hash_strain_with_up.end();iter_up++)
	{
		temp_arrangement=iter_up->first;
		iter_no_up=hash_strain_without_up.find(temp_arrangement);
		if(iter_no_up!=hash_strain_without_up.end())//share with strains (with and without unique patterns)
		{
			vec_time=iter_no_up->second;
			occurrence=vec_time.size();
			iter_o=hash_occurrence.find(occurrence);
			if(iter_o!=hash_occurrence.end())
			{
				vec_o=iter_o->second;
				vec_o.push_back(temp_arrangement);
				hash_occurrence[occurrence]=vec_o;
			}
			if(iter_o==hash_occurrence.end())
			{
				vec_o.clear();
				vec_o.push_back(temp_arrangement);
				hash_occurrence[occurrence]=vec_o;
			}
		}
	}
	//hash_occurrence completed
//cout<<"hash_occurrence.size():"<<hash_occurrence.size()<<"\n";
	
	
	int size_1=hash_strain.size();
	int size_2=hash_strain_num.size();
	vector<int> vec_A(size_2);
	int pseudo=0;
	for(iter_o=hash_occurrence.begin();iter_o!=hash_occurrence.end();iter_o++)
	{
//cout<<"occurrence:"<<iter_o->first<<"\n";
		vec_o=iter_o->second;
		for(i=0;i<vec_o.size();i++)
		{			
			temp_arrangement=vec_o[i];
			//add
			iter_r=hash_reverse.find(temp_arrangement);
			if(iter_r==hash_reverse.end())
			{
				cout<<"error_r:"<<temp_arrangement<<"\n";
			}
			if(iter_r!=hash_reverse.end())
			{
				temp_reverse=iter_r->second;
				iter_r_1=hash_reverse.find(temp_reverse);
				if(iter_r_1==hash_reverse.end())//no reverse
				{
					pseudo++;
					ofs_2<<temp_arrangement<<"\t";
					iter_up=hash_strain_with_up.find(temp_arrangement);
					if(iter_up==hash_strain_with_up.end())
					{
						cout<<"error:"<<temp_arrangement<<"\n";
					}
					if(iter_up!=hash_strain_with_up.end())
					{
						vec_time=iter_up->second;
					}
					ofs_2<<vec_time[0]<<"\t"<<pseudo<<"\n";
					iter_no_up=hash_strain_without_up.find(temp_arrangement);
					if(iter_no_up==hash_strain_without_up.end())
					{
						cout<<"error:"<<temp_arrangement<<"\n";
					}
					if(iter_no_up!=hash_strain_without_up.end())
					{
						vec_time_no=iter_no_up->second;
					}
					//vec_time, vec_time_no complete
					vec_tag.clear();
					vec_tag_no.clear();
					for(j=0;j<size_1;j++)
					{
						vec_tag.push_back(0);
					}
					for(j=0;j<size_2;j++)
					{
						vec_tag_no.push_back(0);
					}
					for(j=0;j<vec_time.size();j++)
					{
						iter_s=hash_strain.find(vec_time[j]);
						if(iter_s==hash_strain.end())
						{
							cout<<"error"<<"\n";
						}
						if(iter_s!=hash_strain.end())
						{
							tag=iter_s->second;
							vec_tag[tag-1]=1;
						}
					}
					for(j=0;j<vec_time_no.size();j++)
					{
						iter_num=hash_strain_num.find(vec_time_no[j]);
						if(iter_num==hash_strain_num.end())
						{
							cout<<"error"<<"\n";
						}
						if(iter_num!=hash_strain_num.end())
						{
							tag=iter_num->second;
							vec_tag_no[tag-1]=1;
							if(vec_A[tag-1]<cga_num)
							{
								vec_A[tag-1]++;
							}
						}
					}
					//vec_tag,vec_tag_no completed	
					for(j=0;j<vec_tag.size();j++)
					{
						ofs<<vec_tag[j]<<"\t";
					}
					ofs<<"\n";
					for(j=0;j<vec_tag_no.size();j++)
					{
						ofs_1<<vec_tag_no[j]<<"\t";
					}
					ofs_1<<"\n";
				}
			}
		}
		if(accumulate(vec_A.begin(),vec_A.end(),0)==(size_2*cga_num))
		{
			//ofs<<"******"<<"\n";
			//ofs_1<<"******"<<"\n";
			//ofs_2<<"*******"<<"\n";
			cout<<"break"<<"\n";
			break;
		}
		
	}
/*
for(i=0;i<vec_A.size();i++)
{
//	cout<<vec_A[i]<<"\t";
}
*/
//cout<<"accumulate(vec_A.begin(),vec_A.end(),0):"<<accumulate(vec_A.begin(),vec_A.end(),0)<<"\n";
//cout<<"vec_A.size():"<<vec_A.size()<<"\n";

	ofs.close();
	ofs_1.close();
	ofs_2.close();
	hash_occurrence.clear();
	hash_strain_with_up.clear();
	hash_strain_without_up.clear();
	vec_temp.clear();
	vec_time.clear();
	vec_time_no.clear();
	vec_A.clear();
	vec_tag.clear();
	vec_tag_no.clear();
	hash_strain.clear();
	hash_strain_num.clear();
	
    return 0;
}