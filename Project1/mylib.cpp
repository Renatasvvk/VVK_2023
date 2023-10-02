#include "mylib.h"
#include <iomanip>
#include <algorithm>

studentas::studentas() {
    vard.clear();
    pav.clear();
    paz.clear();
    egz = 0;
    rez = 0;
}

studentas::studentas(const string& v, const string& p, const vector<int>& pp, int e)
    : vard(v), pav(p), paz(pp), egz(e), rez(0) {}

studentas::studentas(const studentas& temp)
    : vard(temp.vard), pav(temp.pav), paz(temp.paz), egz(temp.egz), rez(temp.rez) {}

studentas& studentas::operator=(const studentas& temp) {
    if (this == &temp) return *this;
    vard = temp.vard;
    pav = temp.pav;
    paz = temp.paz;
    egz = temp.egz;
    rez = temp.rez;
    return *this;
}

void studentas::IvestiDuomenis() {
    cout << "Ivesk varda: ";
    cin >> vard;
    cout << "Ivesk pavarde: ";
    cin >> pav;
    cout << "Kiek pazymiu buvo semestre? ";
    int n;
    cin >> n;
    for (int i = 0; i < n; i++) {
        int k;
        cin >> k;
        paz.push_back(k);
    }
    cout << "Ivesk egzamino pazymi: ";
    cin >> egz;
}

void studentas::IsvestiDuomenis() const {
    cout << "Vardas: " << vard << endl;
    cout << "Pavarde: " << pav << endl;
    cout << "Namu darbai: ";
    for (int nd : paz) {
        cout << nd << " ";
    }
    cout << endl;
    cout << "Egzamino rezultatas: " << egz << endl;
    cout << "Galutinis pazymys: " << SkaiciuotiGalutiniPazymiVidurkiu() << " (vid.) / " << SkaiciuotiGalutiniPazymiMediana() << " (med.)" << endl;
}
double studentas::SkaiciuotiGalutiniPazymiVidurkiu() const {
    if (paz.empty()) {
        return 0.4 * egz;
    }
    else {
        double nd_vidurkis = 0.0;
        for (int nd : paz) {
            nd_vidurkis += nd;
        }
        nd_vidurkis /= paz.size();
        return 0.4 * nd_vidurkis + 0.6 * egz;
    }
}

double studentas::SkaiciuotiGalutiniPazymiMediana() const {
    if (paz.empty()) {
        return 0.4 * egz;
    }
    else {
        vector<int> pazymiai = paz;
        pazymiai.push_back(egz);
        sort(pazymiai.begin(), pazymiai.end());

        if (pazymiai.size() % 2 == 0) {
            int vidurinis1 = pazymiai[pazymiai.size() / 2 - 1];
            int vidurinis2 = pazymiai[pazymiai.size() / 2];
            return 0.4 * (vidurinis1 + vidurinis2) / 2.0 + 0.6 * egz;
        }
        else {
            int vidurinis = pazymiai[pazymiai.size() / 2];
            return 0.4 * vidurinis + 0.6 * egz;
        }
    }
}

void studentas::IsvestiRezultatus() const {
    cout << left << setw(12) << pav << setw(12) << vard
        << fixed << setprecision(2) << setw(20) << SkaiciuotiGalutiniPazymiVidurkiu()
        << fixed << setprecision(2) << SkaiciuotiGalutiniPazymiMediana() << endl;
}
