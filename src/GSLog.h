#pragma once

#ifdef DEBUG_RS
  #define PRINT_RS(...)  Serial.print(__VA_ARGS__)
  #define PRINTLN_RS(...) Serial.println(__VA_ARGS__)
  #define PRINTF_RS(...)  Serial.printf(__VA_ARGS__)
  #define START_TIME_SENSOR_MS uint32_t __ms__ = millis();
  #define STOP_TIME_SENSOR_MS   __ms__ = millis() - __ms__; if (__ms__ > 100) Serial.println(String("############## time: ") + __ms__ + String(" ms"));
#else
  #define PRINT_RS(...)
  #define PRINTLN_RS(...)
  #define PRINTF_RS(...)
  #define START_TIME_SENSOR_MS
  #define STOP_TIME_SENSOR_MS
#endif

#include "HTTPSRedirect.h"

class GSLog : public HTTPSRedirect{
  private:
    const int _port;
    const char* _host = "script.google.com";
    // String _GScriptId;
    String _SheetName;
    String _url;

  public:
    GSLog(const int port = 443) : HTTPSRedirect(port), _port(port){}
    ~GSLog(){}

    bool begin(String GScriptId, String SheetName, String str0 = "", String str1 = "", String str2 = "", String str3 = "", String str4 = "")
    {
      setInsecure();
      setPrintResponseBody(false); // выводит ответ в сериал
      setContentTypeHeader("application/json");
      // _GScriptId = GScriptId;
      _SheetName = SheetName;
      _url  = "/macros/s/" + GScriptId + "/exec";
      bool ret_c = HTTPSRedirect::connect(_host, _port);
      bool ret_i = setHeaders(str0, str1, str2, str3, str4);
      return ret_c & ret_i;
    }

    String getValue(String cell)
    {
      String payload = R"({"sheet_name": ")" + _SheetName + R"(", "command": "get_cell_value", "values": ")" + cell + R"(,,,,,"})";

      if(POST(_url, _host, payload)){
        PRINT_RS("\nPublishing payload: ");
        PRINTLN_RS(payload);
        PRINT_RS("value: ");
        PRINTLN_RS(getResponseBody());
        return getResponseBody();;
      }
      else{
        // do stuff here if publish was not successful
        PRINT_RS("\nPublishing payload: ");
        PRINTLN_RS(payload);
        PRINTLN_RS("Error while connecting (POST)");
      }
      return "_NaN_";
    }

    bool insertRow(String str0 = "", String str1 = "", String str2 = "", String str3 = "", String str4 = "")
    {
      String payload = R"({"sheet_name": ")" + _SheetName + 
          R"(", "command": "insert_row", "values": ")" + str0 + "," + str1 + "," + str2 + "," + str3 + "," + str4 + R"("})";

      if(POST(_url, _host, payload)){
          PRINT_RS("\nPublishing payload: ");
          PRINTLN_RS(payload);
        return true;
      }
      else{
        PRINT_RS("\nPublishing payload: ");
        PRINTLN_RS(payload);
        // do stuff here if publish was not successful
        PRINTLN_RS("Error while connecting (POST)");
      }
      return false;
    }

    bool addRow(String str0 = "", String str1 = "", String str2 = "", String str3 = "", String str4 = "")
    {
      String payload = R"({"sheet_name": ")" + _SheetName + 
          R"(", "command": "append_row", "values": ")" + str0 + "," + str1 + "," + str2 + "," + str3 + "," + str4 + R"("})";

      if(POST(_url, _host, payload)){
          PRINT_RS("\nPublishing payload: ");
          PRINTLN_RS(payload);
        return true;
      }
      else{
        PRINT_RS("\nPublishing payload: ");
        PRINTLN_RS(payload);
        // do stuff here if publish was not successful
        PRINTLN_RS("Error while connecting (POST)");
      }
      return false;
    }

    bool setHeaders(String str0 = "", String str1 = "", String str2 = "", String str3 = "", String str4 = "")
    {
      String payload = R"({"sheet_name": ")" + _SheetName + 
          R"(", "command": "set_headers", "values": ")" + str0 + "," + str1 + "," + str2 + "," + str3 + "," + str4 + R"("})";

      if(POST(_url, _host, payload)){
          PRINT_RS("\nPublishing payload: ");
          PRINTLN_RS(payload);
        return true;
      }
      else{
        PRINT_RS("\nPublishing payload: ");
        PRINTLN_RS(payload);
        // do stuff here if publish was not successful
        PRINTLN_RS("Error while connecting (POST)");
      }
      return false;
    }
};