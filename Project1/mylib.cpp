
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

void Studentas::InputData() {
    std::cout << "Iveskite studento varda: ";
    std::cin >> vardas_;
    std::cout << "Iveskite studento pavarde: ";
    std::cin >> pavarde_;

    int nd;
    std::cout << "Iveskite namu darbu rezultatus (baigti su -1) arba generuoti atsitiktinai (0): ";
    while (true) {
        std::cin >> nd;
        if (nd == -1) {
            break;
        }
        else if (nd == 0) {
            
            std::random_device rd;
            std::mt19937 gen(rd());
            std::uniform_int_distribution<int> distribution(1, 10);
            for (int i = 0; i < 5; ++i) {
                int random_nd = distribution(gen);
                namuDarbai_.push_back(random_nd);
            }
            break;
        }
        else {
            namuDarbai_.push_back(nd);
        }
    }

    std::cout << "Iveskite egzamino rezultata arba generuoti atsitiktinai (0): ";
    std::cin >> egzaminas_;
    if (egzaminas_ == 0) {
        
        std::random_device rd;
        std::mt19937 gen(rd());
        std::uniform_int_distribution<int> distribution(1, 10);
        egzaminas_ = distribution(gen);
    }
    CalculateFinalGrade();
}

void Studentas::OutputData() const {
    std::cout << std::left << std::setw(12) << pavarde_
        << std::left << std::setw(12) << vardas_;

    if (naudotiVidurki_) {
        std::cout << std::fixed << std::setprecision(2) << "Galutinis (Vid.)" << std::setw(10);
    }
    else {
        std::cout << std::fixed << std::setprecision(2) << "Galutinis (Med.)" << std::setw(10);
    }

    std::cout << galutinis_ << std::endl;
}

void Studentas::CalculateFinalGrade() {
    if (namuDarbai_.empty()) {
        std::cerr << "nera namu darbu" << std::endl;
        return;
    }

    if (naudotiVidurki_) {
        double vidurkis = 0.0;
        for (int nd : namuDarbai_) {
            vidurkis += nd;
        }
        vidurkis /= namuDarbai_.size();
        galutinis_ = 0.4 * vidurkis + 0.6 * egzaminas_;
    }
    else {
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
}
void Studentas::WriteToFile(std::ostream& file) const {
    file << pavarde_ << "\t" << vardas_ << "\t";
    for (int nd : namuDarbai_) {
        file << nd << "\t";
    }
    file << egzaminas_ << "\n";
}

bool Studentas::ReadFromFile(std::ifstream& file) {
    if (file >> pavarde_ >> vardas_) {
        namuDarbai_.clear();
        for (int i = 0; i < 5; ++i) { 
            int nd;
            if (file >> nd) {
                namuDarbai_.push_back(nd);
            }
            else {
                std::cerr << "nera namu darbu rezultatu" << std::endl;
                return false; 
            }
        }
        if (file >> egzaminas_) {
            CalculateFinalGrade();
            return true; 
        }
    }
    return false; 
}


void Studentas::GenerateRandomGrades(Studentas& studentas) {
    studentas.namuDarbai_.clear();
    for (int i = 0; i < studentas.namuDarbai_.size(); ++i) {
        int nd = rand() % 10 + 1;
        studentas.namuDarbai_[i] = nd;
    }
    studentas.egzaminas_ = rand() % 10 + 1;
    studentas.CalculateFinalGrade();
}
