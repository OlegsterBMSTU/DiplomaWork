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
	from_s1 = "matrixWork";
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
	while (getline(f1, line)) {		//начинаем заполнять массив данными из файла
		matrixWork[i][j] = fromString<float>(line);//заполням данными из файла
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
	key0 = false;
	key1 = false;
	key2 = false;
	int numberstring = 0, numbercolumn = 0;
	while (k < steps)		//пока не набрали достаточное количество карт
	{
		if (key) {			//если запись разрешена. Для каждой новой первой карты 4х4 первый элемент записываем как максимальный
			max[k] = matrixWork[i][j];	//Для каждой новой первой карты 4х4 первый элемент записываем как максимальный
			key = false;	//и сразу же блокируем ключ. Поднимаем когда всю карту 4х4 просмотрели. 
		}
		(matrixWork[i][j] > max[k]) ? max[k] = matrixWork[i][j] : 0;	//стандартное условие сравнения
		
		if ((j + 1) % 4 == 0) {	//Если дошли до конца строки в карте 4х4
			j = aj;					//обнулить j
			numberstring++;			//посчитали номер строки в карте 4х4
//			numbercolumn = 0;
			key0 = true;			//чтобы не проскочить элемент при проходе
			i++;
		}

		if ((numberstring == 4) && (numbercolumn+1 == 4)) {	//если находимся в ячейке 4-4, то есть прошли карту 4х4 до конца
			numberstring = 0;		//сбрасываем счетчик строк
			numbercolumn = 0;		// сбрасываем счетчик столбцов
			k++;					//начали исследовать следующую карту
			aj += 4;				//повысили индекс aj для дальнейшей работы
			key = true;				//разрешили запись первого элемента для сравнения в массив максимальных
			i = ai;					//сместили i на первую строчку карты 4х4
			j = aj;					//сместили j на первый элемент первой строчки карты 4х4
			key1 = true;			//реагирует на iсброс
		}

		//Когда достигли последнего элемента в проходе по "первой строке" шириной 4i массива.
		// То есть для первой строчки это будет array[3][array.length]
		if ((j == length)) {	// && ((i+1)%4==0)) {	
			ai += 4;				//повысили индекс ai для дальнейшей работы
			i = ai;					//Передвигаем i на следующую строку (вместо 0 стала 4)
			aj = 0;					//установили индекс aj в 0, так как строка начинается 
			j = aj;
			key1 = true;
		}
//		(!key0) ? j++ : 0;
//		key0 ? key0 = false, numbercolumn = 0, numberstring++ : j++, numbercolumn++;
		if (key0) {
			key0 = false;
			numbercolumn = 0;
		}
		else {
			j++;
			numbercolumn++;
		}
		//key1 ? i++, key1 = false : 0;
		//numbercolumn++;
	}

	for (int i = 0; i < steps; i++) {
		f2 << toString(max[i]) << endl;
	}

	//delete[] matrixWork;
	delete[] matrixWork;
}




void writeMaxInFile(float max) {
	ofstream f2(from_s1, ios::app);
	f2 << max << endl;
	f2.close();
}

void trunkInMaxFile() {
	int i = 22;
	ofstream f2(from_s1, ios::trunc);
	cout << "\n!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!" << endl;
	cout << "It was called trunkInMaxFile function" << endl;
	cout << "File " << from_s1 << " was cleared" << endl;
	cout << "!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!" << endl;
	f2.close();
}
