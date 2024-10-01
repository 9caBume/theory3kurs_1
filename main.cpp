#include <iostream>
#include <fstream>
#include <string>

using namespace std;

class Keeper{};//пока пусто, конструктор пустого понадобится

class Person 
{
public:
    string fullName;
    string birthDate; //не нужно


    Person(const string& name, const string& date) : fullName(name), birthDate(date) {}
    Person() : fullName("Пусто"), birthDate("Пусто") {}
    Person(const Person& other) : fullName(other.fullName), birthDate(other.birthDate) {}
    ~Person() {}
    virtual void printInfo() const = 0;
    
    virtual void saveToFile(ofstream& file) const 
    {
        file << fullName << endl;
        file << birthDate << endl;
    }

    virtual void loadFromFile(ifstream& file) 
    {
        getline(file, fullName);
        getline(file, birthDate);
    }
};

class Student : public Person 
{
public:
    string groupNumber;
    string specialty;
    float averageScore;
    //+курс

    Student(const string& name, const string& date, const string& group, const string& spec, float score)
            : Person(name, date), groupNumber(group), specialty(spec), averageScore(score) {}
    Student(): Person(), groupNumber("Пусто"), specialty("Пусто"), averageScore(0) {}
    Student(const Student& other) 
            : Person(other), groupNumber(other.groupNumber), specialty(other.specialty), averageScore(other.averageScore) {}
    ~Student() {}

    void printInfo() const override 
    {
        cout << "--- Student Info ---" << endl;
        cout << "Full Name: " << fullName << endl;
        cout << "Birth Date: " << birthDate << endl;
        cout << "Group Number: " << groupNumber << endl;
        cout << "specialtye: " << specialty << endl;
        cout << "Average Score: " << averageScore << endl;
    }
    
    void saveToFile(ofstream& file) const override 
    {
        Person::saveToFile(file);
        file << groupNumber << endl;
        file << specialty << endl;
        file << averageScore << endl;
    }

    void loadFromFile(ifstream& file) override 
    {
        Person::loadFromFile(file);
        getline(file, groupNumber);
        getline(file, specialty);
        file >> averageScore;
        file.ignore();
    }
};

class Teacher : public Person 
{
public:
    string disciplines;
    int totalStudents;


    Teacher(const string& name, const string& date, const string& disciplinesList, int students)
            : Person(name, date), disciplines(disciplinesList), totalStudents(students) {}
    Teacher() : Person(), disciplines("Пусто"), totalStudents(0) {}
    Teacher(const Teacher& other) : Person(other), disciplines(other.disciplines), totalStudents(other.totalStudents) {}
    ~Teacher() {}
    
    

    void printInfo() const override 
    {
        cout << "--- Teacher Info ---" << endl;
        cout << "Full Name: " << fullName << endl;
        cout << "Birth Date: " << birthDate << endl;
        cout << "Disciplines: " << disciplines << endl;
        cout << "Total Students: " << totalStudents << endl;
    }
    
    void saveToFile(ofstream& file) const override 
    {
        Person::saveToFile(file);
        file << disciplines << endl;
        file << totalStudents << endl;
    }

    void loadFromFile(ifstream& file) override 
    {
        Person::loadFromFile(file);
        getline(file, disciplines);
        file >> totalStudents;
        file.ignore();
    }
};

class DepartmentHead : public Person 
{
public:
    string departmentName;
    string telephone; // new
    string borders; // new


    DepartmentHead(const string& name, const string& date, const string& department)
            : Person(name, date), departmentName(department) {}
    DepartmentHead() : Person(), departmentName("Пусто") {}
    DepartmentHead(const DepartmentHead& other) 
            : Person(other), departmentName(other.departmentName) {}
    ~DepartmentHead() {}

    void printInfo() const override 
    {
        cout << "--- Department Head Info ---" << endl;
        cout << "Full Name: " << fullName << endl;
        cout << "Birth Date: " << birthDate << endl;
        cout << "Department Name: " << departmentName << endl;
    }
    
    void saveToFile(ofstream& file) const override {
        Person::saveToFile(file);
        file << departmentName << endl;
    }

    void loadFromFile(ifstream& file) override {
        Person::loadFromFile(file);
        file >> departmentName;
        file.ignore();
    }
};

class VUZ : public DepartmentHead, public Teacher, public Student
{
    list_students = Keeper();
    list_teachers = Keeper();
    list_department = Keeper();
};

int main() 
{
    return 0;
}
