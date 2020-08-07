#include <map>
#include <iostream>
#include <fstream>
#include <string>
#include <json/json.h>
#include <ready/ready.h>
#include <args.h>
#include <chrono>
#include <iomanip>
#include <time.h>

using namespace std::chrono;

typedef struct info_t{

   std::string arch;
   std::string message;
   
   double exec_time;
   double config_time;
   double scheduling_time;
   
   long clock_cycles;
   double throughput;
   double approximate_throughput;
   long total_input_bytes;
   long total_output_bytes;
        
}info_t;

int main(int argc, char **args);

int exec_dataflow_cpu(std::string &df_file,std::string &input_data_file,std::string &output_data_file);

int exec_dataflow_cgra(std::string &arch_file,std::string &df_file,std::string &input_data_file,std::string &output_data_file);

arch_t read_arch_file(std::string &arch_file);

std::map<int, std::pair<short *,int>> *read_input_data(std::string &data_file);

std::map<int, std::pair<short *,int>> *read_output_data(std::string &data_file);

void write_output_data(std::string &input_data_file,std::string &output_data_file,std::map<int, std::pair<short *,int>> &data_map, const info_t& info);

double calc_conf_time(Cgra *cgraHw, std::string &arch_file,std::string &df_file);
