#include <iostream>
#include <string.h>

namespace fp
{
	using namespace std;
	char *get_file_name(char *file_path)
	{
		char filename[24];
		char temp[128];
		char *p=filename;
		int count=0;

		strcpy(temp,file_path);

		while(*p!='.')
		{
			p++;
		}
		
		while(*p!='/')
		{
			p--;
			count++;
		}				
		
		strncpy(filename,p,sizeof(char)*count);
		filename[count]='\0';
		cout<<filename<<endl;

		return NULL;

	}
	char *get_file_extesion(char *file_path)
	{
		char filename[24];
		char temp[128];
		char *p=filename;

		strcpy(temp,file_path);

		while(*p!='.')
		{
			p++;
		}
		
		strcpy(filename,p+1);
		cout<<filename<<endl;
		return NULL;
	}
}
