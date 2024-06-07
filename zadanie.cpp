#include <iostream>
#include <string>
#include <vector>
#include <map>
#include <list>
#include <algorithm>
#include<windows.h>

using namespace std;

class Ocena {
public:
    int stopien;
    string data_wpisu;
    string imie_prowadzacego;
    string nazwisko_prowadzacego;

    Ocena(int s, string data, string imie, string nazwisko)
        : stopien(s), data_wpisu(data), imie_prowadzacego(imie), nazwisko_prowadzacego(nazwisko) {}
};

class Przedmiot {
public:
    string nazwa;
    vector<Ocena> oceny;

    Przedmiot(string n) : nazwa(n) {}
};

class Semestr {
public:
    int numer;
    vector<Przedmiot> przedmioty;

    Semestr(int nr) : numer(nr) {}
};

class Student {
public:
    int nr_albumu;
    string imie;
    string nazwisko;
    int aktualny_semestr;
    list<Semestr> historia_semestrow;

    Student() : nr_albumu(0), aktualny_semestr(0) {}

    Student(int nr, string i, string n, int semestr)
        : nr_albumu(nr), imie(i), nazwisko(n), aktualny_semestr(semestr) {}
};

void dodajStudenta(map<int, Student>& studenci, int nr_albumu, string imie, string nazwisko, int semestr) {
    studenci[nr_albumu] = Student(nr_albumu, imie, nazwisko, semestr);
}

void usunStudenta(map<int, Student>& studenci, int nr_albumu) {
    studenci.erase(nr_albumu);
}

void edytujStudenta(map<int, Student>& studenci, int nr_albumu, string nowe_imie, string nowe_nazwisko, int nowy_semestr) {
    if (studenci.find(nr_albumu) != studenci.end()) {
        studenci[nr_albumu].imie = nowe_imie;
        studenci[nr_albumu].nazwisko = nowe_nazwisko;
        studenci[nr_albumu].aktualny_semestr = nowy_semestr;
    }
}

void dodajPrzedmiot(map<int, Student>& studenci, int nr_albumu, int numer_semestru, string nazwa_przedmiotu) {
    auto it = studenci.find(nr_albumu);
    if (it != studenci.end()) {
        Student& student = it->second;
        for (auto& semestr : student.historia_semestrow) {
            if (semestr.numer == numer_semestru) {
                semestr.przedmioty.push_back(Przedmiot(nazwa_przedmiotu));
                return;
            }
        }
        Semestr nowy_semestr(numer_semestru);
        nowy_semestr.przedmioty.push_back(Przedmiot(nazwa_przedmiotu));
        student.historia_semestrow.push_back(nowy_semestr);
    } else {
        cout << "Student o nr albumu " << nr_albumu << " nie istnieje.\n";
    }
}

void dodajOcene(map<int, Student>& studenci, int nr_albumu, int numer_semestru, string nazwa_przedmiotu, int stopien, string data_wpisu, string imie_prowadzacego, string nazwisko_prowadzacego) {
    auto it = studenci.find(nr_albumu);
    if (it != studenci.end()) {
        Student& student = it->second;
        for (auto& semestr : student.historia_semestrow) {
            if (semestr.numer == numer_semestru) {
                for (auto& przedmiot : semestr.przedmioty) {
                    if (przedmiot.nazwa == nazwa_przedmiotu) {
                        przedmiot.oceny.push_back(Ocena(stopien, data_wpisu, imie_prowadzacego, nazwisko_prowadzacego));
                        return;
                    }
                }
                cout << "Przedmiot " << nazwa_przedmiotu << " nie istnieje w semestrze " << numer_semestru << ".\n";
                return;
            }
        }
        cout << "Semestr " << numer_semestru << " nie istnieje.\n";
    } else {
        cout << "Student o nr albumu " << nr_albumu << " nie istnieje.\n";
    }
}

void wyswietlStudenta(const Student& student) {
    cout << "Nr albumu: " << student.nr_albumu << "\n";
    cout << "Imie: " << student.imie << "\n";
    cout << "Nazwisko: " << student.nazwisko << "\n";
    cout << "Aktualny semestr: " << student.aktualny_semestr << "\n";
    cout << "Historia semestrow: \n";
    for (const auto& semestr : student.historia_semestrow) {
        cout << "  Semestr " << semestr.numer << ":\n";
        for (const auto& przedmiot : semestr.przedmioty) {
            cout << "    Przedmiot: " << przedmiot.nazwa << "\n";
            for (const auto& ocena : przedmiot.oceny) {
                cout << "      Ocena: " << ocena.stopien
                     << ", Data: " << ocena.data_wpisu
                     << ", Prowadzacy: " << ocena.imie_prowadzacego << " " << ocena.nazwisko_prowadzacego << "\n";
            }
        }
    }
}

void znajdzStudenta(const map<int, Student>& studenci, int nr_albumu) {
    auto it = studenci.find(nr_albumu);
    if (it != studenci.end()) {
        wyswietlStudenta(it->second);
    } else {
        cout << "Student o nr albumu " << nr_albumu << " nie istnieje.\n";
    }
}

int main() {
    map<int, Student> studenci;
    int opcja;

    do {
        cout << "Menu:\n";
        cout << "1. Dodaj studenta\n";
        cout << "2. Usun studenta\n";
        cout << "3. Edytuj studenta\n";
        cout << "4. Wyswietl studenta\n";
        cout << "5. Znajdz studenta\n";
        cout << "6. Dodaj przedmiot do semestru\n";
        cout << "7. Dodaj ocene do przedmiotu\n";
        cout << "8. Wyjdz\n";
        cout << "Wybierz opcje: ";
        cin >> opcja;

        if (opcja == 1) {
            int nr_albumu, semestr;
            string imie, nazwisko;
            system("CLS");
            cout << "Podaj nr albumu: ";
            cin >> nr_albumu;
            cout << "Podaj imie: ";
            cin >> imie;
            cout << "Podaj nazwisko: ";
            cin >> nazwisko;
            cout << "Podaj aktualny semestr: ";
            cin >> semestr;
            dodajStudenta(studenci, nr_albumu, imie, nazwisko, semestr);
            system("CLS");
            cout << "Dodano studenta!" << endl;
            Sleep(1500);
            system("CLS");
        } else if (opcja == 2) {
            int nr_albumu;
            system("CLS");
            cout << "Podaj nr albumu studenta do usuniecia: ";
            cin >> nr_albumu;
            usunStudenta(studenci, nr_albumu);
            system("CLS");
            cout << "Usunieto studenta!" << endl;
            Sleep(1500);
            system("CLS");
        } else if (opcja == 3) {
            int nr_albumu, nowy_semestr;
            string nowe_imie, nowe_nazwisko;
            system("CLS");
            cout << "Podaj nr albumu studenta do edycji: ";
            cin >> nr_albumu;
            cout << "Podaj nowe imie: ";
            cin >> nowe_imie;
            cout << "Podaj nowe nazwisko: ";
            cin >> nowe_nazwisko;
            cout << "Podaj nowy aktualny semestr: ";
            cin >> nowy_semestr;
            edytujStudenta(studenci, nr_albumu, nowe_imie, nowe_nazwisko, nowy_semestr);
            system("CLS");
            cout << "Edytowano studenta!" << endl;
            Sleep(1500);
            system("CLS");
        } else if (opcja == 4) {
            int nr_albumu;
            system("CLS");
            cout << "Podaj nr albumu studenta do wyswietlenia: ";
            cin >> nr_albumu;
            system("CLS");
            znajdzStudenta(studenci, nr_albumu);
            cout <<"---------------------------------"<<endl;
            cout <<"\n"<<endl;


        } else if (opcja == 5) {
            int nr_albumu;
            system("CLS");
            cout << "Podaj nr albumu studenta do znalezienia: ";
            cin >> nr_albumu;
            system("CLS");
            znajdzStudenta(studenci, nr_albumu);
            cout <<"---------------------------------"<<endl;
            cout <<"\n"<<endl;
        } else if (opcja == 6) {
            int nr_albumu, numer_semestru;
            string nazwa_przedmiotu;
            system("CLS");
            cout << "Podaj nr albumu: ";
            cin >> nr_albumu;
            cout << "Podaj numer semestru: ";
            cin >> numer_semestru;
            cout << "Podaj nazwe przedmiotu: ";
            cin >> nazwa_przedmiotu;
            dodajPrzedmiot(studenci, nr_albumu, numer_semestru, nazwa_przedmiotu);
            system("CLS");
            cout << "Dodano!" << endl;
            Sleep(1500);
            system("CLS");
        } else if (opcja == 7) {
            int nr_albumu, numer_semestru, stopien;
            string nazwa_przedmiotu, data_wpisu, imie_prowadzacego, nazwisko_prowadzacego;
            system("CLS");
            cout << "Podaj nr albumu: ";
            cin >> nr_albumu;
            cout << "Podaj numer semestru: ";
            cin >> numer_semestru;
            cout << "Podaj nazwe przedmiotu: ";
            cin >> nazwa_przedmiotu;
            cout << "Podaj stopien: ";
            cin >> stopien;
            cout << "Podaj date wpisu: ";
            cin >> data_wpisu;
            cout << "Podaj imie prowadzacego: ";
            cin >> imie_prowadzacego;
            cout << "Podaj nazwisko prowadzacego: ";
            cin >> nazwisko_prowadzacego;
            dodajOcene(studenci, nr_albumu, numer_semestru, nazwa_przedmiotu, stopien, data_wpisu, imie_prowadzacego, nazwisko_prowadzacego);
            system("CLS");
            cout << "Dodano!" << endl;
            Sleep(1500);
            system("CLS");
        }
    } while (opcja != 8);

    return 0;
}
