// Example Google Scrips code to upload data to Google Sheets from Arduino/ESP8266
// Follow setup instructions found here:
// https://github.com/StorageB/Google-Sheets-Logging
// 
// email: StorageUnitB@gmail.com


// Enter Spreadsheet ID here
var SS = SpreadsheetApp.openById('1LaV3v3S4fpvbNH4nW3sqm5_kFyemSPfaxEdn9865cxI'); // <--- !!!!!!!!!!!!!!!!!!!!!!!!!
var str = "";


function doPost(e) {

  var parsedData;
  var result = {};
  
  try { 
    parsedData = JSON.parse(e.postData.contents);
  } 
  catch(f){
    return ContentService.createTextOutput("Error in parsing request body: " + f.message);
  }
   
  if (parsedData !== undefined){
    var flag = parsedData.format;
    if (flag === undefined){
      flag = 0;
    }
    
    var sheet = SS.getSheetByName(parsedData.sheet_name); // sheet name to publish data to is specified in Arduino code
    var dataArr = parsedData.values.split(","); // creates an array of the values to publish 
    
    var value0 = dataArr [0]; // value0 from Arduino code
    var value1 = dataArr [1]; // value1 from Arduino code
    var value2 = dataArr [2]; // value2 from Arduino code
    var value3 = dataArr [3]; // value3 from Arduino code
    var value4 = dataArr [4]; // value4 from Arduino code
    var value5 = dataArr [5]; // value5 from Arduino code
    var value6 = dataArr [6]; // value6 from Arduino code
    
    
    // read and execute command from the "payload_base" string specified in Arduino code
    switch (parsedData.command) {

      case "set_headers":
         
        //  sheet.insertRows(1); // insert headers
         
         //var range = sheet.getRange("A2:G2");              // use this to insert cells just above the existing data instead of inserting an entire row
         //range.insertCells(SpreadsheetApp.Dimension.ROWS); // use this to insert cells just above the existing data instead of inserting an entire row
         
         sheet.getRange('A1').setValue(value0);   // publish value0 from Arduino code to cell A2
         sheet.getRange('B1').setValue(value1);   // publish value1 from Arduino code to cell B2
         sheet.getRange('C1').setValue(value2);   // publish value2 from Arduino code to cell C2
         sheet.getRange('D1').setValue(value3);   // publish value3 from Arduino code to cell D2
         sheet.getRange('E1').setValue(value4);   // publish value3 from Arduino code to cell E2
         sheet.getRange('F1').setValue(value5);   // publish value4 from Arduino code to cell F2
         sheet.getRange('G1').setValue(value6);   // publish value5 from Arduino code to cell G2

         
         str = "Success"; // string to return back to Arduino serial console
         SpreadsheetApp.flush();
         break;

      case "insert_row":
         
         sheet.insertRows(2); // insert full row directly below header text
         
         //var range = sheet.getRange("A2:G2");              // use this to insert cells just above the existing data instead of inserting an entire row
         //range.insertCells(SpreadsheetApp.Dimension.ROWS); // use this to insert cells just above the existing data instead of inserting an entire row
         
         sheet.getRange('A2').setValue(value0);   // publish value0 from Arduino code to cell A2
         sheet.getRange('B2').setValue(value1);   // publish value1 from Arduino code to cell B2
         sheet.getRange('C2').setValue(value2);   // publish value2 from Arduino code to cell C2
         sheet.getRange('D2').setValue(value3);   // publish value3 from Arduino code to cell D2
         sheet.getRange('E2').setValue(value4);   // publish value3 from Arduino code to cell E2
         sheet.getRange('F2').setValue(value5);   // publish value4 from Arduino code to cell F2
         sheet.getRange('G2').setValue(value6);   // publish value5 from Arduino code to cell G2

         
         str = "Success"; // string to return back to Arduino serial console
         SpreadsheetApp.flush();
         break;
         
      case "append_row":
         
         var publish_array = new Array(); // create a new array

         publish_array [0] = value0;   // add value0 from Arduino code to position 0 in publish_array
         publish_array [1] = value1;   // add value1 from Arduino code to position 1 in publish_array
         publish_array [2] = value2;   // add value2 from Arduino code to position 2 in publish_array
         publish_array [3] = value3;   // add value2 from Arduino code to position 3 in publish_array
         publish_array [4] = value4;   // add value2 from Arduino code to position 3 in publish_array
         publish_array [5] = value5;   // add value2 from Arduino code to position 5 in publish_array
         publish_array [6] = value6;   // add value2 from Arduino code to position 6 in publish_array
         
         sheet.appendRow(publish_array); // publish data in publish_array after the last row of data in the sheet
         
         str = "Success"; // string to return back to Arduino serial console
         SpreadsheetApp.flush();
         break;

      case "get_cell_value":

        str = sheet.getRange(value0).getValue();
        SpreadsheetApp.flush();
        break;
 
    }
    
    return ContentService.createTextOutput(str);
  } // endif (parsedData !== undefined)
  
  else {
    return ContentService.createTextOutput("Error! Request body empty or in incorrect format.");
  }
}