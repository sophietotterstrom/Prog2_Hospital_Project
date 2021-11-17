/* Person class
 * ----------
 * COMP.CS.110 SPRING 2021
 * ----------
 * Class models a Person object, either a staff member or patient.
 * Has methods for editing medicine, and printing.
 * ----------
 * Author information:
 * Name: Sophie Tötterström
 * Student ID: 050102822
 * Username: knsoto
 * Email: sophie.totterstrom@tuni.fi
*/

#include "person.hh"
#include <iostream>
#include <map>

using namespace std;

Person::Person()
{
}

Person::Person(const string &id):
    id_(id)
{
    date_of_birth_ = Date();
}

Person::Person(const string& id, const string& date_of_birth):
    id_(id), date_of_birth_(date_of_birth)
{
}

Person::~Person()
{
}

string Person::get_id() const
{
    return id_;
}

vector<string> Person::get_medicines() const
{
    vector<string> result;
    for( map<string, Prescription>::const_iterator
         iter = medicines_.begin();
         iter != medicines_.end();
         ++iter )
    {
        result.push_back(iter->first);
    }
    return result;
}

void Person::add_medicine(const string& name,
                          unsigned int strength,
                          unsigned int dosage)
{
    Prescription pre;
    pre.strength_ = strength;
    pre.dosage_ = dosage;
    if( medicines_.find(name) != medicines_.end() )
    {
        medicines_.at(name) = pre;
    }
    else
    {
        medicines_.insert({name, pre});
    }
}

void Person::remove_medicine(const string& name)
{
    medicines_.erase(name);
}

void Person::print_id() const
{
    cout << id_;
    //date_of_birth_.print();
    //cout << endl;
}

void Person::print_medicines(const string& pre_text) const
{
    if( medicines_.empty() )
    {
        cout << " None" << endl;
        return;
    }
    cout << endl;
    for( map<string, Prescription>::const_iterator
         iter = medicines_.begin();
         iter != medicines_.end();
         ++iter )
    {
        cout << pre_text
                  << iter->first << " "
                  << iter->second.strength_ << " mg x "
                  << iter->second.dosage_ << endl;
    }
}

bool Person::operator<(const Person &rhs) const
{
    return id_ < rhs.id_;
}

