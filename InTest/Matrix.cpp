#include "stdafx.h"
#include "Matrix.h"


Matrix::Matrix()
{
	//cout << "Const OK\n";
}


int Matrix::Read(char* filename)
{
	n = 0;// For out file clearance if something goes wrong
	ifstream anfile("animals");
	if (anfile.is_open()){
		queue<double> tmp;
		double i;
		int count = 0;

		anfile.seekg(0, std::ios::end);
		int size = anfile.tellg();

		anfile.seekg(0, 0);
		while (!anfile.eof() && count <= size){
			anfile >> i;
			tmp.push(i);
			++count;
		}
		if (count > size) return 1;//Animals is really wrong

		double num;
		animnum = num = (double)count / 3;
		if (num != (double)animnum){
			return 2;//Animals is not 3 params for each
		}
		animals = new Animal[animnum];
		double a = -1, b = -1, c = -1;
		for (int i = 0; i < animnum; i++){
			a = tmp.front();
			tmp.pop();
			b = tmp.front();
			tmp.pop();
			c = tmp.front();
			tmp.pop();
			if (animals[i].setNumber(i) || animals[i].setChance(a) || animals[i].setPresence(b) || animals[i].setscores(c)){
				return 3;//Animals specs is wrong
			}
			a = b = c = -1;
		}
		for (int i = 0; i < animnum; i++){
			//cout << animals[i].getNum() << " " << animals[i].getChance() << " " << animals[i].getHave() << " " << animals[i].getPoints() << "\n";
		}
	}
	anfile.close();
	ifstream infile(filename);
	if (infile.is_open()){
		//cout << "File name:" << filename << "\n";
		int count = 0;
		int size = 0;

		infile.seekg(0, std::ios::end);
		size = infile.tellg();
		//cout << "Size of file = " << size << "\n";

		queue<double> tmp;
		double i;
		infile.clear();
		infile.seekg(0, 0);
		while (!infile.eof() && count <= size){
			infile >> i;
			tmp.push(i);
			//cout << i << "\n";
			++count;
			i = -1;
		}
		if (count > size) return 4;//Input is really wrong
		int strings = 1;//Strings after matrix
		double nd = (sqrt((double)strings*(double)strings + 4 * (double)count) - (double)strings) / 2.0;
		n = (int)nd;


		if (nd != (double)n){
			n = 0;// For out file clearance if something goes wrong
			return 5;//Uncorect num of numbers
		}

		//cout << "n=" << n << "\n";
		arr = new int*[n];
		names = new int[n];
		double cur;
		for (int i = 0; i < n + strings; i++) arr[i] = new int[n];
		for (int i = 0; i < n + strings; i++){
			for (int j = 0; j < n; j++){
				cur = 0;
				cur = tmp.front();
				if (cur < 0){
					n = 0;// For out file clearance if something goes wrong
					return 6;//Something is less then 0
				}

				if (cur == 0 && i < n && i != j){
					n = 0;// For out file clearance if something goes wrong
					return 7;//The path length is 0 between two animals
				}
				else arr[i][j] = (int)cur;

				if (i == j && cur != 0){
					n = 0;// For out file clearance if something goes wrong
					return 8;//The path length is not 0 on diagonal
				}
				else arr[i][j] = (int)cur;

				if (i == n && (cur < 0 || cur >= animnum)){
					n = 0;// For out file clearance if something goes wrong
					return 9;//Number of animal in namelist is less then 0 or bigger then animals in "animals" file
				}
				else names[j] = (int)cur;

				//cout << cur << " ";
				tmp.pop();
			}
			//cout << "\n";
		}
	}
	infile.close();
	return 0;
}

int Matrix::Write(char* filename)
{
	ofstream outfile(filename, ios_base::trunc);
	int* test;
	if (n > 0 && path != 0){//If n==0 then out file will be just cleared
		test = new int[n];
		for (int i = 0; i < n; i++){
			test[i] = 0;
		}
		for (int i = 0; i < n; i++){
			test[path[i]]++;
			if (test[path[i]]>1){
				outfile.close();
				return 0;// Uncorrect path
			}
		}
		if (outfile.is_open()){
			outfile << path[0];
			for (int i = 1; i < n; i++){
				outfile << " " << path[i];
			}
		}
		outfile.close();
		return 1;// Correct
	}
	outfile.close();
	return 0;// Uncorrect
}

int Matrix::Pathfinder(){
	path = new int[n];
	for (int i = 0; i < n; i++){
		path[i] = i;
	}
	int bub = 0;
	for (int i = 0; i < n - 1; i++){
		for (int j = i + 1; j < n; j++){
			if (names[path[i]]>names[path[j]]){
				bub = path[i];
				path[i] = path[j];
				path[j] = bub;
			}
		}
	}
	//path[0] = 0;//Do uncorrect output
	return 1;//path found
}
int** Matrix::getArr(){
	return arr;
}
int* Matrix::getNames(){
	return names;
}
int Matrix::getN(){
	return n;
}
Matrix::~Matrix()
{
}
