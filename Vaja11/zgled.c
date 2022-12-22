
void TIMER2_init(void);

void setup() {
    // put your setup code here, to run once:
    Serial.begin(9600);
}

void loop() {
    // put your main code here, to run repeatedly:
    long rezultat = 0;
    int n, i;
    while (true) {
        Serial.println("Začel sem preračunavat: ");
        for (n = 1; n < 100; n++) {
            for (i = 0; i < 1000; i++) {
                rezultat = (rezultat / i) ^ n + (n ^ 5 + n ^ 7) ^ i;
            }
            Serial.print("Delni rezultat: ");
            Serial.println(rezultat);
        }
        Serial.print("Končal sem: ");
        Serial.println(rezultat);
        delay(10000);
    }
}

void TIMER2_init(void) {
    noInterrupts();
    TCCR2B = 0;            // izklopimo timer
    TCCR2A = 0;            // nastavimo način delovanja
    TCNT2 = 0;             // počistimo števec
    OCR2A = 49999;         // nastavimo primerjalnik
    TIMSK2 = 0b00000010;   // nastavimo prekinitev: OCIE2A
    TCCR2B |= 0b00000100;  // prizgemo stevec f/8
    interrupts();
}