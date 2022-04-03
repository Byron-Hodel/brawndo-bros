#include <iostream>
#include <fstream>
#include <sstream>
#include <stdint.h>
#include <unistd.h>
#include <fcntl.h>
#include <vector>
#include <sys/time.h>

#include <poll.h>

#define SAMPLES 60
#define BUFFER_SIZE 16

void log_to_csv(const std::string str, const std::string file_path) {
	std::ofstream output_stream;
	output_stream.open(file_path, std::ios_base::app);
	output_stream << str;
	output_stream.close();
}

int main(void) {
	// init

	const std::string file_path = "log.csv";

	int port_fd = open("/dev/ttyACM0", O_RDWR | O_NOCTTY | O_NONBLOCK);
	if(port_fd == -1) {
		std::cout << "Failed To Open Port\n";
		return -1;
	}

	struct pollfd pfd = {
		.fd = port_fd,
		.events = POLLIN
	};

	std::vector<float> sensor_values;
	std::vector<std::string> other_values; // most up to date value will be used

	int current_samples = 0;
	std::string line = "";
	while(1) {
		poll(&pfd, 1, -1);
		if((pfd.revents & POLLIN) == POLLIN) {
			char buffer[BUFFER_SIZE+1] = {'\0'};
			int bytes_read = read(port_fd, buffer, BUFFER_SIZE);
			for(int i = 0; i < bytes_read; i++) if(buffer[i] == ',') buffer[i] = ' ';
			line += std::string(buffer);

			if(line[0] == '\n') line.clear();
			if(line.size() == 0) continue;
			if(line[line.size()-1] == '\n') {
				std::stringstream ss(line);

				other_values.clear();

				int index = 0;
				while(ss.peek() != -1) {
					std::string value_str;
					ss >> value_str;
					float value;
					// check if it is a number (int or float)
					if(std::stringstream(value_str) >> value) {
						if(sensor_values.size() <= index) sensor_values.push_back(value);
						else sensor_values[index] += value;
						index++;
					}
					else {
						other_values.push_back(value_str);
					}
				}
				current_samples++;
				line.clear();
			}
			if(current_samples == SAMPLES) {
				time_t t = time(0);
				struct tm* p = localtime(&t);
				char time_str[1000];
				strftime(time_str, 1000, "%d/%m/%y,%H:%M", p);

				for(int i = 0; i < other_values.size(); i++) {
					std::cout << other_values[i] + ",";
				}

				std::string data_str = std::string(time_str) + ",";
				for(int i = 0; i < sensor_values.size(); i++) {
					data_str += std::to_string(sensor_values[i]);
					if(i < sensor_values.size()-1) data_str += ",";
					else data_str += '\n';
				}
				std::cout << data_str;
				log_to_csv(data_str, file_path);
				sensor_values.clear();

				current_samples = 0;
			}
		}
	}

	return 0;
}