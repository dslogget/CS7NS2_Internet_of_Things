#include "common.h"
#include "Credentials.h"
#include "WiFiHelper.h"
#include "esp_wifi.h"

static EventGroupHandle_t wifi_event_group = NULL;
static const char * LOG_WIFI = "WIFI";

#define WIFI_EVENTGROUP_CONNECTED BIT0

static void event_handler( void * arg, esp_event_base_t event_base,
                           int32_t event_id, void* event_data ) {
    if ( event_base == WIFI_EVENT && event_id == WIFI_EVENT_STA_START ) {
        esp_wifi_connect();
    } else if ( event_base == WIFI_EVENT && event_id == WIFI_EVENT_STA_DISCONNECTED ) {
        xEventGroupClearBits(wifi_event_group, WIFI_EVENTGROUP_CONNECTED);
        esp_wifi_connect();
    } else if ( event_base == IP_EVENT && event_id == IP_EVENT_STA_GOT_IP ) {
        ip_event_got_ip_t* event = (ip_event_got_ip_t*) event_data;
        ESP_LOGI( LOG_WIFI, "got ip:" IPSTR, IP2STR( &event->ip_info.ip ) );
        xEventGroupSetBits( wifi_event_group, WIFI_EVENTGROUP_CONNECTED );
    }
}



void initialiseWifi( void ) {
    ESP_ERROR_CHECK( esp_netif_init() );

    wifi_event_group = xEventGroupCreate();

    ESP_ERROR_CHECK( esp_event_loop_create_default() );
    esp_netif_create_default_wifi_sta();

    wifi_init_config_t cfg = WIFI_INIT_CONFIG_DEFAULT();
    ESP_ERROR_CHECK( esp_wifi_init(&cfg) );

    esp_event_handler_instance_t instance_any_id;
    esp_event_handler_instance_t instance_got_ip;
    ESP_ERROR_CHECK(esp_event_handler_instance_register(WIFI_EVENT,
                                                        ESP_EVENT_ANY_ID,
                                                        &event_handler,
                                                        NULL,
                                                        &instance_any_id));

    ESP_ERROR_CHECK(esp_event_handler_instance_register(IP_EVENT,
                                                        IP_EVENT_STA_GOT_IP,
                                                        &event_handler,
                                                        NULL,
                                                        &instance_got_ip));



    ESP_ERROR_CHECK( esp_wifi_set_storage(WIFI_STORAGE_RAM) );

    wifi_config_t wifi_config = {
        .sta = {
            .ssid = WIFI_SSID,
            .password = WIFI_PASSWORD,
        },
    };

    ESP_LOGI( LOG_WIFI, "Setting WiFi configuration SSID %s...", wifi_config.sta.ssid );
    ESP_ERROR_CHECK( esp_wifi_set_mode( WIFI_MODE_STA ) );
    ESP_ERROR_CHECK( esp_wifi_set_config( WIFI_IF_STA, &wifi_config ) );
    ESP_ERROR_CHECK( esp_wifi_start() );
}
