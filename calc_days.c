#include "teshi_date.h"

/*--- y�N m���̓�����Ԃ����� ---*/
// @param y �N
// @param m ��
// @return ���̌��̓���(����4�N�ȑO�͐��m����ۏ؂��Ȃ�)
//         1582�N10���ȊO�� get_lastdate�Ɠ����l��Ԃ��B
int get_days_of_month(int y, int m){
  return y==1582&&m==10 ? mday[--m]-10 : get_lastdate(y,m);
}

/*--- y�N�̓�����Ԃ����� ---*/
int get_days_of_year(int y){
  int days=0;
  int i;
  for(i=0; i<sizeof(mday)/sizeof(mday[0]); i++){
    days += get_days_of_month(y,i+1);
  }
  return days;
}

/*--- dt�̌����߂���̓���(�������܂�)��Ԃ����� ---*/
int days_from_beginning_of_month(const Date_t *dt){
  if(!is_calculable(dt)){
    return -1;
  }
  if(dt->year==1582 && dt->month==10){
    return dt->date<=4 ? dt->date : dt->date-10;
  }
  return dt->date;
}

/*--- dt�̌����܂ł̓���(�������܂܂Ȃ�)��Ԃ�����  ---*/
int days_to_end_of_month(const Date_t *dt){
  if(!is_calculable(dt)){
    return -1;
  }
  if(dt->year==1582 && dt->month==10){
    return dt->date<=4 ? mday[9]-dt->date-10 : mday[9]-dt->date;
  }
  return  mday[dt->month-1]-dt->date;
}

/*--- dt�̔N�n����̓���(�������܂�)��Ԃ�����  ---*/
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

/*--- dt�̔N���܂ł̓���(�������܂܂Ȃ�)��Ԃ�����  ---*/
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

/*--- dt1 �� dt2 �̓�������Ԃ�����---*/
// dt1 �� dt2 �����㐢�̏ꍇ�A�߂�l�����ɂȂ�B
// [��]dt1 = 2017/1/1 �� dt2=2016/1/1
// dt1 �� dt2 ���������ꍇ��
//dt1�Adt2�̂ǂ��炩���邢�͂��̗����̒l���s���ȏꍇ�́A0��Ԃ��B
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
  /*-- dt1 �� dt2 �������N�̏ꍇ�͌v�Z���@���قȂ� ---*/
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
