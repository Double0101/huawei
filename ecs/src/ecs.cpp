#include "common.h"
#include "predict.h"
#include "lib_io.h"
#include "lib_time.h"
#include "stdio.h"

int main(int argc, char *argv[])
{
        // traindata input output
        print_time("Begin");
        char *data[MAX_DATA_NUM];
        char *info[MAX_INFO_NUM];
        int data_line_num;
        int info_line_num;


        char *data_file = argv[1]; // traindata 

        data_line_num = read_file(data, MAX_DATA_NUM, data_file);

        printf("data file line num is :%d \n", data_line_num);
        if (data_line_num == 0)
        {
                printf("Please input valid data file.\n");
                return -1;
        }

        char *input_file = argv[2]; // input

        info_line_num = read_file(info, MAX_INFO_NUM, input_file);

        printf("input file line num is :%d \n", info_line_num);
        if (info_line_num == 0)
        {
                printf("Please input valid info file.\n");
                return -1;
        }

        char *output_file = argv[3]; // output

        predict_server(info, argv[1], data_line_num, output_file);// input traindata 

        release_buff(info, info_line_num);
        release_buff(data, data_line_num);

        print_time("End");

        return 0;
}
