#include "common.h"
#include "pinDefs.h"
#include "globalVariables.h"

static const char * LOG_MISC = "MISC";
static const char * LOG_LED = "LED";

void ledState( void * params ) {
    ESP_LOGI( LOG_MISC, "ledState Task Started!" );
    ESP_ERROR_CHECK( gpio_set_level( PIN_LED, 0 ) );
    u_int32_t notificationValue;
    while( 1 ) {
        ESP_LOGI( LOG_LED, "Awaiting State" );
        xTaskNotifyWait( 0, ULONG_MAX, &notificationValue, portMAX_DELAY );
        ESP_LOGI( LOG_LED, "Received State: %d", notificationValue );
        ESP_ERROR_CHECK( gpio_set_level( PIN_LED, notificationValue ) );
    }
}