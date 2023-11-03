
#ifndef MYLIB_H
#define MYLIB_H

#include <string>
#include <vector>
#include <fstream> 
#include <algorithm>
#include <ctime>
#include <cstdlib>
#include <chrono>
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

    

    const std::string& GetVardas() const { return vardas_; }
    const std::string& GetPavarde() const { return pavarde_; }
    const std::vector<int>& GetNamuDarbai() const { return namuDarbai_; }

    void WriteToFile(std::ostream& file) const;  

    
    Studentas(bool generateRandom);
    void GenerateRandomGrades();
    void WriteToFile(const std::string& filename) const;
    void SetStudentNumber(int number) {
        studentNumber_ = number;
    }
    double GetGalutinis() const { return galutinis_; }
private:
    std::string vardas_;
    std::string pavarde_;
    std::vector<int> namuDarbai_;
    int egzaminas_;
    double galutinis_;
    bool naudotiVidurki_;  
    int studentNumber_;
    void CalculateFinalGrade();
};

#endif