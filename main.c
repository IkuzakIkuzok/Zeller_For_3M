#include "teshi_date.h"

int main(void){
  int y, m ,d;
  printf("���t�����(yyyy/mm/dd):");
  scanf("%d/%d/%d",&y,&m,&d);
  Date_t dt = {y,m,d};
  printf("%s\n",day_to_str(zeller(dt)));

  Date_t birth ={1582,10,4};
  printf("%s��%d������Ă���\n",dt_to_string(&birth),days_between(birth,dt));

  return 0;
}