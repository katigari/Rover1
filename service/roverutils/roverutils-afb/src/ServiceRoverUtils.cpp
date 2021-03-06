/* Copyright 2018 Pedro Cuadra - pjcuadra@gmail.com
 *
 * Licensed under the Apache License, Version 2.0 (the "License");
 * you may not use this file except in compliance with the License.
 * You may obtain a copy of the License at
 *
 *    http://www.apache.org/licenses/LICENSE-2.0
 *
 * Unless required by applicable law or agreed to in writing, software
 * distributed under the License is distributed on an "AS IS" BASIS,
 * WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
 * See the License for the specific language governing permissions and
 * limitations under the License.
 */

/* WARNING: This file is automatically generated by raml2agl */
#include <service/ServiceRoverUtils.h>
#include <roverapi/rover_utils.hpp>

#include <iostream>
#include <fstream>
#include <sstream>
#include <string>
#include <limits>
#include <vector>
#include <numeric>
#include <cstdio>
#include <memory>
#include <stdexcept>
#include <array>


using namespace rover;
using namespace std;

static RoverUtils utils;

ServiceRoverUtils::ServiceRoverUtils() {
  AFB_NOTICE("[ServiceRoverUtils] Constructor ");
}

int ServiceRoverUtils::init() {
  AFB_NOTICE("[ServiceRoverUtils] Init ");
  return 0;
}


/** Autogenrated doc for get_bluetooth_status */
int ServiceRoverUtils::get_bluetooth_status(bool &out_is_on) {

  AFB_NOTICE("[ServiceRoverUtils] Get_bluetooth_status");

  out_is_on = static_cast<bool>(utils.getBluetoothStatus());

  return 0;
}

int get_num_cores() {
  ifstream proc_stat("/proc/stat");
  string line;
  string cpu;
  size_t found;
  int num_cores = 0;

  getline(proc_stat, line);
  // proc_stat.ignore(5, ' '); // Skip the 'cpu' prefix.

  // Read all the needed data form /proc/stat
  while (getline(proc_stat, line)) {
    istringstream is(line);
    is >> cpu;

    // Check if it's a cpu line
    found = cpu.find("cpu");
    if (found == std::string::npos) {
      break;
    }

    num_cores++;
  }

  return num_cores;
}


vector<vector<size_t>> get_cpu_times(int &num_cores) {
  ifstream proc_stat("/proc/stat");
  string line;
  string cpu;
  size_t found;
  vector<vector<size_t>> times;

  getline(proc_stat, line);
  // proc_stat.ignore(5, ' '); // Skip the 'cpu' prefix.

  num_cores = 0;

  // Read all the needed data form /proc/stat
  while (getline(proc_stat, line)) {
    istringstream is(line);
    is >> cpu;

    // Check if it's a cpu line
    found = cpu.find("cpu");
    if (found == std::string::npos) {
      break;
    }

    num_cores++;

    AFB_NOTICE("[ServiceRoverUtils] CPU name %s", cpu.c_str());

    // Read all times
    vector<size_t> this_cpu_times;
    for (size_t time; is >> time; this_cpu_times.push_back(time));

    // Add it to the main vector
    times.push_back(this_cpu_times);
  }

  return times;
}

/** Autogenrated doc for get_core_utilization */
int ServiceRoverUtils::get_core_utilization(double out_core_utilization[], int in_core_utilization_size) {
  vector<vector<size_t>> times0, times1;
  int total_time;
  int idle_time;
  int size = 0;

  AFB_NOTICE("[ServiceRoverUtils] Get_core_utilization");

  times0 = get_cpu_times(size);
  usleep(500000);
  times1 = get_cpu_times(size);

  for (int i = 0; i < in_core_utilization_size; i++) {
    total_time = std::accumulate(times1[i].begin(), times1[i].end(), 0);
    total_time -= std::accumulate(times0[i].begin(), times0[i].end(), 0);

    idle_time = times1[i][3] - times0[i][3];

    AFB_NOTICE("[ServiceRoverUtils] CPU name %d", i);
    AFB_NOTICE("[ServiceRoverUtils]  Idle Time: %d", static_cast<int>(idle_time));
    AFB_NOTICE("[ServiceRoverUtils]  Total Time: %d", static_cast<int>(total_time));

    out_core_utilization[i] = 100 * static_cast<double>((total_time - idle_time)) / total_time;
    AFB_NOTICE("[ServiceRoverUtils]  Usage: %f", out_core_utilization[i]);
  }

  return 0;
}

/** Autogenrated doc for get_ethernet_status */
int ServiceRoverUtils::get_ethernet_status(bool &out_is_on) {

  AFB_NOTICE("[ServiceRoverUtils] Get_ethernet_status");

  out_is_on = static_cast<bool>(utils.getEthernetStatus());

  return 0;
}

/** Autogenrated doc for get_honocloud_status */
int ServiceRoverUtils::get_honocloud_status(const std::string in_host_name,
    const int in_port,
    const std::string in_tenant_name,
    const std::string in_device_id,
    const std::string in_user,
    const std::string in_password,
    bool &out_is_on) {

  AFB_NOTICE("[ServiceRoverUtils] Get_honocloud_status");
  AFB_ERROR("Method Get_honocloud_status not implemented");

  return -1;
}

std::string exec(const char* cmd) {
    std::array<char, 128> buffer;
    std::string result;
    std::shared_ptr<FILE> pipe(popen(cmd, "r"), pclose);
    if (!pipe) throw std::runtime_error("popen() failed!");
    while (!feof(pipe.get())) {
        if (fgets(buffer.data(), 128, pipe.get()) != nullptr)
            result += buffer.data();
    }
    return result;
}

void get_interface_data(string int_name, std::string &ip, std::string  &mac) {
  string data_ex;
  int find_res = 0;

  string cmd = string("ifconfig ") + int_name;

  stringstream interfaces(exec(cmd.c_str()));

  while (interfaces >> data_ex) {

    if (!data_ex.compare("inet")) {
      interfaces >> data_ex;

      find_res = data_ex.find("addr:");

      if (find_res != string::npos) {
        data_ex = data_ex.substr(5);
      }

      ip = data_ex.c_str();

    }

    if (!data_ex.compare("ether")) {
      interfaces >> data_ex;
      mac = data_ex.c_str();
    }

    if (!data_ex.compare("HWaddr")) {
      interfaces >> data_ex;
      mac = data_ex.c_str();
    }
  }

}

void get_interfaces(vector<string> &interfaces) {
  string int_name;
  stringstream cmd_out(exec("ifconfig -a | grep '^[a-z].*' | awk '{ print $1}'"));

  while (cmd_out >> int_name) {

    interfaces.push_back(int_name);
  }

}

/** Autogenrated doc for get_interface_info */
int ServiceRoverUtils::get_interface_info(const int in_interface_idx,
    std::string &out_interface_name,
    std::string &out_ip_addr,
    std::string &out_hw_addr) {
  AFB_NOTICE("[ServiceRoverUtils] Get_interface_info");

  vector<string> interfaces;

  get_interfaces(interfaces);

  if (in_interface_idx >= interfaces.size()) {
    return -1;
  }

  out_interface_name = interfaces[in_interface_idx];

  get_interface_data(interfaces[in_interface_idx], out_ip_addr, out_hw_addr);

  return 0;
}

/** Autogenrated doc for get_internet_status */
int ServiceRoverUtils::get_internet_status(bool &out_is_on) {
  AFB_NOTICE("[ServiceRoverUtils] Get_internet_status");

  out_is_on = static_cast<bool>(utils.getInternetStatus());

  return 0;
}

/** Autogenrated doc for get_number_cores */
int ServiceRoverUtils::get_number_cores(int &out_num_cores) {
  AFB_NOTICE("[ServiceRoverUtils] Get_number_cores");

  out_num_cores = get_num_cores();

  AFB_NOTICE("[ServiceRoverUtils] Get_number_cores cores: %d", out_num_cores);

  return 0;

}

/** Autogenrated doc for get_number_of_network_interfaces */
int ServiceRoverUtils::get_number_of_network_interfaces(int &out_num_interface) {
  AFB_NOTICE("[ServiceRoverUtils] Get_number_of_network_interfaces");
  vector<string> interfaces;

  get_interfaces(interfaces);

  out_num_interface = interfaces.size();

  return 0;
}

/** Autogenrated doc for get_wlan_status */
int ServiceRoverUtils::get_wlan_status(bool &out_is_on) {
  AFB_NOTICE("[ServiceRoverUtils] Get_wlan_status");

  out_is_on = static_cast<bool>(utils.getWlanStatus());

  return 0;
}
