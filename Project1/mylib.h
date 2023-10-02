

#include <iostream>
#include <string>
#include <vector>
#include <fstream>

using namespace std;
class studentas {
    string vard, pav;
    vector<int> paz;
    int egz;
    float rez;

public:
    studentas();
    studentas(const string& v, const string& p, const vector<int>& pp, int e);
    studentas(const studentas& temp);
    studentas& operator=(const studentas& temp);
    void IvestiDuomenis();
    void IsvestiDuomenis() const;
    double SkaiciuotiGalutiniPazymiVidurkiu() const;
    double SkaiciuotiGalutiniPazymiMediana() const;
    inline string GetVardas() const { return vard; }
    // Naujas metodas rezultatų išvedimui
    void IsvestiRezultatus() const;
};


