#include <WiFi.h>
#include <WebServer.h>
#include <Wire.h>
#include <Adafruit_Sensor.h>
#include <Adafruit_BME280.h>

// ---------- Function Prototypes ----------
void handleRoot();
void handleData();
void readSensor();

// ---------- Access Point credentials ----------
const char* ssid = "TEM-HU";
const char* password = "@hlamahfuj";

// ---------- BME280 ----------
#define SEALEVELPRESSURE_HPA 1013.25

Adafruit_BME280 bme;
WebServer server(80);

// ---------- Sensor Values ----------
float temperature = 0;
float humidity = 0;
float pressure = 0;
bool sensorFound = false;

// ---------- SETUP ----------
void setup() {
  Serial.begin(115200);
  Wire.begin();

  if (bme.begin(0x76) || bme.begin(0x77)) {
    sensorFound = true;
    Serial.println("✓ BME280 Found");
  } else {
    Serial.println("✗ BME280 NOT Found");
  }

  WiFi.mode(WIFI_AP);
  WiFi.softAP(ssid, password);

  Serial.print("AP IP: ");
  Serial.println(WiFi.softAPIP());

  server.on("/", handleRoot);
  server.on("/data", handleData);

  server.begin();
}

// ---------- LOOP ----------
void loop() {
  server.handleClient();
}

// ---------- SENSOR ----------
void readSensor() {
  if (!sensorFound) return;

  temperature = bme.readTemperature();
  humidity = bme.readHumidity();
  pressure = bme.readPressure() / 100.0F;
}

// ---------- WEB ROOT ----------
void handleRoot() {
  String page = R"rawliteral(
<!DOCTYPE html>
<html>
<head>
<meta name="viewport" content="width=device-width, initial-scale=1">
<title>TEM-HU Dashboard</title>
<script src="https://cdn.jsdelivr.net/npm/chart.js"></script>
<style>
body{
  margin:0;
  font-family:Segoe UI, sans-serif;
  background:#0f172a;
  color:#e5e7eb;
}
.container{
  max-width:900px;
  margin:auto;
  padding:20px;
}
.card{
  background:#020617;
  padding:20px;
  border-radius:16px;
  box-shadow:0 0 20px rgba(0,0,0,.4);
}
.stats{
  display:flex;
  justify-content:space-around;
  margin:20px 0;
}
.stat{text-align:center}
canvas{margin-top:25px;}
</style>
</head>

<body>
<div class="container">
  <div class="card">
    <h1 style="text-align:center">kYNATIUM LABS : TEM-HU Live Monitor</h1>

    <div class="stats">
      <div class="stat"><p>Temp</p><h2 id="t">-- °C</h2></div>
      <div class="stat"><p>Humidity</p><h2 id="h">-- %</h2></div>
      <div class="stat"><p>Pressure</p><h2 id="p">-- hPa</h2></div>
    </div>

    <canvas id="tempChart"></canvas>
    <canvas id="humChart"></canvas>
    <canvas id="pressChart"></canvas>
  </div>
</div>

<script>
function createChart(ctx,label,color){
  return new Chart(ctx,{
    type:'line',
    data:{labels:[],datasets:[{label:label,data:[],borderColor:color,tension:.4}]},
    options:{responsive:true}
  });
}

const tempChart = createChart(
  document.getElementById('tempChart').getContext('2d'),
  'Temperature °C','#f97316'
);

const humChart = createChart(
  document.getElementById('humChart').getContext('2d'),
  'Humidity %','#38bdf8'
);

const pressChart = createChart(
  document.getElementById('pressChart').getContext('2d'),
  'Pressure hPa','#a855f7'
);

function update(){
  fetch('/data').then(r=>r.json()).then(d=>{
    document.getElementById('t').innerText=d.temperature+" °C";
    document.getElementById('h').innerText=d.humidity+" %";
    document.getElementById('p').innerText=d.pressure+" hPa";

    const time=new Date().toLocaleTimeString();

    [[tempChart,d.temperature],[humChart,d.humidity],[pressChart,d.pressure]]
    .forEach(c=>{
      c[0].data.labels.push(time);
      c[0].data.datasets[0].data.push(c[1]);
      if(c[0].data.labels.length>20){
        c[0].data.labels.shift();
        c[0].data.datasets[0].data.shift();
      }
      c[0].update();
    });
  });
}
setInterval(update,2000);
</script>
</body>
</html>
)rawliteral";

  server.send(200,"text/html",page);
}

// ---------- DATA ----------
void handleData() {
  readSensor();
  String json="{";
  json+="\"temperature\":"+String(temperature,1)+",";
  json+="\"humidity\":"+String(humidity,1)+",";
  json+="\"pressure\":"+String(pressure,1);
  json+="}";
  server.send(200,"application/json",json);
}

