// -------------------------------------------------------
// Bluetooth Color Guessing Game + TCS3200
// -------------------------------------------------------

#include "BluetoothSerial.h"
BluetoothSerial BT;

#define S0 23
#define S1 22
#define S2 19
#define S3 18
#define OUT 5

int Rf, Gf, Bf;

bool gameStarted = false;

// ------------------ Setup ------------------
void setup() {
  Serial.begin(115200);
  BT.begin("ESP32_COLOR_GAME");

  pinMode(S0, OUTPUT);
  pinMode(S1, OUTPUT);
  pinMode(S2, OUTPUT);
  pinMode(S3, OUTPUT);
  pinMode(OUT, INPUT);

  digitalWrite(S0, HIGH);
  digitalWrite(S1, HIGH);

  Serial.println("Bluetooth Color Game Started");
  BT.println("Bluetooth Color Game Ready");

  BT.println("Connected to ESP32!");
  BT.println("Waiting for a valid color to begin the game...");

}

// ------------------ Averaged Frequency ------------------
int readFreq() {
  long total = 0;
  for (int i = 0; i < 10; i++)
    total += pulseIn(OUT, LOW);
  return total / 10;
}

// ------------------ Read RGB Frequencies ------------------
void readRGB() {
  digitalWrite(S2, LOW);
  digitalWrite(S3, LOW);
  delay(20);
  Rf = readFreq();

  digitalWrite(S2, HIGH);
  digitalWrite(S3, HIGH);
  delay(20);
  Gf = readFreq();

  digitalWrite(S2, LOW);
  digitalWrite(S3, HIGH);
  delay(20);
  Bf = readFreq();
}

// ------------------ Color Name Logic ------------------
String getColor(int R, int G, int B) {

  if (R > 35 && G > 45 && B > 45)
    return "No Object";

  if (R < G - 3 && R < B - 3)
    return "Red";

  if (G < R - 3 && G < B - 3)
    return "Green";

  if (B < R - 3 && B < G - 3)
    return "Blue";

  return "Unknown";
}

// ------------------ Game Variables ------------------
int score = 0;
int rounds = 0;
bool hasPositiveScore = false;

void loop() {

  // -------------------------
  // IGNORE NOISE CHARACTERS
  // -------------------------
  if (BT.available()) {
    char incoming = BT.read();

    // Ignore newline, carriage return, space, null chars
    if (incoming == '\n' || incoming == '\r' || incoming == ' ' || incoming == 0) {
      return;
    }

    // If game not started yet, wait for valid color
    if (!gameStarted) {

      readRGB();
      String detectedStart = getColor(Rf, Gf, Bf);

      if (detectedStart == "Red" || detectedStart == "Green" || detectedStart == "Blue") {
        gameStarted = true;
        BT.println("=====================================");
        BT.println("      🎮 COLOR GUESSING GAME 🎮");
        BT.println("=====================================");
        BT.println("Rules:");
        BT.println("• Send your guess via Bluetooth:");
        BT.println("      1 → Red");
        BT.println("      2 → Green");
        BT.println("      3 → Blue");
        BT.println("• Correct guess: +5 points");
        BT.println("• Wrong guess: -2 points (after positive score)");
        BT.println("• Game ends when:");
        BT.println("      → Score ≤ 0 (after being positive)");
        BT.println("      → OR 10 rounds completed");
        BT.println("-------------------------------------");
        BT.println("Game Started! Send 1/2/3 to guess...");
        BT.println("-------------------------------------");
        return;
      } else {
        // Keep waiting for a valid object
        BT.println("Place a Red/Green/Blue object to begin...");
        return;
      }
    }

    // -------------------------
    // MAIN GAME INPUT
    // -------------------------

    // Reject everything except 1, 2, 3
    if (incoming != '1' && incoming != '2' && incoming != '3') {
      BT.println("Invalid Input! Use only: 1=Red, 2=Green, 3=Blue");
      return;
    }

    int guess = incoming - '0';
    String guessName = (guess == 1 ? "Red" :
                        guess == 2 ? "Green" : "Blue");

    readRGB();
    String detected = getColor(Rf, Gf, Bf);

    // Unknown → skip
    if (detected == "Unknown" || detected == "No Object") {
      BT.println("Waiting for valid color...");
      return;
    }

    // Process valid round
    rounds++;

    BT.print("Round ");
    BT.println(rounds);

    BT.print("Your Guess: ");
    BT.println(guessName);

    BT.print("Actual Color: ");
    BT.println(detected);

    if (guessName == detected) {
      score += 5;
      hasPositiveScore = true;
      BT.println("Result: Correct (+5)");
    } else {
      if (hasPositiveScore) score -= 2;
      BT.println("Result: Wrong (-2)");
    }

    BT.print("Score: ");
    BT.println(score);
    BT.println("--------------------------------");

    // Game end conditions
    if ((score <= 0 && hasPositiveScore) || rounds >= 10) {
      BT.println("========== GAME OVER ==========");
      BT.println("Final Score: " + String(score));
      BT.println("================================");

      // Reset
      rounds = 0;
      score = 0;
      hasPositiveScore = false;
      gameStarted = false;

      BT.println("\nShow any valid color (Red/Green/Blue) to start a NEW GAME!");
    }
  }
}
