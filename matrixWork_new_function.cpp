#include "pch.h"

#include <ctime>
#include <iostream>
#include <fstream>
#include <sstream>
#include <cstdio>
#include <string>
#include"common.h"

using namespace std;
float ** matrixWork;
int myFileSize;
float max = 0, current = 0;
int aj=0,ai=0,counter=0;
bool key = true;
bool keyForI = false;

template<typename T>
T fromString(const std::string& s)
{
	std::istringstream iss(s);
	T res;
	iss >> res;
	return res;
}
template <typename T> // шаблон преобразование в string
std::string toString(T val)
{
	std::ostringstream oss;
	oss << val;
	return oss.str();
}

void subSampling(int index1, int index2, int selector)
{
	string line;	//указатель, который считвает
	//Выбираем exit_covolution из множества
	//[ 0_0 ... 5_1]
	string from_s("exit_convolusion_");
	from_s += (toString(index1)) + ' ' + (toString(index2)) + ".txt";

	string file = from_s;	//Название файла с которым работает

	myFileSize = sqrt(sizeFile(file));
	matrixWork= new float * [myFileSize];	//матрица для формирования выходных данных
		for (int i=0;i<myFileSize;i++) matrixWork[i] = new float [myFileSize];
	int k = 0, i = 0;
	//while (i < (myFileSize)) matrixWork[i++] = 0; //Обнуляем всю матрицу
	for (int i=0;i<myFileSize;i++) {
		for (int j=0;j < myFileSize;j++) {
			matrixWork[i][j] = 0;
		}
	}
	
	i = 0; k = 0;
	
	ifstream f1(file);

	// Название выходного файла с данными
	// с учетом его индекса [0..11] или [1..12]
	string from_s1("matrixWork");
	from_s1 += (toString(selector)) + ".txt";

	ofstream f2(from_s1);

	// Цикл выбора максимальных (ReLu) элементов // 
	while (getline(f1, line)) {
		current = fromString <float>(line);
		if ((max > current) || (key)) max = current;	//Выбор максимального
		key = false;
		i++;
		if (i == 16) {  //Потому что ячейки размером 4х4
			matrixWork[k] = max;		//запись максимального в ячейку
			k++;
			f2 << max << endl;			// запись максимального в файл
			key = true;
			i = 0;
		}
	}
	f1.close(); f2.close();
	delete[] matrixWork;
	
	for (int i =0; i< myFileSize; i++) {
		for (int j=0; j<myFileSize; j++) {
			maxFromArray(i,j);
		}
	}
	
}


//Новаz функуия для двумерного массива, проходим картой по массиву
void maxFromArray(int i; int j) {
	current = matrixWork[i][j];
	if ((max > current) || (key)) max = current;
	if ((j==myFileSize)&& (i == myFileSize-ai)) keyForI = true;  // поднимаем ключ для перехода на новые i
	key=false;
	if ((j == aj+4)) {
		j=0;		//Если в квадрате 4х4 закончили строчку то j сбросить в 0
		//i++;
		//counter++;	//повысить счечик
	}
	if (i==ai+4) i=0;	//если закончили по i, но не закончили по j то i сбрасываем
	if ((i == ai+4) && (j == myFileSize)) i+=4;	//если достигли конца матрицы по горизонтали (i=4, j=sizeArray) то переходим на следующую строчку для поиска
}

