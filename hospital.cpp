/* Class hospital
 * ----------
 * Handles different operations for each command given to the CLI.
 * Includes multiple methods to allow editing the hospital and it's members.
 * ----------
 * COMP.CS.110 SPRING 2021
 * ----------
 * Author information:
 * Name: Sophie Tötterström
 * Email: sophie.totterstrom@tuni.fi
*/

#include "hospital.hh"
#include "utils.hh"
#include <iostream>
#include <set>
#include <map>
#include <algorithm>

using namespace std;

Hospital::Hospital()
{
}

// Deconstructor
Hospital::~Hospital()
{
    // Deallocating staff
    for( map<string, Person*>::iterator
         iter = staff_.begin();
         iter != staff_.end();
         ++iter )
    {
        delete iter->second;
    }

    // Remember to deallocate patients also
    for( map<string, Person*>::iterator
         iter = all_patients_.begin();
         iter != all_patients_.end();
         ++iter )
    {
        delete iter->second;
    }
}

// Adds a new staff member
void Hospital::recruit(Params params)
{
    string specialist_id = params.at(0);
    if( staff_.find(specialist_id) != staff_.end() )
    {
        cout << ALREADY_EXISTS << specialist_id << endl;
        return;
    }
    Person* new_specialist = new Person(specialist_id);
    staff_.insert({specialist_id, new_specialist});
    cout << STAFF_RECRUITED << endl;
}

// Adds a new patient into the Hospital
void Hospital::enter(Params params)
{
    string patient_id = params.at(0);
    if(current_patients_.find(patient_id) != current_patients_.end())
    {
        cout << ALREADY_EXISTS << patient_id << endl;
        return;
    }

    // Check to see if a patient has ever entered the hospital.
    // If not, we create a new Person object and add it to both maps
    if (all_patients_.find(patient_id) == all_patients_.end())
    {
        Person* new_patient = new Person(patient_id);
        current_patients_.insert({patient_id, new_patient});
        all_patients_.insert({patient_id, new_patient});
    }
    // Else the patient is re-entering the hospital.
    // In this case we need to instead refer to a pre-existing Person object.
    else
    {
        Person* temp_person = all_patients_.at(patient_id);
        current_patients_.insert({patient_id, temp_person});
    }

    // Now we start a new care period.
    CarePeriod* new_care_period =
            new CarePeriod(utils::today, current_patients_.at(patient_id));

    // To keep track of care periods we have a class attribute with a patient
    // id as the key and a patient's care_periods as the value.

    // If a patient has previous care periods only add to the existing vector.
    if (map_of_care_periods_.find(patient_id) != map_of_care_periods_.end() )
    {
        map_of_care_periods_.at(patient_id).push_back(new_care_period);
    }
    // Else we first need to initialize the vector, add the care period to it,
    // and the insert the vector to the patient's key in the map
    else
    {
        vector<CarePeriod*> vect_of_care_periods;
        vect_of_care_periods.push_back(new_care_period);
        map_of_care_periods_.insert({patient_id, vect_of_care_periods});
    }

    cout << PATIENT_ENTERED << endl;
}

void Hospital::leave(Params params)
{
    string patient_id = params.at(0);
    if (current_patients_.find(patient_id) == current_patients_.end())
    {
        // Patient not a current patient, thus they can't leave.
        cout << CANT_FIND << patient_id << endl;
        return;
    }

    // Check the map to find the patient's care period vector.
    // Access the last one with "back()" and set the end_date to be today.
    map_of_care_periods_.at(patient_id).back()->set_end_date(utils::today);

    // Erase the patient pointer from current_patients. Patient remains in the
    // all_patients map, thus we don't release memory here.
    current_patients_.erase(patient_id);

    cout << PATIENT_LEFT << endl;
}

// Assigns staff to patients
void Hospital::assign_staff(Params params)
{
    string patient_id = params.at(1);
    string staff_id = params.at(0);

    // Checks if staff member is actually a staff member
    if (staff_.find(staff_id) == staff_.end())
    {
        cout << CANT_FIND << staff_id << endl;
        return;
    }

    // Staff can only be assigned to patients currently in the hospital.
    if (current_patients_.find(patient_id) == current_patients_.end())
    {
        cout << CANT_FIND << patient_id << endl;
        return;
    }

    // Find the staff_member object pointer
    Person* staff_mem = staff_.at(staff_id);
    // Find the last care_period of the patient, and use
    // a care period method to assign the staff member to it
    map_of_care_periods_.at(patient_id).back()->assign_staff_member(staff_mem);

    cout << STAFF_ASSIGNED << patient_id << endl;
}

void Hospital::add_medicine(Params params)
{
    string medicine = params.at(0);
    string strength = params.at(1);
    string dosage = params.at(2);
    string patient = params.at(3);
    if( not utils::is_numeric(strength, true) or
        not utils::is_numeric(dosage, true) )
    {
        cout << NOT_NUMERIC << endl;
        return;
    }
    map<string, Person*>::const_iterator
            patient_iter = current_patients_.find(patient);
    if( patient_iter == current_patients_.end() )
    {
        cout << CANT_FIND << patient << endl;
        return;
    }
    patient_iter->second->add_medicine(medicine, stoi(strength), stoi(dosage));
    cout << MEDICINE_ADDED << patient << endl;

}

void Hospital::remove_medicine(Params params)
{
    string medicine = params.at(0);
    string patient = params.at(1);
    map<string, Person*>::const_iterator
            patient_iter = current_patients_.find(patient);
    if( patient_iter == current_patients_.end() )
    {
        cout << CANT_FIND << patient << endl;
        return;
    }
    patient_iter->second->remove_medicine(medicine);
    cout << MEDICINE_REMOVED << patient << endl;
}

// Prints the patient data of one patient
void Hospital::print_patient_info(Params params)
{
    string patient_id = params.at(0);

    // If patient is not found in the all_patients_ map they've never
    // entered the hospital and don't have any info to print
    if (all_patients_.find(patient_id) == all_patients_.end())
    {
        cout << CANT_FIND << patient_id << endl;
        return; // exit the method
    }
    else
    {
        // Loops thrpugh a vector of the patient's care periods
        for (CarePeriod*& care_period : map_of_care_periods_.at(patient_id))
        {
            cout << "* Care period: ";
            care_period->get_start_date().print();
            cout << " - ";

            Date end_date = care_period->get_end_date();
            // If is_default returns false, the care period has ended
            if (not end_date.is_default())
            {
                end_date.print();
            }

            cout << endl << "   - Staff: ";

            // If the returned set is empty, no staff was assigned
            if (care_period->get_staff_name_set().empty())
            {
                cout << "None";
            }
            else
            {
                set<string> names = care_period->get_staff_name_set();
                int index = 1;
                for (string name : names)
                {
                    if (index == (int)names.size())
                    {
                        // last element in the set
                        cout << name;
                    }
                    else {
                        cout << name << " ";
                    }
                    // Increment the index after each name has been printed
                    index++;
                }
            }
            cout << endl;
        }

        cout << "* Medicines:";
        all_patients_.at(patient_id)->print_medicines(" - ");
    }
}

// Prints all care periods a staff member has worked
void Hospital::print_care_periods_per_staff(Params params)
{
    string staff_member_id = params.at(0);

    if (staff_.find(staff_member_id)==staff_.end())
    {
        cout << CANT_FIND << staff_member_id << endl;
    }
    else
    {
        // Initialize a vector of the care periods a staff member is in
        vector<CarePeriod*> all_care_periods;

        // Loops through the a map with patients as keys and
        // a vector of a patient's care periods as the value
        for (auto& key_value_pair : map_of_care_periods_)
        {
            // Loops through a vector of single patient's care periods
            for (auto& care_period : key_value_pair.second)
            {
                // If the staff member is in this specific care periods staff
                // members, add the care period to the vector of care periods
                set<string> staff_set = care_period->get_staff_name_set();
                if (staff_set.find(staff_member_id) != staff_set.end())
                {
                    all_care_periods.push_back(care_period);
                }
            }
        }
        if (all_care_periods.empty())
        {
            cout << "None" << endl;
        }
        else
        {
            // Reverse the vector to achieve the right printing order
            reverse(all_care_periods.begin(), all_care_periods.end());

            for (CarePeriod*& care_per : all_care_periods)
            {
                care_per->get_start_date().print();
                cout << " - ";

                // If the end_date is not default, print it normally
                if (not care_per->get_end_date().is_default())
                {
                    care_per->get_end_date().print();
                }
                cout << endl << "* Patient: ";
                care_per->print_patient_name();
                cout << endl;
            }
        }
    }
}

// Prints all medicines and patients taking them
void Hospital::print_all_medicines(Params)
{
    map<string, set<string>> map_of_meds_and_patients;

    // Loops through all patients who have ever entered the hospital
    for (auto& person : all_patients_)
    {
        // Call the method get_medicines on a Person object
        vector<string> patients_meds = person.second->get_medicines();

        // Loops through all meds in a set of meds the patient is taking
        for (string& med : patients_meds)
        {
            // Check if the med is in the map, if not
            if (map_of_meds_and_patients.find(med)
                    == map_of_meds_and_patients.end())
            {
                // Initialize a set of patients taking that med,
                // add the first patient to that set, and insert it to the map
                set<string> set_of_patients;
                set_of_patients.insert(person.first);
                map_of_meds_and_patients
                        .insert({med, set_of_patients});
            }
            // Else the med is already in the map,
            // only add the patient to the set
            else
            {
                map_of_meds_and_patients.at(med).insert(person.first);
            }
        }
    }
    // Now the map_of_meds_and_set_of_patients_taking_them includes all
    // necessary data, and we can proceed the printing it out

    // If no one in the hospital is taking any medications
    if (map_of_meds_and_patients.empty())
    {

        cout << "None" << endl;
    }
    else
    {
        for (auto& key_and_value_pair : map_of_meds_and_patients)
        {
            cout << key_and_value_pair.first << " prescribed for" << endl;

            for (string person : key_and_value_pair.second)
            {
                cout << "* " << person << endl;
            }
        }
    }
}

void Hospital::print_all_staff(Params)
{
    if( staff_.empty() )
    {
        cout << "None" << endl;
        return;
    }
    for( map<string, Person*>::const_iterator iter = staff_.begin();
         iter != staff_.end();
         ++iter )
    {
        cout << iter->first << endl;
    }
}

// Prints all patients and calls the print_patient_data - method on them
void Hospital::print_all_patients(Params)
{
    if (all_patients_.empty()) {
        cout << "None" << endl;
    }
    else
    {
        for (auto& person : all_patients_)
        {
            cout << person.first << endl; // prints the name
            // Make a temporary vector since the CLI takes input in one
            vector<string> temp_vect_with_name;
            temp_vect_with_name.push_back(person.first);
            print_patient_info(temp_vect_with_name);
        }
    }
}

// Prints current patient and calls the print_patient_data
void Hospital::print_current_patients(Params)
{
    if (current_patients_.empty()) {
        cout << "None" << endl;
    }
    else {
        for (auto& person : current_patients_)
        {
            cout << person.first << endl; // prints the name
            // Make a temporary vector since the CLI takes input in one
            vector<string> temp_vect_with_name;
            temp_vect_with_name.push_back(person.first);
            print_patient_info(temp_vect_with_name);
        }
    }
}

void Hospital::set_date(Params params)
{
    string day = params.at(0);
    string month = params.at(1);
    string year = params.at(2);
    if( not utils::is_numeric(day, false) or
        not utils::is_numeric(month, false) or
        not utils::is_numeric(year, false) )
    {
        cout << NOT_NUMERIC << endl;
        return;
    }
    utils::today.set(stoi(day), stoi(month), stoi(year));
    cout << "Date has been set to ";
    utils::today.print();
    cout << endl;
}

void Hospital::advance_date(Params params)
{
    string amount = params.at(0);
    if( not utils::is_numeric(amount, true) )
    {
        cout << NOT_NUMERIC << endl;
        return;
    }
    utils::today.advance(stoi(amount));
    cout << "New date is ";
    utils::today.print();
    cout << endl;
}
