#define pin_number 7

void setup() {
    Serial.begin(9600);
    pinMode(pin_number, OUTPUT);
}

void loop() {
    // unsigned long i;
    //  Serial.print("Pretekli cas: ");

    // unsigned long start_time = millis();
    // for (i = 0; i < 100000; i++) {
    // digitalWrite(pin_number, HIGH);
    // digitalWrite(pin_number, LOW);

    // PORTD = (1<<PD7); // TURN ON
    // PORTD = (0<<PD7); // TURN OFF
    //  	PORTD |= 0b10000000;
    //  	PORTD &= 0b01111111;

    //}
    // unsigned long end_time = millis();

    // Serial.print(end_time - start_time);
    // Serial.println("ms");

    unsigned long n = 0;
    unsigned long i = 0;
    unsigned char dir = 0;
    while (true) {
        PORTD |= 0b10000000;
        while (i < 500) {
            if (i > n) {
                PORTD &= 0b01111111;
            }
            i++;
        }
        i = 0;
        if (dir) {
            n--;
        } else {
            n++;
        }
        if (n > 500) {
            dir = 1;
        }
        if (n <= 0) {
            dir = 0;
        }
    }

    // while (true);  // neskoncna zanka - ustavimo program
}