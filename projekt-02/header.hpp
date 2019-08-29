#ifndef header	
#define header
#include <iostream>
#include <string>

struct Wezel { //w©zeˆ listy podwieszanej
	Wezel() : size(0), up(nullptr), next(nullptr), prev(nullptr), data(nullptr) {} //domy˜le warto˜ci element¢w struktury
	std::string name; //nazwa pliku/folderu
	int size; //ilo˜† plik¢w/folder¢w w folderze, b¥d« -1 w przypadku pliku
	Wezel* up; //wska«nik na katalog macierzysty
	Wezel* data; //lista przechowuj¥ca zawarto˜† katalogu
	Wezel* next; //nast©pny element listy
	Wezel* prev; //poprzedni element listy
};
// front-end
bool checkName(const std::string &name); //sprawdza czy wprowadzona nazwa pliku/foleru jest poprawna
bool readBool(std::string text, bool def = 0); //Sczytuje wartosc logiczna od uzytkownika; przed czytaniem wypisuje text, w razie blednej wartosci zwraca def
void tree(Wezel* dir, int l = 0); //Wy˜wietla drzewo katalog¢w, pocz¥wszy od katalogu dir
void ls(Wezel* dir); //wypisuje zawarto˜† katalogu dir
void exportT(std::ofstream &file, Wezel* dir); //zapisuje drzewo katalog¢w pocz¥wszy od katalogu dir do pliku binarnego file
bool toFile(Wezel* dir, std::string path, bool all = 0); //zapisuje drzewo katalog¢w pocz¥wszy od bie¾¥cego katalogu do pliku binarnego o nazwie name, all = 1 zapisuje caˆe drzewo
bool fromFile(Wezel* current, std::string path, bool replace); //odtwarza struktur© katalog¢w z pliku path do katalogu current, replace = 1 zast©puje obecn¥ struktur© katalog¢w
	
// back-end
bool czyJest(Wezel* glowa, std::string name); //sprawdza czy w li˜cie istnieje element o nazwie name. Je¾eli tak, zwraca 1, je˜li nie zwraca 0
Wezel* findFile(Wezel* dir, std::string name); //zwraca wska«nik na element o nazwie name znajduj¥cy si© w folderze dir
bool mkdir(Wezel* dir, std::string name); //tworzy katalog o nazwie name w katalogu dir, wstawia element w odpowiednie miejsce, utrzymuj¥c list© posortowan¥
bool rmdir(Wezel* dir, bool s = 0, bool q = 0); //usuwa pusty katalog; -s usuwa wraz z plikami i podkatalogami; -q pomija potwierdzenie usuwania przy usuwaniu z podkatalogami
bool rm(Wezel* dir, bool s, bool q); //usuwa plik lub katalog; -s wraz z podkatalogami; -q pomija potwierdzenie usuwania przy usuwaniu z podkatalogami
bool touch(Wezel* dir, std::string name); //tworzy plik o nazwie name w katalogu dir, wstawia element w odpowiednie miejsce, utrzymuj¥c list© posortowan¥

//shell
void shell(Wezel* root); //gˆ¢wny interfejs programu; root - katalog domowy
void help(); //wy˜wietla plik pomocy
void interpr(Wezel* &current, std::string cmd, std::string arg1, std::string arg2, std::string arg3); //interpretuje wprowadzon¥ komend© i uruchamia odpowiedni program, lub informuje o bˆ©dzie
void cd(Wezel* &dir, std::string cel); //przechodzi z folderu dir do folderu cel
std::string getPath(Wezel* dir); //zwraca ˜cie¾k© bezwzgl©dn¥ folderu dir

//diagnostic
void dinfo(Wezel* file); //pokazuje techniczne informacje o pliku
#endif