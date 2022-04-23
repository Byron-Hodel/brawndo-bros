#include <iostream>
#include <iomanip>
#include <sstream>
#include <stdio.h>

#include <fcntl.h>
#include <termio.h>
#include <unistd.h>

#include <vector>
#include <sys/time.h>
#include <curl/curl.h>

#include <fstream>

#define SAMPLES 60
#define BUFFER_SIZE 64

void log_to_csv(const std::string str, const std::string file_path) {
	std::ofstream output_stream;
	output_stream.open(file_path, std::ios_base::app);
	output_stream << str;
	output_stream.close();
}

size_t write_data(void *buffer, size_t size, size_t nmemb, void *userp) {
	return size * nmemb;
}

typedef struct {
	int32_t last_pump_time;
	float soil_moisture;
	float soil_temperature;
	int32_t pump_state;
} sensor_data_t;

void log_to_server(const std::string str) {
	CURL* curl = curl_easy_init();
	curl_easy_setopt(curl, CURLOPT_URL, "http://brawndotest.mattmoose.net/api/events/plantId/1");
	curl_easy_setopt(curl, CURLOPT_POSTFIELDS, str.c_str());

	struct curl_slist *headers = NULL;
	headers = curl_slist_append(headers, "Accept: application/json");
	headers = curl_slist_append(headers, "Content-Type: application/json");
	headers = curl_slist_append(headers, "charset: utf-8");
	curl_easy_setopt(curl, CURLOPT_HTTPHEADER, headers);
	curl_easy_setopt(curl, CURLOPT_WRITEFUNCTION, write_data);
	curl_easy_setopt(curl, CURLOPT_TIMEOUT, 3);

	CURLcode result = curl_easy_perform(curl);
	if(result != CURLE_OK) {
		std::cout << "Failed To Get Page.\n";
	}
	curl_easy_cleanup(curl);
}



int main(int argc, char** argv) {
	if(argc == 1) {
		std::cout << "Enter Port Name.\n";
		return -1;
	}

	const std::string file_path = "log.csv";

	int port_fd = open(argv[1], O_RDWR | O_NOCTTY);
	if(port_fd == -1) {
		std::cout << "Failed To Open Port\n";
		return -1;
	}
	std::cout << "Opened Port\n";

	struct termios attributes;
	tcgetattr(port_fd, &attributes);
	attributes.c_iflag &= ~ICRNL; // prevent carrage returns from being converted into new lines

	cfsetospeed(&attributes, B9600); // set output baud rate to 9600
	cfsetispeed(&attributes, B9600); // set input baud rate to 9600
	tcsetattr(port_fd, TCSANOW, &attributes); // apply attributes to port fd

	sleep(1);
	tcflush(port_fd, TCIOFLUSH); // flush input and output to get rid of unwanted data present in buffer

	//std::vector<std::string> parameter_names;
	//std::string* str_values;
	//float* sensor_values;
	sensor_data_t avg = {0};
	sensor_data_t prev = {-1};
	bool pump_on = false;

	int current_samples = 0;
	std::string line;
	while(1) {
		char buffer[BUFFER_SIZE+1] = {0};
		read(port_fd, buffer, BUFFER_SIZE);
		line += std::string(buffer);

		{
			std::ifstream istream(file_path);
			if(istream) {
				istream.close();
				log_to_csv("Pump_State,Soil_Moisture,Soil_Temp,Last_Pump_Time", file_path);
			}
			std::cout << "Pump_State,Soil_Moisture,Soil_Temp,Last_Pump_Time";
		}


		if(line[line.size()-1] == '\n') {
			sensor_data_t data;

			sscanf(
				line.c_str(), "%d,%f,%f,%d\n",
				&data.last_pump_time, &data.soil_moisture,
				&data.soil_temperature, &data.pump_state
			);
			avg.pump_state = data.pump_state;
			avg.last_pump_time = data.last_pump_time;
			avg.soil_moisture += data.soil_moisture / SAMPLES;
			avg.soil_temperature += data.soil_moisture / SAMPLES;

			current_samples++;

			if(current_samples == SAMPLES) {
				time_t t = time(0);
				struct tm* p = localtime(&t);
				char time_str[100];
				char json_time_str[100];
				strftime(time_str, 100, "%d/%m/%y,%H:%M", p);
				strftime(json_time_str, 100, "%d/%m/%y %H:%M:%S", p);

				current_samples = 0;
				char str[1024];
				sprintf(
					str, "%s,%d,%.0f,%.0f,%d\n",
					time_str, avg.pump_state, avg.soil_moisture,
					avg.soil_temperature, avg.last_pump_time
				);
				log_to_csv(str, file_path);

				if(prev.pump_state == -1) continue;

				const char json_fmt[] = "{"
					"\"eventType\":\"data\","
					"\"eventSubtype\":\"%s\","
					"\"eventValue\":\"%f\","
					"\"eventTime\":\"%s\""
					"}";

				// send pump event to server when pump has changed state
				if(data.pump_state != prev.pump_state) {
					pump_on = true;
					sprintf(str, json_fmt, "pumpState", (float)data.pump_state, json_time_str);
					log_to_server(std::string(str));
				}

				if(data.soil_moisture != prev.soil_moisture) {
					sprintf(str, json_fmt, "soilMoisture", avg.soil_moisture, json_time_str);
					log_to_server(std::string(str));
				}
				if(data.soil_temperature != prev.soil_temperature) {
					sprintf(str, json_fmt, "soilTemperature", avg.soil_temperature, json_time_str);
					log_to_server(std::string(str));
				}
				prev = data;
			}
		}
	}
	return 0;
}