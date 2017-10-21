/**********************************************************
* STRING class            [written by zzombie@gmx.net]    *
*                                                         *
*     для сайта Азбука Технологий Программирования        *
*                                                         *
*    all rights,lefts & other directions reserved :]      *
*                                                         *
**********************************************************/

#include <iostream.h>
#include <string.h>

class STRING
{
   public:
                             /////
      STRING();                 //
      STRING(const char *const);//
      STRING(const STRING &);   //  конструкторы , 
      STRING(const int);        // описание см. ниже
      STRING(const int,char);   //
                             /////
      ~STRING(); // деструктор

      
      char & operator[](int offset);       //
      char operator[](int offset) const;   // перегруженные операторы, 
      STRING operator+(const STRING&);     // пояснения ниже
      void operator+=(const STRING&);      //
      STRING & operator= (const STRING &); //
      
      friend ostream& operator<<(ostream& ,const STRING&);// объявляем их друзьями чтоб у них
      friend istream& operator>>(istream& ,STRING&);      // был доступ к методам нашего класса
      
      
      int Len() const {return SLen;};    
   private:
   
      char * SContent; // сама строка (не путать с объектом STRING !)
      unsigned short SLen; //длина строки
      
      char * Content() const {return SContent;} //возвращает содержимое строки 
      						//(это для оператора<<) 
     
};

//===============[ конструкторы & деструктор ]================//
STRING::STRING()
{
   SContent = new char[1]; 
   SContent[0] = '\0';     // создает строку нулевой длины
   SLen=0;                 //
}


STRING::STRING(const char * const chS)
{
   SLen = strlen(chS);       // конструктор,
   SContent = new char[SLen+1];  // создает объект  типа STRING
   for (int i = 0; i<SLen; i++)  // из * char (chS)
      SContent[i] = chS[i];      //
   SContent[SLen]='\0';          //
}

STRING::STRING (const STRING & rhs)
{                                //  конструктор-копировщик
   SLen=rhs.Len();               // копирует длину строки 
   SContent = new char[SLen+1];  // и её содержимое 
   for (int i = 0; i<SLen;i++)   // из объекта rhs
      SContent[i] = rhs[i];      //
   SContent[SLen] = '\0';        //
}

STRING::STRING(int len)          //
{                                // конструктор,
   SContent = new char[len+1];   // создает строку длины len
   for (int i = 0; i<=len; i++)  // и заполняет 
         SContent[i] = '\0';     // нулевыми символами
   SLen=len;                     //
}


STRING::STRING(int len,char FillWith)
{
   SContent = new char[len+1];      // конструктор,
   for (int i = 0; i<=len; i++)     // создает строку длины len
   	SContent[i] = FillWith;     // состоящую из символов FillWith
   SLen=len;
}

STRING::~STRING ()      // деструктор, 
{                       // освобождает память
   delete [] SContent;  // занятую содержимым строки
}                       //
                                                   
//=============================================================//




//==================[ Перегруженные операторы ]================//

STRING& STRING::operator=(const STRING & rhs)
{                        //перегруженный оператор присваивания
   if (this == &rhs)  //если хотим присвоить значение объекта
      return *this;   //        самому себе то делать нечего :]
      
   delete [] SContent; //прежнее содержимое строки уже не нужно
   SLen=rhs.Len();  //длина тоже новая
   SContent = new char[SLen+1];
   for (int i = 0; i<SLen;i++) //
      SContent[i] = rhs[i];    // копируем содержимое rhs
   SContent[SLen] = '\0';      //
   return *this;               //
}


char STRING::operator[](int offset) const//оператор индексирования
   {
      if (offset > SLen)      //если вышли за пределы строки
         return SContent[SLen-1];// возвращает последний символ
                                  // а если все правильно возвращает
         return SContent[offset]; //соответствующий символ строки
   }
                                                

char & STRING::operator[](int offset) //оператор индексирования 
{                                     //
   if (offset > SLen)                 // в отличие от предыдущего 
  	return SContent[SLen-1];      //  возвращает
                                      //  ссылку(!) на соответствующий
   return SContent[offset];           //    символ строки
}                                        


STRING STRING::operator+(const STRING& rhs) //оператор суммирования
{
     				    
   STRING tmp(SLen + rhs.Len()); // строка-результат
   int i, j;
   for (i = 0; i<SLen; i++) // записываем  в строку-результат 
      tmp[i] = SContent[i]; // содержимое нашей строки
   for (j = 0; j<rhs.Len(); j++, i++) // и добавляем 
      tmp[i] = rhs[j];              //содержимое правого операнда
   tmp[SLen + rhs.Len()]='\0';
   return tmp;         //возвращаем результат
}

void STRING::operator+=(const STRING& rhs)
{
   STRING  tmp(SLen + rhs.Len());            //
   int i;                                    //  тут наверно все ясно,
   for (i = 0; i<SLen; i++)                  //   если нет см. 
      tmp[i] = SContent[i];                  //  пояснения к оператору +
   for (int j = 0; j<rhs.Len(); j++, i++)    //
      tmp[i] = rhs[j];                       //
   tmp[SLen + rhs.Len()]='\0';               //
   *this = tmp;
}

//==========================================================// 



//================[операторы ввода/вывода]===============================//

ostream& operator<<(ostream& stream,const STRING& str)
{				// берем поток, 
	 stream<<str.Content(); // записываем в него содержимое строки 
	 return stream;         // и возвращаем		
}


istream& operator>>(istream& stream,STRING& str)  //берем поток,
{                                   	
	char* tmp=new char[1000]; 
	// предполагается что больше 1000 символов считывать не будем, если нет поменяйте
	
	stream>>tmp;  //из потока во временную переменную
	str=tmp;  //заменяем содержимое строки на то что считали из потока
	return stream;              // и возвращаем
} 

//=======================================================================//