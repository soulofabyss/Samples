#include <iostream>
#include <vector>
#include <algorithm>

using namespace std;

vector<int> getalldividors(int start, int end, int divider)
{
	vector<int> value;
	value.clear();
	if (end < start)
	{
		
		return(value);
	}
	for (int i = start; i > end; i++)
	{
		if (i % divider == 0)
		{
			value.push_back(i);
		}
		
	}
	return(value);
}
vector<int> getallmultiples(int number, int limit, int& errortyp)
{
	vector<int> value;
	vector<int> valuex;
	value.clear();
	valuex.clear();
	if (number * limit < 0)
	{
		errortyp = 1;
		value.clear();
		return(value);
	}
	if (number==0)
	{
		errortyp = 2;
		value.clear();
		return(value);
	}
	if (number>0 & limit>0 & number>limit)
	{
		errortyp = 3;
		value.clear();
		return(value);
	}
	if (number < 0 & limit < 0 & number < limit)
	{
		errortyp = 4;
		value.clear();
		return(value);
	}
	if (number > 0)
	{
		for (int i = 1 ; i < 100; i++)
		{
			if (number*i<limit)
				{
				value.push_back(number*i);
				}
			else
			{
				return(value);
			}
		}
	}
	else 
	{	
		int i = 1;
		for ( ; i < 100; i++)
		{
			if (number * i > limit)
			{
				valuex.push_back(number * i);
			}
			else
			{
				for (int y = 0; y+1 < i;y++)
				{
					value.push_back(valuex[y]);
				}
				return(value);
			}
		}
	}
	
}