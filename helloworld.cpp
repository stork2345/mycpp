/*

   helloworld cpp
author:stork
date:2015-2-27
Version:1.0

 */
//#include <stdio.h>
#include <iostream>


using namespace std;
//using namespace::std;
int main(void)
{
		int num1=0,num2=0;
		char a=0;
		//cout<<"hello world!"<<endl;
		//cout<<"hello cpp!"<<endl;
		while(1)
		{
				cout<<"请输入两个数字:"<<endl;
				cin>>num1;
				cin>>num2;
				cout<<"请输入运算方式(+-*/):"<<endl;
				cin>>a;
				if((a>=42)&&(a<=47))
				{
						if(a=='+')
						{
								cout<<num1<<"+"<<num2<<"="<<num1+num2<<endl;
						}
						else if(a=='-')
						{
								cout<<num1<<"-"<<num2<<"="<<num1-num2<<endl;
						}
						else if(a=='*')
						{
								cout<<num1<<"*"<<num2<<"="<<num1*num2<<endl;
						}
						else
						{
								cout<<num1<<"/"<<num2<<"="<<num1/num2<<endl;
						}
				}
				else
				{
						cout<<"请输入正确的操作符!"<<endl;
				}
		}

		return 0;
}
