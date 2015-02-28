#include <iostream>
#include <string.h>
#include <stdlib.h>

using namespace std;
namespace fp
{
	char *get_file_name(char *file_path)
	{
		char filename[24];
		char temp[128];
		char *p=filename;
		int count=0;
		char *swap=(char *)calloc(1,sizeof(filename));

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
		
		strncpy(filename,p+1,sizeof(char)*count-1);
		filename[count-1]='\0';
		//cout<<filename<<endl;
		memcpy(swap,filename,sizeof(filename));
		return swap;

	}
	char *get_file_extesion(char *file_path)
	{
		char filename[24];
		char temp[128];
		char *p=filename;
		//int count=0;
		char* swap=(char *)calloc(1,sizeof(filename));

		strcpy(temp,file_path);

		while(*p!='.')
		{
			p++;
		}

		p+=1;

		/*while(*p!='\0')
		{
			p++;
			count++;
		}
		cout<<*p<<endl;*/
		memcpy(swap,p,sizeof(filename));
		//cout<<filename<<endl;
		return swap;
	}
}
