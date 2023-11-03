
#ifndef MYLIB_H
#define MYLIB_H

#include <string>
#include <vector>
#include <fstream> 
#include <algorithm>
#include <ctime>
#include <cstdlib>
#include <iostream>
#include <iomanip>
#include <random>

class Studentas {
public:
    Studentas();
    Studentas(const std::string& vardas, const std::string& pavarde, const std::vector<int>& namuDarbai, int egzaminas, bool naudotiVidurki);
    Studentas(const Studentas& other);
    Studentas& operator=(const Studentas& other);
    ~Studentas();

    void InputData();
    void OutputData() const;
    static void GenerateRandomGrades(Studentas& studentas);
    const std::string& GetVardas() const { return vardas_; }
    const std::string& GetPavarde() const { return pavarde_; }
    const std::vector<int>& GetNamuDarbai() const { return namuDarbai_; }

    void WriteToFile(std::ostream& file) const;  

    bool ReadFromFile(std::ifstream& file); 


private:
    std::string vardas_;
    std::string pavarde_;
    std::vector<int> namuDarbai_;
    int egzaminas_;
    double galutinis_;
    bool naudotiVidurki_;  

    void CalculateFinalGrade();
};

#endif
