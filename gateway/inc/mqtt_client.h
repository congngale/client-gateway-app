#ifndef MQTT_CLIENT_H
#define MQTT_CLIENT_H

#include <string.h>
#include <mosquittopp.h>

#include "broker_info.h"

#define KEEP_ALIVE 60
#define RECONNECT_INTERVAL 5 //5 seconds
#define MAX_WORKING_TIMEOUT 120 //2 minutes
#define GATEWAY_PREFIX "net/gateway/"

using namespace mosqpp;

class MqttClient : public mosquittopp {
  public:
    MqttClient(BrokerInfo broker, std::string gateway_id);
    ~MqttClient();
    
    void check_connection(void);
    void publish_message(std::string message, int qos, bool retain = false);

  private:
    bool m_status;
    BrokerInfo m_broker;
    std::string m_topic;
    long m_last_connect = 0;
    long m_last_working = 0;

    void on_error(void);
    void on_connect(int rc);
    void on_publish(int rc);
    void on_disconnect(int rc);
    void connect_to_broker(void);
    void send_connected_ack(void);
    void send_disconnect_ack(void);
    void on_log(int level, const char * message);
    void on_message(const struct mosquitto_message *message);
};

#endif //MQTT_CLIENT_H
