/* Module Utils
 * ----------
 * COMP.CS.110 SPRING 2021
 * ----------
 * Module for different utilities needed in the program.
 * ----------
 * Author information:
 * Name: Sophie Tötterström
 * Student ID: 050102822
 * Username: knsoto
 * Email: sophie.totterstrom@tuni.fi
*/

#include "utils.hh"

using namespace std;

vector<string> utils::split( string& str, char delim )
{
    vector<string> result = {""};
    bool cont = false;
    for ( auto cha : str )
    {
        if ( cha == '"' )
        {
            cont = not cont;
        }
        else if ( cha == delim and not cont)
        {
            result.push_back("");
        }
        else
        {
            result.back().push_back(cha);
        }
    }
    if ( result.back() == "" )
    {
        result.erase(--result.end());
    }
    return result;
}

bool utils::is_numeric(string s, bool zero_allowed)
{
    if( not zero_allowed )
    {
        bool all_zeroes = true;
        for( unsigned int i = 0; i < s.length(); ++i )
        {
            if( s.at(i) != '0' )
            {
                all_zeroes = false;
            }
        }
        if( all_zeroes )
        {
            return false;
        }
    }
    for( unsigned int i = 0; i < s.length(); ++i )
    {
        if( not isdigit(s.at(i)) )
        {
            return false;
        }
    }
    return true;
}
