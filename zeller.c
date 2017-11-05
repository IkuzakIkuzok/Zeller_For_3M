/*学籍番号  15127      氏名  手嶋  勇太      整理番号  25*/
#include "teshi_date.h"

/*--- Zellerの公式を用いて,曜日を返す函数 ---*/
// @param y 年 (ただし,4より小さい場合はエラー)
// @param m 月
// @param d 日
// @return 月曜日(0)~日曜日(6)で返す。エラーの場合は,-1を返す。
Day_e zeller(Date_t dt){
  if(!is_calculable(&dt)){
    return -1;
  }
  if(dt.month==1 || dt.month==2){
    dt.year--;
    dt.month+=12;
  }
  int large_y = dt.year%100;
  int large_c = dt.year/100;
  int gamma = dt_serialize(&dt) >=15821015 ?
              5*large_c+large_c/4 :
              6*large_c+5;
  return (dt.date+(26*(dt.month+1)/10)+large_y+large_y/4+gamma+5)%7;
}
