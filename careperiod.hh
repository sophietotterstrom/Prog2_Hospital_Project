/* Class CarePeriod
 * ----------
 * COMP.CS.110 SPRING 2021
 * ----------
 * Class for describing a patient's care period in hospital.
 *
 * Note: Students need to implement almost all of this class by themselves.
 * ----------
 * Author information:
 * Name: Sophie Tötterström
 * Student ID: 050102822
 * Username: knsoto
 * Email: sophie.totterstrom@tuni.fi
*/

#ifndef CAREPERIOD_HH
#define CAREPERIOD_HH

#include "person.hh"
#include "date.hh"
#include <string>
#include <set>

class CarePeriod
{
public:
    // Constructor, start date given as a string (ddmmyyyy).
    CarePeriod(const string& start, Person* patient);

    // Constructor, start date given as a Date object.
    CarePeriod(const Date& start, Person* patient);

    // Destructor.
    ~CarePeriod();

    // More public methods

    //Sets the end date of a care period
    void set_end_date(const Date& end);

    // Assigns a staff member to a care period
    void assign_staff_member(Person* staff_member);

    // Returns start date
    Date get_start_date();

    // Returns end date
    Date get_end_date();

    // Returns a set of staff member names as strings.
    set<string> get_staff_name_set();

    // Prints the name of the patient on this Care Period
    void print_patient_name();

private:
    Person* patient_;
    Date start_;
    Date end_;
    set<Person*> staff_members_;
};

#endif // CAREPERIOD_HH
