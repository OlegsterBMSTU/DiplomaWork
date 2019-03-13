#include "pch.h"

#include <ctime>
#include <iostream>
#include <fstream>
#include <sstream>
#include <cstdio>
#include <string>

#include"common.h"

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

//3 массива: входной, средний и выходной
//Заполняем все массивы

float ** outputArray;
float ** inputArray;
float ** middleArray;
float * weightsArray;   //Массив на 25 весов
int myFileSize=0;
int i=0,j=0;
int number;


struct coordinates {
    int i=0,j=0;
} coordinate;

string nameFile;
string pointer; //Указатель на элемент в файле

void createArrays()
{
    // создаим outputArray
    nameFile = "matrixWork6.txt";
    string pointer; //Указатель на элемент в файле
    myFileSize = sqrt(sizeFile(nameFile)));
    outputArray = new float * [myFileSize];
    for (int i=0; i < myFileSize; i++) outputArray[i] = new float [myFileSize]; //Создали двумерный массив
    ifstream outputFile(nameFile);
    i=0;j=0;
    while (getline(outputFile,pointer)) {
        outputArray[i][j++] = fromString<float>(pointer);
        if (j==myFileSize) {
            j=0;
            i++;
        }
    }

    // Создаем middleArray
    nameFile = "exit_convolusion_0 1.txt";
    myFileSize = sqrt(sizeFile(nameFile)));
    middleArray = new float * [myFileSize];
    for (int i=0; i < myFileSize; i++) middleArray[i] = new float [myFileSize]; //Создали двумерный массив
    ifstream middleFile(nameFile);
    i=0;j=0;
    while (getline(middleFile,pointer)) {
        middleArray[i][j++] = fromString<float>(pointer);
        if (j==myFileSize) {
            j=0;
            i++;
        }
    }
    // Создаем inArray
    nameFile = "matrixWork0.txt";
    myFileSize = sqrt(sizeFile(nameFile)));
    inputArray = new float * [myFileSize];
    for (int i=0; i < myFileSize; i++) inputArray[i] = new float [myFileSize]; //Создали двумерный массив
    ifstream inputFile(nameFile);
    i=0;j=0;
    while (getline(inputFile,pointer)) {
        inputArray[i][j++] = fromString<float>(pointer);
        if (j==myFileSize) {
            j=0;
            i++;
        }
    }
    inputFile.close();
    middleFile.close();
    outputFile.close();
}

//Поиск координаты.
//Рандомом берем из outputArray ячейку и владея информацией о ней находим ее положение в middleArray а за тем в inputArray;

void findCoordinate()   //Ищем стартовые координаты в большом массиве inputArray
{
    number = rand()%196;
    //В output[number/sizeFile(outputArray)][number%sizeFile(outputArrat)]
    //В inputArray[number/sizeFile(inputArray)][number%sizeFile(inputArray)]
    nameFile = "matrixWork6.txt";
    int coord_i=number/sizeFile(nameFile);
    int coord_j=number%sizeFile(nameFile);
    for (int i =coord_i*4; i < coord_i*4 + 4; i++) {
        for (int j =coord_j*4; j < coord_j*4 + 4; j++) {
            if (outputArray[coord_i][coord_j] == middleArray[i][j]) {
                //Нашли стартовые координаты в inputArray
                coordinate.i = i;
                coordinate.j = j;
            }
        }
    }
}

float takeSigma(int counter) //Вытаскиваем сигму с номером = number;
{
    ifstream sigmaFile("file_sigma.txt");
    int i=0;
    while (getline(sigmaFile,pointer) && (i!=number)) {
        i++;    //Итератор пока не попадем на нужный элемент, потом будет i == number * counter+1
        if (i == number* counter) return fromString<float>(pointer);
    }
    sigmaFile.close();
}

//Запоняем массив весов 5х5
void fillingArrayOfWeoghts();
{
    float sigma = takeSigma(0);  //Достали нужную сигму
    //Считаем файл весов
    //Не забыть убрать, ибо потом будет в функцию подаваться
    string nameFile = "weight_conv_1.txt";  //для 0,1 = 1, 2,3 = 2, 4,5 = 3
    myFileSize = sizeFile(nameFile);
    ifstream weightsFile(nameFile);
    weightsArray = new float[myFileSize];
    int i=0;
    while(getline(weigtsFile,pointer)) weightsArray[i++] = fromString<float>(pointer);
    weightsFile.close();
}

void deleteArrays()
{
    delete[]weightsArray;
    delete[]newWeightsArray;
    delete[]inputArray;
    delete[]middleArray;
    delete[]outputArray;
}
float * newWeightsArray = new float[myFileSize];    //Массив для новых весов
int number=0;
void coorectWeights()
{
    for (int i = coordinate.i; i<coordinate.i+4;i++) {
        for (int j=coordinate.j;j<coordinate.j+4;j++) { 
            newWeightsArray[number] = weightsArray[number] + 1 * sigma * inputArray[i][j];
        }
    }
    //Записываем всю это в файл
    number =0;
    string nameFile = string nameFile = "weight_conv_1.txt";  //для 0,1 = 1, 2,3 = 2, 4,5 = 3
    ofstream weightsFile(nameFile, ios::trunc);
    while (number < myFileSize) weightsArray << newWeightsArray[number++]<<endl;
    deleteArrays(); //Удаляем все динамические массивы
}



