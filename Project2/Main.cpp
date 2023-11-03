#include "mylib.h"


int main() {
    const int studentCount[] = { 1000, 10000, 100000, 1000000, 10000000 };

    for (int i = 0; i < sizeof(studentCount) / sizeof(studentCount[0]); i++) {
        // failo kurimo laikas
        auto start = std::chrono::high_resolution_clock::now();

        std::vector<Studentas> studentai;

        std::string filename = "studentai_" + std::to_string(studentCount[i]) + ".txt";
        std::ofstream output(filename);

        for (int j = 0; j < studentCount[i]; j++) {
            Studentas studentas(true);
            studentas.SetStudentNumber(j + 1);
            studentas.WriteToFile(output);
            studentai.push_back(studentas);
        }

        output.close();

        auto end = std::chrono::high_resolution_clock::now();
        std::chrono::duration<double> elapsed = end - start;
        std::cout << "Failo kurimas uztruko " << elapsed.count() << " sekundes." << std::endl;

        

        // studentu rusiavimo laikas
        start = std::chrono::high_resolution_clock::now();

        std::vector<Studentas> vargsiukai;
        std::vector<Studentas> kietiakiai;
        for (const Studentas& studentas : studentai) {
            if (studentas.GetGalutinis() < 5.0) {
                vargsiukai.push_back(studentas);
            }
            else {
                kietiakiai.push_back(studentas);
            }
        }

        end = std::chrono::high_resolution_clock::now();
        elapsed = end - start;
        std::cout << "Studentu rusiavimas uztruko " << elapsed.count() << " sekundes." << std::endl;

        // studentu isvedimo laikass
        start = std::chrono::high_resolution_clock::now();

        std::string vargsiukaiFilename = "vargsiukai_" + std::to_string(studentCount[i]) + ".txt";
        std::string kietiakiaiFilename = "kietiakiai_" + std::to_string(studentCount[i]) + ".txt";

        std::ofstream vargsiukaiOutput(vargsiukaiFilename);
        std::ofstream kietiakiaiOutput(kietiakiaiFilename);

        for (const Studentas& studentas : vargsiukai) {
            studentas.WriteToFile(vargsiukaiOutput);
        }

        for (const Studentas& studentas : kietiakiai) {
            studentas.WriteToFile(kietiakiaiOutput);
        }

        vargsiukaiOutput.close();
        kietiakiaiOutput.close();

        end = std::chrono::high_resolution_clock::now();
        elapsed = end - start;
        std::cout << "surusiuotu studentu isvedimo laikas " << elapsed.count() << " sekundes." << std::endl;
    }

    return 0;
}
