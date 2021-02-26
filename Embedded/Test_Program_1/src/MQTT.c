#include "common.h"
#include "globalVariables.h"
#include "pinDefs.h"
#include "Credentials.h"

#include "aws_iot_config.h"
#include "aws_iot_log.h"
#include "aws_iot_version.h"
#include "aws_iot_mqtt_client_interface.h"



extern const char aws_root_ca_pem_start[] asm("_binary_AmazonRootCA1_pem_start");
extern const char aws_root_ca_pem_end[] asm("_binary_AmazonRootCA1_pem_end");
extern const char certificate_pem_crt_start[] asm("_binary_f866013750_certificate_pem_crt_start");
extern const char certificate_pem_crt_end[] asm("_binary_f866013750_certificate_pem_crt_end");
extern const char private_pem_key_start[] asm("_binary_f866013750_private_pem_key_start");
extern const char private_pem_key_end[] asm("_binary_f866013750_private_pem_key_end");


static const char * LOG_MQTT = "MQTT";

void iot_subscribe_callback_handler(AWS_IoT_Client *pClient, char *topicName, uint16_t topicNameLen,
                                    IoT_Publish_Message_Params *params, void *pData) {
    ESP_LOGI(LOG_MQTT, "Subscribe callback");
    ESP_LOGI(LOG_MQTT, "%.*s\t%.*s", topicNameLen, topicName, (int) params->payloadLen, (char *)params->payload);
}

void disconnectCallbackHandler(AWS_IoT_Client *pClient, void *data) {
    ESP_LOGW(LOG_MQTT, "MQTT Disconnect");
    IoT_Error_t rc = FAILURE;

    if(NULL == pClient) {
        return;
    }

    if(aws_iot_is_autoreconnect_enabled(pClient)) {
        ESP_LOGI(LOG_MQTT, "Auto Reconnect is enabled, Reconnecting attempt will start now");
    } else {
        ESP_LOGW(LOG_MQTT, "Auto Reconnect not enabled. Starting manual reconnect...");
        rc = aws_iot_mqtt_attempt_reconnect(pClient);
        if(NETWORK_RECONNECTED == rc) {
            ESP_LOGW(LOG_MQTT, "Manual Reconnect Successful");
        } else {
            ESP_LOGW(LOG_MQTT, "Manual Reconnect Failed - %d", rc);
        }
    }
}

void initialiseMQTT( void * params ) {
    IoT_Error_t rc = FAILURE;

    AWS_IoT_Client client;
    IoT_Client_Init_Params mqttInitParams = iotClientInitParamsDefault;
    IoT_Client_Connect_Params connectParams = iotClientConnectParamsDefault;

    ESP_LOGI(LOG_MQTT, "AWS IoT SDK Version %d.%d.%d-%s", VERSION_MAJOR, VERSION_MINOR, VERSION_PATCH, VERSION_TAG);

    mqttInitParams.enableAutoReconnect = false; // We enable this later below
    mqttInitParams.pHostURL = MQTT_HOST_NAME;
    mqttInitParams.port = MQTT_PORT;

    mqttInitParams.pRootCALocation = (const char *)aws_root_ca_pem_start;
    mqttInitParams.pDeviceCertLocation = (const char *)certificate_pem_crt_start;
    mqttInitParams.pDevicePrivateKeyLocation = (const char *)private_pem_key_start;


    mqttInitParams.mqttCommandTimeout_ms = 20000;
    mqttInitParams.tlsHandshakeTimeout_ms = 5000;
    mqttInitParams.isSSLHostnameVerify = true;
    mqttInitParams.disconnectHandler = disconnectCallbackHandler;
    mqttInitParams.disconnectHandlerData = NULL;

    rc = aws_iot_mqtt_init(&client, &mqttInitParams);
    if(SUCCESS != rc) {
        ESP_LOGE(LOG_MQTT, "aws_iot_mqtt_init returned error : %d ", rc);
        abort();
    }

    connectParams.keepAliveIntervalInSec = 10;
    connectParams.isCleanSession = true;
    connectParams.MQTTVersion = MQTT_3_1_1;
    /* Client ID is set in the menuconfig of the example */
    connectParams.pClientID = AWS_CLIENT_ID;
    connectParams.clientIDLen = (uint16_t) strlen(AWS_CLIENT_ID);
    connectParams.isWillMsgPresent = false;

    ESP_LOGI(LOG_MQTT, "Connecting to AWS...");
    do {
        rc = aws_iot_mqtt_connect(&client, &connectParams);
        if(SUCCESS != rc) {
            ESP_LOGE(LOG_MQTT, "Error(%d) connecting to %s:%d", rc, mqttInitParams.pHostURL, mqttInitParams.port);
            vTaskDelay(1000 / portTICK_RATE_MS);
        }
    } while(SUCCESS != rc);
    vTaskDelete( NULL );
}