#ifndef __TESHI_ZELLER__
  #define __TESHI_ZELLER__
  #include <stdio.h>
  #include <stdbool.h>
  #include <string.h>

  /*--- 日付を表す構造体 ---*/
  typedef struct Date{
    int year;
    int month;
    int date;
  }Date_t;

  typedef enum Day{
    Monday,
    Tuesday,
    Wednesday,
    Thursday,
    Friday,
    Saturday,
    Sunday
  } Day_e;

  static int mday[12] = {31,28,31,30,31,30,31,31,30,31,30,31};
  /*--- うるう年判定函数 ---*/
  // @param y 年
  // @return うるう年なら true が返される。
  //         1582年以前はユリウス暦のため、4年おきに閏年となり、
  //         1582年より後はグレゴリオ暦であるため、400年に3回、
  //         100で割り切れるが400で割り切れない年は、例外で平年となる。
  //         (西暦4年以前は正確さを保証しない)
  static bool is_leap(int y){
    return y<=1582 ? y%4==0 : (y%4==0 && y%100!=0) || y%400==0;
  }

  /*--- y年 m月の最後の日を返す函数 ---*/
  // @param y 年
  // @param m 月
  // @return その月の日数(西暦4年以前は正確さを保証しない)
  static int get_lastdate(int y,int m){
    if(m-- != 2){
      return mday[m];
    }
    return mday[m] + is_leap(y);
  }

  /*--- このプログラムで計算可能な範囲かどうかを返す函数 ---*/
  // 西暦4年よりも前の場合、1582年10月5日～1582年10月14日の場合、
  // そのほか存在しない日付(32日、0月 etc...)
  static bool is_calculable(const Date_t *dt){
    return 4<=dt->year && !(dt->year==1582&&dt->month==10&&4<dt->date&&dt->date<15) &&
           0<dt->month && dt->month<=12 && 0<dt->date && dt->date<=get_lastdate(dt->year,dt->month);
  }

  /*--- Date_t構造体を直列化する函数 ---*/
  //[例]2001/9/10 ⇒ 20010910
  static int dt_serialize(const Date_t *dt){
    if(!is_calculable(dt)){
      return 0;
    }
    return dt->year*10000 + dt->month*100 + dt->date;
  }

  /*--- Date_t構造体の文字列表現を返す函数 ---*/
  //この関数は単一の文字列領域を使いまわす。
  //この関数を複数回呼び出した場合、そのたびにその文字列領域が上書きされる。
  //文字列を保存する必要があれば、呼び出し側でコピーする必要がある。
  static char* dt_to_string(const Date_t *dt){
    if(!is_calculable(dt)){
      return NULL;
    }
    static char retstr[11];
    sprintf(retstr,"%d/%d/%d",dt->year,dt->month,dt->date);
    return retstr;
  }

  /*--- Day_e列挙型の文字列表現を返す函数 ---*/
  static char* day_to_string(Day_e day){
    static char *ws[]={"月","火","水","木","金","土","日"};
    static char errmsg[]="計算できません。";
    if(day<0 || 6<day ){
      return errmsg;
    }
    return ws[day];
  }

  /*--- zeller.c に記述 ---*/
  extern char *day_s[];
  extern Day_e zeller(Date_t dt);
  extern char* day_to_str(int day);

  /*--- calc_days.c に記述 ---*/
  extern int days_between(Date_t dt1, Date_t dt2);

#endif
