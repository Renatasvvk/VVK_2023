#include "mylib.h"


int main() {
    const int studentCount[] = { 1000, 10000, 100000, 1000000, 10000000 };

    for (int i = 0; i < sizeof(studentCount) / sizeof(studentCount[0]); i++) {
        // failo kurimo laikas
        auto start = std::chrono::high_resolution_clock::now();

        std::vector<Studentas> studentai;
        std::vector<Studentas> vargsiukai;

        std::string filename = "studentai_" + std::to_string(studentCount[i]) + ".txt";
        std::ofstream output(filename);

        for (int j = 0; j < studentCount[i]; j++) {
            Studentas studentas(true);
            studentas.SetStudentNumber(j + 1);
            if (studentas.GetGalutinis() < 5.0) {
                vargsiukai.push_back(studentas);
            }
            else {
                studentas.WriteToFile(output);
                studentai.push_back(studentas);
            }
        }

        output.close();

        auto end = std::chrono::high_resolution_clock::now();
        std::chrono::duration<double> elapsed = end - start;
        std::cout << "Failo kurimas uztruko " << elapsed.count() << " sekundes." << std::endl;

        // duomenu nuskaitymo laikas
        start = std::chrono::high_resolution_clock::now();

        end = std::chrono::high_resolution_clock::now();
        elapsed = end - start;
        std::cout << "Duomenu nuskaitymas uztruko " << elapsed.count() << " sekundes." << std::endl;

        // vargsiuku isvedimo laikas
        start = std::chrono::high_resolution_clock::now();

        std::string vargsiukaiFilename = "vargsiukai_" + std::to_string(studentCount[i]) + ".txt";
        std::ofstream vargsiukaiOutput(vargsiukaiFilename);

        for (const Studentas& studentas : vargsiukai) {
            studentas.WriteToFile(vargsiukaiOutput);
        }

        vargsiukaiOutput.close();

        end = std::chrono::high_resolution_clock::now();
        elapsed = end - start;
        std::cout << "Surusiuotu vargsiuku isvedimas uztruko " << elapsed.count() << " sekundes." << std::endl;
    }

    return 0;
}
