/**********************************************************
* STRING class            [written by zzombie@gmx.net]    *
*                                                         *
*     ��� ����� ������ ���������� ����������������        *
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
      STRING(const STRING &);   //  ������������ , 
      STRING(const int);        // �������� ��. ����
      STRING(const int,char);   //
                             /////
      ~STRING(); // ����������

      
      char & operator[](int offset);       //
      char operator[](int offset) const;   // ������������� ���������, 
      STRING operator+(const STRING&);     // ��������� ����
      void operator+=(const STRING&);      //
      STRING & operator= (const STRING &); //
      
      friend ostream& operator<<(ostream& ,const STRING&);// ��������� �� �������� ���� � ���
      friend istream& operator>>(istream& ,STRING&);      // ��� ������ � ������� ������ ������
      
      
      int Len() const {return SLen;};    
   private:
   
      char * SContent; // ���� ������ (�� ������ � �������� STRING !)
      unsigned short SLen; //����� ������
      
      char * Content() const {return SContent;} //���������� ���������� ������ 
      						//(��� ��� ���������<<) 
     
};

//===============[ ������������ & ���������� ]================//
STRING::STRING()
{
   SContent = new char[1]; 
   SContent[0] = '\0';     // ������� ������ ������� �����
   SLen=0;                 //
}


STRING::STRING(const char * const chS)
{
   SLen = strlen(chS);       // �����������,
   SContent = new char[SLen+1];  // ������� ������  ���� STRING
   for (int i = 0; i<SLen; i++)  // �� * char (chS)
      SContent[i] = chS[i];      //
   SContent[SLen]='\0';          //
}

STRING::STRING (const STRING & rhs)
{                                //  �����������-����������
   SLen=rhs.Len();               // �������� ����� ������ 
   SContent = new char[SLen+1];  // � � ���������� 
   for (int i = 0; i<SLen;i++)   // �� ������� rhs
      SContent[i] = rhs[i];      //
   SContent[SLen] = '\0';        //
}

STRING::STRING(int len)          //
{                                // �����������,
   SContent = new char[len+1];   // ������� ������ ����� len
   for (int i = 0; i<=len; i++)  // � ��������� 
         SContent[i] = '\0';     // �������� ���������
   SLen=len;                     //
}


STRING::STRING(int len,char FillWith)
{
   SContent = new char[len+1];      // �����������,
   for (int i = 0; i<=len; i++)     // ������� ������ ����� len
   	SContent[i] = FillWith;     // ��������� �� �������� FillWith
   SLen=len;
}

STRING::~STRING ()      // ����������, 
{                       // ����������� ������
   delete [] SContent;  // ������� ���������� ������
}                       //
                                                   
//=============================================================//




//==================[ ������������� ��������� ]================//

STRING& STRING::operator=(const STRING & rhs)
{                        //������������� �������� ������������
   if (this == &rhs)  //���� ����� ��������� �������� �������
      return *this;   //        ������ ���� �� ������ ������ :]
      
   delete [] SContent; //������� ���������� ������ ��� �� �����
   SLen=rhs.Len();  //����� ���� �����
   SContent = new char[SLen+1];
   for (int i = 0; i<SLen;i++) //
      SContent[i] = rhs[i];    // �������� ���������� rhs
   SContent[SLen] = '\0';      //
   return *this;               //
}


char STRING::operator[](int offset) const//�������� ��������������
   {
      if (offset > SLen)      //���� ����� �� ������� ������
         return SContent[SLen-1];// ���������� ��������� ������
                                  // � ���� ��� ��������� ����������
         return SContent[offset]; //��������������� ������ ������
   }
                                                

char & STRING::operator[](int offset) //�������� �������������� 
{                                     //
   if (offset > SLen)                 // � ������� �� ����������� 
  	return SContent[SLen-1];      //  ����������
                                      //  ������(!) �� ���������������
   return SContent[offset];           //    ������ ������
}                                        


STRING STRING::operator+(const STRING& rhs) //�������� ������������
{
     				    
   STRING tmp(SLen + rhs.Len()); // ������-���������
   int i, j;
   for (i = 0; i<SLen; i++) // ����������  � ������-��������� 
      tmp[i] = SContent[i]; // ���������� ����� ������
   for (j = 0; j<rhs.Len(); j++, i++) // � ��������� 
      tmp[i] = rhs[j];              //���������� ������� ��������
   tmp[SLen + rhs.Len()]='\0';
   return tmp;         //���������� ���������
}

void STRING::operator+=(const STRING& rhs)
{
   STRING  tmp(SLen + rhs.Len());            //
   int i;                                    //  ��� ������� ��� ����,
   for (i = 0; i<SLen; i++)                  //   ���� ��� ��. 
      tmp[i] = SContent[i];                  //  ��������� � ��������� +
   for (int j = 0; j<rhs.Len(); j++, i++)    //
      tmp[i] = rhs[j];                       //
   tmp[SLen + rhs.Len()]='\0';               //
   *this = tmp;
}

//==========================================================// 



//================[��������� �����/������]===============================//

ostream& operator<<(ostream& stream,const STRING& str)
{				// ����� �����, 
	 stream<<str.Content(); // ���������� � ���� ���������� ������ 
	 return stream;         // � ����������		
}


istream& operator>>(istream& stream,STRING& str)  //����� �����,
{                                   	
	char* tmp=new char[1000]; 
	// �������������� ��� ������ 1000 �������� ��������� �� �����, ���� ��� ���������
	
	stream>>tmp;  //�� ������ �� ��������� ����������
	str=tmp;  //�������� ���������� ������ �� �� ��� ������� �� ������
	return stream;              // � ����������
} 

//=======================================================================//