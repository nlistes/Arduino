byte i;
byte ledDigits[4];

void ledPrint(String ledBuffer)
  {
    byte ledSigns[] =
      {
        B11111100, //00 - 0
        B01100000, //01 - 1
        B11011010, //02 - 2
        B11110010, //03 - 3
        B01100110, //04 - 4
        B10110110, //05 - 5
        B10111110, //06 - 6
        B11100000, //07 - 7
        B11111110, //08 - 8
        B11110110, //09 - 9
        B10011100, //10 - C
        B10011110, //11 - E
        B01101110, //12 - H
        B00011100, //13 - L
        B11001110, //14 - P
        B00000000  //15 - space
      };
    char c0, c1;
    byte s = 0, j = 0;
    Serial.println(ledBuffer.length());
    while (s < 4)
      {
        c0 = ' ';
        if (ledBuffer.length() - 1 >= j) c0 = ledBuffer.charAt(j);
        c1 = ' ';
        if (ledBuffer.length() - 1 >= j + 1) c1 = ledBuffer.charAt(j + 1);
        Serial.println(c0);
        switch(c0)
          {
            case '0': ledDigits[s] = ledSigns[0]; break;
            case '1': ledDigits[s] = ledSigns[1]; break;
            case '2': ledDigits[s] = ledSigns[2]; break;
            case '3': ledDigits[s] = ledSigns[3]; break;
            case '4': ledDigits[s] = ledSigns[4]; break;
            case '5': ledDigits[s] = ledSigns[5]; break;
            case '6': ledDigits[s] = ledSigns[6]; break;
            case '7': ledDigits[s] = ledSigns[7]; break;
            case '8': ledDigits[s] = ledSigns[8]; break;
            case '9': ledDigits[s] = ledSigns[9]; break;
            case 'C': ledDigits[s] = ledSigns[10]; break;
            case 'E': ledDigits[s] = ledSigns[11]; break;
            case 'H': ledDigits[s] = ledSigns[12]; break;
            case 'L': ledDigits[s] = ledSigns[13]; break;
            case 'P': ledDigits[s] = ledSigns[14]; break;
            case '.': ledDigits[s] |= 1 << 0;      break;   
            default:  ledDigits[s] = ledSigns[15];  
          }
        j++;
        if (c1 != '.') s++;
      } ;
  }

void setup()
{
  Serial.begin(9600);
  ledPrint("C.23.2");
  for (i = 0; i<4; i++) Serial.println(ledDigits[i], BIN);  
  Serial.println("END");  
}
void loop()
{
}
