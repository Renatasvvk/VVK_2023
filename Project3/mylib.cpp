#include "mylib.h"


Studentas::Studentas() : vardas_(""), pavarde_(""), egzaminas_(0), galutinis_(0.0), naudotiVidurki_(true) {
}

Studentas::Studentas(const std::string& vardas, const std::string& pavarde, const std::vector<int>& namuDarbai, int egzaminas, bool naudotiVidurki)
    : vardas_(vardas), pavarde_(pavarde), namuDarbai_(namuDarbai), egzaminas_(egzaminas), naudotiVidurki_(naudotiVidurki) {
    CalculateFinalGrade();
}

Studentas::Studentas(const Studentas& other)
    : vardas_(other.vardas_), pavarde_(other.pavarde_),
    namuDarbai_(other.namuDarbai_), egzaminas_(other.egzaminas_),
    galutinis_(other.galutinis_), naudotiVidurki_(other.naudotiVidurki_) {
}

Studentas& Studentas::operator=(const Studentas& other) {
    if (this == &other) {
        return *this;
    }
    vardas_ = other.vardas_;
    pavarde_ = other.pavarde_;
    namuDarbai_ = other.namuDarbai_;
    egzaminas_ = other.egzaminas_;
    galutinis_ = other.galutinis_;
    naudotiVidurki_ = other.naudotiVidurki_;
    return *this;
}

Studentas::~Studentas() {
}

void Studentas::CalculateFinalGrade() {
    if (naudotiVidurki_ && !namuDarbai_.empty()) {
        double vidurkis = 0.0;
        for (int nd : namuDarbai_) {
            vidurkis += nd;
        }
        vidurkis /= namuDarbai_.size();
        galutinis_ = 0.4 * vidurkis + 0.6 * egzaminas_;
    }
    else if (!namuDarbai_.empty()) {
        std::vector<int> sortedNamuDarbai = namuDarbai_;
        std::sort(sortedNamuDarbai.begin(), sortedNamuDarbai.end());
        if (sortedNamuDarbai.size() % 2 == 0) {
            int n1 = sortedNamuDarbai[sortedNamuDarbai.size() / 2 - 1];
            int n2 = sortedNamuDarbai[sortedNamuDarbai.size() / 2];
            galutinis_ = (n1 + n2) / 2.0;
        }
        else {
            galutinis_ = sortedNamuDarbai[sortedNamuDarbai.size() / 2];
        }
        galutinis_ = 0.4 * galutinis_ + 0.6 * egzaminas_;
    }
    else {
        std::cerr << "nera namu darbu rezultatu" << std::endl;
    }
}

void Studentas::WriteToFile(std::ostream& file) const {
    file << pavarde_ << "\t" << vardas_ << "\t";
    for (int nd : namuDarbai_) {
        file << nd << "\t";
    }
    file << egzaminas_ << "\t";
    if (naudotiVidurki_) {
        file << "" << "\t" << galutinis_;
    }
    else {
        file << "" << "\t" << galutinis_;
    }
    file << "\n";
}





Studentas::Studentas(bool generateRandom) : egzaminas_(0), galutinis_(0.0), naudotiVidurki_(true) {
    if (generateRandom) {
        static int studentoNumeris = 1; 
        vardas_ = "Vardas" + std::to_string(studentoNumeris);
        pavarde_ = "Pavarde" + std::to_string(studentoNumeris);
        studentoNumeris++; 

        GenerateRandomGrades();
    }
}



void Studentas::GenerateRandomGrades() {
    std::random_device rd;
    std::mt19937 gen(rd());
    std::uniform_int_distribution<int> distribution(1, 10);

    for (int i = 0; i < 5; ++i) {
        int random_nd = distribution(gen);
        namuDarbai_.push_back(random_nd);
    }

    egzaminas_ = distribution(gen);
    CalculateFinalGrade();
}
void Studentas::WriteToFile(const std::string& filename) const {
    std::ofstream file(filename);
    if (file.is_open()) {
        file << pavarde_ << "\t" << vardas_ << "\t";
        for (int nd : namuDarbai_) {
            file << nd << "\t";
        }
        file << egzaminas_ << "\n";
        file.close();
    }
    else {
        std::cerr << "nepavyko atidaryti failo " << filename << std::endl;
    }
}