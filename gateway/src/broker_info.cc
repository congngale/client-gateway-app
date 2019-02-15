#include "broker_info.h"

using namespace std;

BrokerInfo::BrokerInfo() {
  //empty constructor
}

BrokerInfo::BrokerInfo(int port, string host, string password,
  string username) {
  //set data
  m_port = port;
  m_host = host;
  m_password = password;
  m_username = username;
}

BrokerInfo::~BrokerInfo() {
  //empty constructor
}

int BrokerInfo::port() {
  return m_port;
}

string BrokerInfo::host() {
  return m_host;
}

string BrokerInfo::password() {
  return m_password;
}

string BrokerInfo::username() {
  return m_username;
}

string BrokerInfo::to_string() {
  return "Broker info: host = " + m_host + ",port = " + std::to_string(m_port)
    + ", username = " + m_username + ", password = " + m_password;
}