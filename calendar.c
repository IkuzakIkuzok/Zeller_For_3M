#include "teshi_date.h"

void make_calendar(int y, int m, char s[7][22]){
   Date_t dt = {y,m,1};
   Date_t exception = {1582,10,1};

   int i, j;
   int wd=zeller(dt);
   char buff[4];
   /*存在しない月であれば、空文字列を返す*/
   if(!is_calculable(&dt)){
     for(i=0; i<7; i++){
       s[i][0]='\0';
     }
     return;
   }
   /*タイトル(y/m)*/
   sprintf(s[0], "%10d / %02d%6s",y,m," ");
   /*タイトル以外のバッファをクリア*/
   for(i=1; i<7; i++){
     s[i][0] = '\0';
   }
   if(days_between(dt,exception)==0){
     return;
   }
   i=1;
   sprintf(s[i], "%*s",3*wd," ");              /*1日の左側を空白で埋める*/
   for(j=1; j<=get_days_of_month(y,m); j++){
     sprintf(buff,"%3d",j);
     strcat(s[i],buff);                        /*i日の日付を追加*/
     if(++wd%7==0){                            /*日曜日で改行する*/
       i++;
     }
   }
   /*最終日の右側を空白で埋める*/
   if(wd%7==0){
     i--;
   }else{
     for(wd%=7; wd<7; wd++){
       strcat(s[i], "   ");
     }
   }
   /*使われていない行を空白で埋める*/
   while(++i<7){
     sprintf(s[i],"%21s"," ");
   }
 }

void print_calendar(const char s[7][22]) {
  int i,j;
  printf("%s\n",s[0]);
  for(i=0; i<7; i++){
    
  }
  printf("---------------------\n");
  for(i=1; i<7; i++){
    printf("%21s\n",s[i]);
  }
  putchar('\n');
}
