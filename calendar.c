#include "teshi_date.h"

void make_calendar(int y, int m, char s[7][22]){
   Date_t dt = {y,m,1};

   int i, j;
   int wd=zeller(dt);
   char buff[4];
   /*���݂��Ȃ����ł���΁A�󕶎����Ԃ�*/
   if(!is_calculable(&dt)){
     for(i=0; i<7; i++){
       s[i][0]='\0';
     }
     return;
   }
   /*�^�C�g��(y/m)*/
   sprintf(s[0], "%10d / %02d%6s",y,m," ");
   /*�^�C�g���ȊO�̃o�b�t�@���N���A*/
   for(i=1; i<7; i++){
     s[i][0] = '\0';
   }
   i=1;
   sprintf(s[i], "%*s",3*wd," ");       /*1���̍������󔒂Ŗ��߂�*/
   for(j=1; j<=get_lastdate(y,m); j++){
     sprintf(buff,"%3d",j);
     strcat(s[i],buff);                 /*j���̓��t��ǉ�*/
     if(y==1582 && m==10 && j==4){
       int tmp_wd = wd;
       printf("DEBUG: %d\n",tmp_wd);
       for(tmp_wd%=7; tmp_wd<7; tmp_wd++){
         strcat(s[i],"   ");
       }
       i++;
       Date_t oct15 = {1582,10,15};
       sprintf(s[i],"%*s",3*zeller(oct15)," ");
       j=15;
     }else if(++wd%7==0){               /*���j���ŉ��s����*/
       i++;
     }
   }
   /*�ŏI���̉E�����󔒂Ŗ��߂�*/
   if(wd%7==0){
     i--;
   }else{
     for(wd%=7; wd<7; wd++){
       strcat(s[i], "   ");
     }
   }
   /*�g���Ă��Ȃ��s���󔒂Ŗ��߂�*/
   while(++i<7){
     sprintf(s[i],"%21s"," ");
   }
 }

void print_calendar(const char s[7][22]) {
  int i,j;
  printf("%s\n",s[0]);
  for(i=0; i<7; i++){
    printf("%3s",day_to_string(i));
  }
  putchar('\n');
  printf("---------------------\n");
  for(i=1; i<7; i++){
    printf("%21s\n",s[i]);
  }
  putchar('\n');
}
