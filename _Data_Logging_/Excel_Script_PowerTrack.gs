function doGet(e) { 
  Logger.log( JSON.stringify(e) );  // view parameters
  var result = 'Ok'; // assume success
  if (e.parameter == 'undefined') {
    result = 'No Parameters';
  }
  else {
    var sheet_id = '1cYx2q8KgtQQhcOKwXJrPBospRPrHGkOvMoFrkTc4DGg'; 		// Spreadsheet ID
    var sheet = SpreadsheetApp.openById(sheet_id).getActiveSheet();		// get Active sheet
    var newRow = sheet.getLastRow() + 1;						
    var rowData = [];
    d=new Date();
    rowData[0] = d; // Timestamp in column A
    rowData[1] = d.toLocaleTimeString(); // Timestamp in column A
    
    for (var param in e.parameter) {
      Logger.log('In for loop, param=' + param);
      var value = stripQuotes(e.parameter[param]);
      Logger.log(param + ':' + e.parameter[param]);
      switch (param) {
        case 'val1': //Parameter 1, It has to be updated in Column in Sheets in the code, orderwise
          rowData[2] = value; //Value in column A
          result = 'Written on column A';
          break;
        case 'val2': //Parameter 2, It has to be updated in Column in Sheets in the code, orderwise
          rowData[3] = value; //Value in column B
          result += ' Written on column B';
          break;
        case 'val3': //Parameter 3, It has to be updated in Column in Sheets in the code, orderwise
          rowData[4] = value; //Value in column C
          result += ' Written on column C';
          break;
        case 'val4': //Parameter 4, It has to be updated in Column in Sheets in the code, orderwise
          rowData[5] = value; //Value in column C
          result += ' Written on column D';
          break;
        case 'val5': //Parameter 5, It has to be updated in Column in Sheets in the code, orderwise
          rowData[6] = value; //Value in column C
          result += ' Written on column E';
          break;  
        default:
          result = "unsupported parameter";
      }
    }
    Logger.log(JSON.stringify(rowData));
    // Write new row below
    var newRange = sheet.getRange(newRow, 1, 1, rowData.length);
    newRange.setValues([rowData]);
  }
  // Return result of operation
  return ContentService.createTextOutput(result);
}
function stripQuotes( value ) {
  return value.replace(/^["']|['"]$/g, "");
}