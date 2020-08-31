#include <vector>
#include <string>
#include <iostream>
#include "strutils.h"

using namespace std;

bool isValidCode(string & temp);
bool fixCode(string & temp, const int & q);
bool isExist(string & code, vector<string> & temp);

struct LC{
	int size;
	vector<string> code;

	LC(int s=4, int q=2):
		size(s)
	{
		bool flag = true;
		for(int i=0; i<pow(s,q) && flag; i++)
		{
			string c;
			cout << "Enter the base: ";
			cin >> c;
			if(c == "end")
				flag = false;
			if( (c.length() != s || isValidCode(c)) && flag)
			{
				cout << "INVALID CODE! Enter the code again: ";
				cin >> c;
				if(c == "end")
					flag = false;
			}
			if(flag)
			{
				fixCode(c,q);
				if(!isExist(c,code))
				{
					code.push_back(c);
				}
			}
		}
	}

};

//checks wheter the code exists or not, returns true if the code exists
bool isExist(string & code, vector<string> & temp)
{
	if(temp.size() == 0)
		return false;
	for(int i=0; i<temp.size(); i++)
	{
		if(temp[i] == code)
			return true;
	}
	return false;
}

// c = c1(mod q)
bool fixCode(string & temp, const int & q)
{
	string temp2="";
	for(int i=0; i<temp.length();i++)
	{
		//int num = atoi(temp.substr(i,1));
		int num = temp.at(i) - '0';
		num = num%q;
		temp2 += '0' + num;
	}
	temp = temp2;
	return true;
}

// checks the validity of the code, lenght and digits
bool isValidCode(string & temp)
{
	for(int i=0; i<temp.length(); i++)
	{
		if( isalpha(temp.at(i)) == 0)
			return false;
	}
	return true;
}

//vector print
template<class temp>
void print(vector<temp> & temp)
{
	int i;
	for(i=0;i<temp.size()-1;i++)
	{
		cout << temp[i] << ",";
	}
	cout << temp[i];
}

//matrixPrint
template<class temp>
void print2(vector<temp> & temp)
{
	for(int i=0; i<temp.size();i++)
	{
		for(int j=0; j<temp[0].size();j++)
			cout << temp[i][j];
		cout << endl;
	}
}

//generates all possible codes of length n in Fq
vector<string> findAllCodes(const int q, const int n)
{
	vector<string> result;

	int convertFromCopy, digit, convertTo;
	unsigned int convertFrom;
	string stringDigit, answer;

	int total = pow(q,n);
	convertTo = q;

	for(int i=0; i<total; i++)
	{
		answer = "";
		convertFrom = i;

		convertFromCopy = convertFrom;

		while (convertFrom != 0){
			digit = convertFrom % convertTo;

			if (digit < 10)
				stringDigit = '0' + digit;
			else
				stringDigit = digit - 10 + 'A';

			answer = stringDigit + answer;

			convertFrom /= convertTo;                
		}
		int l=answer.length();
		while(l != n)
		{
			answer = '0' + answer;
			l++;
		}
		result.push_back(answer);
	}
	return result;
}

vector<string> findBaseParams(const int k)
{
	vector<string> result;

	int convertFromCopy, digit, convertTo;
	unsigned int convertFrom;
	string stringDigit, answer;

	int total = pow(2,k);
	convertTo = 2;

	for(int i=0; i<total; i++)
	{
		answer = "";
		convertFrom = i;

		convertFromCopy = convertFrom;

		while (convertFrom != 0){
			digit = convertFrom % convertTo;

			if (digit < 10)
				stringDigit = '0' + digit;
			else
				stringDigit = digit - 10 + 'A';

			answer = stringDigit + answer;

			convertFrom /= convertTo;                
		}
		int l=answer.length();
		while(l != k)
		{
			answer = '0' + answer;
			l++;
		}
		result.push_back(answer);
	}
	return result;
}

bool innerProduct(string & c1, string & c2, const int & n, const int & q)
{
	int sum = 0;

	string zero = "";
	for(int i=0; i<n;i++)
		zero += "0";
	if(zero == c1 || zero == c2)
		return true;

	for(int i=0; i<n; i++)
	{
		int a = c1.at(i) - '0';
		int b = c2.at(i) - '0';
		sum += a*b;
	}
	sum = sum %	q;
	if(sum == 0)
		return true;
	return false;
}

int spanInnerProduct(string & c1, int & a, const int & n)
{
	int sum = 0;
	for(int i=0; i<n; i++)
	{
		sum += a * (c1.at(i) - '0');
	}
	return sum;
}

string vectorAddition(vector<string> temp, const int & n, const int & q)
{
	string result = "";
	for(int i=0; i<n; i++)
	{
		int sum = 0;
		for(int j=0; j<temp.size(); j++)
		{
			sum += temp[j].at(i) - '0';
		}
		sum = sum%q;
		result += '0' + sum;
	}

	return result;
}

vector<string> span(vector<string> bases, vector<string> baseParams, const int & n, const int & q)
{	
	string zero = "";
	for(int i=0; i<n;i++)
		zero += "0";
	vector<string> vectorSpace;
	vectorSpace.push_back(zero);

	for(int i=1; i<baseParams.size(); i++)
	{
		string param = baseParams[i];

		vector<string> temp;

		for(int j=0; j<bases.size(); j++)
		{
			//string a = param.substr(j,1);
			char a = param.at(j);
			int a_int = a - '0';
			string v = bases[j];

			string tempV = "";
			for(int x=0; x<v.length() ;x++)
			{
				tempV += '0' + (a_int * (v.at(x) - '0')) % q;
			}
			temp.push_back(tempV);
		}
		string add = vectorAddition(temp,n,q);
		if(!isExist(add,vectorSpace))
			vectorSpace.push_back(add);
	}
	return vectorSpace;
}

int minDisCalculator(const vector<string> vectorSpace, const int & n)
{
	int min = 100;
	for(int i=0; i<vectorSpace.size(); i++)
	{
		string code1 = vectorSpace[i];
		for(int j=i+1; j<vectorSpace.size(); j++)
		{
			string code2 = vectorSpace[j];
			int count = 0;
			for(int k=0; k<n; k++)
			{
				if(code1.at(k) != code2.at(k) && code1!=code2)
					count += 1;
			}
			if(count<min)
				min = count;
		}
	}
	return min;
}

int main()
{
	int q,n,k;
	cout << "Enter the q,n and k values(q,n,k): ";
	cin >> q >> n >> k;
	
	cout << "There will be maximum --> " << pow(q,n) << " # of codes." << endl;
	vector<string> Codes;
	Codes = findAllCodes(q,n);

	vector<string> BaseParams;
	BaseParams = findBaseParams(k);

	print(BaseParams);
	cout << endl;
	LC myCodes(n,q);
	vector<string> vectorSpace;
	vectorSpace = span(myCodes.code,BaseParams,n,q);
	cout << "Our vector space is: ";
	print(vectorSpace);
	cout << endl;
	cout << endl;

	//cout << "The codes in my set S are: ";
	//
	//if(!myCodes.code.empty())
	//	print(myCodes.code);
	//else
	//	cout << "No codes.";

	//cout << endl;

	/*
	cout << endl << "All the codes are: ";
	print(Codes);
	cout << endl;
	*/
	
	vector<string> Duals;

	for(int i=0; i<Codes.size(); i++)
	{
		bool isDual = true;
		for(int k=0; k<vectorSpace.size() && isDual; k++)
		{
			isDual = innerProduct(Codes[i] , vectorSpace[k] , n , q);
		}

		if(isDual)
			Duals.push_back(Codes[i]);
	}

	cout << "The dual codes of C are: ";
	if(!Duals.empty())
		print(Duals);
	else
		cout << "No dual codes.";
	cout << endl;
	cout << endl;

	vector<string> intersectingCodes;

	for(int i=0; i<vectorSpace.size(); i++)
	{
		if(isExist(vectorSpace[i],Duals))
			intersectingCodes.push_back(vectorSpace[i]);
	}
	
	cout << "The codes that are intersecting with C and C dual are: ";
	print(intersectingCodes);
	cout << endl;
	cout << endl;

	if(intersectingCodes.size() == 1)
	{	
		cout << endl;
		cout << "This is an LCD code!" << endl;
		cout << endl;
		cout << "Min distance is: " << minDisCalculator(vectorSpace,n) << endl;
	}
	else
		cout << "Not an LCD code!" << endl;

	return 0;
}