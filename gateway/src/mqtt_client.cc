#include "mqtt_client.h"

#include <iostream>

using namespace std;

MqttClient::MqttClient(BrokerInfo broker, string gateway_id) 
  : mosquittopp(gateway_id.c_str()) {
  //assign data
  m_status =  false;
  m_broker = broker;
  m_topic = string(GATEWAY_PREFIX) + gateway_id;

  //init mqtt
  lib_init();
}

MqttClient::~MqttClient() {
  //check status
  if (m_status) {
    //disconnect
    disconnect();
  }

  //clean up
  lib_cleanup();
}

void MqttClient::check_connection() {
  //loop
  loop(0);

  //get current time
  long current_time = time(NULL);

  //check working timeout
  if (current_time - m_last_working > MAX_WORKING_TIMEOUT) {
    //set disconnect
    m_status = false;
  }

  //check disconnect
  if (!m_status && current_time - m_last_connect > RECONNECT_INTERVAL) {
    //set last connect
    m_last_connect = current_time;

    //connect
    connect_to_broker();
  }
}

void MqttClient::publish_message(string message, int qos, bool retain) {
  //publish message to topic
  if(m_status) {
    //public message
    publish(NULL, m_topic.c_str(), message.length(), message.c_str(),
      qos, retain);
    
    //print message
    cout << "Public message = " << message << ", topic = " << m_topic << endl;
  }
}

void MqttClient::connect_to_broker() {
  //set user password
  username_pw_set(m_broker.username().c_str(), m_broker.password().c_str());

  //log debug
  cout << "Connect to broker with info = " << m_broker.to_string() << endl;

  //connect to broker
  connect_async(m_broker.host().c_str(), m_broker.port(), KEEP_ALIVE);
}

void MqttClient::on_error() {
  //log error
  m_status = false;
  cout << "Mqtt client is error" << endl;
}

void MqttClient::on_connect(int rc) {
  //log info
  cout << "Mqtt client is connected with rc = " << rc << endl;

  //handle on connect
  switch (rc) {
    case 0:
      //success
      m_status = true;
      break;
  }
}

void MqttClient::on_message(const struct mosquitto_message *message) {
  //get topic 
  string topic = string(message->topic);

  //init message buffer
  char message_buffer[message->payloadlen];

  //clear message buffer
  memset(message_buffer, 0, message->payloadlen * sizeof(char));

  //copy data to message buffer
  memcpy(message_buffer, message->payload, message->payloadlen);

  //log debug
  cout << "Mqtt client received message = " << message_buffer 
    << ", topic = " << topic << endl;
}

void MqttClient::on_publish(int rc) {
  //log debug
  cout << "Mqtt client published message with mid = " << rc << endl;
}

void MqttClient::on_disconnect(int rc) {
  //set status
  m_status = false;
  
  //log debug
  cout << "Mqtt client is disconnected with rc = " << rc << endl;
}

void MqttClient::on_log(int level, const char * message) {
  //update last working
  m_last_working = time(NULL);

  //log debug
  cout << "Mqtt client log with level = " << level << ", message = "
    << message << endl;
}