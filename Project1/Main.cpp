#include "mylib.h"
#include <iomanip>

int main() {
    cout << "Iveskite studentus" << endl;
    vector<studentas> grupe;

    for (int i = 0; i < 3; i++) {
        studentas K;
        K.IvestiDuomenis();
        grupe.push_back(K);
    }

    cout << endl << "Rezultatai:" << endl;
    cout << left << setw(12) << "Pavarde" << setw(12) << "Vardas"
        << "Galutinis (Vid.)" << "Galutinis (Med.)" << endl;
    cout << "-----------------------------------------------------------" << endl;

    for (const auto& a : grupe) {
        a.IsvestiRezultatus();
    }

    return 0;
}
