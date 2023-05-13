#include <iostream>
#include <vector>
using namespace std;
const string INVALID_ARGUMENTS = "INVALID_ARGUMENTS";
class Mission
{
public:
    string get_mission_id() { return mission_id; }
    int get_start_time_stamp() { return start_time_stamp; }
    int get_end_time_stamp() { return end_time_stamp; }
    void set_reward(int r) { reward = r; }
    Mission(string mission_id_str_form, string start_time_stamp_str_form, string end_time_stamp_str_form, int r);
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
    distance_mission(string mission_id_str_form, string start_time_stamp_str_form, string end_time_stamp_str_form, int distance_, int reward_) : Mission(mission_id_str_form, start_time_stamp_str_form, end_time_stamp_str_form, reward_)
    {
        if (distance_ < 0)
            throw INVALID_ARGUMENTS;
        set_distance(distance_);
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
    time_mission(string mission_id_str_form, string start_time_stamp_str_form, string end_time_stamp_str_form, int time_, int reward_)
        : Mission(mission_id_str_form, start_time_stamp_str_form, end_time_stamp_str_form, reward_)
    {
        if (time_ < 0)
            throw INVALID_ARGUMENTS;
        set_time(time_);
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
    count_mission(string mission_id_str_form, string start_time_stamp_str_form, string end_time_stamp_str_form, int count_, int reward_)
        : Mission(mission_id_str_form, start_time_stamp_str_form, end_time_stamp_str_form, reward_)
    {
        if (count_ < 0)
            throw INVALID_ARGUMENTS;
        set_count(count_);
    }
    virtual void print_mission();
    ~count_mission();
};
class Driver
{
public:
    Driver(int id_) { driver_id = id_; }
    int get_id() { return driver_id; }

private:
    int driver_id;
    vector<Mission *> all_mission;
};
// template<class T>
class DataBase
{
public:
    void add_count_mission(count_mission *c) { count_mission_data.push_back(c); }
    void add_time_mission(time_mission *c) { time_mission_data.push_back(c); }
    void add_distance_mission(distance_mission *c) { distance_mission_data.push_back(c); }
    bool assign_mission(int mission_id,int driver_id);
    template <typename T>
    void add_mission()
    {
        string mission_id_, start_time_stamp_, end_time_stamp_, distance_, mission_quality_;
        cin >> mission_id_ >> start_time_stamp_ >> end_time_stamp_ >> distance_ >> mission_quality_;
        total_mission.push_back(new T(mission_id_, start_time_stamp_, end_time_stamp_, stoi(distance_), stoi(mission_quality_)));
    }

    void add_driver_id(int id);
    bool check_driver(int is);
    vector<count_mission *> get_count_mission_data() { return count_mission_data; }
    vector<Mission *> total_mission;

private:
    vector<count_mission *> count_mission_data;
    vector<distance_mission *> distance_mission_data;
    vector<time_mission *> time_mission_data;
    // friend ostream &operator<<(ostream &out, vector<count_mission *> count_mission_data);
    vector<Driver *> Drivers_data;
};
void distance_mission::print_mission()
{
    cout << mission_id << " " << start_time_stamp << " " << end_time_stamp << " " << distance << " " << reward << "\n";
}
void count_mission::print_mission()
{
    cout << mission_id << " " << start_time_stamp << " " << end_time_stamp << " " << count << " " << reward << "\n";
}
void time_mission::print_mission()
{
    cout << mission_id << " " << start_time_stamp << " " << end_time_stamp << " " << time << " " << reward << "\n";
}
bool DataBase ::check_driver(int id)
{
    for (int i = 0; i < Drivers_data.size(); i++)
    {
        if (Drivers_data[i]->get_id() == id)
            return true;
    }
    return false;
}
void DataBase::add_driver_id(int id)
{
    Drivers_data.push_back(new Driver(id));
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

Mission::Mission(string mission_id_str_form, string start_time_stamp_str_form, string end_time_stamp_str_form, int reward_)
{
    if (mission_id=="" || start_time_stamp_str_form=="" || end_time_stamp_str_form=="")
    throw INVALID_ARGUMENTS;
    mission_id = mission_id_str_form;
    start_time_stamp = stol(start_time_stamp_str_form);
    end_time_stamp = stol(end_time_stamp_str_form);
    set_reward(reward_);
    if (end_time_stamp < start_time_stamp || reward_ < 0)
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
                cout << Error << '\n';
            }
            // cout << "OK";
        }

        // vector<count_mission *> djkj = new_database.get_count_mission_data();

        for (int i = 0; i < new_database.total_mission.size(); i++)
        {
            new_database.total_mission[i]->print_mission();
        }
    }

    cout << "hi";
}