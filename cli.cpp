/* Class for describing a command line interpreter. Preserves all commands
 * used in hospital program.
 * ----------
 * COMP.CS.110 SPRING 2021
 * ----------
 * Author information:
 * Name: Sophie Tötterström
 * Student ID: 050102822
 * Username: knsoto
 * Email: sophie.totterstrom@tuni.fi
*/

#include "cli.hh"
#include "utils.hh"
#include <fstream>
#include <sstream>

using namespace std;

Cli::Cli(Hospital* hospital, const string& prompt):
    hospital_(hospital),
    prompt_(prompt),
    can_start(hospital != nullptr)
{
}

bool Cli::exec()
{
    if( not can_start )
    {
        cout << UNINITIALIZED << endl;
        return false;
    }
    vector<string> input;
    string cmd;
    cout << prompt_;
    getline(cin, cmd);
    input = utils::split(cmd, ' ');
    if( input.empty() )
    {
        return true;
    }
    cmd = input.front();
    pop_front(input);
    Cmd* func = find_command(cmd);
    if ( func == nullptr )
    {
        cout << UNKNOWN_CMD << endl;
        return true;
    }

    // The number of parameters of commands Quit and Help does not matter
    if ( func->name == "Quit" )
    {
        return false;
    }

    if  ( func->name == "Help" )
    {
        print_help(input);
        return true;
    }

    if ( func->params.size() != input.size() )
    {
        cout << WRONG_PARAMETERS << endl;
        return true;
    }

    if ( func->name == "Read" )
    {
        if ( not read_from_file(input.at(0)) )
        {
            cout << FILE_READING_ERROR << endl;
            return false;
        }
        else
        {
            cout << FILE_READING_OK << input.at(0) << endl;
        }
        return true;
    }

    // Call to member func ptr: (OBJ ->* FUNC_PTR)(PARAMS)
    (hospital_->*(func->func_ptr))(input);
    return true;
}

void Cli::pop_front(vector<string> &vec)
{
    vec.erase(vec.begin(), ++vec.begin());
}

Cmd *Cli::find_command(const string& cmd)
{
    string upper_cmd = cmd;
    for ( unsigned int i = 0; i < cmd.size(); ++i )
    {
        upper_cmd.at(i) = toupper(cmd.at(i));
    }
    // I didn't make this for loop, please don't take points for not passing
    // things as reference :( I didn't have the guts to edit it
    for ( auto command = cmds_.begin(); command != cmds_.end(); ++command )
    {
        for ( auto alias : command->aliases )
        {
            if ( alias == upper_cmd )
            {
                return &(*command);
            }
        }
    }
    return nullptr;
}

void Cli::print_help(const vector<string>& params)
{
    if ( params.size() != 0 )
    {
        print_cmd_info(find_command(params.at(0)), true);
        return;
    }
    for ( Cmd cmd : cmds_ )
    {
        print_cmd_info(&cmd);
    }
}

void Cli::print_cmd_info(Cmd* cmd, bool longer) const
{
    cout << cmd->name << " : " ;
    for ( auto alias : cmd->aliases )
    {
        cout << alias << " ";
    }
    cout << endl;
    if ( longer )
    {
        cout << "Params: " << endl;
        if ( cmd->params.size() == 0 )
        {
            cout << "None." << endl;
        }
        else
        {
            for ( auto param : cmd->params )
            {
                cout << param << endl;
            }
        }
    }
}

bool Cli::read_from_file(const string &filename)
{
    ifstream inputfile(filename);
    if ( not inputfile )
    {
        return false;
    }
    // Redirect the file to cin and save the old cin
    auto cinbuf = cin.rdbuf(inputfile.rdbuf());
    ostringstream unwanted_output;
    auto coutbuf = cout.rdbuf(unwanted_output.rdbuf());

    while( exec() ){}

    cin.rdbuf(cinbuf);
    cout.rdbuf(coutbuf);
    inputfile.close();

    return true;
}
