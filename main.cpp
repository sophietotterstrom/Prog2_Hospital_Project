/* Main program
 * ----------
 * COMP.CS.110 SPRING 2021
 * ----------
 * Initializes a hospital object and runs the CLI using that object.
 * After running, deletes the object and returns EXIT_SUCCESS.
 * ----------
 * Author information:
 * Name: Sophie Tötterström
 * Student ID: 050102822
 * Username: knsoto
 * Email: sophie.totterstrom@tuni.fi
*/

#include "cli.hh"
#include "hospital.hh"
#include <string>

using namespace std;

const string PROMPT = "Hosp> ";


int main()
{
    Hospital* hospital = new Hospital();
    Cli cli(hospital, PROMPT);
    while ( cli.exec() ){}

    delete hospital;
    return EXIT_SUCCESS;
}
