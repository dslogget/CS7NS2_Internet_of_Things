# CS7NS2 Internet of Things Group 5 Project

## Circuit Setup
Attach the ESP-32 Devkit-C V4 to the components outlined in the schematic in [KiCad Schematics/CurrentSchematic.pdf](KiCad%20Schematics/CurrentSchematic.pdf)

## Building and uploading the program to the ESP-32
- Ensure you have the "espressif 32" platform installed on platformio. [See here for a tutorial for VSCode](https://www.youtube.com/watch?v=5edPOlQQKmo)
- Open the platformio project in your preferred platformio platform (eg Visual Studio Code)
- Add your wifi credentials to the file `Embedded/Test_Program_1/include/Credentials.h` **Note:** an example of the include file is contained in [Embedded/Test_Program_1/include/Credentials.h.template](Embedded/Test_Program_1/include/Credentials.h.template)
This can be renamed, and your credentials filled in
- Build the project
- Upload the project to the ESP-32
**Note:** Your board may require you to hold down the **boot** button while platformio starts attempting to upload to the ESP-32
