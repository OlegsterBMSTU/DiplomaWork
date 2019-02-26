#include "pch.h"

#include <ctime>
#include <iostream>
#include <fstream>
#include <sstream>
#include <cstdio>
#include <string>
#include "common.h"

using namespace std;
//��� ������� ����� ����� ������ ����� ������ ������� MatrixWork [0..5]
//������������� ����� matrixWork [6..11]

/* ��� �������
matrixWork0 -> exitConvolution1_0 -> matrixWork5
*/

struct indexes
{
	int i = 0;
	int j = 0;
};

float **exitDataArray;
float **intermediateDataArray;
float **inDataArray;
indexes * coordinates = new indexes[196];

template<typename T>
T fromString(const string& s)
{
	istringstream iss(s);
	T res;
	iss >> res;
	return res;
}
template <typename T> // ������ �������������� � string
string toString(T val)
{
	std::ostringstream oss;
	oss << val;
	return oss.str();
}




void fillingArrays() {
	int i = 0, j = 0;
	int myFileSize = 0;
	string fileNameOut = "matrixWork" + toString(i + 6) + ".txt";	//�������� ���� 196*196 ���������
	string fileNameIn = "matrixWork" + toString(i) + ".txt";		// ������� ���� 3600*3600
	string fileNameIntermediate = "exit_convolusion_" + toString(j) + ' ' + toString(0) + ".txt";
	string pointer;	//��������� �� �������, ������� ��������
	/* ������� �������,���� ������� ������ �� ������ ��� ������ ��������� */
	/* ������� ������� � ��������� ���������, ��� ����� ��������� �������*/

	myFileSize = sqrt(sizeFile(fileNameOut));    // ��������� ������ �������� ������
	 exitDataArray = new float*[myFileSize];
	 for (int i = 0; i < myFileSize; i++) 
	 {
		 exitDataArray[i] = new float[myFileSize];
	 }

	 myFileSize = sqrt(sizeFile(fileNameIntermediate));   //��������� ������ ������������� ������
	 intermediateDataArray = new float*[myFileSize];
	 for (int i = 0; i < myFileSize; i++)
	 {
		 intermediateDataArray[i] = new float[myFileSize];
	 }

	 myFileSize = sqrt(sizeFile(fileNameIn));                 //��������� ������ ������� ������
	 inDataArray= new float* [myFileSize];
	 for (int i=0;i<myFileSize;i++)
	 {
		 inDataArray[i] = new float[myFileSize];
	 }

	 ifstream exitFile(fileNameOut);
	 ifstream iterFile(fileNameIntermediate);
	 ifstream inFIle(fileNameIn);

	 // ���������� ������ �� ������ � �������
	 myFileSize = sqrt(sizeFile(fileNameOut));
	 for (int i = 0; i < myFileSize; i++) 
	 {
		 for (int j = 0; j <myFileSize ; j++) 
		 {
			 exitDataArray[i][j] = fromString<float>(pointer);
		 }
	 }

	 myFileSize = sqrt(sizeFile(fileNameIntermediate);
	 for (int i = 0; i < myFileSize; i++)
	 {
		 for (int j = 0; j < myFileSize; j++)
		 {
			 intermediateDataArray[i][j] = fromString<float>(pointer);
		 }
	 }

	 myFileSize = sqrt(sizeFile(fileNameIn));
	 for (i = 0; i < myFileSize; i++) 
	 {
		 for (j = 0; j < myFileSize; j++) 
		 {
			 inDataArray[i][j] = fromString<float>(pointer);
		 }
	 }		 
}

//��� ������� ����� ������ ����������� �������� � ������� �������
void lookingForCoordinates() {
}

