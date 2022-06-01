/* Class Date
 * ----------
 * COMP.CS.110 SPRING 2021
 * ----------
 * Class for describing a date.
 *
 * Note: Students need not change this class, but they can if necessary.
 * ----------
 * Author information for the rest of the project, not this specific class:
 * Name: Sophie Tötterström
 * Email: sophie.totterstrom@tuni.fi
*/

#ifndef DATE_HH
#define DATE_HH

#include <string>

using namespace std;

class Date
{
public:
    // Default constructor.
    // Uses the default value 1 for day, month, and year.
    Date();

    // Constructor.
    // If any of the given parameter is out of sensible limits,
    // default value 1 used instead.
    Date(unsigned int day, unsigned int month, unsigned int year);

    // Constructor.
    // Assumes the parameter string to follow the format ddmmyyyy.
    Date(const string& date_as_str);

    // Destructor.
    ~Date();

    // Sets new values for the date.
    void set(unsigned int day, unsigned int month, unsigned int year);

    // Returns true if the date is a default one,
    // otherwise returns false.
    // Meant for checking if a care periods has ended or not.
    // Namely, the end date of a care period can be set only when the
    // period ends, before that it has a default value.
    bool is_default() const;

    // Advances the date with given amount of days.
    // Can't be anvanced by negative amounts.
    void advance(unsigned int days);

    // Prints the date (dd.mm.yyyy).
    void print() const;

    // Comparison operators.
    bool operator==(const Date& rhs) const;
    bool operator<(const Date& rhs) const;

private:
    // Obvious attributes.
    unsigned int day_;
    unsigned int month_;
    unsigned int year_;

    // Returns true if the year of the date is a leap year,
    // otherwise returns false.
    bool is_leap_year() const;

    // Converts a date part (day, month, year) from a string to an integer.
    // If a date part begins with zero, drops it away.
    unsigned int str_to_date_int(const string& date_part) const;
};

#endif // DATE_HH
