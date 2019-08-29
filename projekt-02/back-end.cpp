#include "header.hpp"

using namespace std;

bool czyJest(Wezel* glowa, string name) { //sprawdza czy w li˜cie istnieje element o nazwie name. Je¾eli tak, zwraca 1, je˜li nie zwraca 0
	while (glowa != nullptr) {
		if (glowa->name == name) {
			return 1;
		}
		glowa = glowa->next;
	}
	return 0;
}

Wezel* findFile(Wezel* dir, string name) { //zwraca wska«nik na w©zeˆ o nazwie name, b¥d« nullptr w razie braku
	Wezel* copy = dir->data;
	while (copy != nullptr) {
		if (copy->name == name)
			return copy;
		copy = copy->next;
	}
	return nullptr;
}

bool mkdir(Wezel* dir, string name) { //tworzy katalog o nazwie name w katalogu dir, wstawia element w odpowiednie miejsce, utrzymuj¥c list© posortowan¥
	if (dir->data == nullptr) { //je¾eli dir jest pusty
		dir->data = new Wezel;
		dir->data->name = name;
		dir->data->up = dir;
		dir->size++;
		return 0;
	}
	if (czyJest(dir->data, name)) { //sprawdza czy name ju¾ istnieje w dir
		cout << "Plik badz katalog o podanej nazwie juz istnieje" << endl;
		return 1;
	}
	else {
		Wezel* copy = dir->data;
		while (copy->next != nullptr) {
			if (copy->name > name)
				break;
			copy = copy->next;
		}
		Wezel* nowy = new Wezel; //je¾eli dir nie jest pusty
		nowy->name = name;
		nowy->up = dir;
		if (copy->name < name) {
			nowy->prev = copy;
			copy->next = nowy;
			dir->size++;
			return 0;
		}
		nowy->next = copy;
		nowy->prev = copy->prev;
		if (copy->prev != nullptr) {
			copy->prev->next = nowy;
		}
		else {
			dir->data = nowy;
		}
		copy->prev = nowy;
		dir->size++;
		return 0;
	}
}

bool rmdir(Wezel* dir, bool s, bool q) { //usuwa pusty katalog; -s usuwa wraz z plikami i podkatalogami; -q pomija potwierdzenie usuwania
	if (dir == nullptr)
		return 0;
	if (dir->size > 0) { //je˜li niepusty
		if (!s) {
			cout << "Katalog nie jest pusty! By usuwa† niepuste katalogi u¾yj znacznika -s." << endl;
			return 1;
		}
		if (!q) {
			if (!readBool("Katalog nie jest pusty! Czy chcesz go usun¥† wraz ze wszystkimi jego plikami i podkatalogami? [y/N]")) {
				cout << "Operacja przerwana przez u¾ytkownika." << endl;
				return 1;
			}
		}
		while (dir->data != nullptr) {
			rm(dir->data, 1, 1);
		}
	}
	if (dir->size < 0) { //je˜li plik
		cout << "Wskazany obiekt nie jest katalogiem. By usuwa† pliki u¾yj polecenia rm." << endl;
		return 1;
	}
	//usuwanie
	if (dir->prev == nullptr) { //je˜li pierwszy element listy
		if (dir->up->size == 1) { //je¾eli jedyny element listy
			dir->up->data = nullptr;
			dir->up->size--;
			delete dir;
			return 0;
		}
		dir->up->data = dir->next;
		dir->next->up = dir->up;
		dir->next->prev = nullptr;
		dir->up->size--;
		delete dir;
		return 0;
	}
	dir->prev->next = dir->next;
	if (dir->next != nullptr) //je˜li nie ostatni
		dir->next->prev = dir->prev;
	dir->up->size--;
	delete dir;
	return 0;
}

bool rm(Wezel* dir, bool s, bool q) { //usuwa plik lub katalog; -s wraz z podkatalogami; -q pomija potwierdzenie usuwania przy usuwaniu z podkatalogami
	if (dir == nullptr)
		return 0;
	if (dir->size >= 0) { //je˜li niepusty
		if (!s) {
			cout << "Plik jest katalogiem! By usuwa† katalogi u¾yj znacznika -s." << endl;
			return 1;
		}
		if (!q && dir->size > 0) {
			if (!readBool("Katalog nie jest pusty! Czy chcesz go usun¥† wraz ze wszystkimi jego plikami i podkatalogami? [y/N]")) {
				cout << "Operacja przerwana przez u¾ytkownika." << endl;
				return 1;
			}
		}
		while (dir->data != nullptr) {
			rm(dir->data, 1, 1);
		}
	}
	//usuwanie
	if (dir->prev == nullptr) { //je˜li pierwszy element listy
		if (dir->up->size == 1) { //je¾eli jedyny element listy
			dir->up->data = nullptr;
			dir->up->size--;
			delete dir;
			return 0;
		}
		dir->up->data = dir->next;
		dir->next->up = dir->up;
		dir->next->prev = nullptr;
		dir->up->size--;
		delete dir;
		return 0;
	}
	dir->prev->next = dir->next;
	if (dir->next != nullptr) //je˜li nie ostatni
		dir->next->prev = dir->prev;
	dir->up->size--;
	delete dir;
	return 0;
}
bool touch(Wezel* dir, string name) { //tworzy plik o nazwie name w katalogu dir, wstawia element w odpowiednie miejsce, utrzymuj¥c list© posortowan¥
	if (dir->data == nullptr) { //je¾eli dir jest pusty
		dir->data = new Wezel;
		dir->data->size = -1;
		dir->data->name = name;
		dir->data->up = dir;
		dir->size++;
		return 0;
	}
	if (czyJest(dir->data, name)) { //sprawdza czy name ju¾ istnieje w dir
		cout << "Plik badz katalog o podanej nazwie juz istnieje" << endl;
		return 1;
	}
	else {
		Wezel* copy = dir->data;
		while (copy->next != nullptr) {
			if (copy->name > name)
				break;
			copy = copy->next;
		}
		Wezel* nowy = new Wezel; //je¾eli dir nie jest pusty
		nowy->size = -1;
		nowy->name = name;
		nowy->up = dir;
		if (copy->name < name) {
			nowy->prev = copy;
			copy->next = nowy;
			dir->size++;
			return 0;
		}
		nowy->next = copy;
		nowy->prev = copy->prev;
		if (copy->prev != nullptr) {
			copy->prev->next = nowy;
		}
		else {
			dir->data = nowy;
		}
		copy->prev = nowy;
		dir->size++;
		return 0;
	}
}
