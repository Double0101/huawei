#include "common.h"

#include <ctime>
#include <iomanip>
#include <iostream>
using namespace std;

void predict_server(char * info[MAX_INFO_NUM], char * training_data_file_path, int data_num, char * filename)
{
        istringstream iss(info[0]), iss1(info[2]);
        int num_cpu, num_mem, count_flavor;
        iss >> num_cpu;
        iss >> num_mem;
        iss1 >> count_flavor;
        vector<int> flavor_list;
        for (int i = 3; i < 3 + count_flavor; ++i)
        {
                istringstream is(info[i]);
                string s_type;
                is >> s_type;
                int flavor= atoi(s_type.substr(6, s_type.size()).c_str());
                //cout << flavor<< endl;
                flavor_list.push_back(flavor- 1);
        }

        istringstream is_t1(info[6+count_flavor]), is_t2(info[7+count_flavor]), is_type(info[4+count_flavor]);
        string s_type;
        is_type >> s_type;
        int type = 0;
        if (strcmp(s_type.c_str() ,"CPU")) type = 1;

        string time1, time2;
        is_t1 >> time1;
        is_t2 >> time2;

        char *cha1 = (char*)time1.data();
        char *cha2 = (char*)time2.data();
        tm tm_1, tm_2;
        int year, month, day, hour, minute, second;
        sscanf(cha1, "%d-%d-%d %d:%d:%d", &year, &month, &day, &hour, &minute, &second);
        tm_1.tm_year = year - 1900;
        tm_1.tm_mon = month - 1;
        tm_1.tm_mday = day;
        tm_1.tm_hour = hour;
        tm_1.tm_min = minute;
        tm_1.tm_sec = second;
        tm_1.tm_isdst = 0;
        sscanf(cha2, "%d-%d-%d %d:%d:%d", &year, &month, &day, &hour, &minute, &second);
        tm_2.tm_year = year - 1900;
        tm_2.tm_mon = month - 1;
        tm_2.tm_mday = day;
        tm_2.tm_hour = hour;
        tm_2.tm_min = minute;
        tm_2.tm_sec = second;
        tm_2.tm_isdst = 0;
        time_t t_1 = mktime(&tm_1);
        time_t t_2 = mktime(&tm_2);

        int delta_day = (t_2 - t_1) / 86400;

        // set paras
        int duration   = delta_day;
        double alpha   = 0.01;
        int dimensions = 5;
        int num_iter   = 1500;
        vector<int> results;

        train(training_data_file_path, alpha, dimensions, num_iter, duration, flavor_list, results);

        string tmp_result = allot(num_cpu, num_mem, flavor_list, results, type);

        cout<<tmp_result<<endl;

        //char result_file[2048];
        //memcpy(result_file, tmp_result.data, tmp_result.length());

        write_result(tmp_result.data(), filename);
}
