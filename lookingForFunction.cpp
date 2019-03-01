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

ofstream testFile("testFile.txt"); // проверка корректного заполнения файла, будем записывать все в файл

string fileNameOut;
string fileNameIn;
string fileNameIntermediate;

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

int control(int i, int j, int myFileSize);




void fillingArrays() {
	int i = 0, j = 0;
	int myFileSize = 0;
	fileNameOut = "matrixWork" + toString(i + 6) + ".txt";	//Выходной файл 196*196 элементов
	fileNameIn = "matrixWork" + toString(i) + ".txt";		// входной файл 3600*3600
	fileNameIntermediate = "exit_convolusion_" + toString(i) + ' ' + toString(1) + ".txt"; // Задано статично 0.1 для тестов и проверки. Потом переделать чтобы по координатам нормально работало
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
	inDataArray = new float*[myFileSize];
	for (int i = 0; i < myFileSize; i++)
	{
		inDataArray[i] = new float[myFileSize];
	}

	ifstream exitFile(fileNameOut);
	ifstream iterFile(fileNameIntermediate);
	ifstream inFile(fileNameIn);

	// Записываем данные из файлов в массивы
	//Заполняем массив выходящий
	// Переделал функции на while для нормальной работы с файлом
	myFileSize = sqrt(sizeFile(fileNameOut));
	testFile << "\nExit File:" << endl << endl;
	while (getline(exitFile, pointer)) {
		exitDataArray[i][j] = fromString<float>(pointer);
		testFile << exitDataArray[i][j] << "       ";
		j++;
		if (j == myFileSize) {
			i++;
			j = 0;
			testFile << endl;
		}
	}


	//Заполняем массив средний
	myFileSize = sqrt(sizeFile(fileNameIntermediate));
	i = 0;
	testFile << "\nMiddle File:" << endl << endl;
	while (getline(iterFile, pointer)) {
		intermediateDataArray[i][j] = fromString<float>(pointer);
		testFile << intermediateDataArray[i][j] << "       ";
		j++;
		if (j == myFileSize) {
			i++;
			j = 0;
			testFile << endl;
		}

	}

	//Заполняем массив Входной
	myFileSize = sqrt(sizeFile(fileNameIn));
	//	 testFile << "In File:" <<endl<<endl;
	i = 0;
	while (getline(inFile, pointer)) {
		inDataArray[i][j] = fromString<float>(pointer);
		//testFile << inDataArray[i][j] << "       ";
		j++;
		if (j == myFileSize) {
			i++;
			j = 0;
			//testFile << endl;
		}
	}

}

//Эта функция будет искать коордитнаты значения в главном массиве
// Пока не работает. Заполняет первые 14 значений, далее беда. Бум думать
void lookingForCoordinatesInTheMiddleArray() {
	// Будем пробовать искать координату в интермедиэйт массиве исходя из из данных в выходном массиве
	// и будем сохранять в структуру 
	testFile << endl << endl;
	testFile << "void lookingForCoordinatesInTheMiddleArray" << endl;
	int myFileSizeOut = (sizeFile(fileNameOut));		//храним размер массива выходного файла
	int myFileSizeIntermediate = sqrt(sizeFile(fileNameIntermediate));	// храним размер массива среднего файла
	int k = 0;
	for (int i = 0; i < sqrt(myFileSizeOut); i++) {
		for (int j = 0; j < sqrt(myFileSizeOut); j++) {
			for (int x = i * 4; x < i * 4 + 4; x++) {
				/* от элемента i*4 до i*4+4 для того что i однозначно определяет в каком
				диапазоне будет находится координата в среднем массиве */
				for (int y = j * 4; y < j * 4 + 4; y++) {
					/* от элемента j*4 до j*4+4 для того что j однозначно определяет в каком
					диапазоне будет находится координата в среднем массиве */
					if (exitDataArray[i][j] == intermediateDataArray[x][y]) { //Если элемент выходного массива найден в среднем
						coordinates[k].i = x;	//тогда сохраняем координату i
						coordinates[k].j = y;   // и координату j
						k++;
					}
				}
			}
		}
	}


	for (int i = 0; i < 196; i++) {
		testFile << coordinates[i].i << " " << coordinates[i].j << endl;
	}
	testFile.close();
}

void deleteArrays()
{
	delete[] intermediateDataArray;
	delete[] exitDataArray;
	delete[] inDataArray;
}
