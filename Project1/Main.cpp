
#include "mylib.h"

int main() {
    std::srand(static_cast<unsigned>(std::time(0))); 
    std::vector<Studentas> studentai;

    
    std::ifstream input("kursiokai.txt");
    if (input.is_open()) {
        Studentas studentas;
        while (studentas.ReadFromFile(input)) {
            studentas.ReadFromFile(input);
            studentai.push_back(studentas);
        }
        input.close();
    }

    
    for (Studentas& studentas : studentai) {
        if (studentas.GetNamuDarbai().empty()) {
            Studentas::GenerateRandomGrades(studentas);
        }
    }

    
    std::sort(studentai.begin(), studentai.end(), [](const Studentas& a, const Studentas& b) {
        return a.GetVardas() < b.GetVardas();
        });

    
    std::cout << "--------------------------------------------------------------\n";
    std::cout << std::left << std::setw(12) << "Pavarde"
        << std::left << std::setw(12) << "Vardas"
        << "Galutinis (Vid)\n";
    std::cout << "--------------------------------------------------------------\n";

    for (const Studentas& studentas : studentai) {
        studentas.OutputData();
    }

    return 0;
}
