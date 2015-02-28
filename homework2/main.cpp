#include <iostream>
#include <stdlib.h>
#include <string.h>
using namespace std;

#include "fp.h"
using namespace fp;

int main(int argc,char *argv[])
{
	char filename[128]="/media/sdcard/yesterday.mp3";
	char temp[24];
	char *p=get_file_name(filename);
//	strncpy(temp,p,sizeof(temp));
	
	strcpy(temp,p);
	cout<<temp<<endl;
	free(p);
	p=get_file_extesion(filename);
	strncpy(temp,p,sizeof(temp));
	cout<<temp<<endl;
	//cout<<*p<<endl;
	free(p);
	return 0;
}
