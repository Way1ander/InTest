#pragma once

class Matrix
{
private:
	int** arr;
	int* names;
	int n;
	Animal* animals;
	int animnum;
	int* path = 0;
public:
	Matrix();
	int Read(char* file);
	int Write(char* file);
	int Pathfinder();
	int** getArr();
	int* getNames();
	int getN();
	~Matrix();
};



