#include "pch.h"

#include <ctime>
#include <iostream>
#include <fstream>
#include <sstream>
#include <cstdio>
#include <string>
#include "common.h"

using namespace std;
//Для прохода назад будем искать какая ячейка матрицы MatrixWork [0..5]
//соответствует ячеке matrixWork [6..11]

/* для примера
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
template <typename T> // шаблон преобразование в string
string toString(T val)
{
	std::ostringstream oss;
	oss << val;
	return oss.str();
}




void fillingArrays() {
	int i = 0, j = 0;
	int myFileSize = 0;
	string fileNameOut = "matrixWork" + toString(i + 6) + ".txt";	//Выходной файл 196*196 элементов
	string fileNameIn = "matrixWork" + toString(i) + ".txt";		// входной файл 3600*3600
	string fileNameIntermediate = "exit_convolusion_" + toString(j) + ' ' + toString(0) + ".txt";
	string pointer;	//указатель на элемент, который считваем
	/* Создаем массивы,куда считаем данные из файлов для поиска элементов */
	/* Элемент запишем в отдельную структуру, где будут храниться индексы*/

	myFileSize = sqrt(sizeFile(fileNameOut));    // двумерный массив выходных данных
	 exitDataArray = new float*[myFileSize];
	 for (int i = 0; i < myFileSize; i++) 
	 {
		 exitDataArray[i] = new float[myFileSize];
	 }

	 myFileSize = sqrt(sizeFile(fileNameIntermediate));   //двумерный массив промежуточных данных
	 intermediateDataArray = new float*[myFileSize];
	 for (int i = 0; i < myFileSize; i++)
	 {
		 intermediateDataArray[i] = new float[myFileSize];
	 }

	 myFileSize = sqrt(sizeFile(fileNameIn));                 //двумерный массив входных данных
	 inDataArray= new float* [myFileSize];
	 for (int i=0;i<myFileSize;i++)
	 {
		 inDataArray[i] = new float[myFileSize];
	 }

	 ifstream exitFile(fileNameOut);
	 ifstream iterFile(fileNameIntermediate);
	 ifstream inFIle(fileNameIn);

	 // Записываем данные из файлов в массивы
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

//Эта функция будет искать коордитнаты значения в главном массиве
void lookingForCoordinatesInTheMiddleArray() {	
	// Будем пробовать искать координату в интермедиэйт массиве исходя из из данных в выходном массиве
	// и будем сохранять в структуру 
	int myFileSizeOut = sqrt(sizeFile(fileNameOut));		//храним размер массива выходного файла
	int myFileSizeIntermediate = sqrt(sizeFile(fileNameIntermediate));	// храним размер массива среднего файла
	for (int i = 0; i < myFileSizeOut; i++) {
		for (int j = 0; j < myFileSizeOut; j++) {
			for (int x = i * 4; x < i*4+4; x++) { 
			/* от элемента i*4 до i*4+4 для того что i однозначно определяет в каком
			диапазоне будет находится координата в среднем массиве */	
				for (int y = 0; y < myFileSizeIntermediate; y++) 	{
				/* от элемента j*4 до j*4+4 для того что j однозначно определяет в каком
				диапазоне будет находится координата в среднем массиве */
					if (exitDataArray[i][j] == intermediateDataArray[x][y]) { //Если элемент выходного массива найден в среднем
						coordinates[i].i = i;	//тогда сохраняем координату i
						coordinates[i].j = j;   // и координату j
				}
			}
		}
	}
	
}

