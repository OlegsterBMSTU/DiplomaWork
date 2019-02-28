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
float current = 0;
int aj = 0, ai = 0, countBitch = 0;
bool key0 = false, key1 = false, key2 = 0;


string from_s1;

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

void maxFromArray(int i, int j);
void writeMaxInFile(float max);

void subSampling(int index1, int index2, int selector)
{
	string line;	//указатель, который считвает
	//Выбираем exit_covolution из множества
	//[ 0_0 ... 5_1]
	string from_s("exit_convolusion_");
	from_s += (toString(index1)) + ' ' + (toString(index2)) + ".txt";

	string file = from_s;	//Название файла с которым работает

	myFileSize = sqrt(sizeFile(file));
	matrixWork = new float *[myFileSize];	//матрица для формирования выходных данных
	for (int i = 0; i < myFileSize; i++) matrixWork[i] = new float[myFileSize];
	int k = 0, i = 0;
	//while (i < (myFileSize)) matrixWork[i++] = 0; //Обнуляем всю матрицу
	for (int i = 0; i < myFileSize; i++) {
		for (int j = 0; j < myFileSize; j++) {
			matrixWork[i][j] = 0;
		}
	}

	i = 0; k = 0;

	ifstream f1(file);

	// Название выходного файла с данными
	// с учетом его индекса [0..11] или [1..12]
	from_s1= "matrixWork";
	from_s1 += (toString(selector)) + ".txt";
	ofstream f2(from_s1);
	
	

	// Цикл выбора максимальных (ReLu) элементов // 
	/*	while (getline(f1, line)) {
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
	}*/
	// Заполняем матрицу matrixWork
	i = 0; int j = 0;
	while (getline(f1, line)) {
		matrixWork[i][j] = fromString<float>(line);
		//f2 << matrixWork[i][j] << endl;
		j++;
		if (j == myFileSize) {
			j = 0; i++;
		}
	}
	f1.close(); 
	int length = sqrt(sizeFile(from_s));
	int steps = ((sizeFile(from_s)) / 16);	//потому то входной файл из 3136 / 16 есть результат последнего файла
	int ai = 0, aj = 0;
	k = 0;
	i = 0; j = 0;
	float * max = new float[length];
	bool key = true;
	while ((k < steps) && (j!=length))
	{
		if (key) {
			max[k] = matrixWork[i][j];
			key = false;
		}
		(matrixWork[i][j] > max[k]) ? max[k] = matrixWork[i][j] : 0;
		
		if ((j + 1) % 4 == 0) {	//когда достигли 4 ой ячейки по горизонтали в карте 4х4
			j = aj;	//сбросить j
			key0 = true;
		}
		if (((j + 1) % 4 == 0) && ((i + 1) % 4 == 0)) {  //когда карту 4х4 прохавали до конца, т.е. i=4,j=4
			i = ai;
			j++;
			aj += 4;
			k++;			// подняли итератор
			key = true;		//для разрешения забись для сравнения в новом наборе данных
		}
		if ((j == length) && ((i+1)%4) ==0 ) { //когда достигли последней карты 4х4 в строке матрицы
			i++;		//передвинули i на следующую строку
			j = 0;		// поставили индекс j в начало
			ai += 4;
		}
		if (!key0) j++;
		if (key0) {
			i++;
			key0 = 0;
		}
	}

	for (int i = 0; i < steps; i++) {
		f2 << toString(max[i]) << endl;
	}

	//delete[] matrixWork;
}


/*
//Новаz функуия для двумерного массива, проходим картой по массиву
void maxFromArray(int i, int j) {
	current = matrixWork[i][j];
	if ((max > current) || (key)) max = current;
	if ((j == myFileSize) && (i == myFileSize - ai)) {
		keyForI = true;  // поднимаем ключ для перехода на новые i
	}
	key = false;
	if ((j == aj + 4)) {
		j = 0;		//Если в квадрате 4х4 закончили строчку то j сбросить в 0
		i++;		//надо оставить чтобы в основную функцию вернул значение
		countBitch++;	//повысить счечик для контроля прохода по окну
	}
	if ((countBitch == 4) && (j == aj + 4)) { // если прошли карту 4х4 до конца
		countBitch = 0;		//сбрасываем счетчик
		aj = aj + 4;		//повышаем указатель для j на 4 для прохода по следующей карте
		keyForMax = true;
	}
	if (keyForMax) {
		writeMaxInFile(max);
		keyForMax = 0;
	}
	if ((i == ai + 4) && (j == aj + 4)) {  //если закончили по i и по j, то есть прошли строку шириной в 4i до кноца
		ai += 4;		//увеличиваем ai на 4 для работы со следующим набором i
		j = 0;		//на всякий пожарный. В теории когда (i == 3 ) && (j == 14) для первой строки j сбросится в 0 по условиям основного цикла
	}

	if (i == ai + 4) i = ai;	//если закончили по i, но не закончили по j то i сбрасываем, точнее присваиваем +4
	if ((i == ai + 4) && (j == myFileSize)) i += 4;	//если достигли конца матрицы по горизонтали (i=4, j=sizeArray) то переходим на следующую строчку для поиска
	//продумать переход ai и aj
}

*/
//вернуть 2 значения

void writeMaxInFile(float max) {
	ofstream f2(from_s1, ios::app);
	f2 << max << endl;
	f2.close();
}
