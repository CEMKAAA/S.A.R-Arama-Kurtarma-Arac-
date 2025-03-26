#include <Arduino.h>
#include <esp_now.h>
#include <WiFi.h>
#include <vector>
#include <ESP32Servo.h>

extern "C" {
    #include <esp_wifi.h> // Required for setting Wi-Fi channels
}

// Motor movement directions
#define UP 1
#define DOWN 2
#define LEFT 3
#define RIGHT 4
#define UP_LEFT 5
#define UP_RIGHT 6
#define DOWN_LEFT 7
#define DOWN_RIGHT 8
#define TURN_LEFT 9
#define TURN_RIGHT 10
#define STOP 0

// Motor indices
#define FRONT_RIGHT_MOTOR 0
#define BACK_RIGHT_MOTOR 1
#define FRONT_LEFT_MOTOR 2
#define BACK_LEFT_MOTOR 3

// Motor directions
#define FORWARD 1
#define BACKWARD -1

#define PAN_PIN 5
#define TILT_PIN 2

Servo panServo;
Servo tiltServo;

// Define the motor pin structure
struct MOTOR_PINS {
  int pinIN1;
  int pinIN2;
  int pinEn; 
  int pwmSpeedChannel;
};

std::vector<MOTOR_PINS> motorPins = {
    {18, 15, 14, 4},  // FRONT_RIGHT_MOTOR - Right driver IN3, IN4, ENB
    {19, 22, 33, 5},   // BACK_RIGHT_MOTOR - Right driver IN1, IN2, ENA
    {12, 13, 27, 6},  // FRONT_LEFT_MOTOR - Left driver IN1, IN2, ENA
    {23, 21, 32, 7},  // BACK_LEFT_MOTOR - Left driver IN3, IN4, ENB
};

const int PWMFreq = 1000; /* 1 KHz */
const int PWMResolution = 8;

#define SIGNAL_TIMEOUT 1000  // Signal timeout in milliseconds
unsigned long lastRecvTime = 0;
int currentSpeed = 150; // Default speed

// Function prototypes
void rotateMotor(int motorNumber, int motorDirection);
void processCarMovement(int inputValue);

// Function to process car movement based on direction commands
void processCarMovement(int inputValue) {
  switch(inputValue) {
    case UP:
      rotateMotor(FRONT_RIGHT_MOTOR, FORWARD);
      rotateMotor(BACK_RIGHT_MOTOR, FORWARD);
      rotateMotor(FRONT_LEFT_MOTOR, FORWARD);
      rotateMotor(BACK_LEFT_MOTOR, FORWARD);                  
      break;
  
    case DOWN:
      rotateMotor(FRONT_RIGHT_MOTOR, BACKWARD);
      rotateMotor(BACK_RIGHT_MOTOR, BACKWARD);
      rotateMotor(FRONT_LEFT_MOTOR, BACKWARD);
      rotateMotor(BACK_LEFT_MOTOR, BACKWARD);   
      break;
  
    case LEFT:
      rotateMotor(FRONT_RIGHT_MOTOR, FORWARD);
      rotateMotor(BACK_RIGHT_MOTOR, BACKWARD);
      rotateMotor(FRONT_LEFT_MOTOR, BACKWARD);
      rotateMotor(BACK_LEFT_MOTOR, FORWARD);   
      break;
  
    case RIGHT:
      rotateMotor(FRONT_RIGHT_MOTOR, BACKWARD);
      rotateMotor(BACK_RIGHT_MOTOR, FORWARD);
      rotateMotor(FRONT_LEFT_MOTOR, FORWARD);
      rotateMotor(BACK_LEFT_MOTOR, BACKWARD);  
      break;
  
    case UP_LEFT:
      rotateMotor(FRONT_RIGHT_MOTOR, FORWARD);
      rotateMotor(BACK_RIGHT_MOTOR, STOP);
      rotateMotor(FRONT_LEFT_MOTOR, STOP);
      rotateMotor(BACK_LEFT_MOTOR, FORWARD);  
      break;
  
    case UP_RIGHT:
      rotateMotor(FRONT_RIGHT_MOTOR, STOP);
      rotateMotor(BACK_RIGHT_MOTOR, FORWARD);
      rotateMotor(FRONT_LEFT_MOTOR, FORWARD);
      rotateMotor(BACK_LEFT_MOTOR, STOP);  
      break;
  
    case DOWN_LEFT:
      rotateMotor(FRONT_RIGHT_MOTOR, STOP);
      rotateMotor(BACK_RIGHT_MOTOR, BACKWARD);
      rotateMotor(FRONT_LEFT_MOTOR, BACKWARD);
      rotateMotor(BACK_LEFT_MOTOR, STOP);   
      break;
  
    case DOWN_RIGHT:
      rotateMotor(FRONT_RIGHT_MOTOR, BACKWARD);
      rotateMotor(BACK_RIGHT_MOTOR, STOP);
      rotateMotor(FRONT_LEFT_MOTOR, STOP);
      rotateMotor(BACK_LEFT_MOTOR, BACKWARD);   
      break;
  
    case TURN_LEFT:
      rotateMotor(FRONT_RIGHT_MOTOR, FORWARD);
      rotateMotor(BACK_RIGHT_MOTOR, FORWARD);
      rotateMotor(FRONT_LEFT_MOTOR, BACKWARD);
      rotateMotor(BACK_LEFT_MOTOR, BACKWARD);  
      break;
  
    case TURN_RIGHT:
      rotateMotor(FRONT_RIGHT_MOTOR, BACKWARD);
      rotateMotor(BACK_RIGHT_MOTOR, BACKWARD);
      rotateMotor(FRONT_LEFT_MOTOR, FORWARD);
      rotateMotor(BACK_LEFT_MOTOR, FORWARD);   
      break;
  
    case STOP:
    default:
      rotateMotor(FRONT_RIGHT_MOTOR, STOP);
      rotateMotor(BACK_RIGHT_MOTOR, STOP);
      rotateMotor(FRONT_LEFT_MOTOR, STOP);
      rotateMotor(BACK_LEFT_MOTOR, STOP);    
      break;
  }
}

// Helper function to control individual motors
void rotateMotor(int motorNumber, int motorDirection) {
  if (motorDirection == FORWARD) {
    digitalWrite(motorPins[motorNumber].pinIN1, HIGH);
    digitalWrite(motorPins[motorNumber].pinIN2, LOW);    
  }
  else if (motorDirection == BACKWARD) {
    digitalWrite(motorPins[motorNumber].pinIN1, LOW);
    digitalWrite(motorPins[motorNumber].pinIN2, HIGH);     
  }
  else {
    digitalWrite(motorPins[motorNumber].pinIN1, LOW);
    digitalWrite(motorPins[motorNumber].pinIN2, LOW);       
  }
}

// Translate Turkish direction names to English
String translateDirection(String turkishDir) {
  if (turkishDir == "dogu") return "RIGHT";  // Changed
  if (turkishDir == "bati") return "LEFT";   // Changed
  if (turkishDir == "kuzey") return "UP";    // Changed
  if (turkishDir == "guney") return "DOWN";  // Changed
  return "CENTER"; // Default
}

// Determine combined movement direction from left and right joysticks
int getCombinedDirection(String leftDir, String rightDir, bool isMovementMode) {
  // Translate Turkish directions
  leftDir = translateDirection(leftDir);
  rightDir = translateDirection(rightDir);
  
  Serial.println(leftDir + " " + rightDir);
  
  if (isMovementMode) {
    // MOVEMENT MODE
    if (leftDir == "CENTER") return STOP;
    
    if (leftDir == "UP") {
      if (rightDir == "RIGHT") return UP_RIGHT;
      if (rightDir == "LEFT") return UP_LEFT;
      return UP;
    } 
    else if (leftDir == "DOWN") {
      if (rightDir == "RIGHT") return DOWN_RIGHT;
      if (rightDir == "LEFT") return DOWN_LEFT;
      return DOWN;
    }
    else if (leftDir == "LEFT") {
      return LEFT;
    }
    else if (leftDir == "RIGHT") {
      return RIGHT;
    }
  } else {
    // TURN MODE
    if (leftDir == "LEFT") return TURN_LEFT;
    if (leftDir == "RIGHT") return TURN_RIGHT;
  }
  
  return STOP;
}

// Callback function executed when ESP-NOW data is received
void OnDataRecv(const uint8_t* mac, const uint8_t* incomingData, int len) {
    Serial.print("Data received from: ");
    char macStr[18];
    snprintf(macStr, sizeof(macStr), "%02X:%02X:%02X:%02X:%02X:%02X", 
             mac[0], mac[1], mac[2], mac[3], mac[4], mac[5]);
    Serial.println(macStr);

    // Convert incoming data to a String (assumes null-terminated string)
    String cmd = String((char*) incomingData);
    Serial.print("Received command: ");
    Serial.println(cmd);

    lastRecvTime = millis();  // Update the timestamp for watchdog timer

    // Parse the command: MOVE:L:direction,R:direction,SPEED:value
    bool isMovementMode = cmd.startsWith("MOVE:");
    
    // Extract L direction
    int lIndex = cmd.indexOf("L:");
    int commaIndex = cmd.indexOf(",", lIndex);
    String leftDir = "";
    if (lIndex >= 0 && commaIndex > lIndex) {
        leftDir = cmd.substring(lIndex + 2, commaIndex);
    }
    
    // Extract R direction
    int rIndex = cmd.indexOf("R:");
    commaIndex = cmd.indexOf(",", rIndex);
    String rightDir = "";
    if (rIndex >= 0 && commaIndex > rIndex) {
        rightDir = cmd.substring(rIndex + 2, commaIndex);
    }

    // Extract PAN value (for servo control)
    int panIndex = cmd.indexOf("PAN:");
    int panValue = -1; // Default value to indicate no pan value
    if (panIndex >= 0) {
        commaIndex = cmd.indexOf(",", panIndex);
        if (commaIndex > panIndex) {
            panValue = cmd.substring(panIndex + 4, commaIndex).toInt();
        } else {
            // If no comma after PAN, go to the end of the string
            panValue = cmd.substring(panIndex + 4).toInt();
        }
        
        // Apply PAN value to servo if valid
        if (panValue >= 0 && panValue <= 180) {
            panServo.write(panValue);
            Serial.print("Setting PAN to: ");
            Serial.println(panValue);
        }
    }
    
    // Extract TILT value (for servo control)
    int tiltIndex = cmd.indexOf("TILT:");
    int tiltValue = -1; // Default value to indicate no tilt value
    if (tiltIndex >= 0) {
        commaIndex = cmd.indexOf(",", tiltIndex);
        if (commaIndex > tiltIndex) {
            tiltValue = cmd.substring(tiltIndex + 5, commaIndex).toInt();
        } else {
            // If no comma after TILT, go to the end of the string
            tiltValue = cmd.substring(tiltIndex + 5).toInt();
        }
        
        // Apply TILT value to servo if valid
        if (tiltValue >= 0 && tiltValue <= 180) {
            tiltServo.write(tiltValue);
            Serial.print("Setting TILT to: ");
            Serial.println(tiltValue);
        }
    }
    
    // Extract speed
    int speedIndex = cmd.indexOf("SPEED:");
    int speedValue = 150; // Default speed
    if (speedIndex >= 0) {
        speedValue = cmd.substring(speedIndex + 6).toInt();
        // Map from 1-10 to PWM range
        speedValue = map(speedValue, 1, 10, 50, 255);
        currentSpeed = speedValue;
        
        // Set speed for all motors
        for (int i = 0; i < motorPins.size(); i++) {
            ledcWrite(motorPins[i].pwmSpeedChannel, speedValue);
        }
    }
    
    // Get combined direction from both joysticks
    int movementValue = getCombinedDirection(leftDir, rightDir, isMovementMode);
    
    Serial.print("Left income: "); Serial.println(leftDir);

    Serial.print("Right income: "); Serial.println(rightDir);

    Serial.print("Speed income: "); Serial.println(speedValue);

    Serial.print("Mode income: "); Serial.println(isMovementMode);

    // Process the movement
    processCarMovement(movementValue);
    
    // Debug output
    Serial.print("Processed movement: ");
    Serial.print(movementValue);
    Serial.print(", Speed: ");
    Serial.println(speedValue);
}

void setUpPinModes() {
    // Initialize motor pins
    for (int i = 0; i < motorPins.size(); i++) {
        pinMode(motorPins[i].pinIN1, OUTPUT);
        pinMode(motorPins[i].pinIN2, OUTPUT);  
        
        // Set up PWM for motor speed
        ledcSetup(motorPins[i].pwmSpeedChannel, PWMFreq, PWMResolution);  
        ledcAttachPin(motorPins[i].pinEn, motorPins[i].pwmSpeedChannel);
        ledcWrite(motorPins[i].pwmSpeedChannel, 0);     
        rotateMotor(i, STOP);  
    }
}

void setup() {
    // Initialize serial communication
    Serial.begin(115200);
    delay(1000);
    
    // Set up pin modes for motors
    setUpPinModes();
    
    // Initialize WiFi in station mode
    WiFi.mode(WIFI_STA);
    Serial.print("Receiver ESP32 MAC Address: ");
    Serial.println(WiFi.macAddress());
    
    // Disconnect from any previous WiFi connection
    WiFi.disconnect();
    delay(100);
    
    // Set WiFi channel for ESP-NOW
    int AP_Channel = 5; // Use the same channel as your sender
    esp_err_t channel_err = esp_wifi_set_channel(AP_Channel, WIFI_SECOND_CHAN_NONE);
    if (channel_err != ESP_OK) {
        Serial.println("Error setting WiFi channel");
        return;
    } else {
        Serial.printf("WiFi channel set to %d\n", AP_Channel);
    }
    
    // Initialize ESP-NOW
    if (esp_now_init() != ESP_OK) {
        Serial.println("Error initializing ESP-NOW");
        return;
    }
    Serial.println("ESP-NOW initialized successfully");
    
    // Register callback function
    esp_now_register_recv_cb(OnDataRecv);

    // Initialize servos after boot and WiFi setup is complete
    delay(100);  // Give boot process time to complete
    panServo.attach(PAN_PIN);
    tiltServo.attach(TILT_PIN);
    
    // Set initial servo positions
    panServo.write(90);
    tiltServo.write(90);

    Serial.println("Ready to receive commands");
    
    // Initialize timestamp for signal timeout
    lastRecvTime = millis();
}

void loop() {
    // Check for signal timeout
    if (millis() - lastRecvTime > SIGNAL_TIMEOUT) {
        // No signal received for a while, stop the car
        processCarMovement(STOP);
        Serial.println("the reason of stopping is me!!!");
    }
    
    // Small delay to prevent CPU hogging
    delay(10);
}