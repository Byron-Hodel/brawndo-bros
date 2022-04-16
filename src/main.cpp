#include <iostream>
#include <sstream>
#include <stdio.h>

#include <fcntl.h>
#include <termio.h>
#include <unistd.h>

#include <vector>
#include <sys/time.h>
#include <curl/curl.h>

#include <fstream>

#define SAMPLES 10
#define BUFFER_SIZE 64

void log_to_csv(const std::string str, const std::string file_path) {
	std::ofstream output_stream;
	output_stream.open(file_path, std::ios_base::app);
	output_stream << str;
	output_stream.close();
}

void log_to_server(CURL* curl, const std::string str) {
	curl_easy_setopt(curl, CURLOPT_URL, "http://domain_name_goes_here");
	CURLcode result = curl_easy_perform(curl);
	curl_easy_setopt(curl, CURLOPT_POST, 1);
	if(result != CURLE_OK) {
		std::cout << "Failed To Get Page.";
	}
}



int main(void) {
	CURL* curl = curl_easy_init();
/*
	curl_easy_setopt(curl, CURLOPT_URL, "http://brawndotest.mattmoose.net/api/users/userId/0");
	CURLcode result = curl_easy_perform(curl);
	if(result != CURLE_OK) {
		std::cout << "Failed To Get Page.\n";
	}
*/
	const std::string file_path = "log.csv";

	int port_fd = open("/dev/ttyACM1", O_RDWR | O_NOCTTY);
	if(port_fd == -1) {
		std::cout << "Failed To Open Port\n";
		return -1;
	}

	struct termios attributes;
	tcgetattr(port_fd, &attributes);
	attributes.c_iflag &= ~ICRNL; // prevent carrage returns from being converted into new lines

	cfsetospeed(&attributes, B9600); // set output baud rate to 9600
	cfsetispeed(&attributes, B9600); // set input baud rate to 9600
	tcsetattr(port_fd, TCSANOW, &attributes); // apply attributes to port fd

	sleep(1);
	tcflush(port_fd, TCIOFLUSH); // flush input and output to get rid of unwanted data present in buffer

	std::vector<std::string> parameter_names;
	std::string* str_values;
	float* sensor_values;

	int current_samples = 0;
	std::string line;
	while(1) {
		char buffer[BUFFER_SIZE+1] = {0};
		int32_t bytes_read = read(port_fd, buffer, BUFFER_SIZE);
		for(int i = 0; i < bytes_read; i++) if(buffer[i] == ',') buffer[i] = ' ';
		line += std::string(buffer);

		// read csv when line is complete
		if(line[line.size()-1] == '\n') {
			std::stringstream ss(line);
			// make sure parameter names are read in
			if(parameter_names.size() == 0) {
				std::string parameter_str = "Date,Time,";
				while(ss.peek() != -1) {
					std::string param;
					ss >> param;
					if(param == "") break;
					parameter_str += param + ',';
					parameter_names.push_back(param);
				}
				// replace end comma with a new line character
				parameter_str[parameter_str.size()-1] = '\n';
				std::cout << parameter_str;
				log_to_csv(parameter_str, file_path);
				str_values = new std::string[parameter_names.size()];
				sensor_values = new float[parameter_names.size()];
				for(int i = 0; i < parameter_names.size(); i++) sensor_values[i] = 0;
			}
			// after parameter names are received, read actual data
			else {
				int index = 0;
				while(ss.peek() != -1) {
					std::string value_str;
					ss >> value_str;
					if(value_str == "") continue;
					float value;
					// check if it is a number (int or float), forces first read in value to be a string
					if(std::stringstream(value_str) >> value && index != 0) {
						sensor_values[index] += value;
					}
					else {
						sensor_values[index] = -1;
						str_values[index] = value_str;
					}
					index++;
				}
				current_samples++;
			}
			// if sample limit has been reached, average data and log to csv
			if(current_samples == SAMPLES) {
				time_t t = time(0);
				struct tm* p = localtime(&t);
				char time_str[1000];
				strftime(time_str, 1000, "%d/%m/%y,%H:%M", p);

				std::string data_str = std::string(time_str) + ",";

				for(int i = 0; i < parameter_names.size(); i++) {
					if(sensor_values[i] == -1) data_str += str_values[i];
					else data_str += std::to_string(sensor_values[i] / (float)SAMPLES);
					sensor_values[i] = 0;
					if(i < parameter_names.size()-1) data_str += ",";
					else data_str += '\n';
				}
				std::cout << data_str;
				log_to_csv(data_str, file_path);

				current_samples = 0;
			}
			line.clear();
		}
	}
	curl_easy_cleanup(curl);
	return 0;
}