#include <iostream>
using namespace std;

#include <time.h>
#include "datetime.h"
using namespace iotek;
	
Datetime::Datetime(int year,int month,int date)
{
	m_year=year;
	m_month=month;
	m_date=date;
}
Datetime::~Datetime()
{
}
void Datetime::showtime()
{
	cout<<" year:  "<<m_year;
	cout<<" month:  "<<m_month;
	cout<<" date: "<<m_date;
	cout<<endl;
}

void Datetime::addDate()
{
	m_date+=1;
	switch (m_month)
	{
		case 1:
			if(m_date>31)
			{
				m_date=1;
				m_month+=1;
			}
			break;
		case 2:
			if(isleapyear())
			{
				if(m_date>29)
				{
					m_date=1;
					m_month+=1;
				}
		
			}
			else 
			{
				if(m_date>28)
				{
					m_date=1;
					m_month+=1;
				}
			}
			break;
		case 3:
			if(m_date>31)
			{
				m_date=1;
				m_month+=1;
			}
		case 4:
			if(m_date>30)
			{
				m_date=1;
				m_month+=1;
			}
			break;
		case 5:
			if(m_date>31)
			{
				m_date=1;
				m_month+=1;
			}
		case 6:
			if(m_date>30)
			{
				m_date=1;
				m_month+=1;
			}
			break;
		case 7:
			if(m_date>31)
			{
				m_date=1;
				m_month+=1;
			}
			break;
		case 8:
			if(m_date>31)
			{
				m_date=1;
				m_month+=1;
			}
			break;
		case 9:
			if(m_date>30)
			{
				m_date=1;
				m_month+=1;
			}
			break;
		case 10:
			if(m_date>31)
			{
				m_date=1;
				m_month+=1;
			}
			break;
		case 11:
			if(m_date>30)
			{
				m_date=1;
				m_month+=1;
			}
			break;
		case 12:
			if(m_date>31)
			{
				m_date=1;
				m_month+=1;
			}
			break;
		default:break;
	}
	if(m_month>12)
	{
		m_month=1;
		m_year++;
	}
}

bool Datetime::isleapyear()
{
	if((m_year%4)>0)
	{
		return false;
	}
	else
	{
		return true;
	}
}
