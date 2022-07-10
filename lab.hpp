#ifndef lab_hpp
#define lab_hpp

#include <iostream>
#include <fstream>
#include <string>
#include <iomanip>
#include <vector>
#include <io.h>
#include <conio.h>

using namespace std;

ofstream fout;
ifstream fin;
fstream binf;

const int Count = 5;
char filename[10] = "test.txt";
char binfile[15] = "binfile.txt";
char delfile[11] = "def.txt";

struct Cities {
    char name[10];
    int people;
    char country[10];
    int created;
    int area;
}ct;

void sorted(Cities* cities, int n);

void filtr(char* str) {
    int x;
    int xl = 0,
        xr = strlen(str) - 1; 
    while (str[xl] == ' ') xl++;
    while (str[xr] == ' ') xr--;
    for (x = xl; x <= xr; x++)
        str[x - xl] = str[x];
    str[x - xl] = '\0';
}

ostream& operator << (ostream& out, const Cities& Cities) {
    out << left
        << setw(10) << Cities.name
        << setw(10) << Cities.people
        << setw(10) << Cities.country
        << setw(10) << Cities.created
        << setw(10) << Cities.area;
    return out;
}

istream& operator >> (istream& in, Cities& Cities) {
    char T[255];
    in.get(Cities.name, 10);
    in >> Cities.people;
    in.get(Cities.country, 10);
    in >> Cities.created >> Cities.area;
    filtr(Cities.name);
    filtr(Cities.country);
    in.getline(T, 255);
    return in;
}

void createFile(char* file) {
    fout.open(file);
m: cout << "Введите все поля данные для одной структуры:\n";  
    cin >> ct;
    fout << ct;
    cout << "Для завершения нажмите '0'\nЕсли хотите продолжить, то введите любой другой симвойл:\n";
    char c;
    c = _getch();
    if (c == '0'){
        fout.close();
        return;
    }
    else {
        fout << endl;
        goto m;
    }
}

void createBin(char* data, char* binfile){

    ifstream file(data);
    if (!file.is_open()){
        cout << "Такого файла нет!\n";
        system("pause");
        exit(0);
    }
    fout.open(binfile, ios::binary);
    while (!file.eof()){
        file >> ct;
        fout.write((char*)&ct, sizeof(Cities));
    }
    fout.close();
    file.close();
}

void RemoveLine(char* filedel, char* binfile) {
    int z = sizeof(Cities);
    int ch = 0;
    cout << "Удаление из бинарного файла" << endl;
    fin.open(filedel);
    if (!fin) {
        cout << "Error(def.txt)";
        exit(0);
    }
    binf.open(binfile, ios::in | ios::out | ios::binary);
    if (!binf) {
        cout << "Error(binf)";
        exit(0);
    }
    long size_f = 0;
    while (binf.peek() != EOF) {
        binf.write((char*)&ct, z);
        size_f += z;
    }
    string data;
    vector<string> cache;
    while (!fin.eof()) {
        getline(fin, data);
        if (data.empty())  cout << "\nБыла найдена пустая строка\n";
        else cache.push_back(data);
    }
    for (auto it = cache.begin(); it != cache.end(); it++) {
        binf.clear();
        binf.seekg(0, ios::beg);
        while (binf.peek() != EOF) {
            binf.read((char*)&ct, z);
            if (ct.area == stoi(*it)) { 
                ch++;
                while (binf.peek() != EOF) {
                    binf.read((char*)&ct, z);
                    binf.seekp(-2 * z, ios::cur); //смещаем указатель файла на одну структуру назад
                    binf.write((char*)&ct, z); //запись в файл откорректированной структуры
                    binf.seekp(+z, ios::cur);
                };
                int handle = _open(binfile, ios::in | ios::binary);
                size_f -= z;
                _chsize(handle, size_f);
                _close(handle);
            }
        }
        if (ch == 0) {
            cout << "\nне была удалена структура с параметром: " << *it << "\n";
        }
        else {
            ch = 0;
            cout << "\nбыла удалена структура с параметром: " << *it << "\n";
        }
    }
    cout << "\n";
    fin.close();
    binf.close();

};

void correction(char* binfile) {
    binf.open(binfile, ios::binary | ios::in);
    fout.open("corr.txt");
    while (binf.read((char*)&ct, sizeof(Cities))) {
        fout << ct << "\n";
    }
    fout.close();
    binf.close();
}

void rbinf(char* binfile) {
    cout << "\n\nЧтение файла по ПЗ #1:\n";
    binf.open(binfile, ios::binary | ios::in);
    while (binf.read((char*)&ct, sizeof(Cities))) {
        cout << ct << "\n";
    }
    binf.close();
}

void sortedBinary(char* binfile) {
    binf.open(binfile, ios::in | ios::out | ios::binary);
    if (!binf) {
        cout << "Error(binf)";
        exit(0);
    }
    int size = 0;
    Cities* cities = new Cities[Count]();
    while (binf.read((char*)&ct, sizeof(Cities))) cities[size++] = ct;
    binf.close();
    sorted(cities, size);
    binf.open(binfile);
    if (!binf) {
        cout << "Error(binf)";
        exit(0);
    }
    for (int i = 0; i < size; i++)
        binf.write((char*)&cities[i], sizeof(Cities));
    delete[] cities;
    binf.close();
}

void sorted(Cities* cities, int n) {
    int i, j, step;
    Cities tmp;
    int stmp;
    for (step = n / 2; step > 0; step /= 2)
        for (i = step; i < n; i++){
            tmp = cities[i];
            stmp = cities[i].area;
            for (j = i; j >= step; j -= step){
                if (stmp < cities[j - step].area)
                    cities[j] = cities[j - step];
                else
                    break;
            }
            cities[j] = tmp;
        }
}

void outputMenu() {
    cout << "\n                    МЕНЮ: \n"
        << "\nСоздание файла------------------------------ 1"
        << "\nЧтение файла-------------------------------- 2"
        << "\nСортировка файла---------------------------- 3"
        << "\nУдаление данных из файла-------------------- 4"
        << "\nВыход--------------------------------------- 5";
    cout << "\n\nДля выполнения операции введите нажмите нужную клавишу: ";
}

void printHeaderTable() {
    string header[5] = { "                             Города ",
        "|================|================|===========|============|================|",
        "|      Название  | Численность    |Страна     | Год        |  Площадь       |",
        "|                |  населения     |           | создания   |  кв.км         |",
        "|================|================|===========|============|================|",
    };
    for (int i = 0; i < 5; i++) cout << header[i] << "\n";
}

void printFooterTabele() {
    cout << "|================|================|===========|============|================|" << endl;
}

void printLineTable(Cities city) {
    cout << left <<
        "|" << setw(16) << city.name <<
        "|" << setw(16) << city.people <<
        "|" << setw(11) << city.country <<
        "|" << setw(12) << city.created <<
        "|" << setw(16) << city.area <<
        "|" << endl;
}

void CheckEdit(char* binfile) {
    printHeaderTable();
    binf.open(binfile, ios::binary | ios::in);
    while (binf.read((char*)&ct, sizeof(Cities))) {
        printLineTable(ct);
    }
    binf.close();
    printFooterTabele();
}

void Create() {
    system("cls");
    //createFile(filename);
    createBin(filename, binfile);
}

void Read() {
    system("cls");
    CheckEdit(binfile);
}

void Sorted() {
    system("cls");
    sortedBinary(binfile);
    correction(binfile);
    CheckEdit(binfile);
}

void Remove() {
    system("cls");
    RemoveLine(delfile, binfile);
    correction(binfile);
    CheckEdit(binfile);
}

void Exit() { exit(1); }

int inputNumber() {
    int a;
    (cin >> a).get();
    return a;
}

void(*Processing[5])() = { Create,  Read, Sorted, Remove, Exit };

#endif
