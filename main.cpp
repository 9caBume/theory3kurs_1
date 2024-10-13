#include <iostream>
#include <fstream>
#include <string>
#include <stdarg.h>

using namespace std;



class Person 
{
public:
    string fullName;


    Person(const string& name) : fullName(name) {}
    Person() : fullName("Пусто") {}
    Person(const Person& other) : fullName(other.fullName) {}
    ~Person() {}
    
    virtual void saveToFile(ofstream& file) const 
    {
        file << fullName << endl;
    }

    virtual void loadFromFile(ifstream& file) 
    {
        getline(file, fullName);
    }
    
    virtual void printInfo() const
    {
        cout << fullName;
    }
};

class Student : public Person 
{
public:
    string groupNumber;
    string specialty;
    string curr_course;//new kurs
    string averageScore;

    Student(const string& name, const string& group, const string& spec, const string& curr, const string& score)
            : Person(name), groupNumber(group), specialty(spec), curr_course(curr), averageScore(score) {}
    Student(): Person(), groupNumber("Пусто"), specialty("Пусто"), curr_course("0"), averageScore("0") {}
    Student(const Student& other) 
            : Person(other), groupNumber(other.groupNumber), specialty(other.specialty), curr_course(other.curr_course), averageScore(other.averageScore) {}
    ~Student() {}
    
    void saveToFile(ofstream& file) const override 
    {
        Person::saveToFile(file);
        file << groupNumber << endl;
        file << specialty << endl;
        file << curr_course << endl;
        file << averageScore << endl;
    }

    void loadFromFile(ifstream& file) override 
    {
        Person::loadFromFile(file);
        getline(file, groupNumber);
        getline(file, specialty);
        getline(file, curr_course);
        getline(file, averageScore);
        file.ignore();
    }
    
    void printInfo() const
    {
        Person::printInfo();
        cout << groupNumber << endl;
    }
};

class Teacher : public Person 
{
public:
    string disciplines;
    int totalStudents;


    Teacher(const string& name, const string& disciplinesList, int students)
            : Person(name), disciplines(disciplinesList), totalStudents(students) {}
    Teacher() : Person(), disciplines("Пусто"), totalStudents(0) {}
    Teacher(const Teacher& other) : Person(other), disciplines(other.disciplines), totalStudents(other.totalStudents) {}
    ~Teacher() {}
    
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
    string telephone;
    string borders;


    DepartmentHead(const string& name, const string& department, const string& tele, const string& bord)
            : Person(name), departmentName(department), telephone(tele), borders(bord) {}
    DepartmentHead() : Person(), departmentName("Пусто"), telephone("Пусто"), borders("Пусто") {}
    DepartmentHead(const DepartmentHead& other) 
            : Person(other), departmentName(other.departmentName), telephone(other.telephone), borders(other.borders){}
    ~DepartmentHead() {}
    
    void saveToFile(ofstream& file) const override {
        Person::saveToFile(file);
        file << departmentName << endl;
        file << telephone << endl;
        file << borders << endl;
    }

    void loadFromFile(ifstream& file) override {
        Person::loadFromFile(file);
        file >> departmentName;
        file >> telephone;
        file >> borders;
        file.ignore();
    }
};

class VUZ : public DepartmentHead, public Teacher, public Student
{
    public:
    string typ;
    Person* obj;
    VUZ(const string& tip, ...) : typ(tip)
    {
        va_list mas;
        int size;
        
        if (tip == "Student")
        {
            va_start(mas, tip);
            string n = va_arg(mas, string); 
            obj = new Student(va_arg(mas, string), va_arg(mas, string), va_arg(mas, string), va_arg(mas, string), va_arg(mas, string));
        }
        else if (tip == "Teacher")
        {
            obj = new Teacher;
            size = 3;
        }
        else if (tip == "Dep")
        {
            obj = new DepartmentHead;
            size = 4;
        }
        
    }
    
    VUZ() : typ ("None") {}
};

class Keeper 
{
private:
    VUZ* data; 
    size_t capacity;
    size_t size;

public:
    
    Keeper() : data(new VUZ[10]), capacity(10), size(0) {}

    
    Keeper(size_t initialCapacity, string typee) : data(new VUZ[initialCapacity]), capacity(initialCapacity), size(0) {}

    
    ~Keeper() 
    {
        delete[] data;
    }

    
    void add(const VUZ& element) {
        
        if (size == capacity) 
        {
            resize(capacity * 2);
        }

        
        data[size] = element;
        size++;
    }

    
    void erase(size_t index) {
        if (index >= size) {
            throw std::out_of_range("Index out of bounds");
        }

        
        for (size_t i = index; i < size - 1; i++) {
            data[i] = data[i + 1];
        }
        size--;
    }

    
    VUZ& operator[](size_t index) {
        if (index >= size) {
            throw std::out_of_range("Index out of bounds");
        }
        return data[index];
    }

    
    bool empty() const {
        return size == 0;
    }

    
    size_t getSize() const {
        return size;
    }

    
    void resize(size_t newCapacity) {
        
        VUZ* newData = new VUZ[newCapacity];

        
        for (size_t i = 0; i < size; i++) {
            newData[i] = data[i];
        }

        
        delete[] data;

        
        data = newData;
        capacity = newCapacity;
    }
    
    void printInfo() const
    {
        for(int i =0; i < capacity; ++i)
        {
            cout << data[i].typ << ": ";
            data[i].obj->printInfo();
        }
    }
};

int main() 
{
    Keeper baza;
    VUZ vanya("Student", "1243", "Worker", "3", "4.2");
    baza.add(vanya);
    baza.printInfo();
    return 0;
}