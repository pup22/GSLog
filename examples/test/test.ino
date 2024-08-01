#include <Arduino.h>
#include <ESP8266WiFi.h>
#include "GSLog.h"
#include "../secret.h"

// defined in secret.h
// #define SSID "xxxxx"
// #define PASS "xxxxxxxxxx"
// Enter Google Script Deployment ID:
// #define GSCRIPT_ID "AKfycbyoWiQTpcWuPUzowfvEG5akZXqN3WGcCyKzMkW2Tt2Mjejyq8kn6H6F_ia8SXvn77dV"

GSLog gsl;

void setup() {
    Serial.begin (115200);

  // Connect to WiFi
  {
    WiFi.begin(SSID, PASS);
    Serial.println("\nConnecting to WiFi ...");
    while (WiFi.status() != WL_CONNECTED) {
      delay(500);
      Serial.print(".");
    }
    Serial.println("\nConnection established!");  
    Serial.print("IP address:\t");
    Serial.println(WiFi.localIP());
  }

  if(!gsl.begin( GSCRIPT_ID , "SheetLog", "time", "temperature", "ID"))
  {
    Serial.println("no connected!");
  }

  // Устанавливает заголовки таблицы (в первой строке)
  // gsl.setHeaders("ID", "temperature", "time");

  uint16_t i{99};
  // Вставляет во вторую строку. Пять значений или меньше. Если содержимое ячейки начинается с "=" , оно интерпретируется как формула.
  if(!gsl.insertRow("insert", String(i), "setup()", String(215), "=B2+D2"))
  {
    Serial.println("no connected!");
  }

  // Возвращает значение указанной ячейки
  Serial.print("\nCell 'B2' = ");
  i = gsl.getValue("B2").toInt();
  Serial.println(i);

  // Добавляет строку в конец области данных на листе. Пять значений или меньше. Если содержимое ячейки начинается с "=" , оно интерпретируется как формула.
  gsl.addRow("add", "this row", "i = ", String(i), "setup()");

  i++;
  gsl.addRow(); // пустая строка в конец не добавится!

  gsl.addRow("", "next row", "(i + 1) / 10 ", String(i / 10));

}

const uint32_t period_send{5000};
void loop() {
  static uint32_t timer_send = period_send;
  static uint16 id{}, x{}, y{};
  if(millis() - timer_send >= period_send || millis() - timer_send < 0){
    timer_send = millis();
    id++;
    x += 5;
    y += x * 2;
    
    START_TIME_SENSOR_MS
    // отправка данных длится 3-4 секунды! (косяк в парсере HTTPSRedirect)
    if(!gsl.insertRow(String(millis()), "23°C", String(id), String(y), "=C2+D2"))
    {
      PRINTLN_RS("ERROR. No insert.");
    }
    STOP_TIME_SENSOR_MS
  }
  // static int i{0};i++;Serial.print(i);Serial.println(" *********************** ");
}
