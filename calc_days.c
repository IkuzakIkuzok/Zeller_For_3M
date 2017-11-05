#include "teshi_date.h"

/*--- y年 m月の日数を返す函数 ---*/
// @param y 年
// @param m 月
// @return その月の日数(西暦4年以前は正確さを保証しない)
//         1582年10月以外は get_lastdateと同じ値を返す。
int get_days_of_month(int y, int m){
  return y==1582&&m==10 ? mday[--m]-10 : get_lastdate(y,m);
}

/*--- y年の日数を返す函数 ---*/
int get_days_of_year(int y){
  int days=0;
  int i;
  for(i=0; i<sizeof(mday)/sizeof(mday[0]); i++){
    days += get_days_of_month(y,i+1);
  }
  return days;
}

/*--- dtの月初めからの日数(今日を含む)を返す函数 ---*/
int days_from_beginning_of_month(const Date_t *dt){
  if(!is_calculable(dt)){
    return -1;
  }
  if(dt->year==1582 && dt->month==10){
    return dt->date<=4 ? dt->date : dt->date-10;
  }
  return dt->date;
}

/*--- dtの月末までの日数(今日を含まない)を返す函数  ---*/
int days_to_end_of_month(const Date_t *dt){
  if(!is_calculable(dt)){
    return -1;
  }
  if(dt->year==1582 && dt->month==10){
    return dt->date<=4 ? mday[9]-dt->date-10 : mday[9]-dt->date;
  }
  return  mday[dt->month-1]-dt->date;
}

/*--- dtの年始からの日数(今日を含む)を返す函数  ---*/
int days_from_beginning_of_year(const Date_t *dt){
  if(!is_calculable(dt)){
    return -1;
  }
  int days=0;
  int i;
  for(i=1; i<dt->month; i++){
    days += get_days_of_month(dt->year,i);
  }
  days += days_from_beginning_of_month(dt);
  return days;
}

/*--- dtの年末までの日数(今日を含まない)を返す函数  ---*/
int days_to_end_of_year(const Date_t *dt){
  if(!is_calculable(dt)){
    return -1;
  }
  int days=0;
  int i;
  for(i=12; i>dt->month; i--){
    days += get_days_of_month(dt->year,i);
  }
  days += days_to_end_of_month(dt);
  return days;
}

/*--- dt1 と dt2 の日数差を返す函数---*/
// dt1 が dt2 よりも後世の場合、戻り値が負になる。
// [例]dt1 = 2017/1/1 で dt2=2016/1/1
// dt1 と dt2 が等しい場合と
//dt1、dt2のどちらかあるいはその両方の値が不正な場合は、0を返す。
int days_between(Date_t dt1, Date_t dt2){
  if(dt_serialize(&dt1) == dt_serialize(&dt2) ||
    !is_calculable(&dt1) || !is_calculable(&dt2)){
    return 0;
  }
  int swap_flag = 1;
  if(dt_serialize(&dt1) > dt_serialize(&dt2)){
    swap_flag = -1;
    Date_t tmp = dt2;
    dt2 = dt1;
    dt1 = tmp;
  }
  int days=0;
  /*-- dt1 と dt2 が同じ年の場合は計算方法が異なる ---*/
  if(dt1.year == dt2.year){
    days = days_from_beginning_of_year(&dt2)-days_from_beginning_of_year(&dt1);
  }else{
    days += days_to_end_of_year(&dt1);
    int i;
    for(i=dt1.year+1; i<=dt2.year-1; i++){
      days += get_days_of_year(i);
    }
    days += days_from_beginning_of_year(&dt2);
  }
  return days*swap_flag;
}
