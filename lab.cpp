#ifndef p_hpp
#define p_hpp

void filtr(char* str);
ostream& operator << (ostream& out, const Cities& Cities);
istream& operator >> (istream& in, Cities& Cities);
void createFile(char* file);
void createBin(char* data, char* binfile);
void RemoveLine(char* filedel, char* binfile);
void correction(char* binfile);
void rbinf(char* binfile);
void sortedBinary(char* binfile);
void sorted(Cities* cities, int n);
void outputMenu();
void printHeaderTable();
void printFooterTabele();
void printLineTable(Cities city);
void CheckEdit(char* binfile);
void Create();
void Read();
void Sorted();
void Remove();
void Exit() { exit(1); }
int inputNumber();
void(*Processing[5])() = { Create,  Read, Sorted, Remove, Exit };
#endif