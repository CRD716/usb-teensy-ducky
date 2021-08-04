#include <SD.h>
bool trycmdadmin = true;
char commandseperator = ';';

void setup() {
  pinMode(13, OUTPUT); // Onboard LED
  digitalWrite(13, LOW);
  delay(500);

  // Get CMD to try to run as admin
  Keyboard.press(MODIFIERKEY_GUI);
  delay(250);
  Keyboard.press(KEY_R);
  delay(250);
  Keyboard.release(MODIFIERKEY_GUI);
  Keyboard.release(KEY_R);
  Keyboard.print("CMD");
  if (trycmdadmin) {
    Keyboard.press(MODIFIERKEY_CTRL);
    Keyboard.press(MODIFIERKEY_SHIFT);
  }
  Keyboard.press(KEY_ENTER);
  delay(100);
  Keyboard.release(KEY_ENTER);
  if (trycmdadmin) {
    Keyboard.release(MODIFIERKEY_CTRL);
    Keyboard.release(MODIFIERKEY_SHIFT);

    // accept UAC prompt
    delay(500);
    Keyboard.press(KEY_LEFT);
    Keyboard.release(KEY_LEFT);
    delay(326);
    Keyboard.press(KEY_ENTER);
    Keyboard.release(KEY_ENTER);
    delay(362);
  }

  // Start reading the commands

  SD.begin(BUILTIN_SDCARD);
  File dataFile = SD.open("commands.txt");
  if (dataFile) {
    // Loop to run commands until no more new lines
    bool finishedcommands = false;
    while (!finishedcommands) {
      String command = "";
      while (true) {
        char nextChar = (char)dataFile.read();
        if (nextChar == commandseperator) {
          break;
        }
        if () {
          finishedcommands = true;
          break;
        }
        // Keyboard.print(nextChar); //Debug, types out the characters one by one. Keeping incase there's basic detection.
        command += nextChar;
      }
      Keyboard.print(command);
      delay(80);
      Keyboard.press(KEY_ENTER);
      delay(70);
      Keyboard.release(KEY_ENTER);
    }
    dataFile.close();

  }
  else {
    Keyboard.write("echo No commands.txt file found. Exiting.");
    Keyboard.press(KEY_ENTER);
    delay(100);
    Keyboard.release(KEY_ENTER);
  }

  digitalWrite(13, HIGH);
}

void loop() {
  exit(0);
}
