#include "commen.h"

using namespace std;

void predict_server(char * info[MAX_INFO_NUM], char * data[MAX_DATA_NUM], int data_num, char * filename)
{
	// ÐèÒªÊä³öµÄÄÚÈÝ
	char * result_file = (char *)"17\n\n0 8 0 20";
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
        int type = atoi(s_type.substr(6, s_type.size()).c_str());
        cout << type << endl;
        flavor_list.push_back(type);
    }

    istringstream is_t1(info[6+count_flavor]), is_t2(info[7+count_flavor]), is_type(info[4+count_flavor]);
    string s_type;
    is_type >> s_type;
    int type = 0;
    if (strcmp(s_type.c_str() ,"CPU")) type = 1;
    tm t1,t2;
    is_t1 >> get_time(&t1, "%Y-%m-%d %H:%M:%S");
    is_t2 >> get_time(&t2, "%Y-%m-%d %H:%M:%S");
    int delta_day = (mktime(&t2)-mktime(&t1)) / 86400;

	// Ö±½Óµ÷ÓÃÊä³öÎÄ¼þµÄ·½·¨Êä³öµ½Ö¸¶¨ÎÄ¼þÖÐ(psÇë×¢Òâ¸ñÊ½µÄÕýÈ·ÐÔ£¬Èç¹ûÓÐ½â£¬µÚÒ»ÐÐÖ»ÓÐÒ»¸öÊý¾Ý£»µÚ¶þÐÐÎª¿Õ£»µÚÈýÐÐ¿ªÊ¼²ÅÊÇ¾ßÌåµÄÊý¾Ý£¬Êý¾ÝÖ®¼äÓÃÒ»¸ö¿Õ¸ñ·Ö¸ô¿ª)
	write_result(result_file, filename);
}