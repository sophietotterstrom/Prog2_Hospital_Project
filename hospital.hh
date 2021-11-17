/* Class Hospital
 * ----------
 * COMP.CS.110 SPRING 2021
 * ----------
 * Class for describing a hospital. Only a single object created from this
 * class. Implements all commands in hospital program.
 *
 * Note: Students need change this class to implement commands missing
 * in the template code.
 * ----------
 * Author information:
 * Name: Sophie Tötterström
 * Student ID: 050102822
 * Username: knsoto
 * Email: sophie.totterstrom@tuni.fi
*/

#ifndef HOSPITAL_HH
#define HOSPITAL_HH

#include "person.hh"
#include "careperiod.hh"
#include "date.hh"
#include <map>
#include <vector>

using namespace std;

// Error and information outputs
const string ALREADY_EXISTS = "Error: Already exists: ";
const string NOT_NUMERIC = "Error: Wrong type of parameters.";
const string CANT_FIND = "Error: Can't find anything matching: ";
const string STAFF_RECRUITED = "A new staff member has been recruited.";
const string PATIENT_ENTERED = "A new patient has entered.";
const string PATIENT_LEFT = "Patient left hospital, care period closed.";
const string MEDICINE_ADDED= "Medicine added for: ";
const string MEDICINE_REMOVED= "Medicine removed from: ";
const string STAFF_ASSIGNED= "Staff assigned for: ";

using Params = const vector<string>&;

class Hospital
{
public:
    // Constructor.
    Hospital();

    // Destructor.
    ~Hospital();

    // Recruits a new staff member (creates a new person object).
    void recruit(Params params);

    // Adds a patient in the hospital and creates a new care period.
    // If the person given as a parameter has never visited hospital earlier,
    // creates a new person object, otherwise just adds an existing person
    // in the newly created care period.
    void enter(Params params);

    // Removes the person given as a parameter from the hospital, and closes
    // person's care period.
    // However, the care period still exists.
    void leave(Params params);

    // Assigns the given staff member for the given patient.
    // If the patient already has the staff member assigned
    // (in the current care period), nothing happens.
    void assign_staff(Params params);

    // Adds the given medicine (name, strength, dosage) for the given patient.
    // If the given patient already has the medicine,
    // the prescription (strength, dosage) possibly changes.
    // If the given patien already has the medicine with same prescription,
    // nothing happens.
    void add_medicine(Params params);

    // Removes the given medicine from the patient.
    // If the patient does not have the medicine, nothing happens.
    void remove_medicine(Params params);

    // Prints the given patient's medicines.
    //void print_patient_medicines(Params params); // ei käytössä

    // Prints the given patient's all care periods and their current medicines,
    // i.e. those that have been added but not removed.
    void print_patient_info(Params params);

    // Prints the patients of the given staff member, i.e. those patients whose
    // care periods the given staff member has worked in.
    //void print_patients_per_staff(Params params); // ei käytössä

    // Prints the care periods of the given staff member, i.e. those
    // care periods the given staff member has worked in.
    void print_care_periods_per_staff(Params params);

    // Prints all medicines that are used by some patient visited the hospital
    // at some time, i.e. all medicines of current and earlier patients.
    void print_all_medicines(Params);

    // Prints all staff recruited in hospital.
    void print_all_staff(Params);

    // Prints all patients visited the hospital at some time, i.e. all
    // current and earlier patients.
    // More precisely, prints each patient's id and patient info
    // (in the same format as the method print_patient_info).
    void print_all_patients(Params);

    // Prints all patients currently in hospital at some time.
    // More precisely, prints each patient's id and patient info
    // (in the same format as the method print_patient_info).
    void print_current_patients(Params);

    // Sets a new value for the current date.
    void set_date(Params params);

    // Advances the current date with the given number of days.
    void advance_date(Params params);

private:
    // Obvious container attributes:

    map<string, Person*> current_patients_;
    map<string, Person*> staff_;

    // includes both past and current patients
    map<string, Person*> all_patients_;

    // patient id/name as the key, and a vector of careperiods as the value
    map<string, vector<CarePeriod*>> map_of_care_periods_;

};

#endif // HOSPITAL_HH
