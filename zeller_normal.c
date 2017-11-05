/*学籍番号  15127      氏名  手嶋  勇太      整理番号  25*/
#include <stdio.h>
#include <stdbool.h>

typedef struct Date{
  int year;
  int month;
  int date;
}Date_t;

const int mday[12] = {31,28,31,30,31,30,31,31,30,31,30,31};

/*--- うるう年判定函数 ---*/
// @param y 年
// @return うるう年なら true が返される。
//         1582年以前はユリウス暦のため、4年おきに閏年となり、
//         1582年より後はグレゴリオ暦であるため、400年に3回、
//         100で割り切れるが400で割り切れない年は、例外で平年となる。
//         (西暦4年以前は正確さを保証しない)
bool is_leap(int y){
  return y<=1582 ? y%4==0 : y%4==0 && y%100!=0 || y%400==0;
}

/*--- y年 m月の最後の日を返す函数 ---*/
// @param y 年
// @param m 月
// @return その月の日数(西暦4年以前は正確さを保証しない)
int get_lastdate(int y,int m){
  if(m-- != 2){
    return mday[m];
  }
  return mday[m] + is_leap(y);
}

/*--- y年 m月の日数を返す函数 ---*/
// @param y 年
// @param m 月
// @return その月の日数(西暦4年以前は正確さを保証しない)
//         1582年10月以外は get_lastdateと同じ値を返す。
int get_dates(int y, int m){
  return y==1582&&m==10 ? mday[--m]-10 : get_lastdate(y,m);
}

/*--- このプログラムで計算可能な範囲かどうかを返す函数 ---*/
bool is_calculable(const Date_t *dt){
  return 4<=dt->year && !(dt->year==1582&&dt->month==10&&4<dt->date&&dt->date<15) &&
         0<dt->month && dt->month<=12 && 0<dt->date && dt->date<=get_lastdate(dt->year,dt->month);
}

/*--- Zellerの公式を用いて,曜日を返す函数 ---*/
// @param y 年 (ただし,4より小さい場合はエラー)
// @param m 月
// @param d 日
// @return 月曜日(1)~日曜日(7)で返す。エラーの場合は,0を返す。
int zeller(Date_t dt){
  if(!is_calculable(&dt)){
    return 0;
  }
  if(dt.month==1 || dt.month==2){
    dt.year--;
    dt.month+=12;
  }
  int large_y = dt.year%100;
  int large_c = dt.year/100;
  int gamma = (dt.year*10000 + dt.month*100 + dt.date) >=15821015 ?
              5*large_c+large_c/4 :
              6*large_c+5;
  return (dt.date+(26*(dt.month+1)/10)+large_y+large_y/4+gamma+5)%7+1;
}

/*--- 曜日の文字列表現を返す函数 ---*/
char* day_to_str(int day){
  switch(day){
    case 0: return "計算できません。";
    case 1: return "月";
    case 2: return "火";
    case 3: return "水";
    case 4: return "木";
    case 5: return "金";
    case 6: return "土";
    case 7: return "日";
    default:  return NULL;
  }
}

int main(void){
  int y, m ,d;
  printf("日付を入力(yyyy/mm/dd):");
  scanf("%d/%d/%d",&y,&m,&d);
  Date_t dt = {y,m,d};
  printf("%s\n",day_to_str(zeller(dt)));
  return 0;
}
