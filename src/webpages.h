const char index_html[] PROGMEM = R"rawliteral(
<!DOCTYPE HTML><html>
<head>
  <title>ESP32 Homepage</title>
  <meta name="viewport" content="width=device-width, initial-scale=1">
  <link rel="stylesheet" href="https://use.fontawesome.com/releases/v5.7.2/css/all.css" integrity="sha384-fnmOCqbTlWIlj8LyTjo7mOUStjsKC4pOpQbqyi7RrhN7udi9RwhKkMHpvLbHG9Sr" crossorigin="anonymous">
  <style>
    html {
     font-family: Arial;
     display: inline-block;
     margin: 0px auto;
     text-align: center;
    }
    h2 {
      font-size: 4.0rem;
      text-align: center;
      padding: 3px;
      color: black;
    }
    p {
      font-size: 3.0rem;
    }
    .dht-labels{
      font-size: 3.0rem;
      vertical-align:middle;
      padding-bottom: 15px;
    }
    .footer {
      font-size: 1.0rem;
      float: right;
      text-align: center;
      padding: 3px;
      background-color: gray;
      color: black;
    }
  </style>
</head>
<body>
  <h2>ESP32 Homepage</h2>
  <p><a href="/temp">ESP32 Temperature Sensor Data</a></p>
  <p><a href="/update">Update</a></p>
  <p><a href="https://github.com/anthonysleck/ESP32TemperatureMonitor">Github</a></p>
  <footer>
  <p>
    <span class="footer">Rev </span> 
    <span class="footer" id="revision">%REVISION%</span>
  <p>
  </footer>
</body>
<script>

setInterval(function ( ) {
  var xhttp = new XMLHttpRequest();
  xhttp.onreadystatechange = function() {
    if (this.readyState == 4 && this.status == 200) {
      document.getElementById("revision").innerHTML = this.responseText;
    }
  };
  xhttp.open("GET", "/revision", true);
  xhttp.send();
}, 10000 ) ;

</script>
</html>)rawliteral";
const char temp_html[] PROGMEM = R"rawliteral(
<!DOCTYPE HTML><html>
<head>
  <title>ESP32 Temperature Sensor Data</title>
  <meta name="viewport" content="width=device-width, initial-scale=1">
  <link rel="stylesheet" href="https://use.fontawesome.com/releases/v5.7.2/css/all.css" integrity="sha384-fnmOCqbTlWIlj8LyTjo7mOUStjsKC4pOpQbqyi7RrhN7udi9RwhKkMHpvLbHG9Sr" crossorigin="anonymous">
  <style>
    html {
     font-family: Arial;
     display: inline-block;
     margin: 0px auto;
     text-align: center;
    }
    h2 {
      font-size: 4.0rem;
      text-align: center;
      padding: 3px;
      color: black;
    }
    p {
      font-size: 3.0rem;
    }
    .dht-labels{
      font-size: 3.0rem;
      vertical-align:middle;
      padding-bottom: 15px;
    }
    .footer {
      font-size: 1.0rem;
      float: right;
      text-align: center;
      padding: 3px;
      background-color: gray;
      color: black;
    }
  </style>
</head>
<body>
  <h2>ESP32 Temperature Sensor Data</h2>
  <p>
    <i class="fas fa-thermometer-half" style="color:#059e8a;"></i> 
    <span class="dht-labels">Temperature</span> 
    <span class="dht-labels" id="esptemperature">%ESPTEMPERATURE%</span>
    <span class="dht-labels">&deg;F</span>
  </p>
</body>
<script>

setInterval(function ( ) {
  var xhttp = new XMLHttpRequest();
  xhttp.onreadystatechange = function() {
    if (this.readyState == 4 && this.status == 200) {
      document.getElementById("esptemperature").innerHTML = this.responseText;
    }
  };
  xhttp.open("GET", "/esptemperature", true);
  xhttp.send();
}, 10000 ) ;
</script>
</html>)rawliteral";