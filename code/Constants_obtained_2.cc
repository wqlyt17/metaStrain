#include <bits/stdc++.h>
using namespace std;


int main(int argc,char* argv[])
{
    
	ifstream ifs;
	istringstream istr;
	ofstream ofs(argv[6]);
	ofstream ofs_1(argv[7]);
	ofstream ofs_2(argv[8]);
	ofstream ofs_3(argv[9]);
	ofstream ofs_4(argv[10]);//matrix G
	ofstream ofs_5(argv[11]);//matrix CI
	
	map<string,vector<string> > hash_strain;//strain(UP)> species+num
	map<string,vector<string> >::iterator iter_s;
	map<string,vector<float> > hash_abundance;//species --> abundance of strains
	map<string,vector<float> >::iterator iter_a;
	vector<string> vec_species_num;
	vector<float> vec_abundance;
	
	string temp;
	string temp_1;
	string temp_2;
	string temp_3;
	string temp_4;
	string temp_5;
	string temp_6;
	string temp_7;
	string temp_species;
	string temp_num;
	int num;
	int i;
	int j;
	map<string,vector<int> > hash_num;//species -> num_noup_strain;num_pseudo
	map<string,vector<int> >::iterator iter_num;
	vector<int> vec_num;
	
	ifs.open(argv[1]);//Constant_input_1.txt
	while(getline(ifs,temp))
	{
		if(temp[0]!='#')
		{
			istr.str(temp);
			istr>>temp_1>>temp_2>>temp_3>>temp_4;
			istr.clear();
			
			if(temp_1=="1")//strains with Up
			{
				iter_s=hash_strain.find(temp_3);
				if(iter_s==hash_strain.end())
				{
					vec_species_num.clear();
					vec_species_num.push_back(temp_2);//species
					vec_species_num.push_back(temp_4);//num
					hash_strain[temp_3]=vec_species_num;
				}
				if(iter_s!=hash_strain.end())
				{
					cout<<"error_1:"<<temp_3<<"\n";
				}
				
				iter_a=hash_abundance.find(temp_2);
				if(iter_a==hash_abundance.end())
				{
					vec_abundance.clear();
					vec_abundance.push_back(0);
					hash_abundance[temp_2]=vec_abundance;
				}
				if(iter_a!=hash_abundance.end())
				{
					vec_abundance=iter_a->second;
					vec_abundance.push_back(0);
					hash_abundance[temp_2]=vec_abundance;
				}
			}
		}
	}
	ifs.close();
	//hash_strain completed; hash_abundance half-completed





	
	ifs.open(argv[2]);//Constant_input_2.txt
	while(getline(ifs,temp))
	{
		if(temp[0]!='#')
		{
			istr.str(temp);
			istr>>temp_1>>temp_2>>temp_3>>temp_4>>temp_5>>temp_6>>temp_7;
			istr.clear();
			
			iter_s=hash_strain.find(temp_1);
			if(iter_s!=hash_strain.end())
			{
				vec_species_num=iter_s->second;
				temp_species=vec_species_num[0];
				temp_num=vec_species_num[1];
				num=atoi(temp_num.c_str());
				
				iter_a=hash_abundance.find(temp_species);
				if(iter_a==hash_abundance.end())
				{
					cout<<"error_2:"<<temp_1<<"\n";
				}
				if(iter_a!=hash_abundance.end())
				{
					vec_abundance=iter_a->second;
					vec_abundance[num-1]=atof(temp_7.c_str());
					iter_a->second=vec_abundance;
				}
			}
			if(iter_s==hash_strain.end())//Constant_input_2.txt may contain abundance of strains without UP
			{
				//cout<<"error_2:"<<temp_1<<"\n";
			}
		}
			
	}
	ifs.close();
	//hash_abundance completed
	
	
	map<string,vector<vector<float> > > hash_matrix_B;//species -> B
	vector<vector<float> > Vec_time;
	vector<float> vec_time;
	map<string,vector<vector<float> > >::iterator iter_m;
	
	map<string,vector<float> > hash_pseudo_reads_counts;
	map<string,vector<float> >::iterator iter_p;
	vector<float> vec_reads_counts;
	
	ifs.open(argv[3]);//Constant_matrix_B.txt
	while(getline(ifs,temp))
	{
		if(temp[0]!='#')
		{
			if(temp[0]=='*')
			{
				if(Vec_time.size()==0)
				{
					temp_species=temp;
				}
				if(Vec_time.size()!=0)
				{
					hash_matrix_B[temp_species]=Vec_time;
					hash_pseudo_reads_counts[temp_species]=vec_reads_counts;
					vec_reads_counts.clear();
					Vec_time.clear();
					temp_species=temp;
				}	
			}
			if(temp[0]!='*')
			{
				vec_time.clear();
				istr.str(temp);
				while(istr>>temp_1)
				{
					vec_time.push_back(atof(temp_1.c_str()));
				}
				istr.clear();
				Vec_time.push_back(vec_time);//b
				vec_reads_counts.push_back(0);
			}
	
		}
	}
	ifs.close();
	hash_matrix_B[temp_species]=Vec_time;
	hash_pseudo_reads_counts[temp_species]=vec_reads_counts;
	vec_reads_counts.clear();
	Vec_time.clear();
	//hash_matrix_B completed;hash_pseudo_reads_counts half-completed
	
	ifs.open(argv[4]);//Constant_input_3.txt
	while(getline(ifs,temp))
	{
		if(temp[0]!='#')
		{
			istr.str(temp);
			istr>>temp_1>>temp_2>>temp_3;//genome; pattern; reads num
			istr.clear();
			
			iter_s=hash_strain.find(temp_1);
			if(iter_s==hash_strain.end())
			{
				cout<<"error_3:"<<temp_1<<"\n";
			}
			if(iter_s!=hash_strain.end())
			{
				vec_species_num=iter_s->second;
				temp_species=vec_species_num[0];
				iter_p=hash_pseudo_reads_counts.find(temp_species);
				num=atoi(temp_2.c_str());//pseudo num
				vec_reads_counts=iter_p->second;
				vec_reads_counts[num-1]=atof(temp_3.c_str());
				iter_p->second=vec_reads_counts;
			}
		}
	}
	ifs.close();
	//hash_pseudo_reads_counts completed
	
	vector<float> vec_constants;
	float sum;
	//0803
	map<string,vector<float> > hash_species_ce;//species -> ce
	map<string,vector<float> >::iterator iter_ce;
	//0803
	for(iter_a=hash_abundance.begin();iter_a!=hash_abundance.end();iter_a++)
	{
		temp_species=iter_a->first;
		
    	iter_m=hash_matrix_B.find(temp_species);//1225
		if(iter_m!=hash_matrix_B.end())//1225
		{
		
    		ofs<<temp_species<<"\n";
    		ofs_1<<temp_species<<"\n";
    		//ofs_2<<temp_species<<"\n";
    		vec_abundance=iter_a->second;
    		
    		for(i=0;i<vec_abundance.size();i++)
    		{
    			ofs<<vec_abundance[i]<<"\t";
    		}
    		ofs<<"\n";
    		
    		iter_m=hash_matrix_B.find(temp_species);
    		Vec_time=iter_m->second;
    		
    		iter_p=hash_pseudo_reads_counts.find(temp_species);
    		vec_reads_counts=iter_p->second;
    		for(i=0;i<vec_reads_counts.size();i++)
    		{
    			ofs_1<<vec_reads_counts[i]<<"\t";
    		}
    		ofs_1<<"\n";
    		
    		vec_constants.clear();
    		for(i=0;i<Vec_time.size();i++)
    		{
    			vec_time=Vec_time[i];
    			sum=0;
    			for(j=0;j<vec_time.size();j++)
    			{
    				sum=sum+vec_time[j]*vec_abundance[j];
    			}
    			vec_constants.push_back(sum);	
    		}
    		for(i=0;i<vec_constants.size();i++)
    		{
    			vec_constants[i]=vec_constants[i]-vec_reads_counts[i];
    			//ofs_2<<vec_constants[i]<<"\t";
    		}	
    		hash_species_ce[temp_species]=vec_constants;//0803
    		//ofs_2<<"\n";
    	}//1225
	}
	

	
	map<string,vector<vector<float> > > hash_matrix_A;//species->A
	map<string,vector<vector<float> > >::iterator iter_ma;
	map<string,vector<int> > hash_row;//row content --> row num
	map<string,vector<int> >::iterator iter_r;
	int row;
	vector<int> vec_row;
	string temp_row;
	float ce_sum;
	float ce_average;
	vector<float> vec_ce;
	vector<float> vec_ce_1;
	
	ifs.open(argv[5]);//Constant_matrix_A.txt
	while(getline(ifs,temp))
	{
		if(temp[0]=='*')
		{
			
			if(hash_row.size()==0)
			{
				temp_species=temp;
				row=0;//add 1226
			}
			if(hash_row.size()!=0)
			{
/*
for(iter_r=hash_row.begin();iter_r!=hash_row.end();iter_r++)
{
	cout<<iter_r->first<<"\n";
	vec_row=iter_r->second;
	for(int i=0;i<vec_row.size();i++)
	{
		cout<<vec_row[i]<<"\t";
	}
	cout<<"\n";
}
*/
				//hash_row completed
				iter_ce=hash_species_ce.find(temp_species);
				if(iter_ce==hash_species_ce.end())
				{
					cout<<"error:"<<temp_species<<"\n";
				}
				if(iter_ce!=hash_species_ce.end())
				{
					vec_ce=iter_ce->second;
				}
				
				Vec_time.clear();
				vec_ce_1.clear();//new ce
				for(iter_r=hash_row.begin();iter_r!=hash_row.end();iter_r++)
				{
					temp_row=iter_r->first;
					vec_time.clear();
					ce_sum=0;
					istr.str(temp_row);
					while(istr>>temp_1)
					{
						vec_time.push_back(atof(temp_1.c_str()));
					}
					istr.clear();
					Vec_time.push_back(vec_time);
					
					vec_row=iter_r->second;//row num
					for(int i=0;i<vec_row.size();i++)
					{
						ce_sum=ce_sum+vec_ce[vec_row[i]];
					}
					ce_average=ce_sum/vec_row.size();
					vec_ce_1.push_back(ce_average);	
				}
				//Vec_time completed
				//vec_ce_1 completed
				hash_matrix_A[temp_species]=Vec_time;
				hash_species_ce[temp_species]=vec_ce_1;
				temp_species=temp;
				hash_row.clear();
				row=0;
			}	
		}
		if(temp[0]!='*')
		{
			iter_r=hash_row.find(temp);
			if(iter_r==hash_row.end())
			{
				vec_row.clear();
				vec_row.push_back(row);
				hash_row[temp]=vec_row;
				row++;
			}
			if(iter_r!=hash_row.end())
			{
				vec_row=iter_r->second;
				vec_row.push_back(row);
				hash_row[temp]=vec_row;
				row++;
			}
		}
	}
	ifs.close();
	
	iter_ce=hash_species_ce.find(temp_species);
	if(iter_ce==hash_species_ce.end())
	{
		cout<<"error:"<<temp_species<<"\n";
	}
	if(iter_ce!=hash_species_ce.end())
	{
		vec_ce=iter_ce->second;
	}
				
	Vec_time.clear();
	vec_ce_1.clear();//new ce
	for(iter_r=hash_row.begin();iter_r!=hash_row.end();iter_r++)
	{
		temp_row=iter_r->first;
		vec_time.clear();
		ce_sum=0;
		istr.str(temp_row);
		while(istr>>temp_1)
		{
			vec_time.push_back(atof(temp_1.c_str()));
		}
		istr.clear();
		Vec_time.push_back(vec_time);
					
		vec_row=iter_r->second;//row num
		for(int i=0;i<vec_row.size();i++)
		{
			ce_sum=ce_sum+vec_ce[vec_row[i]];
		}
		ce_average=ce_sum/vec_row.size();
		vec_ce_1.push_back(ce_average);	
	}
	//Vec_time completed
	//vec_ce_1 completed
	hash_matrix_A[temp_species]=Vec_time;
	hash_species_ce[temp_species]=vec_ce_1;

	for(iter_ce=hash_species_ce.begin();iter_ce!=hash_species_ce.end();iter_ce++)
	{
		ofs_2<<iter_ce->first<<"\n";
		vec_ce_1=iter_ce->second;
		for(int i=0;i<vec_ce_1.size();i++)
		{
			if(vec_ce_1[i]<=0)
			{
				ofs_2<<vec_ce_1[i]<<"\t";
			}
			if(vec_ce_1[i]>0)
			{
				ofs_2<<0<<"\t";
			}
			
		}
		ofs_2<<"\n";
	}
/*
for(iter_ma=hash_matrix_A.begin();iter_ma!=hash_matrix_A.end();iter_ma++)
{
	ofs<<iter_ma->first<<"\n";
	Vec_time=iter_ma->second;
	for(int i=0;i<Vec_time.size();i++)
	{
		for(int j=0;j<Vec_time[i].size();j++)
		{
			ofs<<Vec_time[i][j]<<"\t";
		}
		ofs<<"\n";
	}
	ofs<<"\n";
}
*/
	int num_noup_strain;
	int num_pseudo;
	for(iter_ma=hash_matrix_A.begin();iter_ma!=hash_matrix_A.end();iter_ma++)
	{
		Vec_time=iter_ma->second;
		num_pseudo=Vec_time.size();
		num_noup_strain=Vec_time[0].size();
		vec_num.clear();
		vec_num.push_back(num_noup_strain);
		vec_num.push_back(num_pseudo);
		hash_num[iter_ma->first]=vec_num;
		
		for(i=0;i<Vec_time.size();i++)
		{
			vec_time=Vec_time[i];
			for(j=0;j<Vec_time.size();j++)//add pseudo-num 0 to vec_time
			{
				vec_time.push_back(0);
			}
			vec_time[i+num_noup_strain]=1;
			Vec_time[i]=vec_time;
		}
		iter_ma->second=Vec_time;
		/*//0727
		vec_num.clear();
		vec_num.push_back(num_noup_strain);
		vec_num.push_back(num_pseudo);
		hash_num[iter_ma->first]=vec_num;
		//0727*/
	}
	//hash_matrix_A completed
	
	
	vector<vector<float> > Vec_T;
	//int row;
	int column;
	for(iter_ma=hash_matrix_A.begin();iter_ma!=hash_matrix_A.end();iter_ma++)
	{
		ofs_3<<iter_ma->first<<"\n";
		Vec_time=iter_ma->second;
		row=Vec_time.size();
		column=Vec_time[0].size();
		vec_time.clear();
		Vec_T.clear();
		for(i=0;i<row;i++)
		{
			vec_time.push_back(0);
		}
		for(i=0;i<column;i++)
		{
			Vec_T.push_back(vec_time);
		}
		for(i=0;i<column;i++)
		{
			for(j=0;j<row;j++)
			{
				Vec_T[i][j]=Vec_time[j][i];
				ofs_3<<Vec_T[i][j]<<"\t";
			}
			ofs_3<<"\n";
		}
		/*
		for(i=0;i<row;i++)
		{
			for(j=0;j<column;j++)
			{
				cout<<Vec_time[i][j]<<"\t";
			}
			cout<<"\n";
		}
		*/
	}
	//output the transposition of hash_matrix_A (i.e. CE)
	
	
	//matrix G;CI
	int num_x;
	for(iter_num=hash_num.begin();iter_num!=hash_num.end();iter_num++)
	{
		ofs_4<<iter_num->first<<"\n";
		ofs_5<<iter_num->first<<"\n";
		vec_num=iter_num->second;
		num_noup_strain=vec_num[0];
		num_pseudo=vec_num[1];
//cout<<num_noup_strain<<"\n";
//cout<<num_pseudo<<"\n";		
		num_x=num_noup_strain+num_pseudo;
		//G
		for(i=1;i<=num_x;i++)
		{
			for(j=1;j<=num_x;j++)
			{
				if(i==j)
				{
					if(i<=num_noup_strain)
					{
						ofs_4<<"0.00000002"<<"\t";
					}
					if(i>num_noup_strain)
					{
						ofs_4<<"2"<<"\t";
					}
				}
				if(i!=j)
				{
					ofs_4<<"0"<<"\t";
				}
			}
			ofs_4<<"\n";
		}
		//CI
		for(i=1;i<=num_x;i++)
		{
			for(j=1;j<=num_noup_strain;j++)
			{
				if(i==j)
				{
					ofs_5<<"1"<<"\t";
				}
				if(i!=j)
				{
					ofs_5<<"0"<<"\t";
				}
			}
			ofs_5<<"\n";
		}		
	}
	
	
	
	
	
	
	
	
	ofs.close();
	ofs_1.close();
	ofs_2.close();
	ofs_3.close();
	ofs_4.close();
	ofs_5.close();
	hash_abundance.clear();
	hash_matrix_B.clear();
	hash_matrix_A.clear();
	hash_pseudo_reads_counts.clear();
	hash_strain.clear();
	vec_abundance.clear();
	vec_constants.clear();
	vec_reads_counts.clear();
	vec_species_num.clear();
	vec_time.clear();
	Vec_time.clear();
    return 0;
}