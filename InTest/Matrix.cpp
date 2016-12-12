#include "stdafx.h"
#include "Matrix.h"


Matrix::Matrix()
{
	//cout << "Const OK\n";
}


int Matrix::Read(char* filename)
{
	n = 0;// �������� ���� ����� ���� ��� ������
	ifstream anfile("animals");
	if (anfile.is_open()){
		queue<double> tmp;
		double i;
		int count = 0;
		animnum = std::count(std::istreambuf_iterator<char>(anfile),
			std::istreambuf_iterator<char>(), '\n') + 1;
		//int max = animnum * 3;//��������� ���������� �����
		anfile.seekg(0, std::ios::end);
		int size = anfile.tellg();
		anfile.seekg(0, 0);
		while (!anfile.eof() && count <= size){
			anfile >> i;
			tmp.push(i);
			++count;
		}

		if (count > size) return 6;//��������� ���������� ��������� ���������
		double num;
		animnum = num = (double)count / 3;
		if (num != (double)animnum){
			return 9;//��� ��������� ���� ������ 3� ����������
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
				return 7;//������������ ��������� ���������
			}
			a = b = c = -1;
		}
		cout << "animals's properties:\n";
		for (int i = 0; i < animnum; i++){
			cout << animals[i].getNumber() << " " << animals[i].getChance() << " " << animals[i].getPresence() << " " << animals[i].getscores() << "\n";
		}
	}
	anfile.close();
	ifstream infile(filename);
	if (infile.is_open()){
		cout << filename << ":\n";
		int count = 0;
		int size = 0;
		infile.seekg(0, std::ios::end);
		size = infile.tellg();
		queue<double> tmp;
		double i;
		infile.clear();
		infile.seekg(0, 0);
		while (!infile.eof() && count <= size){
			infile >> i;
			tmp.push(i);
			++count;
			i = -1;
		}
		if (count > size) return 8;//�������� ���������� �����
		int str = 1;//����� �-�� ���������� ����� ���� ������
		double nd = (pow(pow((double)str, 2) + 4 * (double)count, 0.5) - (double)str) / 2.0;
		n = (int)nd;

		if (nd != (double)n){
			n = 0;
			return 1;//���������� ���������� �������� �� ������������� ���������� ��������
		}

		cout << "n=" << n << "\n";
		arr = new int*[n];
		names = new int[n];
		double cur;
		for (int i = 0; i < n; i++) arr[i] = new int[n];
		for (int i = 0; i < n + str; i++){
			for (int j = 0; j < n; j++){
				cur = 0;
				cur = tmp.front();
				if (cur < 0){
					n = 0;
					return 2;//�������� <0
				}

				if (cur == 0 && i < n && i != j){
					n = 0;
					return 3;//���� ����� ��������� =0
				}

				if (i == j && cur != 0){
					n = 0;
					return 4;//�� ������� ��������� ������������ �����, �������� �� 0 (���� �� ��������� � ������ ���� !=0)
				}
				else{
					if (i < n){
						if (i != j)	arr[i][j] = (int)cur;
						else arr[i][j] = inf;
					}
				}

				if (i == n && (cur < 0 || cur >= animnum)){
					n = 0;
					return 5;//���-�� �������� � animals � input �� ���������
				}
				else{
					if (i == n) names[j] = (int)cur;
				}

				//cout << cur << " ";
				tmp.pop();
			}
			//cout << "\n";
		}
	}
	infile.close();
	for (int i = 0; i < n; i++)
		for (int j = 0; j < n; j++)
			if (arr[i][j] != arr[j][i]) return 10;
	return 0;
}

int Matrix::Write(char* filename)
{
	ofstream outfile(filename, ios_base::trunc);
	int* test;
	if (n > 0 && path != 0){//n==0, ���� ���������
		test = new int[animnum];
		for (int i = 0; i < animnum; i++){
			test[i] = 0;
		}
		for (int i = 0; i < n; i++){
			test[path[i]]++;
			if (test[path[i]]>1){
				outfile.close();
				return 0;// ������������ ����(*)
			}
		}
		if (outfile.is_open()){
			outfile << path[0];
			for (int i = 1; i < n; i++){
				outfile << " -> " << path[i];
			}
		}
		outfile.close();
		return 1;// �������
	}
	outfile.close();
	return 0;// ������� � �������
}
/*int Matrix::Pathfinder(){
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
}*/
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
