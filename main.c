#include "teshi_date.h"

int main(void){
  int y, m ,d;
  char calendar[7][22];

  printf("日付を入力(yyyy/mm/dd):");
  scanf("%d/%d/%d",&y,&m,&d);
  Date_t dt = {y,m,d};
  make_calendar(y,m,calendar);
  print_calendar(calendar);
  printf("%s\n",day_to_string(zeller(dt)));

  Date_t birth ={1582,10,4};
  printf("%sと%d日離れている\n",dt_to_string(&birth),days_between(birth,dt));

  return 0;
}
