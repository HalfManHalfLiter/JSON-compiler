#include <iostream>
#include <string>
#include <fstream>
#include <stack>

using namespace std;

// Menu
void displayMenu() {
    cout << "\n\n\n\n\n\n\n\n\n";
    cout << "                  .d8888. d88888D db    db .88b  d88.  .d88b.  d8b   db      d8888b. db       .d8b.  d888888b  .d8b.  \n";
    cout << "                  88'  YP YP  d8' `8b  d8' 88'YbdP`88 .8P  Y8. 888o  88      88  `8D 88      d8' `8b `~~88~~' d8' `8b \n";
    cout << "                  `8bo.      d8'   `8bd8'  88  88  88 88    88 88V8o 88      88oodD' 88      88ooo88    88    88ooo88 \n";
    cout << "                    `Y8b.   d8'      88    88  88  88 88    88 88 V8o88      88~~~   88      88~~~88    88    88~~~88 \n";
    cout << "                  db   8D  d8' db    88    88  88  88 `8b  d8' 88  V888      88      88booo. 88   88    88    88   88 \n";
    cout << "                  `8888Y' d88888P    YP    YP  YP  YP  `Y88P'  VP   V8P      88      Y88888P YP   YP    YP    YP   YP \n\n\n";
    cout << "                                                 |                         h - help                       |\n";
    cout << "                                                 |     o (nazwa_pliku) - otwieranie wybranego pliku       |\n";
    cout << "                                                 | c - sprawdzanie, czy plik jest poprawnym formatem JSON |\n\n\n";
}

// Poprawnosc formatu JSON
void validateJSON(const string& filename) {
    fstream file(filename);
    if (!file.is_open()) {
        cout << "Nie udalo sie otworzyc pliku: " << filename << endl;
        return;
    }

    string line;
    int lineNumber = 1;
    stack<char> brackets; // Stos do sprawdzania zagniezdzonych nawiasow
    bool insideString = false;
    char stringDelimiter = 0;

    while (getline(file, line)) {
        // Usuwanie bialych znakow z poczatku i konca linii dla uproszczenia
        line.erase(0, line.find_first_not_of(" \t"));
        line.erase(line.find_last_not_of(" \t") + 1);

        if (line.empty()) {
            lineNumber++;
            continue; // Pomijamy puste linie
        }

        // Sprawdzanie pierwszego znaku w pliku
        if (lineNumber == 1 && line[0] != '{' && line[0] != '[') {
            cout << "Blad w linii " << lineNumber << ": Plik JSON powinien zaczynac sie od '{' lub '['" << endl;
            file.close();
            return;
        }

        for (size_t i = 0; i < line.length(); ++i) {
            char c = line[i];

            // Obsluga stringow (ignorowanie znakow w cudzyslowach)
            if (insideString) {
                if (c == stringDelimiter) {
                    insideString = false; // Koniec stringa
                }
                continue;
            } else if (c == '"' || c == '\'') {
                insideString = true;
                stringDelimiter = c;
                continue;
            }

            // Sprawdzanie nawiasow
            if (c == '{' || c == '[') {
                brackets.push(c);
            } else if (c == '}' || c == ']') {
                if (brackets.empty()) {
                    cout << "Blad w linii " << lineNumber << ": Nadmiarowy nawias zamykajacy '" << c << "'" << endl;
                    file.close();
                    return;
                }
                char expected = (c == '}') ? '{' : '[';
                if (brackets.top() != expected) {
                    cout << "Blad w linii " << lineNumber << ": Niesparowany nawias '" << c << "'" << endl;
                    file.close();
                    return;
                }
                brackets.pop();
            }

            // Sprawdzanie dwukropka
            if (c == ':' && !insideString) {
                if (i == 0 || i == line.length() - 1) {
                    cout << "Blad w linii " << lineNumber << ": Dwukropek ':' w niepoprawnej pozycji" << endl;
                    file.close();
                    return;
                }
            }

            // Sprawdzanie przecinka
            if (c == ',' && !insideString) {
                if (i == 0 || i == line.length() - 1) {
                    cout << "Blad w linii " << lineNumber << ": Przecinek ',' w niepoprawnej pozycji" << endl;
                    file.close();
                    return;
                }
            }
        }
        lineNumber++;
    }

    // Sprawdzanie, czy wszystkie nawiasy zostaly zamkniete
    if (!brackets.empty()) {
        cout << "Blad: Nie wszystkie nawiasy zostaly zamkniete" << endl;
        file.close();
        return;
    }

    cout << "Plik JSON jest poprawny!" << endl;
    file.close();
}

// Funkcja otwierajaca plik i wywolujaca walidacje
void openFile(const string& filename) {
    fstream file(filename);
    if (file.is_open()) {
        cout << "Udalo sie otworzyc plik: " << filename << endl;
        file.close();
        validateJSON(filename);
    } else {
        cout << "Nie udalo sie otworzyc pliku: " << filename << endl;
    }
}

int main() {
    string input;
    string filename;

    while (true) {
        displayMenu();
        cout << "Operacja: ";
        getline(cin, input); // Pobieramy cala linie, aby obsluzyc "o nazwa_pliku"

        if (input.empty()) {
            continue;
        }

        char operation = input[0];
        if (operation == 'h') {
            continue; // Ponowne wyswietlenie menu
        } else if (operation == 'o') {
            if (input.length() > 2) {
                filename = input.substr(2); // Pobieramy nazwe pliku po "o "
                openFile(filename);
            } else {
                cout << "Prosze podac nazwe pliku po 'o', np. 'o plik.json'" << endl;
            }
        } else if (operation == 'c') {
            if (!filename.empty()) {
                validateJSON(filename);
            } else {
                cout << "Najpierw otworz plik za pomoca operacji 'o'" << endl;
            }
        } else if (operation == 'q') {
            cout << "Zamykanie programu..." << endl;
            break;
        } else {
            cout << "Nieznana operacja. Uzyj 'h' aby wyswietlic menu." << endl;
        }
    }

    return 0;
}
