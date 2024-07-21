#include <Adafruit_MPU6050.h>
#include <Adafruit_Sensor.h>
#include <Kalman.h>
#include <ESP8266WiFi.h>

#define ssid  ""
#define pwsd  ""
const int httpPort = 80;
const char* host = "";  // Server IP address

// Create instances for Kalman filter
Kalman kalmanRoll;

// Create instances for Mpu6050 Sensor
Adafruit_MPU6050 mpu;

// WifiClient instance
WiFiClient client;

// Time step
unsigned long lastTime;
unsigned long currentTime = micros();
float dt;
double x;
double y;
double z;

void setup() {
    Serial.begin(115200);
    Serial.println();
    Serial.println();
    Serial.print("Connecting to ");
    Serial.println(ssid);

    WiFi.mode(WIFI_STA);
    WiFi.begin(ssid, pwsd);

    while (WiFi.status() != WL_CONNECTED) {
        delay(500);
        Serial.print(".");
    }

    Serial.println("");
    Serial.println("WiFi connected");
    Serial.println("IP address: ");
    Serial.println(WiFi.localIP());

    // Try to initialize!
  if (!mpu.begin()) {
    Serial.println("Failed to find MPU6050 chip");
    while (1) {
      mpu.begin();
    }
  }

  // Initialize the Kalman filter
  kalmanRoll.setAngle(0); // Starting angle

  // Initialize time
  lastTime = micros();

  //setupt motion detection
  mpu.setAccelerometerRange(MPU6050_RANGE_2_G);
  mpu.setGyroRange(MPU6050_RANGE_250_DEG);
  mpu.setFilterBandwidth(MPU6050_BAND_21_HZ);
}

void loop() {

  // Calculate the time step
  
  dt = (currentTime - lastTime) / 1000000.0;
  lastTime = currentTime;

  /* Get new sensor events with the readings */
  sensors_event_t a, g, temp;
  mpu.getEvent(&a, &g, &temp);

  float accelX = a.acceleration.x;
  float accelY = a.acceleration.y;
  float accelZ = a.acceleration.z;
  float gyroX = g.gyro.x;
  float gyroY = g.gyro.y;
  float gyroZ = g.gyro.z;

  // Converting Values of accelaration into angle
  int xAng = atan2(accelY, accelZ) * 180 / PI;
  int yAng = atan2(accelX, accelZ) * 180 / PI;
  int zAng = atan2(accelY, accelX) * 180 / PI;

  // Adjust Kalman filter parameters for faster response
  kalmanRoll.setQangle(0.3);  // Process noise covariance for the accelerometer
  kalmanRoll.setQbias(0.1);   // Process noise covariance for the gyroscope
  kalmanRoll.setRmeasure(0.8); // Measurement noise covariance

  // Sensor Fusion Using Kalman Filter of Gyro and Accelerometer data
  float roll = kalmanRoll.getAngle(xAng, gyroX, dt);

  /* Print out the values */
  Serial.print("X Angle:");
  Serial.println(xAng);
  Serial.print("Roll Angle:");
  Serial.println(roll);

  // Transmitting data to receiver  
  
  if (!client.connect(host, httpPort)) {
    Serial.println("Connection failed");
    return;
  }

  client.print(String(roll) + "\n");
  Serial.println("Sent value: " + String(roll));

  client.stop();
  delay(50);
}
