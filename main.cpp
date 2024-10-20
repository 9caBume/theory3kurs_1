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
        cout << fullName << " ";
    }
};

class Student : public Person 
{
public:
    string groupNumber;
    string specialty;
    string curr_course;
    string averageScore;

    Student(const string& name, const string& group, const string& spec, const string& curr, const string& score)
            : Person(name), groupNumber(group), specialty(spec), curr_course(curr), averageScore(score) {}
    Student(): Person(), groupNumber("Пусто"), specialty("Пусто"), curr_course("0"), averageScore("0") {}
    Student(const Student& other) 
            : Person(other), groupNumber(other.groupNumber), specialty(other.specialty), curr_course(other.curr_course), averageScore(other.averageScore) {}
    ~Student() {}
    
    void saveToFile(ofstream& file) const override 
    {
        file << "Student" << endl;
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
        cout << groupNumber << " " << specialty << " " << curr_course << " " << averageScore;
    }
};

class Teacher : public Person 
{
public:
    string disciplines;
    string totalStudents;


    Teacher(const string& name, const string& disciplinesList, const string& students)
            : Person(name), disciplines(disciplinesList), totalStudents(students) {}
    Teacher() : Person(), disciplines("Пусто"), totalStudents("0") {}
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
    
    void printInfo() const
    {
        Person::printInfo();
        cout << disciplines << " " << totalStudents;
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
    
    void printInfo() const
    {
        Person::printInfo();
        cout << departmentName << " " << telephone << " " << borders;
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
        va_start(mas, tip);
        if (tip == "Student")
        {
            obj = new Student(va_arg(mas, const char*), va_arg(mas, const char*), va_arg(mas, const char*), va_arg(mas, const char*), va_arg(mas, const char*));
        }
        else if (tip == "Teacher")
        {
            obj = new Teacher(va_arg(mas, const char*), va_arg(mas, const char*), va_arg(mas, const char*));
        }
        else if (tip == "DepartmentHead")
        {
            obj = new DepartmentHead(va_arg(mas, const char*), va_arg(mas, const char*), va_arg(mas, const char*), va_arg(mas, const char*));
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
    
    Keeper() : data(new VUZ[1]), capacity(1), size(0) {}

    
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
            throw out_of_range("Index out of bounds");
        }

        
        for (size_t i = index; i < size - 1; i++) {
            data[i] = data[i + 1];
        }
        capacity--;
        size--;
    }

    
    VUZ& operator[](size_t index) 
    {
        if (index >= size) 
        {
            throw std::out_of_range("Index out of bounds");
        }
        return data[index];
    }

    
    bool empty() const 
    {
        return size == 0;
    }

    
    size_t getSize() const 
    {
        return size;
    }

    
    void resize(size_t newCapacity) 
    {
        
        VUZ* newData = new VUZ[newCapacity];

        
        for (size_t i = 0; i < size; i++) 
        {
            newData[i] = data[i];
        }

        
        delete[] data;

        
        data = newData;
        capacity = newCapacity;
    }
    
    void prints() const
    {
        for(int i =0; i < capacity; ++i)
        {
            cout << data[i].typ << ": ";
            data[i].obj->printInfo();
            cout << endl;
        }
    }
    
    void load(string f) const
    {
        ifstream out;
        out.open(f);
        for(int i = 0; i < capacity; ++i)
        {
            data[i].obj->loadFromFile(out);
        }
        out.close();
    }
    
    void save(string f) const
    {
        ofstream in;
        in.open(f);
        for(int i = 0; i < capacity; ++i)
        {
            data[i].obj->saveToFile(out);
        }
        in.close();
    }
};

int main() 
{
    Keeper baza;
    string k1, k2, k3, k4, k5;
    string v;
    string n2;
    for(;;)
    {
        cout << "Введите: 1 - Добавить, 2 - Просмотреть, 3 - Удалить, 4 - Загрузка с файла, 5 - Сохранение, Остальное - Выйти" << endl;
        int n;
        cin >> n;
        switch(n)
        {
            case 1:
                cout << "1 - Студент, 2 - Учитель, 3 - Департментнтнт" << endl;
                cin >> n2;
                if (n2 == "1")
                {
                    cout << "Введите имя" << endl;
                    cin >> k1;
                    cout << "Введите номер группы" << endl;
                    cin >> k2;
                    cout << "Введите специальность" << endl;
                    cin >> k3;
                    cout << "Введите текущий курс" << endl;
                    cin >> k4;
                    cout << "Введите средний балл" << endl;
                    cin >> k5;
                    VUZ temp("Student", k1.c_str(), k2.c_str(), k3.c_str(), k4.c_str(), k5.c_str());
                    baza.add(temp);
                }
                
                else if (n2 == "2")
                {
                    cout << "Введите имя" << endl;
                    cin >> k1;
                    cout << "Введите дисциплины" << endl;
                    cin >> k2;
                    cout << "Введите количество студентов" << endl;
                    cin >> k3;
                    VUZ temp("Teacher", k1.c_str(), k2.c_str(), k3.c_str());
                    baza.add(temp);
                }
                else if (n2 == "3")
                {
                    cout << "Введите имя" << endl;
                    cin >> k1;
                    cout << "Введите должность" << endl;
                    cin >> k2;
                    cout << "Введите телефон" << endl;
                    cin >> k3;
                    cout << "Введите область ответственности" << endl;
                    cin >> k4;
                    VUZ temp("DepartmentHead", k1.c_str(), k2.c_str(), k3.c_str(), k4.c_str());
                    baza.add(temp);
                }
                break;
            case 2:
                baza.prints();
                break;
            case 3:
                cout << "Введите индекс, который удалить" << endl;
                cin >> n2;
                baza.erase(stoi(n2));
                break;
            case 4:
                baza.load("qwerty");
                break;
            case 5:
                baza.save("qwerty");
            default:
                cout << "Пока!";
                return 0;
        }
    }
    return 0;
}