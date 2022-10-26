#include <stdio.h>
#include <stdlib.h>

float izracunajOsnovoZaDohodnino(float dohodek){
    float pokojninsko = dohodek*0.155;
    float normStroski = dohodek * 0.1;
    float olajsava = 3500;
    if(dohodek > 13316.83){
        olajsava = 	3500 + (18700.38 - 1.40427 * dohodek);
    }
    float osnova = dohodek - pokojninsko - normStroski - olajsava;
    if(osnova < 0){
        return 0;
    }
    return osnova;
}

void izracunajDohodnino(float osnova){
    float dohodnina;
    float preostanek;
    if(osnova < 8500){
        dohodnina = osnova*0.16;
        preostanek = 8500 - osnova;
    }else{
        if(osnova < 25000){
            dohodnina = 1360 +  (osnova - 8500) * 0.26;
            preostanek = 25000 - osnova;
        } else {
            if(osnova < 50000){
                dohodnina = 5650 + (osnova - 25000)*0.33;
                preostanek = 50000 - osnova;
            }else {
                if(osnova < 72000){
                    dohodnina = 13900 +(osnova - 50000) * 0.39;
                    preostanek = 72000- osnova;
                }else {
                    dohodnina = 22480.00 + (osnova - 72000) * 0.5;
                    preostanek = 0;
                }
            }
        }
    }
    printf("Vaša dohodnina znaša %f.\n Razlika do naslednjega dohodninskega razreda je %f.\n",dohodnina, preostanek);
}

int main(){
    float dohodek;
    printf("Vnesi vaš bruto dohodek: ");
    scanf("%f", &dohodek);
    float osnova = izracunajOsnovoZaDohodnino(dohodek);
    printf("Osnova za dohodnino je %f.\n", dohodek);
    izracunajDohodnino(osnova);
    return 0;
}