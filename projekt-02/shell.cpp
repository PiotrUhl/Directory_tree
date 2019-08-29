#include <sstream>
#include <stack>
#include "header.hpp"

using namespace std;

string getPath(Wezel* dir) { //zwraca ˜cie¾k© bezwzgl©dn¥ folderu dir
	stack <string> stos;
	while (dir->up != nullptr) {
		stos.push(dir->name);
		dir = dir->up;
	}
	stringstream sstream;
	while (!stos.empty()) {
		sstream << "/" << stos.top();
		stos.pop();
	}
	string ret;
	sstream >> ret;
	if (ret == "")
		return "/";
	return ret;
}

void cd(Wezel* &dir, std::string cel) {
	if (cel == "") {
		cout << "Nieprawidˆowa skˆadnia polecenia. Zobacz \"help\"" << endl;
		return;
	}
	if (cel == "..") {
		if (dir->up == nullptr) {
			cout << "Nie mo¾na przej˜† wy¾ej z katalogu gˆ¢wnego" << endl;
			return;
		}
		dir = dir->up;
		return;
	}
	Wezel* copy = dir->data;
	while (copy != nullptr) {
		if (copy->name == cel) {
			if (copy->size == -1) {
				cout << cel << " nie jest katalogiem" << endl;
				return;
			}
			dir = copy;
			return;
		}
		copy = copy->next;
	}
	cout << "Nie znaleziono folderu o podanej nazwie." << endl;
}

void help() {
	cout << "Drzewo katalog¢w - drugi projekt na zaj©cia z Podstaw Programowania Komputer¢w" << endl << "Autor: Piotr Uhl" << endl << endl;
	cout << "Dost©pne polecenia: " << endl << endl;
	cout << "help - wy˜wietla ten plik pomocy" << endl;
	cout << "exit - usuwa struktur© z pami©ci i koäczy prac© programu" << endl;
	cout << "ls - wy˜wietla zawarto˜† obecnego folderu" << endl;
	cout << "cd <folder> - przechodzi do podanego folderu" << endl;
	cout << "tree - wy˜wietla drzewo katalog¢w pocz¥wszy od obecnie wybranego katalogu" << endl;
	cout << "mkdir <nazwa> - tworzy katalog" << endl;
	cout << "touch <nazwa> - tworzy plik" << endl;
	cout << "rmdir <nazwa> {-s} {-q} - usuwa pusty katalog\n\t-s - usuwa r¢wnie¾ katalogi niepuste\n\t-q - nie pyta o potwierdzenie w przypadku usuwania katalogu niepustego" << endl;
	cout << "rm <nazwa> {-s} {-q} - usuwa plik\n\t-s - usuwa r¢wnie¾ katalogi\n\t-q - nie pyta o potwierdzenie w przypadku usuwania katalogu niepustego" << endl;
	cout << "export <nazwa> {-a} - ekportuje struktur© katalog¢w i plik¢w do pliku o podanej nazwie, pocz¥wszy od obecnego folderu\n\t-a - eksportuje caˆ¥ struktur©, pocz¥wszy od folderu gˆ¢wnego" << endl;
	cout << "import <nazwa> {-r} - importuje struktur© katalog¢w i plik¢w z pliku o podanej nazwie oraz wstawia j¥ do obecnie wybranego folderu\n\t-r - zast©puje obecn¥ struktur© katalog¢w struktur¥ zapisan¥ w pliku" << endl;
}

void interpr(Wezel* &current, string cmd, string arg1, string arg2, string arg3) { //interpretuje wprowadzon¥ komend© i uruchamia odpowiedni program, lub informuje o bˆ©dzie
//	cout << cmd << " " << arg1 << " " << arg2 << " " << arg3 << endl; //debug
	if (cmd == "help") {
		help();
		return;
	}
	if (cmd == "cd") {
		cd(current, arg1);
		return;
	}
	if (cmd == "ls") {
		ls(current);
		return;
	}
	if (cmd == "exit") {
		while (current->up != nullptr)
			current = current->up;
		rm(current->data, 1, 1);
		delete current;
		exit(0);
	}
	if (cmd == "mkdir") {
		if (arg1 == "") {
			cout << "Nieprawidˆowa skˆadnia polecenia! Zobacz \"help\"" << endl;
			return;
		}
		if (!checkName(arg1)) {
			cout << "Nazwa pliku nie mo¾e zawiera† ¾adnego z nast©puj¥cych znak¢w: \n\t/ \\ : * ? \" < > |" << endl;
			return;
		}
		if(!mkdir(current, arg1))
			cout << "Operacja zakoäczona powodzeniem" << endl;
		return;
	}
	if (cmd == "touch") {
		if (arg1 == "") {
			cout << "Nieprawidˆowa skˆadnia polecenia! Zobacz \"help\"" << endl;
			return;
		}
		if (!checkName(arg1)) {
			cout << "Nazwa pliku nie mo¾e zawiera† ¾adnego z nast©puj¥cych znak¢w: \n\t/ \\ : * ? \" < > |" << endl;
			return;
		}
		if (!touch(current, arg1))
			cout << "Operacja zakoäczona powodzeniem" << endl;
		return;
	}
	if (cmd == "rmdir") {
		if (arg1 == "") {
			cout << "Nieprawidˆowa skˆadnia polecenia! Zobacz \"help\"" << endl;
			return;
		}
		if (!czyJest(current->data, arg1)) {
			cout << "Nie znaleziono katalogu" << endl;
			return;
		}
		int s = 0;
		int q = 0;
		if (arg3 == "-s" || arg2 == "-s" || arg3 == "/s" || arg2 == "/s")
			s = 1;
		if (arg3 == "-q" || arg2 == "-q" || arg3 == "/q" || arg2 == "/q")
			q = 1;
		if (!rmdir(findFile(current, arg1), s, q))
			cout << "Operacja zakoäczona powodzeniem" << endl;
		return;
	}
	if (cmd == "rm") {
		if (arg1 == "") {
			cout << "Nieprawidˆowa skˆadnia polecenia! Zobacz \"help\"" << endl;
			return;
		}
		if (!czyJest(current->data, arg1)) {
			cout << "Nie znaleziono pliku" << endl;
			return;
		}
		int s = 0;
		int q = 0;
		if (arg3 == "-s" || arg2 == "-s" || arg3 == "/s" || arg2 == "/s")
			s = 1;
		if (arg3 == "-q" || arg2 == "-q" || arg3 == "/q" || arg2 == "/q")
			q = 1;
		if (!rm(findFile(current, arg1), s, q))
			cout << "Operacja zakoäczona powodzeniem" << endl;
		return;
	}
	if (cmd == "tree") {
		tree(current);
		return;
	}
	if (cmd == "export") {
		if (arg1 == "") {
			cout << "Nieprawidˆowa skˆadnia polecenia! Zobacz \"help\"" << endl;
			return;
		}
		if (arg2 == "-a" || arg2 == "/a") {
			if (!checkName(arg1)) {
				cout << "Nazwa pliku nie mo¾e zawiera† ¾adnego z nast©puj¥cych znak¢w: \n\t/ \\ : * ? \" < > |" << endl;
				return;
			}
			if (!toFile(current, arg1, 1)) {
				cout << "Operacja zakoäczona powodzeniem" << endl;
				return;
			}
		}
		if (arg1 == "-a" || arg1 == "/a") {
			if (!checkName(arg2)) {
				cout << "Nazwa pliku nie mo¾e zawiera† ¾adnego z nast©puj¥cych znak¢w: \n\t/ \\ : * ? \" < > |" << endl;
				return;
			}
			if (!toFile(current, arg2, 1)) {
				cout << "Operacja zakoäczona powodzeniem" << endl;
				return;
			}
		}
		if (!checkName(arg1)) {
			cout << "Nazwa pliku nie mo¾e zawiera† ¾adnego z nast©puj¥cych znak¢w: \n\t/ \\ : * ? \" < > |" << endl;
			return;
		}
		if (!toFile(current, arg1)) {
			cout << "Operacja zakoäczona powodzeniem" << endl;
			return;
		}
	}
	if (cmd == "import") {
		if (arg1 == "") {
			cout << "Nieprawidˆowa skˆadnia polecenia! Zobacz \"help\"" << endl;
			return;
		}
		if (arg2 == "-r" || arg2 == "/r") {
			if (!fromFile(current, arg1, 1)) {
				cout << "Operacja zakoäczona powodzeniem" << endl;
				return;
			}
		}
		if (arg1 == "-r" || arg1 == "/r") {
			if (!fromFile(current, arg2, 1)) {
				cout << "Operacja zakoäczona powodzeniem" << endl;
				return;
			}
		}
		if(!fromFile(current, arg1, 0))
		cout << "Operacja zakoäczona powodzeniem" << endl;
		return;
	}
	if (cmd == "dinfo") {
		dinfo(findFile(current, arg1));
		return;
	}
	cout << "Polecenie \"" << cmd << "\" nie zostaˆo odnalezione" << endl;
}

void shell(Wezel* root) { //gˆ¢wny interfejs programu; root - katalog domowy
	cout << "Drzewo katalog¢w - drugi projekt na zaj©cia z Podstaw Programowania Komputer¢w" << endl <<"Wersja: 1.0.2" << endl<< "Autor: Piotr Uhl" << endl;
	cout << endl << "Wpisz \"help\" by zobaczy† dost©pne polecenia" << endl << endl;
	Wezel* current = root;
	while (true) {
		cout << getPath(current) << "> ";
		//Pobieranie komendy
		string cmd = "";
		string arg1 = "";
		string arg2 = "";
		string arg3 = "";
		cin >> cmd;
		if (cin.get() == 32) {
			cin >> arg1;
			if (cin.get() == 32) {
				cin >> arg2;
				if (cin.get() == 32) {
					cin >> arg3;
					if (cin.get() == 32) {
						cin.ignore(numeric_limits<streamsize>::max(), '\n');
					}
				}
			}
		}
		//Interpretacja i wykonanie komendy
		interpr(current, cmd, arg1, arg2, arg3);
	}
}