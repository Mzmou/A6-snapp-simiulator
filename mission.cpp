#include <iostream>
using namespace std;
class Mission{
    public:
    string get_mission_id(){ return mission_id;}
    string get_start_time_stamp(){ return start_time_stamp;}
    string get_end_time_stamp(){ return ennd_time_stamp;}
    Mission(string mission_id_str_form,string start_time_stamp_str_form,string end_time_stamp_str_form);

    private:
    string mission_id;
    string start_time_stamp;
    string end_time_stamp;
    
}
Mission:: Mission(string mission_id_str_form,string start_time_stamp_str_form,string end_time_stamp_str_form){
mission_id=mission_id_str_form;
start_time_stamp=start_time_stamp_str_form;
end_time_stamp=end_time_stamp_str_form;
}

int main(){


}