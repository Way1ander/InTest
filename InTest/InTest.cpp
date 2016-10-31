// InTest.cpp: определяет точку входа для консольного приложения.
//

#include "stdafx.h"

int test(char* filename, int expect, int** inarr = 0, int* innames = 0, int inn = 0);

int _tmain(int argc, _TCHAR* argv[])
{
	
	test("input.txt", 0);
	test("err1.txt", 1);
	test("err2.txt", 2);
	test("err3.txt", 3);
	test("err4.txt", 4);
	test("err5.txt", 5);
	test("err6.txt", 6);

	return 0;
}

int test(char* filename, int expect, int** inarr, int* innames, int inn){
	Matrix mat;
	int ret = 0;
	int err = mat.Read(filename);
	if (err == expect){
		ret = 1;//Correct
	}
	if (err == expect && err == 0){
		int** arr = mat.getArr();
		int* names = mat.getNames();
		int** arr1;
		int* names1;
		int n = mat.getN();
		if (n == 3){
			arr1 = new int*[n];
			for (int i = 0; i < n; i++){
				arr1[i] = new int[n];
			}
			names1 = new int[n];
			arr1[0][0] = 0; arr1[0][1] = 24; arr1[0][2] = 3;
			arr1[1][0] = 4; arr1[1][1] = 0;	 arr1[1][2] = 6;
			arr1[2][0] = 7; arr1[2][1] = 8;  arr1[2][2] = 0;
			names1[0] = 5;  names1[1] = 2;   names1[2] = 9;
			for (int i = 0; i < n; i++){
				for (int j = 0; j < n; j++){
					if (arr1[i][j] != arr[i][j]){
						ret = 0;//Неверно
						break;
					}
				}
				if (names1[i] != names[i]){
					ret = 0;//Неверно
					break;
				}
			}
		}
		else{
			if (inarr != 0 && innames != 0 && inn != 0){
				for (int i = 0; i < inn; i++){
					for (int j = 0; j < inn; j++){
						if (inarr[i][j] != arr[i][j]){
							ret = 0;//неверно
							break;
						}
					}
					if (innames[i] != names[i]){
						ret = 0;//Неверно
						break;
					}
				}
			}
		}
	}
	if (ret == 1) cout << filename << " - ok\n";
	if (ret != 1) cout << filename << " - error\n";
	return ret;//Неверно
}
