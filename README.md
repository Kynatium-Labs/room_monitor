# kYNATIUM LABS - TEM-HU Weather Station

ESP32-based environmental monitoring system with BME280 sensor operating in WiFi Access Point mode. Features real-time temperature, humidity, and pressure monitoring with individual live charts.

## 🌟 Overview

This project creates a standalone weather station that hosts its own WiFi network - no router or internet connection required. Perfect for remote monitoring, educational projects, or portable environmental sensing applications.

## 🎯 Key Features

- ✅ **Standalone WiFi Access Point** - Creates its own network (TEM-HU)
- ✅ **BME280 Sensor Integration** - High-precision environmental sensing
- ✅ **Real-time Monitoring** - Temperature, Humidity & Atmospheric Pressure
- ✅ **Three Dedicated Charts** - Individual live graphs for each measurement
- ✅ **Auto-refresh Dashboard** - Updates every 2 seconds
- ✅ **Responsive Web Interface** - Works on phones, tablets, and computers
- ✅ **JSON REST API** - Easy integration with other systems
- ✅ **No Internet Required** - Fully offline operation
- ✅ **Professional UI** - Modern dark theme with Chart.js visualization

## 🔧 Hardware Requirements

| Component | Description |
|-----------|-------------|
| **ESP32** | Any ESP32 development board |
| **BME280** | Temperature, Humidity & Pressure sensor module |
| **Wires** | Jumper wires for connections |
| **Power** | USB cable or 5V power supply |

## 📌 Wiring Diagram

Connect the BME280 sensor to ESP32 using I2C interface:

```
BME280 Module    ESP32 Board
─────────────────────────────
VCC          →   3.3V
GND          →   GND
SCL          →   GPIO 22 (I2C Clock)
SDA          →   GPIO 21 (I2C Data)
```

### Connection Notes:
- ⚠️ Use **3.3V** (not 5V) for BME280 power
- I2C uses two wires: SCL (clock) and SDA (data)
- Most BME280 modules have built-in pull-up resistors
- Sensor address is auto-detected (0x76 or 0x77)

## 📦 Arduino IDE Setup

### 1. Install ESP32 Board Support

1. Open Arduino IDE
2. Go to `File → Preferences`
3. Add this URL to **Additional Board Manager URLs**:
   ```
   https://dl.espressif.com/dl/package_esp32_index.json
   ```
4. Go to `Tools → Board → Boards Manager`
5. Search for "esp32"
6. Install "esp32 by Espressif Systems"

### 2. Install Required Libraries

Open `Sketch → Include Library → Manage Libraries` and install:

| Library | Author | Purpose |
|---------|--------|---------|
| **Adafruit BME280 Library** | Adafruit | BME280 sensor driver |
| **Adafruit Unified Sensor** | Adafruit | Required dependency |

The Adafruit Unified Sensor library will be automatically prompted for installation.

## 🚀 Installation & Setup

### Step 1: Configure WiFi (Optional)

Default Access Point credentials:
```cpp
const char* ssid = "TEM-HU";
const char* password = "@hlamahfuj";
```

To customize, edit these lines at the top of `hutupu.ino`.

### Step 2: Upload Code

1. Connect ESP32 to computer via USB
2. Open `hutupu.ino` in Arduino IDE
3. Select board: `Tools → Board → ESP32 Dev Module`
4. Select port: `Tools → Port → (your COM port)`
5. Click the **Upload** button (→)
6. Wait for "Done uploading" message

### Step 3: Verify Operation

1. Open Serial Monitor (`Ctrl+Shift+M`)
2. Set baud rate to **115200**
3. You should see:
   ```
   ✓ BME280 Found
   AP IP: 192.168.4.1
   ```

### Step 4: Connect & Access

**On your device (phone/tablet/computer):**

1. **Connect to WiFi network:**
   - Network: `TEM-HU`
   - Password: `@hlamahfuj`

2. **Open web browser and visit:**
   ```
   http://192.168.4.1
   ```

3. **View real-time sensor data!** 🎉

## 📊 Dashboard Features

### Real-time Display Cards

The dashboard shows three metric cards:

- 🌡️ **Temperature** - Current reading in °C
- 💧 **Humidity** - Relative humidity percentage
- 📊 **Pressure** - Atmospheric pressure in hPa

### Live Charts

Three separate live-updating charts:

1. **Temperature Chart** (Orange) - Shows temperature trends
2. **Humidity Chart** (Blue) - Displays humidity variations
3. **Pressure Chart** (Purple) - Tracks pressure changes

**Chart Features:**
- Rolling 20-point history
- Auto-updates every 2 seconds
- Time-stamped data points
- Smooth line animations
- Responsive design

## 🌐 API Documentation

### Endpoint: `/data`

Returns current sensor readings in JSON format.

**Request:**
```http
GET http://192.168.4.1/data
```

**Response:**
```json
{
  "temperature": 24.5,
  "humidity": 62.3,
  "pressure": 1013.2
}
```

**Use Cases:**
- Data logging applications
- Custom mobile apps
- IoT integrations
- Home automation systems

### Endpoint: `/`

Serves the complete web dashboard interface.

## ⚙️ Configuration Options

### Change WiFi Credentials

```cpp
const char* ssid = "YOUR_NETWORK_NAME";
const char* password = "YOUR_PASSWORD";
```

### Adjust Update Interval

In the HTML section, modify the JavaScript:
```javascript
setInterval(update, 2000);  // Change 2000 to desired milliseconds
```

### Change Chart History Length

```javascript
if(c[0].data.labels.length > 20){  // Change 20 to desired points
```

### Modify I2C Address

If your BME280 uses a specific address:
```cpp
if (bme.begin(0x76)) {  // Try 0x76 or 0x77
```

### Customize Sea Level Pressure

For altitude calculations:
```cpp
#define SEALEVELPRESSURE_HPA 1013.25  // Adjust for your location
```

## 🐛 Troubleshooting

### ❌ BME280 Not Found

**Symptoms:** Serial Monitor shows "✗ BME280 NOT Found"

**Solutions:**
- ✓ Verify I2C wiring (SDA→GPIO21, SCL→GPIO22)
- ✓ Check power connection (3.3V)
- ✓ Ensure sensor is not damaged
- ✓ Try swapping SDA/SCL wires
- ✓ Test with I2C scanner sketch

### ❌ Cannot Connect to WiFi Network

**Symptoms:** "TEM-HU" network not visible

**Solutions:**
- ✓ Check Serial Monitor for "AP IP: 192.168.4.1"
- ✓ Move closer to ESP32
- ✓ Restart ESP32 (press reset button)
- ✓ Check if ESP32 is powered properly
- ✓ Look for network starting with "TEM"

### ❌ Dashboard Won't Load

**Symptoms:** Browser can't reach 192.168.4.1

**Solutions:**
- ✓ Verify connected to "TEM-HU" WiFi
- ✓ Use `http://` not `https://`
- ✓ Try `http://192.168.4.1/` (with trailing slash)
- ✓ Disable mobile data on phone
- ✓ Clear browser cache
- ✓ Try different browser

### ❌ Data Shows "-- °C"

**Symptoms:** Values not updating

**Solutions:**
- ✓ Check Serial Monitor for sensor detection
- ✓ Verify BME280 connections
- ✓ Refresh browser page (F5)
- ✓ Check browser console for errors (F12)

### ❌ Charts Not Displaying

**Symptoms:** Numbers show but no graphs

**Solutions:**
- ✓ Ensure internet access for Chart.js CDN (first load only)
- ✓ Check browser console for JavaScript errors
- ✓ Try clearing browser cache
- ✓ Use updated browser version

## 💡 Usage Tips

### Portable Operation
- Power ESP32 with USB power bank
- Take measurements anywhere
- No WiFi router needed

### Multiple Simultaneous Users
- Up to 4 devices can connect
- Each sees real-time data
- No lag or interference

### Data Logging
- Use `/data` API endpoint
- Log readings to database
- Create historical records

### Custom Integration
- Parse JSON data programmatically
- Build custom dashboards
- Integrate with IoT platforms

## 📱 Mobile Access

The dashboard is fully optimized for mobile devices:

- ✓ **Smartphones** - iOS and Android
- ✓ **Tablets** - All sizes
- ✓ **Laptops** - Windows, Mac, Linux
- ✓ **Desktop** - All modern browsers

**Recommended Browsers:**
- Chrome / Edge
- Firefox
- Safari
- Opera

## 🔐 Security Considerations

**Current Setup:**
- Open Access Point with password protection
- WPA2 encryption enabled by default
- Suitable for local/educational use

**For Production:**
- Change default password to strong passphrase
- Implement additional authentication
- Consider adding HTTPS
- Enable MAC address filtering if needed

## 📈 Technical Specifications

### Sensor (BME280)
- **Temperature Range:** -40°C to +85°C
- **Temperature Accuracy:** ±1°C
- **Humidity Range:** 0-100% RH
- **Humidity Accuracy:** ±3% RH
- **Pressure Range:** 300-1100 hPa
- **Pressure Accuracy:** ±1 hPa
- **Interface:** I2C (0x76 or 0x77)

### System Performance
- **Update Rate:** 2 seconds
- **Chart History:** 20 data points per metric
- **Max Connections:** 4 simultaneous devices
- **Power Consumption:** 80-260mA (typical)
- **Operating Voltage:** 5V USB or 3.3-5V regulated

### Network Details
- **Mode:** WiFi Access Point (AP)
- **Default IP:** 192.168.4.1
- **SSID:** TEM-HU
- **Security:** WPA2-PSK
- **Channel:** Auto-selected

## 🎨 Dashboard Design

**Color Scheme:**
- Background: Dark slate (#0f172a)
- Cards: Darker slate (#020617)
- Temperature: Orange (#f97316)
- Humidity: Cyan (#38bdf8)
- Pressure: Purple (#a855f7)
- Text: Light gray (#e5e7eb)

**Typography:**
- Font: Segoe UI (sans-serif fallback)
- Responsive sizing
- Clean, modern aesthetic

## 🔄 Firmware Updates

To update the code:
1. Make changes to `hutupu.ino`
2. Upload via Arduino IDE
3. Device will restart automatically
4. Reconnect to TEM-HU network

## 📂 Project Structure

```
hutupu.ino
├── Libraries
│   ├── WiFi (ESP32 built-in)
│   ├── WebServer (ESP32 built-in)
│   ├── Wire (I2C communication)
│   ├── Adafruit_Sensor
│   └── Adafruit_BME280
├── Web Interface (embedded HTML/CSS/JS)
│   ├── Chart.js (CDN)
│   ├── Responsive layout
│   └── Three canvas charts
└── REST API
    ├── GET / (dashboard)
    └── GET /data (JSON)
```

## 🎓 Educational Value

**Learn About:**
- ESP32 microcontroller programming
- I2C sensor communication
- WiFi Access Point creation
- Web server implementation
- Real-time data visualization
- REST API development
- Responsive web design
- JSON data handling

## 🚀 Advanced Modifications

### Add Temperature Alerts
```cpp
if (temperature > 30) {
  // Trigger alert
}
```

### Store Historical Data
```cpp
// Add SD card logging
// Store readings with timestamps
```

### Add More Sensors
```cpp
// Integrate CO2, light, or other sensors
// Expand dashboard accordingly
```

### Custom Themes
Modify CSS section to change colors and styles.

## 📝 License

Free to use and modify for personal, educational, and commercial projects.

## 🤝 Support & Troubleshooting

**Serial Monitor Output:**
- Baud Rate: **115200**
- Shows sensor status
- Displays AP IP address
- Useful for debugging

**Common Issues:**
1. Check connections first
2. Verify power supply
3. Confirm library installations
4. Review Serial Monitor output

## ⚡ Power Requirements

**USB Power:**
- 5V 1A minimum
- 2A recommended for stable operation

**Battery Operation:**
- Use 3.7V LiPo with voltage regulator
- Or 5V power bank
- Typical runtime: 8-12 hours (2000mAh)

## 🌍 Applications

- **Home Monitoring** - Indoor climate tracking
- **Greenhouse** - Plant environment control
- **Weather Station** - Personal meteorology
- **HVAC Systems** - Performance monitoring
- **Education** - IoT learning projects
- **Data Center** - Temperature monitoring
- **Laboratory** - Environmental logging
- **Portable Sensing** - Field measurements

---

**Built with ❤️ by kYNATIUM LABS**

**Technology Stack:** ESP32 + BME280 + Chart.js

**Access Point Mode - Freedom from Router Dependency!** 📡🌡️💧📊
