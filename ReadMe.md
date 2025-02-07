# LED Matrix v2

## Overview
The LED Matrix v2 project brings together firmware code for controlling an LED matrix and a dedicated Python interface for easier interaction.
This Project is currently divided into two parts:
![LED Matrix Image](assets/Heart.png)

1. The Code
2. Python Interface

---

## Part 1: The Code

### Description
This section contains the firmware code written for the LED matrix. The code is designed to run on a microcontroller using PlatformIO, managing the LED matrix behaviors, animations, and hardware interactions.

### Project Structure
- **src/**: Contains the main firmware source files.
- **include/**: Header files and definitions for the project.
- **lib/**: Additional libraries if any.
- **platformio.ini**: Configuration file for PlatformIO, defining environment settings and build parameters.

### Dependencies
- PlatformIO Core (CLI) for building and uploading code.
- Required microcontroller-specific libraries (e.g., FastLED, Adafruit GFX, etc.)

### Setup & Installation
1. Install [PlatformIO](https://platformio.org/install).
2. Open the project folder in your preferred IDE (VSCode recommended with the PlatformIO extension).
3. If necessary, edit the `platformio.ini` to match your hardware configuration.
4. Build and upload the firmware:
    - Use the PlatformIO Build command (`PlatformIO: Build`) to compile the code.
    - Use the PlatformIO Upload command (`PlatformIO: Upload`) to flash the firmware to your microcontroller.

### Code Highlights
- **Initialization**: Setup routines for the LED matrix, including pin configuration and matrix dimensions.
- **Animation Logic**: Code operations for animating sequences, colors, and brightness adjustments.
- **Utilities**: Helper functions for LED color calculations and hardware interfacing.

---

## Part 2: Python Interface

### Description
The Python interface facilitates communication between your computer and the LED matrix device. It allows real-time control and testing of LED patterns via a user-friendly script.

### Features
- Real-time command sending to the LED matrix.
- Diagnostic outputs to monitor the matrix status.
- GUI options (if extended) for a more dynamic control experience.

### Requirements
- Python 3.x installed.
- Packages such as `pyserial` for serial communication.
- Additional libraries based on your control method (e.g., `tkinter` for GUI development).

### Setup & Usage
1. **Install Dependencies:**
    - Use pip to install necessary libraries:
      Command:  
      `pip install pyserial`

2. **Configuration:**
    - Edit the Python script (e.g., `interface.py`) to match the correct COM port and baud rate:
      Example snippet:
      <pre>
import serial

# Update with your device's details
ser = serial.Serial('COM3', 9600, timeout=1)
      </pre>

3. **Running the Interface:**
    - Execute the Python script:
      Command:  
      `python interface.py`
    - Follow on-screen instructions to send commands and receive responses from the LED matrix.

### Extending the Interface
- **GUI Development:** Explore libraries like PyQt or Tkinter to create a visual control panel.
- **Script Automation:** Integrate command scripts to automate complex light shows.

---

## License
This project is licensed under the MIT License.

## Contact
For questions or contributions, please contact the maintainer.
