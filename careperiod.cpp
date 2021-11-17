/* Class for describing a patient's care period in hospital.
 * ----------
 * COMP.CS.110 SPRING 2021
 * ----------
 * Author information:
 * Name: Sophie Tötterström
 * Student ID: 050102822
 * Username: knsoto
 * Email: sophie.totterstrom@tuni.fi
*/

#include "careperiod.hh"
#include <iostream>

using namespace std;

CarePeriod::CarePeriod(const string& start, Person* patient):
    patient_(patient), start_(start)
{
}

CarePeriod::CarePeriod(const Date &start, Person* patient):
    patient_(patient), start_(start)
{
}

CarePeriod::~CarePeriod()
{
}

void CarePeriod::set_end_date(const Date &end)
{
    end_ = end;
}

void CarePeriod::assign_staff_member(Person *staff_member)
{
    staff_members_.insert(staff_member);
}

Date CarePeriod::get_start_date()
{
    return start_;
}

Date CarePeriod::get_end_date()
{
    return end_;
}

set<string> CarePeriod::get_staff_name_set()
{
    set<string> staff_mem_names;
    for (auto& staff_mem : staff_members_)
    {
        string staff_mem_name = staff_mem->get_id();
        staff_mem_names.insert(staff_mem_name);
    }
    return staff_mem_names;
}

void CarePeriod::print_patient_name()
{
    patient_->print_id();
}
