#include <map>
#include <iostream>
#include <fstream>
#include <string>
#include <json/json.h>
#include <ready/ready.h>
#include <args.h>
#include <chrono>

using namespace std::chrono;

int main(int argc, char **args);

int exec_dataflow_cpu(std::string &df_file,std::string &input_data_file,std::string &output_data_file);

int exec_dataflow_cgra(std::string &arch_file,std::string &df_file,std::string &input_data_file,std::string &output_data_file);

arch_t read_arch_file(std::string &arch_file);

std::map<int, std::pair<short *,int>> *read_input_data(std::string &data_file);

std::map<int, std::pair<short *,int>> *read_output_data(std::string &data_file);

void write_output_data(std::string &input_data_file,std::string &output_data_file,std::map<int, std::pair<short *,int>> &data_map, double time_exec);


