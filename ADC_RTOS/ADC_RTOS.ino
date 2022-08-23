#include <Arduino_FreeRTOS.h>
#include <queue.h>

QueueHandle_t xQueue;

void setup()
{
  Serial.begin(9600);
  xQueue = xQueueCreate(5, sizeof(int));
  if (xQueue != NULL)
  {
    xTaskCreate(sadc, "send", 100, NULL, 1, NULL);
    xTaskCreate(radc, "recieve", 100, NULL, 2, NULL);
    vTaskStartScheduler();
  }
  
}

void loop(){
  
}

void sadc(void * pvParameters){
  for (;;)
  {
    int vadc;
    vadc = analogRead(A0);
    xQueueSend(xQueue, &vadc, portMAX_DELAY == pdPASS);
    Serial,println(vadc);
    vTaskDelay(100);
  }
}

void radc (void * pvParameters){
  int ReceivedValue = 0;
  for(;;)
  {
    if(xQueueReceive)xQueue, &ReceivedValue, portMAX_DELAY)==pdPASS)
    {
      Serial.println(ReceivedValue);
    }
  }
}
