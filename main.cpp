#include <iostream>
#include <vector>
#include <sstream>
using namespace std;
const string INVALID_ARGUMENTS = "INVALID_ARGUMENTS";
const string MISSION_NOT_FOUND = "MISSION_NOT_FOUND";
const string delim = " ";
const string DRIVER_MISSION_NOT_FOUND = "DRIVER_MISSION_NOT_FOUND";

class Exception
{
public:
    Exception(string s) { set_err_sentence(s); }
    void print_error() { cout << err_sentence; }

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
class Mission
{
public:
    string get_mission_id() { return mission_id; }
    int get_start_time_stamp() { return start_time_stamp; }
    int get_end_time_stamp() { return end_time_stamp; }
    void set_reward(int r) { reward = r; }
    Mission(string mission_id_str_form, string start_time_stamp_str_form, string end_time_stamp_str_form, string r);
    Mission() { set_reward(0); }
    virtual void print_mission() = 0;

protected:
    string mission_id;
    // string start_time_stamp;
    // string end_time_stamp;
    long int start_time_stamp;
    long int end_time_stamp;
    int reward;
    int id;
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
    virtual void print_mission();
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
    void virtual print_mission();
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
    virtual void print_mission();
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
    string get_id() { return driver_id; }
    void add_misssion_assignment(Mission *mission_)
    {
        all_mission.push_back(mission_);
    }
    vector<Mission *> get_all_missions() { return all_mission; }

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
    vector<Driver *> get_drivers_data() { return Drivers_data; }
    Mission *check_mission(string mission_id_);
    template <typename T>
    void add_mission()
    {
        string arguments_str_form;
        getline(cin, arguments_str_form);
        stringstream arguments_str_form_ss(arguments_str_form);

        vector<string> arguments;
        string token;
        int space_counter = 0;
        size_t pos = 0;
        int i = 0;
        while (getline(arguments_str_form_ss, token, ' '))
        {
            arguments.push_back(token);
        }
        // string mission_id_ = "", start_time_stamp_ = "", end_time_stamp_ = "", distance_ = "", mission_quality_ = "";
        if (arguments.size() < 6)
            throw INVALID_ARGUMENTS;
        // cout<<"jdsj"<< arguments.size()<<'\n';
        // for(int i=0;i<arguments.size();i++)
        // cout<<arguments[i]<<' ';
        // cin >> mission_id_ >> start_time_stamp_ >> end_time_stamp_ >> distance_ >> mission_quality_;
        // arguments.resize(6);
        // cout<<arguments[1]<<"jdsfjsfd\n";

        total_mission.push_back(new T(arguments[1], arguments[2], arguments[3], arguments[4], arguments[5]));
    }

    void add_driver_mission(string id, Mission *mission_);
    Driver *check_driver(string is);
    vector<count_mission *> get_count_mission_data() { return count_mission_data; }
    vector<Mission *> total_mission;
    void show_mission_status(string driver_id_);

private:
    vector<count_mission *> count_mission_data;
    vector<distance_mission *> distance_mission_data;
    vector<time_mission *> time_mission_data;
    // friend ostream &operator<<(ostream &out, vector<count_mission *> count_mission_data);
    vector<Driver *> Drivers_data;
};
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
void distance_mission::print_mission()
{
    cout << "mission" << mission_id << ":" << '\n';
    cout << "start_time_stamp: " << start_time_stamp << '\n';
    cout << "end_time_stamp: " << end_time_stamp << '\n';
    cout << "reward: " << reward << '\n';
    cout << "status: "
         << "completed" << '\n';
}
void count_mission::print_mission()
{
    cout << "mission" << mission_id << ":" << '\n';
    cout << "start_time_stamp: " << start_time_stamp << '\n';
    cout << "end_time_stamp: " << end_time_stamp << '\n';
    cout << "reward: " << reward << '\n';
    cout << "status: "
         << "completed" << '\n';
}
void time_mission::print_mission()
{
    cout << "mission" << mission_id << ":" << '\n';
    cout << "start_time_stamp: " << start_time_stamp << '\n';
    cout << "end_time_stamp: " << end_time_stamp << '\n';
    cout << "reward: " << reward << '\n';
    cout << "status: "
         << "completed" << '\n';
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
    throw MISSION_NOT_FOUND;
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
    try
    {
        Mission *mission_target = check_mission(mission_id_);
        add_driver_mission(driver_id_, mission_target);
    }
    catch (string Error)
    {
        cerr << Error << '\n';
    }
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

Mission::Mission(string mission_id_str_form, string start_time_stamp_str_form, string end_time_stamp_str_form, string reward_)
{
    // if (mission_id == "" || start_time_stamp_str_form == "" || end_time_stamp_str_form == "" || reward_ == "")
    //  throw INVALID_ARGUMENTS;
    mission_id = mission_id_str_form;
    start_time_stamp = stol(start_time_stamp_str_form);
    end_time_stamp = stol(end_time_stamp_str_form);
    set_reward(stoi(reward_));
    if (end_time_stamp < start_time_stamp || reward < 0)
        throw INVALID_ARGUMENTS;
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
                new_database.add_mission<count_mission>();
                // new_database.add_mission(new count_mission(mission_id, start_time_stamp, end_time_stamp, stoi(target_number), stoi(reward)));
            }
            catch (string Error)
            {
                cout << Error << '\n';
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
                new_database.add_mission<time_mission>();
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
                new_database.add_mission<distance_mission>();
                //  new_database.add_mission(new distance_mission(mission_id, start_time_stamp, end_time_stamp, stoi(distance), stoi(reward)));
            }
            catch (string Error)
            {
                cout<<Error;
            }
            // cout << "OK";
        }
        if (command == "assign_mission")
        {
            string mission_id = "", driver_id = "";
            cin >> mission_id >> driver_id;
            new_database.assign_mission(mission_id, driver_id);
        }
        if (command == "show_missions_status")
        {
            string driver_id_ = "";
            cin >> driver_id_;
        }

        // vector<count_mission *> djkj = new_database.get_count_mission_data();

        for (int i = 0; i < new_database.total_mission.size(); i++)
        {
            new_database.total_mission[i]->print_mission();
        }
        vector<Driver *> driver = new_database.get_drivers_data();
        for (int i = 0; i < driver.size(); i++)
        {
            vector<Mission *> m = driver[i]->get_all_missions();
            for (int j = 0; j < m.size(); j++)
                m[j]->print_mission();
        }
    }

    cout << "hi";
}