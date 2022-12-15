#define pin_number 7

void setup() {
    Serial.begin(9600);
    pinMode(pin_number, OUTPUT);
}

void loop() {
    unsigned long i;
    Serial.print("Pretekli cas: ");

    unsigned long start_time = millis();
    for (i = 0; i < 1000000; i++) {
        digitalWrite(pin_number, HIGH);
        digitalWrite(pin_number, LOW);
    }
    unsigned long end_time = millis();

    Serial.print(end_time - start_time);
    Serial.println("ms");

    while (true);  // neskoncna zanka - ustavimo program
}
