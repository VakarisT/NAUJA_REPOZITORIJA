#include "studentas.h"

const std::vector<std::string> nameList{"Nojus", "Domas", "Arvydas", "Rokas", "Vytautas", "Aurimas", "Joris", "Ramunas", "Povilas", "Mindaugas"};
const std::vector<std::string> surnameList{"Vaicekauskas", "Kateiva", "Kardauskas", "Zalionis", "Norkus", "Ozelis", "Stasiunas", "Oginskas", "Petrauskas", "Pakuckas"};

Student::Student() : hwRes_({0})
{
    name_ = "NeraVardo";
    surname_ = "NeraPavardes";
    exRes_ = 0;
    avg_ = 0.0;
    med_ = 0.0;
    std::cout << "Konstruktorius tuscias suveike" << std::endl;
}

Student::Student(std::string name, std::string surname) : hwRes_({0})
{
    name_ = name;
    surname_ = surname;
    exRes_ = 0;
    avg_ = 0.0;
    med_ = 0.0;
    std::cout << "Konstruktorius su vardu suveike" << std::endl;
}

Student::~Student()
{
    hwRes_.clear();
    std::cout << "Destruktorius suveike" << std::endl;
}

Student::Student(const Student &St_)
{
    name_ = St_.name_;
    surname_ = St_.surname_;
    hwRes_ = St_.hwRes_;
    exRes_ = St_.exRes_;
    avg_ = St_.avg_;
    med_ = St_.med_;
    std::cout << "Kopijavimo konstruktorius suveike" << std::endl;
}

Student::Student(Student &&St_) noexcept
{
    name_ = std::move(St_.name_);
    surname_ = std::move(St_.surname_);
    hwRes_ = std::move(St_.hwRes_);
    exRes_ = std::move(St_.exRes_);
    avg_ = std::move(St_.avg_);
    med_ = std::move(St_.med_);
    St_.clear_All();
    std::cout << "Perkelimo konstruktorius suveike" << std::endl;
}

Student &Student::operator=(const Student &St_)
{
    if (this != &St_)
    {
        name_ = St_.name_;
        surname_ = St_.surname_;
        hwRes_ = St_.hwRes_;
        exRes_ = St_.exRes_;
        avg_ = St_.avg_;
        med_ = St_.med_;
    }
    std::cout << "Priskyrimo operatorius suveike" << std::endl;
    return *this;
}

Student &Student::operator=(Student &&St_) noexcept
{
    name_ = std::move(St_.name_);
    surname_ = std::move(St_.surname_);
    hwRes_ = std::move(St_.hwRes_);
    exRes_ = std::move(St_.exRes_);
    avg_ = std::move(St_.avg_);
    med_ = std::move(St_.med_);
    St_.clear_All();
    std::cout << "Perkelimo operatorius suveike" << std::endl;
    return *this;
}

std::istringstream &operator>>(std::istringstream &input, Student &St_)
{
    std::string name, surname;
    if (!(input >> name >> surname))
        throw std::runtime_error("Nepavyko nuskaityti vardo ir pavardes");
    St_.set_Name(name);
    St_.set_Surname(surname);
    int hw;
    St_.clear_Hw();
    while (input >> hw)
        St_.set_Hw(hw);
    if (!St_.hwRes_Empty())
    {
        St_.set_ExRes(St_.hw_Last());
        St_.del_LastHw();
        St_.hw_Sort();
        St_.set_Avg(St_.Average());
        St_.set_Med(St_.Median());
    }
    std::cout << "As esu ivedimo is failo operatoriuje >>" << std::endl;
    return input;
}

std::istream &operator>>(std::istream &input, Student &St_)
{
    std::string name, surname;
    int hw, ex;
    std::cout << "Vardas: ";
    std::cin >> name;
    std::cout << "Pavarde: ";
    std::cin >> surname;
    St_.set_Name(name);
    St_.set_Surname(surname);
    St_.clear_Hw();
    while (true)
    {
        std::cout << "Namu darbu pazymys (\"-1\", kad uzbaigti): ";
        std::cin >> hw;
        if (std::cin.fail())
            throw std::runtime_error("Klaidinga ivestis");
        if (hw < 0)
            break;
        St_.set_Hw(hw);
    }
    std::cout << "Egzamino pazymys: ";
    std::cin >> ex;
    if (std::cin.fail())
        throw std::runtime_error("Klaidinga ivestis");
    St_.set_ExRes(ex);
    St_.set_Avg(St_.Average());
    St_.set_Med(St_.Median());
    std::cout << "As esu ivedimo per konsole operatoriuje >>" << std::endl;
    return input;
}

std::ostream &operator<<(std::ostream &output, const Student &St_)
{
    output << std::left << std::setw(15) << St_.get_Name() << std::setw(15) << St_.get_Surname() << std::setw(20) << St_.get_Avg() << std::setw(15) << St_.get_Med() << std::endl;
    return output;
}

std::ofstream &operator<<(std::ofstream &output, const Student &St_)
{
    std::stringstream out;
    out << std::left << std::setw(15) << St_.get_Surname() << std::setw(15) << St_.get_Name() << std::setw(20) << St_.get_Avg() << std::setw(15) << St_.get_Med() << std::endl;
    output << out.str();
    out.clear();
    return output;
}

double Student::Average()
{
    if (hwRes_Size() > 0)
        return 0.4 * hw_Sum() / hwRes_Size() + 0.6 * get_exRes();
    else
        return 0.6 * get_exRes();
}

double Student::Median()
{
    std::vector<int> hwRes = get_HwRes();
    int size = hwRes_Size();
    if (size % 2 == 0 && size > 0)
        return (hwRes[size / 2 - 1] + hwRes[size / 2]) / 2.0 * 0.4 + 0.6 * get_exRes();
    else if (size % 2 != 0 && size > 0)
        return hwRes[size / 2] * 0.4 + 0.6 * get_exRes();
    else
        return 0.6 * get_exRes();
}

bool compareName(const Student &a, const Student &b)
{
    return a.get_Name() < b.get_Name();
}

bool compareSurname(const Student &a, const Student &b)
{
    return a.get_Surname() < b.get_Surname();
}

bool compareAvg(const Student &a, const Student &b)
{
    return a.get_Avg() < b.get_Avg();
}

bool compareMed(const Student &a, const Student &b)
{
    return a.get_Med() < b.get_Med();
}

int RandGrade()
{
    std::random_device rd;
    std::mt19937 gen(rd());
    std::uniform_int_distribution<> dis(1, 10);
    return dis(gen);
}

void GenFile(int size, int hw)
{
    std::string input = "Stud" + std::to_string(size) + ".txt";
    std::ofstream output(input);
    std::stringstream out;

    out << std::left << std::setw(25) << "Vardas" << std::setw(25) << "Pavarde";
    for (int i = 1; i <= hw; i++)
        out << std::left << std::setw(10) << "ND" + std::to_string(i) << " ";
    out << std::left << std::setw(10) << "Egz." << std::endl;
    for (int i = 1; i <= size; i++)
    {
        out << std::left << std::setw(25) << "Vardas" + std::to_string(i) << std::setw(25) << "Pavarde" + std::to_string(i);
        for (int j = 0; j < hw; j++)
            out << std::left << std::setw(10) << RandGrade() << " ";
        out << std::left << std::setw(10) << RandGrade() << std::endl;
    }

    output << out.str();
    out.clear();
    output.close();
    std::cout << "Failas: " << input << " sugeneruotas sekmingai :)" << std::endl;
}

void ReadFile(std::vector<Student>& studVector, int& size)
{
    try
    {
        system("dir *.txt");
        std::cout << "Kiek studentu norite pamatyti (jei norite pabaigti, irasykite \"0\"): " << std::endl;
        //std::string fileName;
        //std::cout << "Irasykite failo pavadinima (jei norite pabaigti, irasykite \"exit\"): ";
        std::cin >> size;
        if (size == 0)
            return;

        std::ifstream input("studentai" + std::to_string(size) + ".txt");
        if (!input.is_open())
            throw std::runtime_error("Nepavyko atidaryti failo! :(");

        const auto start = std::chrono::high_resolution_clock::now();

        Student stud;
        std::string line;
        input.ignore(1000, '\n');
        while (std::getline(input, line))
        {
            std::istringstream iss(line);
            std::string name, surname;
            if (!(iss >> name >> surname))
                throw std::runtime_error("Nepavyko nuskaityti failo! :(");
            stud.set_Name(name);
            stud.set_Surname(surname);
            int hw;
            stud.clear_Hw();
            while (iss >> hw)
                stud.set_Hw(hw);
            if (!stud.hwRes_Empty())
            {
                stud.set_ExRes(stud.hw_Last());
                stud.del_LastHw();
                stud.hw_Sort();
                stud.set_Avg(stud.Average());
                stud.set_Med(stud.Median());
            }
            studVector.push_back(stud);
        }

        input.close();
        //std::cout << "Failas sekmingai nuskaitytas :)" << std::endl;
        studVector.shrink_to_fit();
        const auto end = std::chrono::high_resolution_clock::now();
        const std::chrono::duration<double> diff = end - start;
        std::cout << "Failo nuskaitymo laikas: " << diff.count() << " sekundes" << std::endl;
    }
    catch (const std::exception& e)
    {
        std::cerr << e.what() << '\n';
    }
}

void Selection(std::vector<Student>& studVector, int choice, std::vector<Student>& best, std::vector<Student>& worst)
{
    try
    {
        const auto start = std::chrono::high_resolution_clock::now();
        switch (choice) {
        case 1:
            sort(studVector.begin(), studVector.end(),
                [](const Student& a, const Student& b) { return (a.get_Name() < b.get_Name()); });
            break;
        case 2:
            sort(studVector.begin(), studVector.end(),
                [](const Student& a, const  Student& b) { return (a.get_Avg() < b.get_Avg()); });
            break;
        case 3:
            sort(studVector.begin(), studVector.end(),
                [](const Student& a, const Student& b) { return (a.get_Med() < b.get_Med()); });
            break;
        }
        Student st;
        for (int i = 0; i < studVector.size(); i++)
        {
            //Stud st = A.at(i);
            if (studVector.at(i).get_Avg() < 5.0)
            {
                st.set_Name(studVector.at(i).get_Name());
                st.set_Surname(studVector.at(i).get_Surname());
                st.set_Avg(studVector.at(i).get_Avg());
                st.set_Med(studVector.at(i).get_Med());
                worst.push_back(st);
                //st.clear();
            }
            else if (studVector.at(i).get_Avg() >= 5.0)
            {
                st.set_Name(studVector.at(i).get_Name());
                st.set_Surname(studVector.at(i).get_Surname());
                st.set_Avg(studVector.at(i).get_Avg());
                st.set_Med(studVector.at(i).get_Med());
                best.push_back(st);
                //st.clear();
            }
        }
        studVector.clear();
        const auto end = std::chrono::high_resolution_clock::now();
        const std::chrono::duration<double> diff = end - start;
        std::cout << "Studentu atrankos laikas: " << diff.count() << " sekundes" << std::endl;
    }
    catch (const std::exception& e)
    {
        std::cerr << e.what() << '\n';
    }
}

void Results(std::ofstream& fout, std::vector<Student>& A, std::string m)
{
    try
    {
        const auto start = std::chrono::high_resolution_clock::now();
        if (A.size() < 1)
            throw std::runtime_error("Nera duomenu vektoriaus masyve!");
        fout << std::left << std::setw(15) << "Pavarde" << std::setw(15) << "Vardas" << std::setw(20) << "Galutinis (Vid.)" << std::setw(15) << "Galutinis (Med.)" << std::endl;
        fout << "------------------------------------------------------------------" << std::endl;
        fout << std::fixed << std::setprecision(2);
        for (const auto& i : A)
            fout << std::left << std::setw(15) << i.get_Name() << std::setw(15) << i.get_Surname() << std::setw(20) << i.get_Avg() << std::setw(15) << i.get_Med() << std::endl;
        const auto end = std::chrono::high_resolution_clock::now();
        const std::chrono::duration<double> diff = end - start;
        std::cout << m << " isvedimo laikas: " << diff.count() << " sekundes" << std::endl;
    }
    catch (const std::exception& e)
    {
        std::cerr << e.what() << '\n';
    }
}

void ReadUser(std::vector<Student> &studVector)
{
    try
    {
        Student temp;
        std::cin >> temp;
        studVector.push_back(temp);
    }
    catch (const std::exception &e)
    {
        std::cerr << e.what() << '\n';
    }
}

void GenUser(std::vector<Student> &studVector, int size, int hw)
{
    for (int i = 0; i < size; i++)
    {
        Student temp;
        temp.set_Name(nameList[RandGrade() - 1]);
        temp.set_Surname(surnameList[RandGrade() - 1]);
        temp.clear_Hw();
        for (int j = 0; j < hw; j++)
            temp.set_Hw(RandGrade());
        temp.set_ExRes(RandGrade());
        temp.set_Avg(temp.Average());
        temp.set_Med(temp.Median());
        studVector.push_back(temp);
    }
}

void CinError()
{
    std::cin.clear();
    std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
    throw std::runtime_error("Klaidinga ivestis");
}