#include <iostream>
using namespace std;

#include "output.h"


int main(int argc,char *argv[])
{
	using namespace one;

	int age=0;
	char name[24]="secret";

	cout<<"age?"<<endl;
	cin>>age;

	if(argc==1)
	{
		output_info(name,age);
	}
	else
	{
		output_info(argv[1],age);
	}

	return 0;
}
