#include "teshi_date.h"

 void make_calendar(int y, int m, char s[7][22]){
   sprintf(s[0], "%10d / %02d%6s",y,m," ");
   int i;
   for(i=1; i<7; i++){
     s[i][0] = '\0';
   }
   
 }
