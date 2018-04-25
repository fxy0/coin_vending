#include <stdint.h>
#include <stdio.h>
#include "tm4c123gh6pm.h"
#include <stdlib.h>
#include <string.h>

#define RW 0x20  //PA5
#define RS 0x40  //PA6
#define E  0x80  //PA7
#define LINE1 0x80 //1. satýr
#define LINE2 0xC0 //2. satýr

void PLL_Ayar(void);
void sayiBastir(int sayilar[]);
int farkHesapla(double para2, double para, double bozulanPara);
double paraBoz(double para, double miktar);
void yazdir(char dizi[]);
void port_e();
void islemciHiz(void);
void zeki(double para);
void LCD1602_Ayar(void);
void LCD1602_Temizle(void);
void LCD1602_EkranString(unsigned char *str);
void LCD1602_EkranChar(unsigned char CHAR);
void LCD1602_EkranDec(unsigned int number);
void LCD1602_EkranPozisyon(unsigned char Line,unsigned int digit);
void SysTick_Ayar(void);
void SysTick_Delay(unsigned long delay);
void SysTick_Delay1us(unsigned long delay);
void SysTick_Delay1ms(unsigned long delay);

int main(void){
    A:
    islemciHiz();
    SysTick_Ayar();
    LCD1602_Ayar();
    LCD1602_EkranPozisyon(LINE1,0);

    char paraIsimleri[][20] = { "yirmilik", "onluk", "beslik", "birlik", "yarimlik", "ceyreklik", "metelik", "delik" , "kurusluk" };

    double bir=0,iki=0,uc=0,dort=0;

    //tüm paralarin miktarlari
    int i=0,j;

    double paralar[] = {20,10,5,1,0.5,0.25,0.1,0.05,0.01};

    //sayýnýn ekranda gösterilmesi
    unsigned int buton_1=0,buton_2=0,buton_3=0,buton_4=0,buton_5=0;

    LCD1602_Temizle();
    LCD1602_EkranPozisyon(LINE1,0);
    yazdir("Girilen");
    SysTick_Delay1ms(500);

    port_e();
    int sayac=0,enter=0,onay=0;

    while(1){

            buton_1 = GPIO_PORTE_DATA_R & 0x02; // PE1
            buton_2 = GPIO_PORTE_DATA_R & 0x04; // PE2
            buton_3 = GPIO_PORTE_DATA_R & 0x08; // PE3
            buton_4 = GPIO_PORTE_DATA_R & 0x10; // PE4 0001 0000
            buton_5 = GPIO_PORTE_DATA_R & 0x20; // PE5 0010 0000

    if(buton_1 == 0){
        LCD1602_EkranPozisyon(LINE1,10);
        if(bir == 9) bir = 0; else bir++;
        LCD1602_EkranDec(bir);
        SysTick_Delay1ms(200);
        enter=0;
        continue;
    }

    if(buton_2 == 0){
        LCD1602_EkranPozisyon(LINE1,11);
        if(iki == 9) iki = 0; else iki++;
        LCD1602_EkranDec(iki);
        SysTick_Delay1ms(200);
        enter=0;
        continue;

    }

    if(buton_3 == 0){
        LCD1602_EkranPozisyon(LINE1,12);
        yazdir(".");
        SysTick_Delay1ms(200);
        //continue;
            while(buton_3 == 0){
                SysTick_Delay1ms(800);
                sayac++;

                if(sayac==5){
                        bir=0;
                        iki=0;
                        uc=0;
                        dort=0;
                        LCD1602_Temizle();
                        LCD1602_EkranPozisyon(LINE1,0);
                        yazdir("-Reset Islemi-");
                        SysTick_Delay1ms(2000);
                        LCD1602_Temizle();
                        LCD1602_EkranPozisyon(LINE1,0);
                        yazdir("Girilen:");
                        sayac=0;
                        break;
                }else{
                    //sayac=0;
                    break;
                }
            }
            //sayac=0;
            SysTick_Delay1ms(200);
            enter=0;
            continue;
    }

    if(buton_4 == 0){
         LCD1602_EkranPozisyon(LINE1,13);
         if(uc == 9) uc = 0; else uc++;
         LCD1602_EkranDec(uc);
         SysTick_Delay1ms(200);
         enter=0;
         continue;
        }

    if(buton_5 == 0){
         LCD1602_EkranPozisyon(LINE1,14);
         if(dort == 9) dort = 0; else dort++;
         LCD1602_EkranDec(dort);
         SysTick_Delay1ms(200);
         enter=0;
         continue;
        }


    else{
        if(buton_1 !=0 && buton_2 !=0 && buton_3 !=0 && buton_4 !=0 && buton_5 !=0){
            SysTick_Delay1ms(50);
            enter++;

            if(enter==25){
                onay=1;
            }

        }
    }

    if(onay==1){
        break;
    }

    SysTick_Delay1ms(100);
    }

    SysTick_Delay1ms(2000);

    LCD1602_Temizle();

    //kullanicidan alinacak paralarin birleþtirilmesi
    double para = bir*10 + iki + uc*0.1 + dort*0.01, para2;

     while(para > 0.000000){ i++;
// para sürekli eksiliyor. 0 dan küçük olana kadar iþlem devam edecek.
         para2 = para; // farký hesaplamak için kullanýlan temp.
               for(j = 0; j < 9; j++){
                   if(para >= paralar[j]){
                        LCD1602_Temizle();
                        LCD1602_EkranPozisyon(LINE1,0);
                        yazdir("Kalan: ");
                        para = paraBoz(para,paralar[j]);// o anki banknot deðerini mevcut paradan çýkarýr
                        zeki(para);

                        int fark = farkHesapla(para2,para,paralar[j]);
                        LCD1602_EkranPozisyon(LINE2,2);
                        LCD1602_EkranDec(fark);
                        yazdir(" ");
                        yazdir(paraIsimleri[j]);
                        SysTick_Delay1ms(4000);
                        break;
                    }
               }
      if(i > 50) break;

     }
     sayac=0;
     while(1){
                     buton_1 = GPIO_PORTE_DATA_R & 0x02; // PE1
                     buton_2 = GPIO_PORTE_DATA_R & 0x04; // PE2
                     buton_3 = GPIO_PORTE_DATA_R & 0x08; // PE3
                     buton_4 = GPIO_PORTE_DATA_R & 0x10; // PE4 0001 0000
                     buton_5 = GPIO_PORTE_DATA_R & 0x20; // PE5 0010 0000

         if(buton_3 == 0){
                 SysTick_Delay1ms(200);

                     while(buton_3 == 0){
                         SysTick_Delay1ms(800);
                         sayac++;

                         if(sayac==5){
                                 LCD1602_Temizle();
                                 LCD1602_EkranPozisyon(LINE1,0);
                                 yazdir("-Reset Islemi-");
                                 SysTick_Delay1ms(2000);
                                 bir=0;
                                 iki=0;
                                 uc=0;
                                 dort=0;
                                 LCD1602_Temizle();
                                 LCD1602_EkranPozisyon(LINE1,0);
                                 yazdir("Girilen");
                                 sayac=0; para2=0;
                                 goto A;
                         }else{
                             //sayac=0;
                             break;
                         }
                     }

             }
     }

}

void yazdir(char dizi[]){
    int i=0;
    while(dizi[i] != '\0'){
        LCD1602_EkranChar(dizi[i]);
        i++;
    }
}
double paraBoz(double para, double miktar){
    int tamSayi = para / miktar;
    return para - (miktar*tamSayi);
}

int farkHesapla(double para2, double para, double bozulanPara){
    return (para2-para)/bozulanPara;
}
void sayiBastir(int sayilar[]){
    LCD1602_EkranPozisyon(LINE1,11);

    int i;
    for(i=0; i <4; i++){
        if(i == 2) yazdir(".");
        LCD1602_EkranDec(sayilar[i]);
    }
}

void port_e(){
               SYSCTL_RCGC2_R |= SYSCTL_RCGC2_GPIOE;
               GPIO_PORTE_AMSEL_R = 0x00;
               GPIO_PORTE_DIR_R = 0x00;
               GPIO_PORTE_AFSEL_R = 0x00;
               GPIO_PORTE_DEN_R = 0x3E; // 0011 1110
}

void islemciHiz(void)
{
    SYSCTL_RCC2_R |=  0x80000000;
    SYSCTL_RCC2_R |=  0x00000800;
    SYSCTL_RCC_R = (SYSCTL_RCC_R &~0x000007C0)
                 + 0x00000540;
    SYSCTL_RCC2_R &= ~0x00000070;
    SYSCTL_RCC2_R &= ~0x00002000;
    SYSCTL_RCC2_R |= 0x40000000;
    SYSCTL_RCC2_R = (SYSCTL_RCC2_R&~ 0x1FC00000)
                  + (4<<22);
    while((SYSCTL_RIS_R&0x00000040)==0){};
    SYSCTL_RCC2_R &= ~0x00000800;
}

void zeki(double para){
    int para2,temp;
    double ara;
    para2=(int)para;
    ara= para-(double)para2;
    temp=100*ara;

    if(para2>=10){
        LCD1602_EkranPozisyon(LINE1,11);
        LCD1602_EkranDec(para2);
        LCD1602_EkranPozisyon(LINE1,13);
        yazdir(".");
        LCD1602_EkranPozisyon(LINE1,14);
        LCD1602_EkranDec(temp);
    }
    else{
        LCD1602_EkranPozisyon(LINE1,11);
        LCD1602_EkranDec(para2);
        LCD1602_EkranPozisyon(LINE1,12);
        yazdir(".");
        if(temp>=10){
            LCD1602_EkranPozisyon(LINE1,13);
            LCD1602_EkranDec(temp);
        }else{
            LCD1602_EkranPozisyon(LINE1,13);
            LCD1602_EkranDec(0);
            LCD1602_EkranPozisyon(LINE1,14);
            LCD1602_EkranDec(temp);
        }
    }
}
void GPIO_PortAB_Ayar(void){
    volatile unsigned long delay;
// A TANIMLAMALARI
    SYSCTL_RCGC2_R |= 0x00000001;
    delay = SYSCTL_RCGC2_R;
    GPIO_PORTA_AMSEL_R &= ~0xE0;
    GPIO_PORTA_PCTL_R &= ~0xFFF00000;
    GPIO_PORTA_DIR_R |= 0xE0;
    GPIO_PORTA_AFSEL_R &= ~0xE0;
    GPIO_PORTA_DEN_R |= 0xE0;
    GPIO_PORTA_DR8R_R |= 0xE0;

// B TANIMLAMALARI
    SYSCTL_RCGC2_R |= 0x00000002;
    delay = SYSCTL_RCGC2_R;
    GPIO_PORTB_AMSEL_R &= ~0xFF;
    GPIO_PORTB_PCTL_R &= ~0xFFFFFFFF;
    GPIO_PORTB_DIR_R |= 0xFF;
    GPIO_PORTB_AFSEL_R &= ~0xFF;
    GPIO_PORTB_DEN_R |= 0xFF;
    GPIO_PORTB_DR8R_R |= 0xFF;
}

void Write_Command(unsigned char LCD_Comment){
    GPIO_PORTA_DATA_R &= ~(RS+RW+E);
    GPIO_PORTB_DATA_R = LCD_Comment;
    GPIO_PORTA_DATA_R |= E;
    GPIO_PORTA_DATA_R &= ~(RS+RW);
    SysTick_Delay(19);
    GPIO_PORTA_DATA_R &= ~(RS+RW+E);
    SysTick_Delay1ms(1);
}

void Write_Data(unsigned char LCD_Data){
    GPIO_PORTB_DATA_R = LCD_Data;
    GPIO_PORTA_DATA_R |= RS+E;
    GPIO_PORTA_DATA_R &= ~RW;
    SysTick_Delay(19);
    GPIO_PORTA_DATA_R &= ~(RS+RW+E);
    SysTick_Delay1ms(1);
}

void LCD1602_Ayar(){
    GPIO_PortAB_Ayar();
    SysTick_Delay1ms(15);
    Write_Command(0x38);
    SysTick_Delay1ms(5);
    Write_Command(0x38);
    SysTick_Delay1us(150);
    Write_Command(0x0C);
    Write_Command(0x01);
    Write_Command(0x06);
    SysTick_Delay1ms(50);
}

void LCD1602_Temizle(){
    Write_Command(0x01);
}

void LCD1602_EkranString(unsigned char *str){
    while(*str != 0){
        Write_Data(*str++);
    }
}
void LCD1602_EkranChar(unsigned char CHAR){
    Write_Data(CHAR);
}

void LCD1602_EkranDec(unsigned int number){
    if(number >=10){
        LCD1602_EkranDec(number/10);
        number = number%10;
    }
    LCD1602_EkranChar(number+'0');
}

void LCD1602_EkranPozisyon(unsigned char Line,unsigned int digit){
    Write_Command(Line + digit);
}

int fputc(int ch, FILE *f){
    if((ch == 10) || (ch == 13) || (ch == 27)){
        LCD1602_EkranChar(13);
        LCD1602_EkranChar(10);
        return 1;
    }
    LCD1602_EkranChar(ch);
    return 1;
}
void SysTick_Ayar(void){
    NVIC_ST_CTRL_R = 0;
    NVIC_ST_CTRL_R = 0x00000005;
}

void SysTick_Delay(unsigned long delay){
    NVIC_ST_RELOAD_R = delay-1;
    NVIC_ST_CURRENT_R = 0;
    while((NVIC_ST_CTRL_R&0x00010000)==0){
    }
}
void SysTick_Delay1us(unsigned long delay){
    unsigned long i;
    for(i=0; i<delay; i++)    {
       SysTick_Delay(80);                 // wait 1us
    }
}
void SysTick_Delay1ms(unsigned long delay){
    unsigned long i;
    for(i=0; i<delay; i++)    {
       SysTick_Delay(80000);
    }
}
