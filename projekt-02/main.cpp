//Drugi projekt na zaj©cia z Podstaw Programowania Komputer¢w - Drzewo katalog¢w
//Autor: Piotr Uhl
//(grupa 4, sekcja 8)
//
//Napisa† program przechowuj¥cy w pami©ci operacyjnej struktur© katalog¢w. Struktura ta powinna zawiera† katalog gˆ¢wny
//oraz, dla ka¾dego katalogu w nim zawartego, list© jego katalog¢w potomnych(dla dowolnego stopnia zagnie¾d¾ania katalog¢w).
//Program powinien mie† mo¾liwo˜† wy˜wietlenia zawarto˜ci wybranego katalogu, dodawania, sortowania i usuwania do niego
//katalog¢w potomnych oraz funkcj© zapisu i odczytu z pliku binarnego caˆej struktury.

#include "header.hpp"

int main() {
	Wezel* root = new Wezel;
	root->name = "/";
	shell(root);
	return 1;
}