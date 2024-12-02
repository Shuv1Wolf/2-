#include <iostream>
#include <vector>
#include <string>
using namespace std;

// Абстрактный базовый класс Person
class Person {
protected:
    string name;
    int age;
public:
    Person(const string& name, int age) : name(name), age(age) {}
    virtual ~Person() = default;

    string getName() const { return name; }
    int getAge() const { return age; }
};

// Класс пациента
class Patient : public Person {
private:
    string healthInfo;
public:
    Patient(const string& name, int age, const string& healthInfo)
        : Person(name, age), healthInfo(healthInfo) {}

    string getHealthInfo() const { return healthInfo; }
};

// Абстрактный класс сотрудника
class Staff : public Person {
protected:
    string position;
public:
    Staff(const string& name, int age, const string& position)
        : Person(name, age), position(position) {}
    virtual ~Staff() = default;

    string getPosition() const { return position; }
};

// Интерфейс MedSupport
class MedSupport {
public:
    virtual void provideMedicalSupport() = 0;
};

// Интерфейс PatientService
class PatientService {
public:
    virtual void servePatient(Patient& patient) = 0;
};

// Класс врача
class Doctor : public Staff, public MedSupport, public PatientService {
private:
    string specialization;
public:
    Doctor(const string& name, int age, const string& specialization)
        : Staff(name, age, "Doctor"), specialization(specialization) {}

    void provideMedicalSupport() override {
        cout << "Doctor " << name << " is providing medical support.\n";
    }

    void servePatient(Patient& patient) override {
        cout << "Doctor " << name << " is serving patient " << patient.getName() << ".\n";
    }

    string getSpecialization() const { return specialization; }
};

// Класс медсестры
class Nurse : public Staff, public MedSupport {
public:
    Nurse(const string& name, int age)
        : Staff(name, age, "Nurse") {}

    void provideMedicalSupport() override {
        cout << "Nurse " << name << " is providing medical support.\n";
    }
};

// Класс регистратора
class Receptionist : public Staff {
public:
    Receptionist(const string& name, int age)
        : Staff(name, age, "Receptionist") {}

    void registerPatient(Patient& patient) {
        cout << "Receptionist " << name << " is registering patient " << patient.getName() << ".\n";
    }
};

// Класс приема у врача
class Appointment {
private:
    Patient& patient;
    Doctor& doctor;
    string date;
public:
    Appointment(Patient& patient, Doctor& doctor, const string& date)
        : patient(patient), doctor(doctor), date(date) {}

    void displayInfo() const {
        cout << "Appointment Info:\n";
        cout << "Patient: " << patient.getName() << "\n";
        cout << "Doctor: " << doctor.getName() << " (Specialization: " << doctor.getSpecialization() << ")\n";
        cout << "Date: " << date << "\n";
    }
};

// Главный класс клиники
class Clinic {
private:
    vector<Patient> patients;
    vector<Staff*> staff;
public:
    void addPatient(const Patient& patient) {
        patients.push_back(patient);
    }

    void addStaff(Staff* member) {
        staff.push_back(member);
    }

    void listPatients() const {
        cout << "Patients in the clinic:\n";
        for (const auto& patient : patients) {
            cout << "- " << patient.getName() << ", Age: " << patient.getAge() << "\n";
        }
    }

    void listStaff() const {
        cout << "Staff in the clinic:\n";
        for (const auto& member : staff) {
            cout << "- " << member->getName() << ", Position: " << member->getPosition() << "\n";
        }
    }

    ~Clinic() {
        for (auto member : staff) {
            delete member;
        }
    }
};

int main() {
    Clinic clinic;

    // Добавляем пациентов
    Patient p1("John Doe", 30, "Healthy");
    Patient p2("Jane Smith", 25, "Flu");
    clinic.addPatient(p1);
    clinic.addPatient(p2);

    // Добавляем сотрудников
    Doctor* d1 = new Doctor("Dr. Brown", 45, "Cardiology");
    Nurse* n1 = new Nurse("Nancy", 35);
    Receptionist* r1 = new Receptionist("Alice", 28);

    clinic.addStaff(d1);
    clinic.addStaff(n1);
    clinic.addStaff(r1);

    // Выводим информацию
    clinic.listPatients();
    clinic.listStaff();

    // Прием
    Appointment app(p1, *d1, "2024-12-05");
    app.displayInfo();

    // Освобождение ресурсов автоматически в деструкторе Clinic
    return 0;
}
