#include <vector>
#include <string>
#include <iostream>
#include <ctime>
#include <fstream>
#include <sstream>

#include <windows.h>
#include <mmsystem.h>
#pragma comment(lib,"Winmm.lib")

using namespace std;

int PROGRESBAR = 16384;
int PARTS = 16384;

#define COMBINATIONFILE "Combinations.txt"
#define POSSIBLEBASESFILE "Possible Bases.txt"

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
			cout << temp[i][j] << " ";
		cout << endl;
	}
}

template<class temp>
void print3(vector<temp> & temp, ofstream & o)
{
	int i;
	for(i=0;i<temp.size()-1;i++)
	{
		o << temp[i] << ",";
	}
	o << temp[i];
}

template<class temp>
int print4(vector<temp> & temp, ofstream & o)
{
	static int count=0;
	int i;
	for(int i=0; i<temp.size();i++)
	{
		for(int j=0; j<temp[0].size();j++)
			o << temp[i][j] << " ";
		o << endl;
		count ++;
	}
	return count;
}

template<class temp>
void print5(vector<temp> & temp, ofstream & o)
{
	int i;
	for(i=0;i<temp.size();i++)
	{
		o << temp[i] << " ";
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

vector<string> findBaseParams(const int & k, const int & q)
{
	vector<string> result;

	int convertFromCopy, digit, convertTo;
	unsigned int convertFrom;
	string stringDigit, answer;

	int total = pow(q,k);
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

string vectorAddition(vector<string> & temp, const int & n, const int & q)
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

vector<string> span(vector<string> & bases, vector<string> & baseParams, const int & n, const int & q)
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

int minDisCalculator(const vector<string> & vectorSpace, const int & n)
{
	int min = 10000;
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

void getCofactor(vector<vector<int> > & mat, vector<vector<int> > & temp, int p, int q, int n) 
{ 
	int i = 0, j = 0; 

	// Looping for each element of the matrix 
	for (int row = 0; row < n; row++) 
	{ 
		for (int col = 0; col < n; col++) 
		{ 
			//  Copying into temporary matrix only those element 
			//  which are not in given row and column 
			if (row != p && col != q) 
			{ 
				temp[i][j++] = mat[row][col]; 

				// Row is filled, so increase row index and 
				// reset col index 
				if (j == n - 1) 
				{ 
					j = 0; 
					i++; 
				} 
			} 
		} 
	} 
} 

int determinantOfMatrix(vector<vector<int> > & mat, int n, const int & q) 
{ 
	int D = 0; // Initialize result 

	//  Base case : if matrix contains single element 
	if (n == 1) 
		return mat[0][0]; 

	//int temp[N][N]; // To store cofactors 
	vector<vector<int> > temp(n, vector<int> (n));

	int sign = 1;  // To store sign multiplier 

	// Iterate for each element of first row 
	for (int f = 0; f < n; f++) 
	{ 
		// Getting Cofactor of mat[0][f] 
		getCofactor(mat, temp, 0, f, n); 
		D += sign * mat[0][f] * determinantOfMatrix(temp, n - 1,q); 

		// terms are to be added with alternate sign 
		sign = -sign; 
	} 

	return (D%q); 
} 

vector<vector<int> > matrixStrtoInt(vector<string> & BaseParams, const int & n)
{
	vector<vector<int> > result;

	for(int i=0; i<BaseParams.size(); i++)
	{
		vector<int> temp;
		for(int j=0; j<n; j++)
		{
			temp.push_back(BaseParams[i].at(j) - '0');
		}
		result.push_back(temp);
	}
	return result;
}

void pretty_print(const vector<string> & v, vector<vector<string> > & combinations, ofstream & CombinationsFile) {
	static int count = 0;
	vector<string> temp;
	for (int i = 0; i < v.size(); ++i) { 
		temp.push_back(v[i]);
	}
	combinations.push_back(temp);
	count ++;	
	if(count%PARTS == 0)
	{
		print4(combinations,CombinationsFile);
		combinations.clear();
	}
}

void go(int offset, int k, vector<string> & codes, vector<string> & combination,vector<vector<string> > & combinations, ofstream & CombinationsFile) {
	if (k == 0) { 
		pretty_print(combination,combinations, CombinationsFile );
		return;
	}
	for (int i = offset; i <= codes.size() - k; ++i) {
		combination.push_back(codes[i]);
		go(i+1, k-1,codes,combination,combinations, CombinationsFile);
		combination.pop_back();
		if(i%PROGRESBAR == 0)
			cout << ".";
	}
}

double baseTester(ifstream & CombinationsFile, const int & n, ofstream & PossibleBasesFile, const int & q, const int & count)
{
	string zero = "";
	for(int i=0; i<n;i++)
		zero += "0";
	string line;
	double i=0;
	int realCount = 0;
	while( getline(CombinationsFile,line))
	{
		vector<string> trial;
		string code;
		istringstream iss(line);
		while(iss>>code)
			trial.push_back(code);

		if(!isExist(zero,trial))
		{
			vector<vector<int> > temp;
			temp = matrixStrtoInt(trial,trial.size());

			if(determinantOfMatrix(temp,trial.size(),q) != 0)
			{
				print5(trial, PossibleBasesFile);
				PossibleBasesFile << endl;
			}
			realCount++;
		}
		i++;
		if(int(i)%PROGRESBAR == 0)
			cout << "%" << int( (i / count * 100)) << "\t";
	}
	return realCount;
}

bool LCDchecker(vector<string> & bases, vector<string> & Codes, vector<string> & BaseParams ,const int & n, const int & q)
{
	vector<string> vectorSpace;
	vectorSpace = span(bases,BaseParams,n,q);

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

	vector<string> intersectingCodes;

	for(int i=0; i<vectorSpace.size(); i++)
	{
		if(isExist(vectorSpace[i],Duals))
			intersectingCodes.push_back(vectorSpace[i]);
	}

	if(intersectingCodes.size() == 1)
	{
		//cout << "This is an LCD code!" << endl;
		return true;
	}
	else
	{
		//cout << "Not an LCD code!" << endl;
		return false;
	}
}

bool LCDcheckerFaster(vector<string> bases, const int & k, const int & q, const int & n)
{
	vector<vector<int> > matrix;
	matrix = matrixStrtoInt(bases,n);
	vector<vector<int> > transpose (n, vector<int> (k));
	for(int i=0; i<n; i++)
	{
		for(int j=0; j<k; j++)
		{
			transpose[i][j] = matrix[j][i];
		}
	}

	vector<vector<int> > result(k,vector<int> (k));

	for(int i=0; i<bases.size(); i++)
	{
		for(int j=0; j<transpose[0].size();j++)
		{
			for(int x=0; x<transpose.size(); x++)
			{
				result[i][j] += matrix[i][x] * transpose[x][j];
			}
		}
	}

	if(determinantOfMatrix(result,k,q) != 0)
		return true;
	else
		return false;
}

int lineCounter(ifstream & in)
{
	int count=0;
	string line;
	while(getline(in,line))
		count++;
	in.clear();
	in.seekg(0);
	return count;
}

int main()
{
	ofstream out, CombinationsFileWrite,PossibleBasesWrite;
	ifstream CombinationsFileRead, PossibleBasesRead;

	vector<string> emptyVec;
	vector<vector<string> > emptyMat;
	clock_t time;
	int q,n,k;
	cout << "Enter the q,n and k values(q,n,k): ";
	cin >> q >> n >> k;

	string fileName = "Generator Matrices.txt"; 
	out.open(fileName);
	CombinationsFileWrite.open(COMBINATIONFILE);

	double start = clock();

	vector<string> Codes;
	Codes = findAllCodes(q,n);

	vector<string> BaseParams;
	BaseParams = findBaseParams(k,q);

	cout << "--> Creating Combinations!!!" << endl;
	vector<string> combination;
	vector<vector<string> > combinations;
	go(0,k,Codes,combination,combinations,CombinationsFileWrite);
	int CombinationFileSize = print4(combinations,CombinationsFileWrite);
	combinations.clear();
	CombinationsFileWrite.close();

	cout << endl << "--> Combinations are done!!!" << endl;

	CombinationsFileRead.open(COMBINATIONFILE);
	PossibleBasesWrite.open(POSSIBLEBASESFILE);

	cout << endl << "!!! There are " << CombinationFileSize << " combinations." << endl << endl;

	cout << "--> Base Testing has been started!!!" << endl;

	vector<vector<string> > possibleBases;
	int sizePossibleBases = baseTester(CombinationsFileRead,n,PossibleBasesWrite,q,CombinationFileSize);
	PossibleBasesWrite.close();
	CombinationsFileRead.close();
	cout << endl << "--> Base Testing is done!!!" << endl;
	cout << endl << "!!! There are " << sizePossibleBases << " possible bases." << endl << endl;
	
	cout << "--> LCD Checking has been started!!!" << endl;
	PossibleBasesRead.open(POSSIBLEBASESFILE);

	combination.clear();
	combination = emptyVec;

	vector<vector<string> > LCD_Bases;

	string line;
	double i=0;
	while(getline(PossibleBasesRead,line))
	{
		vector<string> temp;
		string code;
		istringstream iss(line);
		while(iss>>code)
			temp.push_back(code);

		//if(LCDchecker(temp,Codes,BaseParams,n,q))
			//LCD_Bases.push_back(temp);
		if(LCDcheckerFaster(temp,k,q,n))
			LCD_Bases.push_back(temp);

		i++;
		if(int(i)%PROGRESBAR == 0)
			cout << "%" << int( (i / sizePossibleBases * 100) * 100 / 37) << "\t";
	}
	PossibleBasesRead.close();

	cout << endl << "--> LCD Checking is done!!!" << endl;
	
	cout << endl << "!!! There are " << LCD_Bases.size() << " LCD Codes." << endl << endl;

	cout << "--> Minimum Distance Search has been started!!!" << endl;

	vector<int> minDistances;
	for(double i=0; i<LCD_Bases.size(); i++)
	{
		vector<string> vectorSpace;
		vectorSpace = span(LCD_Bases[i],BaseParams,n,q);
		minDistances.push_back(minDisCalculator(vectorSpace,n));
		if(int(i)%PROGRESBAR == 0 && i != 0)
			cout << "%" << int( (i / LCD_Bases.size() * 100)) << "\t";
	}
	cout << endl << "--> Minimum Distance Search is done!!!" << endl;

	int max=0;
	for(int i=0; i<minDistances.size();i++)
	{
		if(minDistances[i] > max)
			max = minDistances[i];
	}
	cout << endl << "------------------------" << endl;
	cout << "--> The largest min dist for LCD(" << n << "," << k << ") is: " << max;
	cout << endl;

	//out << "The largest min dist for LCD(" << n << "," << k << ") is: " << max;
	//out << endl;
	out << "Here are the generator matrices for LCD(" << n << "," << k << "," << max <<")-codes." << endl;

	int LCDmin = 0;
	for(int i=0; i<minDistances.size(); i++)
	{
		if(minDistances[i] == max)
		{
			LCDmin++;
			print3(LCD_Bases[i], out);
			out << endl;
		}
	}

	cout << endl << "!!! There are " << LCDmin << " LCD Codes with largest minimum distance." << endl << endl;

	double end = clock();
	double difference = end-start;

	double seconds = difference / CLOCKS_PER_SEC;
	int hour = seconds / 3600;
	int minutes = int (seconds / 60) % 60;
	int secs = int(seconds) % 60;

	cout << endl << "It took " << hour << " hours : " << minutes << " minutes : " << secs << " seconds." << endl << endl;
	//cout << "The largest minimum distance is: " << max << endl;

	out.close();

	PlaySound(TEXT("test.wav"), NULL, SND_FILENAME);

	return 0;
}