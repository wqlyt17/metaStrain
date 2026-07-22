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
	
	string path=argv[2];
	//float threshold=atof(argv[3]);//species with top abundance

	string temp;

	ifs.open(argv[1]);//meta_sample_species.txt
	while(getline(ifs,temp))
	{
		ofs<<path<<temp<<"\n";
		
	}
	ifs.close();

	return 0;
}



