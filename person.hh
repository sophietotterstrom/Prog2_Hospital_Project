/* Class Person
 * ----------
 * COMP.CS.110 SPRING 2021
 * ----------
 * Class for describing a person that can be a patient or a staff member
 * in hospital.
 *
 * Note: Students can change this class, but most probably they need not.
 * ----------
 * Author information:
 * Name: Sophie Tötterström
 * Student ID: 050102822
 * Username: knsoto
 * Email: sophie.totterstrom@tuni.fi
 */

#ifndef PERSON_HH
#define PERSON_HH

#include "date.hh"
#include <string>
#include <map>
#include <vector>

using namespace std;

class Person
{
public:
    // Default constructor.
    Person();

    // Constructor with an id.
    Person(const string& id);

    // Constructor with an id and a date of birth (actually useless)
    Person(const string& id, const string& date_of_birth);

    // Destructor.
    ~Person();

    // Obvious getter methods.
    string get_id() const;
    vector<string> get_medicines() const;

    // Adds a medicine for the person.
    void add_medicine(const string& name,
                      unsigned int strength,
                      unsigned int dosage);

    // Removes medicine from the person.
    void remove_medicine(const string& name);

    // Prints person's id.
    void print_id() const;

    // Prints person's medicines.
    void print_medicines(const string& pre_text) const;

    // Comparison operator, enables forming a set of Person objects.
    bool operator<(const Person& rhs) const;

private:
    string id_;          // Can be a name or any other identifier
    Date date_of_birth_; // Not actually needed

    struct Prescription
    {
        unsigned int strength_;
        unsigned int dosage_;
    };
    // Medicine names and their prescriptions
    map<string, Prescription> medicines_;
};

#endif // PERSON_HH
