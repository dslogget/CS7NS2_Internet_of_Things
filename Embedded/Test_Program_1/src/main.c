#define LOG_LOCAL_LEVEL ESP_LOG_VERBOSE
#include "common.h"
#include "pinDefs.h"
#define VARIABLES_IMPL
#include "globalVariables.h"
#include "tasksInclude.h"
#include "generalHelpers.h"
#include "WiFiHelper.h"
#include "MQTTHelper.h"
#include "nvs_flash.h"
#include "esp_sntp.h"
#include "interrupts.h"

static const char * LOG_MISC = "MISC";
static const char * LOG_LED = "LED";
static const char * LOG_LDR = "LDR";
static const char * LOG_WIFI = "WIFI";
static const char * LOG_MQTT = "MQTT";
static const char * LOG_SERVO = "SERVO";
static const char * LOG_MIC = "MIC";

static void initialiseLogs( void ) {
    esp_log_level_set( "*", ESP_LOG_WARN );
    esp_log_level_set( LOG_MISC, ESP_LOG_INFO );
    esp_log_level_set( LOG_LED, ESP_LOG_WARN );
    esp_log_level_set( LOG_LDR, ESP_LOG_INFO );
    esp_log_level_set( LOG_WIFI, ESP_LOG_INFO );
    esp_log_level_set( LOG_MQTT, ESP_LOG_INFO );
    esp_log_level_set( LOG_SERVO, ESP_LOG_INFO );
    esp_log_level_set( LOG_MIC, ESP_LOG_INFO );
}

static void startTasks( void ) {
    // xTaskCreatePinnedToCore( &ledState, "ledState", 2048, NULL, 1, &ledStateTaskHandle, 1 );
    // xTaskCreatePinnedToCore( &blinkLED, "blinkLED", 2048, NULL, 1, NULL, 1 );
    xTaskCreatePinnedToCore( &ldrRead, "ldrRead", 2048, NULL, 1, NULL, 1 );
    xTaskCreatePinnedToCore( &microphoneTask, "microphone", 2048, NULL, 1, &microphoneTaskHandle, 1 );
}

static void initialisePins( void ) {
    adc1_config_width( ADC_WIDTH_BIT_11 );
    adc1_config_channel_atten( CHANNEL_LDR, ADC_ATTEN_DB_11 );
    // Characterize ADC
    adc1_chars = calloc(1, sizeof(esp_adc_cal_characteristics_t));
    esp_adc_cal_characterize( ADC_UNIT_1, ADC_ATTEN_11db,
                              ADC_WIDTH_BIT_11,
                              DEFAULT_VREF,
                              adc1_chars );

    gpio_config_t config = { GPIO_SEL_4,
                             GPIO_MODE_OUTPUT,
                             GPIO_PULLUP_DISABLE,
                             GPIO_PULLDOWN_DISABLE,
                             GPIO_INTR_DISABLE };

    ESP_ERROR_CHECK( gpio_config( &config ) );
    config.pin_bit_mask = GPIO_SEL_5;

    ESP_ERROR_CHECK( gpio_config( &config ) );

    config.pin_bit_mask = GPIO_SEL_17;
    config.mode = GPIO_MODE_INPUT;
    config.intr_type = GPIO_INTR_POSEDGE;
    ESP_ERROR_CHECK( gpio_config( &config ) );


    //install gpio isr service
    ESP_ERROR_CHECK( gpio_install_isr_service( 0 ) );

    ESP_ERROR_CHECK( gpio_isr_handler_add( PIN_MICROPHONE, microphoneISR, (void*) PIN_MICROPHONE ) );
}

static void setupQueues( void ) { 
    
}

static void setupTimes( void ) {
    sntp_setoperatingmode(SNTP_OPMODE_POLL);
    sntp_setservername(0, "pool.ntp.org");
    sntp_init();

    int retryCounter = 10;

    while ( retryCounter && sntp_get_sync_status() != SNTP_SYNC_STATUS_COMPLETED ) {
        vTaskDelay( 1000 / portTICK_PERIOD_MS );
    }
}

void app_main() {
     //Initialize NVS
    esp_err_t ret = nvs_flash_init();
    if ( ret == ESP_ERR_NVS_NO_FREE_PAGES || ret == ESP_ERR_NVS_NEW_VERSION_FOUND ) {
      ESP_ERROR_CHECK( nvs_flash_erase() );
      ret = nvs_flash_init();
    }
    ESP_ERROR_CHECK( ret );


    initialiseLogs();

    ESP_ERROR_CHECK( esp_read_mac( MAC_ADDRESS, 0 ) );
    ESP_LOGI( LOG_MISC, "Hello World!\n" );
    initialiseWifi();

    initialiseMQTT();

    setupQueues();

    initialisePins();
    
    servoInit();

    setupTimes();
    
    startTasks();

    fflush( stdout );
    vTaskDelete( NULL );
}