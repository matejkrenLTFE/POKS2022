#define R_PIN 11
#define B_PIN 10
#define G_PIN 9

int R = 255;
int B = 0;
int G = 0;

void TIMER2_init(void);

void setup() {
    // put your setup code here, to run once:
    Serial.begin(9600);
    TIMER2_init();
}

ISR(TIMER2_COMPA_vect) {
    // izvajanje prekinitvene rutine!!!

    if (R == 255 & B == 0) {
        G++;
    }
    if (G == 255 & B == 0) {
        R--;
    }
    if (R == 0 && G == 255) {
        B++;
    }
    if (B == 255 && R == 0) {
        G--;
    }
    if (G == 0 && B == 255) {
        R++;
    }
    if (R == 255 && G == 0) {
        B--;
    }

    analogWrite(R_PIN, R);
    analogWrite(G_PIN, G);
    analogWrite(B_PIN, B);
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