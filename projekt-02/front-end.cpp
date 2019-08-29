#include <limits>
#include <fstream>
#include <conio.h>
#include "header.hpp"

using namespace std;

bool readBool(string text, bool def) { //Sczytuje wartosc logiczna od uzytkownika; przed czytaniem wypisuje text, w razie blednej wartosci zwraca def
	cout << text << endl;
	unsigned char ch = _getch();
	if (ch == 121 || ch == 89 || ch == 116 || ch == 84 || ch == 49) // y Y t T 1
		return 1;
	if (ch == 110 || ch == 78 || ch == 48) // n N 0
		return 0;
	cout << "Warto˜† nierozpoznana. Ustawiono warto˜† domy˜ln¥." << endl;
	return def;
}

bool checkName(const string &name) { //sprawdza czy wprowadzona nazwa pliku/foleru jest poprawna
									 //niedozwolone znaki: \\ : * ? \" < > |
	if (name.find("\\") != string::npos || name.find(":") != string::npos || name.find("*") != string::npos || name.find("?") != string::npos || name.find("\"") != string::npos || name.find("<") != string::npos || name.find(">") != string::npos || name.find("|") != string::npos)
		return 0;
	return 1;
}

void tree(Wezel* dir, int l) { //Wy˜wietla drzewo katalog¢w, pocz¥wszy od katalogu dir
	cout << dir->name << endl;
	Wezel* copy = dir->data;
	while (copy != nullptr) {
		if (copy->size == -1) {
			copy = copy->next;
			continue;
		}
		for (int i = 0; i < l; i++) {
			cout << "|  ";
		}
		cout << "|--";
		tree(copy, l + 1);
		copy = copy->next;
	}
}

void ls(Wezel* dir) { //wypisuje zawarto˜† katalogu dir
	Wezel* copy = dir->data;
	cout << endl << " Katalog: " << getPath(dir) << endl;
	if (copy != nullptr) //unikni©cie nadmiarowego entera przy listowaniu pustych katalog¢w
		cout << endl;
	while (copy != nullptr) {
		if (copy->size == -1)
			cout << "\t" << copy->name << endl;
		else
			cout << "  <" << copy->size << ">\t" << copy->name << endl;
		copy = copy->next;
	}
	cout << endl;
}

void exportT(ofstream &file, Wezel* dir) {
	file.write("/", 1); // / - folder
	file.write(dir->name.c_str(), dir->name.size() + 1);
	if (dir->data == nullptr)
		return;
	file.write(">", 1); // > - zejd« w d¢ˆ drzewa
	Wezel* copy = dir->data;
	while (copy != nullptr) {
		if (copy->size == -1) {
			file.write("|", 1); // | - plik
			file.write(copy->name.c_str(), copy->name.size() + 1);
		}
		else {
			exportT(file, copy);
		}
		copy = copy->next;
	}
	file.write("<", 1); // < - wr¢† w g¢r© drzewa
}

bool toFile(Wezel* dir, string path, bool all) { //zapisuje drzewo katalog¢w pocz¥wszy od bie¾¥cego katalogu do pliku binarnego o nazwie name, -a zapisuje caˆe drzewo
	if (all) //je¾eli -a zaczyna od katalogu gˆ¢wnego
		while (dir->up != nullptr)
			dir = dir->up;
	ofstream file;
	file.open(path, ios::binary | ios::trunc);
	if (!file.is_open()) {
		cout << "Nie mo¾na utworzy† pliku \"" << path << "\"." << endl;
		return 1;
	}
	exportT(file, dir);
	file.close();
	return 0;
}

bool fromFile(Wezel* current, string path, bool replace) {
	ifstream file;
	file.open(path, ios::binary);
	if (!file.is_open()) {
		cout << "Nie mo¾na otworzy† pliku \"" << path << "\"." << endl;
		return 1;
	}
	if (replace) {//je¾eli -r zast©puje obecn¥ struktur©
		while (current->up != nullptr)
			current = current->up;
		rm(current->data, 1, 1);
	}
	string curname;
	getline(file, curname, '>');
	if (curname[0] != '/' || curname[curname.size()-1] != '\0') { //Weryfikacja poprawno˜ci pliku
		cout << "Nieprawidˆowy plik wej˜ciowy" << endl;
		return 1;
	}
	char ch;
	while (!file.eof()) {
		file.read(&ch, sizeof(char));
		if (ch == '/') {
			string name;
			getline(file, name, '\0');
			mkdir(current, name);
			continue;
		}
		if (ch == '|') {
			string name;
			getline(file, name, '\0');
			touch(current, name);
			continue;
		}
		if (ch == '>') {
			current = current->data;
			while (current->next != nullptr)
				current = current->next;
			continue;
		}
		if (ch == '<') {
			if (current->up == nullptr)
				break;
			current = current->up;
			continue;
		}
	}
	return 0;
}

void dinfo(Wezel* file) { //pokazuje techniczne informacje o pliku file
	cout << "name = " << file->name << endl;
	cout << "size = " << file->size << endl;
	cout << "up   = " << file->up << endl;
	cout << "data = " << file->data << endl;
	cout << "next = " << file->next << endl;
	cout << "prev = " << file->prev << endl;
}
