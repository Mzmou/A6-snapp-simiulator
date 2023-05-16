#include <iostream>
#include <vector>
#include <sstream>
#include <map>
#include <bits/stdc++.h>
using namespace std;
const string INVALID_ARGUMENTS = "INVALID_ARGUMENTS";
const string MISSION_NOT_FOUND = "MISSION_NOT_FOUND";
const string delim = " ";
const string DRIVER_MISSION_NOT_FOUND = "DRIVER_MISSION_NOT_FOUND";
const string DUPLICATE_MISSION_ID = "DUPLICATE_MISSION_ID";

class Exception
{
public:
    Exception(string s) { set_err_sentence(s); }
    void print_error() { cout << err_sentence << '\n'; }

protected:
    string err_sentence;
    void set_err_sentence(string s) { err_sentence = s; }
};
class InvalidArgument : public Exception
{
public:
    InvalidArgument(string s) : Exception(s) { set_err_sentence(s); }
};
class MissionNotFound : public Exception
{
public:
    MissionNotFound(string s) : Exception(s) { set_err_sentence(s); }
};
class DriverMissionNotFound : public Exception
{
public:
    DriverMissionNotFound(string s) : Exception(s) { set_err_sentence(s); }
};
class DuplicateMissionId : public Exception
{
public:
    DuplicateMissionId(string s) : Exception(s) { set_err_sentence(s); }
};
class Mission
{
public:
    string get_mission_id() { return mission_id; }
    int get_start_time_stamp() { return start_time_stamp; }
    int get_end_time_stamp() { return end_time_stamp; }
    void set_reward(int r) { reward = r; }
    Mission(string mission_id_str_form, string start_time_stamp_str_form, string end_time_stamp_str_form, string r);
    Mission() { set_reward(0); }
    void print_mission();
    void print_mission(long long int end_time_stamp_);
    virtual void calculate_mission(long long int start_time_stamp_, long long int end_time_stamp_, int distance_) = 0;
    bool check_in_interval(long long int start_time_stamp_, long long int end_time_stamp_);
    string get_status() { return status; }

protected:
    string mission_id;
    void set_status(string status_) { status = status_; }
    // string start_time_stamp;
    // string end_time_stamp;
    long long int start_time_stamp;
    long long int end_time_stamp;
    int reward;
    int id;
    string status;
};
class distance_mission : public Mission
{

private:
    int distance;

public:
    void set_distance(int distance_) { distance = distance_; }
    int get_distance() { return distance; }
    distance_mission(string mission_id_str_form, string start_time_stamp_str_form, string end_time_stamp_str_form, string distance_, string reward_) : Mission(mission_id_str_form, start_time_stamp_str_form, end_time_stamp_str_form, reward_)
    {
        if (stoi(distance_) < 0 || distance_ == "")
            throw INVALID_ARGUMENTS;
        set_distance(stoi(distance_));
    }
    ~distance_mission();

    void calculate_mission(long long int start_time_stamp_, long long int end_time_stamp_, int distance_);
};
class time_mission : public Mission
{

private:
    int time;

public:
    void set_time(int time_) { time = time_; }
    int get_time() { return time; }
    time_mission(string mission_id_str_form, string start_time_stamp_str_form, string end_time_stamp_str_form, string time_, string reward_)
        : Mission(mission_id_str_form, start_time_stamp_str_form, end_time_stamp_str_form, reward_)
    {
        if (stoi(time_) < 0 || time_ == "")
            throw INVALID_ARGUMENTS;
        set_time(stoi(time_));
    }
    time_mission()
    {
        set_time(0);
    }
    ~time_mission();

    virtual void calculate_mission(long long int start_time_stamp_, long long int end_time_stamp_, int distance_);
};
class count_mission : public Mission
{

private:
    int count;

public:
    void set_count(int count_) { count = count_; }
    int get_count() { return count; }
    count_mission(string mission_id_str_form, string start_time_stamp_str_form, string end_time_stamp_str_form, string count_, string reward_)
        : Mission(mission_id_str_form, start_time_stamp_str_form, end_time_stamp_str_form, reward_)
    {
        if (stoi(count_) < 0 || count_ == "")
            throw INVALID_ARGUMENTS;
        set_count(stoi(count_));
    }

    void calculate_mission(long long int start_time_stamp_, long long int end_time_stamp_, int distance_);
    ~count_mission();
};
class Driver
{
public:
    Driver(string id_, Mission *mission_)
    {
        driver_id = id_;
        add_misssion_assignment(mission_);
    }
    int get_number_of_missions() { return all_mission.size(); }
    string get_id() { return driver_id; }
    void add_misssion_assignment(Mission *mission_)
    {
        all_mission.push_back(mission_);
    }
    vector<Mission *> get_all_missions() { return all_mission; }

    vector<map<Mission *, vector<long long int>>> end_times;

private:
    string driver_id;
    vector<Mission *> all_mission;
};
// template<class T>
class DataBase
{
public:
    void add_count_mission(count_mission *c) { count_mission_data.push_back(c); }
    void add_time_mission(time_mission *c) { time_mission_data.push_back(c); }
    void add_distance_mission(distance_mission *c) { distance_mission_data.push_back(c); }
    void assign_mission(string mission_id_, string driver_id);
    vector<string> read_input(int number_of_arguments);
    vector<Driver *> get_drivers_data() { return Drivers_data; }
    Mission *check_mission(string mission_id_);
    void check_duplicate_id(string mission_id);
    template <typename T>
    void add_mission(vector<string> arguments)
    {
        try
        {
            // vector<string> arguments = read_input(6);
            //  cout << "Id is " << arguments[1] << '\n';
            check_duplicate_id(arguments[1]);
            if (stoll(arguments[2]) < stol(arguments[3]))
                throw InvalidArgument(INVALID_ARGUMENTS);
            total_mission.push_back(new T(arguments[1], arguments[2], arguments[3], arguments[4], arguments[5]));
        }
        catch (DuplicateMissionId &mission_error)
        {
            mission_error.print_error();
        }
    }

    void add_driver_mission(string id, Mission *mission_);
    Driver *check_driver(string is);
    vector<count_mission *> get_count_mission_data() { return count_mission_data; }
    vector<Mission *> total_mission;
    void show_mission_status(string driver_id_);
    void record_drive(vector<string> arguments);

private:
    vector<count_mission *> count_mission_data;
    vector<distance_mission *> distance_mission_data;
    vector<time_mission *> time_mission_data;
    // friend ostream &operator<<(ostream &out, vector<count_mission *> count_mission_data);
    vector<Driver *> Drivers_data;
};
/*

*/
void DataBase::record_drive(vector<string> arguments)
{

    Driver *target_driver = check_driver(arguments[3]);
    vector<Mission *> target_missions = target_driver->get_all_missions();
    target_driver->end_times.resize(target_missions.size());
    for (int i = 0; i < target_missions.size(); i++)
    {
        cout << "completed mission for driver " << arguments[3] << ":\n";
        if (target_missions[i]->check_in_interval(stoll(arguments[1]), stoll(arguments[2])) && target_missions[i]->get_status() == "ongoing")
        {
            //  cout << "the interval is ok\n";
            target_missions[i]->calculate_mission(stoll(arguments[1]), stoll(arguments[2]), stoi(arguments[4]));
            target_driver->end_times[i][target_missions[i]].push_back(stoll(arguments[2]));
            if (target_missions[i]->get_status() == "completed")
            {
                vector<long long int> v = target_driver->end_times[i][target_missions[i]];
                //  *max_element(v.begin(), v.end());
                target_missions[i]->print_mission(*max_element(v.begin(), v.end()));
                cout << '\n';
            }
        }
    }
    /*


    cout << "completed mission for driver " << arguments[3] << ":\n";
    for (int i = 0; i < target_missions.size(); i++)
    {
        if (target_missions[i]->get_status() == "completed")
        {
            vector<long long int> v = target_driver->end_times[i][target_missions[i]];
            //  *max_element(v.begin(), v.end());
            target_missions[i]->print_mission(*max_element(v.begin(), v.end()));
        }
    }
    for (int i = target_missions.size() - 1; i >= 0; i--)
    {
        if (target_missions[i]->get_status() == "completed")
        {
            target_missions.erase(target_missions.begin() + i);
            target_driver->end_times.erase(target_driver->end_times.begin() + i);
        }
    }
    */
}

void distance_mission::calculate_mission(long long int start_time_stamp_, long long int end_time_stamp_, int distance_)
{
    distance = distance - distance_;
    if (distance <= 0)
        set_status("completed");
}
void time_mission::calculate_mission(long long int start_time_stamp_, long long int end_time_stamp_, int distance_)
{
    time = time - (start_time_stamp_ - end_time_stamp_);
    if (time <= 0)
        set_status("completed");
}
void count_mission::calculate_mission(long long int start_time_stamp_, long long int end_time_stamp_, int distance_)
{
    count = count - 1;
    if (count <= 0)
        set_status("completed");
}
void DataBase::show_mission_status(string driver_id_)
{
    try
    {
        Driver *target_driver = check_driver(driver_id_);
        vector<Mission *> target_mission = target_driver->get_all_missions();
        for (int i = 0; i < target_mission.size(); i++)
        {
            target_mission[i]->print_mission();
        }
    }
    catch (string Error)
    {
        std::cerr << Error << '\n';
    }
}
void Mission::print_mission()
{
    cout << "mission " << mission_id << ":" << '\n';
    cout << "start_time_stamp: " << start_time_stamp << '\n';
    cout << "end_time_stamp: " << end_time_stamp << '\n';
    cout << "reward: " << reward << '\n';
    cout << "status: "
         << get_status() << '\n';
}

void Mission::print_mission(long long int end_time_stamp_)
{
    cout << "mission " << mission_id << ":" << '\n';
    cout << "start_time_stamp: " << start_time_stamp << '\n';
    cout << "end_time_stamp: " << end_time_stamp_ << '\n';
    cout << "reward: " << reward << '\n';
}
Driver *DataBase ::check_driver(string id)
{
    for (int i = 0; i < Drivers_data.size(); i++)
    {
        if (Drivers_data[i]->get_id() == id)
            return Drivers_data[i];
    }
    throw DRIVER_MISSION_NOT_FOUND;
}

Mission *DataBase::check_mission(string mission_id_)
{
    for (int i = 0; i < total_mission.size(); i++)
    {
        if (total_mission[i]->get_mission_id() == mission_id_)
            return total_mission[i];
    }
    throw MissionNotFound(MISSION_NOT_FOUND);
}
void DataBase::add_driver_mission(string id, Mission *mission_)
{
    for (int i = 0; i < Drivers_data.size(); i++)
    {
        if (Drivers_data[i]->get_id() == id)
        {

            Drivers_data[i]->add_misssion_assignment(mission_);
            return;
        }
    }

    Drivers_data.push_back(new Driver(id, mission_));
}
void DataBase::assign_mission(string mission_id_, string driver_id_)
{

    Mission *mission_target = check_mission(mission_id_);
    add_driver_mission(driver_id_, mission_target);
}
/*


template <typename T>
void DataBase ::add_mission()
{
    string mission_id_, start_time_stamp_, end_time_stamp_, distance_, mission_quality_;
    cin >> mission_id_ >> start_time_stamp_ >> end_time_stamp_ >> distance_ >> mission_quality_;
    total_mission.push_back(new T(mission_id_, start_time_stamp_, end_time_stamp_, distance_, mission_quality_));
}
*/

void DataBase ::check_duplicate_id(string mission_id_)
{

    for (int i = 0; i < total_mission.size(); i++)
    {
        if (total_mission[i]->get_mission_id() == mission_id_)
        {
            throw DuplicateMissionId(DUPLICATE_MISSION_ID);
        }
    }
}
Mission::Mission(string mission_id_str_form, string start_time_stamp_str_form, string end_time_stamp_str_form, string reward_)
{
    // if (mission_id == "" || start_time_stamp_str_form == "" || end_time_stamp_str_form == "" || reward_ == "")
    //  throw INVALID_ARGUMENTS;
    mission_id = mission_id_str_form;
    start_time_stamp = stoll(start_time_stamp_str_form);
    end_time_stamp = stoll(end_time_stamp_str_form);
    status = "ongoing";
    set_reward(stoi(reward_));
    if (end_time_stamp < start_time_stamp || reward < 0)
        throw INVALID_ARGUMENTS;
}
vector<string> DataBase::read_input(int number_of_arguments)
{
    string arguments_str_form;
    getline(cin, arguments_str_form);
    stringstream arguments_str_form_ss(arguments_str_form);
    vector<string> arguments;
    string token;
    // int space_counter = 0;
    // size_t pos = 0;
    // int i = 0;
    while (getline(arguments_str_form_ss, token, ' '))
    {
        arguments.push_back(token);
    }
    // string mission_id_ = "", start_time_stamp_ = "", end_time_stamp_ = "", distance_ = "", mission_quality_ = "";
    if (arguments.size() < number_of_arguments)
        throw InvalidArgument(INVALID_ARGUMENTS);
    return arguments;
}
bool Mission ::check_in_interval(long long int start_time_stamp_, long long int end_time_stamp_)
{
    if (start_time_stamp_ > start_time_stamp && end_time_stamp_ < end_time_stamp)
        return true;
    return false;
}

int main()
{
    string command;
    DataBase new_database;
    while (cin >> command)
    {

        if (command == "add_count_mission")
        {
            // string mission_id, start_time_stamp, end_time_stamp, target_number, reward;
            // cin >> mission_id >> start_time_stamp >> end_time_stamp >> target_number >> reward;
            try
            {
                vector<string> arguments = new_database.read_input(6);
                new_database.add_mission<count_mission>(arguments);
                // new_database.add_mission(new count_mission(mission_id, start_time_stamp, end_time_stamp, stoi(target_number), stoi(reward)));
            }
            catch (InvalidArgument &arguments_error)
            {
                arguments_error.print_error();
            }
            // cout << "OK";
        }
        if (command == "add_time_mission")
        {
            // string mission_id, start_time_stamp, end_time_stamp, time, reward;
            // cin >> mission_id >> start_time_stamp >> end_time_stamp >> time >> reward;
            try
            {
                // time_mission t;
                vector<string> arguments = new_database.read_input(6);
                new_database.add_mission<time_mission>(arguments);
                // new_database.add_mission(new time_mission(mission_id, start_time_stamp, end_time_stamp, stoi(time), stoi(reward)));
            }
            catch (string Error)
            {
                cout << Error << '\n';
            }
            // cout << "OK";
        }

        if (command == "add_distance_mission")
        {
            // string mission_id_, start_time_stamp_, end_time_stamp_, distance_, reward_;
            // cin >> mission_id_ >> start_time_stamp_ >> end_time_stamp_ >> distance_ >> reward_;
            try
            {
                vector<string> arguments = new_database.read_input(6);
                new_database.add_mission<distance_mission>(arguments);
                //  new_database.add_mission(new distance_mission(mission_id, start_time_stamp, end_time_stamp, stoi(distance), stoi(reward)));
            }
            catch (InvalidArgument &arguments_error)
            {
                arguments_error.print_error();
            }
            // cout << "OK";
        }
        if (command == "assign_mission")
        {
            // string mission_id = "", driver_id = "";
            // cin >> mission_id >> driver_id;
            try
            {

                vector<string> arguments = new_database.read_input(3);
                new_database.assign_mission(arguments[1], arguments[2]);
            }
            catch (InvalidArgument &arguments_error)
            {
                arguments_error.print_error();
            }
            catch (MissionNotFound &mission_error)
            {
                mission_error.print_error();
            }
        }
        if (command == "show_missions_status")
        {
            // string driver_id_ = "";
            //  cin >> driver_id_;
            vector<string> arguments = new_database.read_input(2);
            new_database.show_mission_status(arguments[1]);
        }
        if (command == "record_ride")
        {
            vector<string> arguments = new_database.read_input(5);
            new_database.record_drive(arguments);
        }
    }
}