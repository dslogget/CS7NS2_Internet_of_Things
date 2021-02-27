#include "common.h"
#include "globalVariables.h"
#include "pinDefs.h"
#include "Credentials.h"



extern const char aws_root_ca_pem_start[] asm("_binary_AmazonRootCA1_pem_start");
extern const char aws_root_ca_pem_end[] asm("_binary_AmazonRootCA1_pem_end");
extern const char certificate_pem_crt_start[] asm("_binary_f866013750_certificate_pem_crt_start");
extern const char certificate_pem_crt_end[] asm("_binary_f866013750_certificate_pem_crt_end");
extern const char private_pem_key_start[] asm("_binary_f866013750_private_pem_key_start");
extern const char private_pem_key_end[] asm("_binary_f866013750_private_pem_key_end");


static const char * LOG_MQTT = "MQTT";


static void dataRecvHandler( char * topic, int topic_len, char * data, int data_len ) {
    if ( strncmp( "homeAutomation/LED1", topic, topic_len ) == 0 ) {
        if ( data_len > 0 && data[0] == '1' ) {
            gpio_set_level( PIN_LED, 1 );
        } else {
            gpio_set_level( PIN_LED, 0 );
        }
    } 
}

static esp_err_t mqtt_event_handler(esp_mqtt_event_handle_t event)
{
    esp_mqtt_client_handle_t client = event->client;
    int msg_id;
    // your_context_t *context = event->context;
    switch (event->event_id) {
        case MQTT_EVENT_CONNECTED:
            ESP_LOGI( LOG_MQTT, "MQTT_EVENT_CONNECTED" );
            //msg_id = esp_mqtt_client_publish( client, "devices/dev1", "Online", 0, 1, 1 );
            //ESP_LOGI( LOG_MQTT, "sent publish successful, msg_id=%d", msg_id );

            msg_id = esp_mqtt_client_subscribe( client, "homeAutomation/LED1", 1 );
            ESP_LOGI( LOG_MQTT, "sent subscribe successful, msg_id=%d", msg_id );

            // msg_id = esp_mqtt_client_unsubscribe( client, "/topic/qos1" );
            // ESP_LOGI( LOG_MQTT, "sent unsubscribe successful, msg_id=%d", msg_id );
            break;
        case MQTT_EVENT_DISCONNECTED:
            ESP_LOGI( LOG_MQTT, "MQTT_EVENT_DISCONNECTED" );
            break;

        case MQTT_EVENT_SUBSCRIBED:
            ESP_LOGI( LOG_MQTT, "MQTT_EVENT_SUBSCRIBED, msg_id=%d", event->msg_id );
            break;
        case MQTT_EVENT_UNSUBSCRIBED:
            ESP_LOGI( LOG_MQTT, "MQTT_EVENT_UNSUBSCRIBED, msg_id=%d", event->msg_id );
            break;
        case MQTT_EVENT_PUBLISHED:
            ESP_LOGI( LOG_MQTT, "MQTT_EVENT_PUBLISHED, msg_id=%d", event->msg_id );
            break;
        case MQTT_EVENT_DATA:
            ESP_LOGI( LOG_MQTT, "MQTT_EVENT_DATA" );
            ESP_LOGI( LOG_MQTT, "TOPIC=%.*s\r\n", event->topic_len, event->topic );
            ESP_LOGI( LOG_MQTT, "DATA=%.*s\r\n", event->data_len, event->data );
            dataRecvHandler( event->topic, event->topic_len, event->data, event->data_len );

            break;
        case MQTT_EVENT_ERROR:
            ESP_LOGI( LOG_MQTT, "MQTT_EVENT_ERROR" );
            break;
        default:
            ESP_LOGI( LOG_MQTT, "Other event id:%d", event->event_id );
            break;
    }
    return ESP_OK;
}

void initialiseMQTT( void )
{
    esp_mqtt_client_config_t mqtt_cfg = {
        .uri = MQTT_URI,
        .event_handle = mqtt_event_handler,
        .cert_pem = aws_root_ca_pem_start,
        .cert_len = ( size_t )( aws_root_ca_pem_end - aws_root_ca_pem_start ),
        .client_cert_pem = certificate_pem_crt_start,
        .client_cert_len = ( size_t )( certificate_pem_crt_end - certificate_pem_crt_start ),
        .client_key_pem= private_pem_key_start,
        .client_key_len = ( size_t )( private_pem_key_end - private_pem_key_start ),
        // .user_context = (void *)your_context
    };

    mqttClient = esp_mqtt_client_init( &mqtt_cfg );
    esp_mqtt_client_start( mqttClient );
}