#ifndef __TESHI_ZELLER__
  #define __TESHI_ZELLER__
  #include <stdio.h>
  #include <stdbool.h>
  #include <string.h>

  /*--- ���t��\���\���� ---*/
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
  /*--- ���邤�N���蔟�� ---*/
  // @param y �N
  // @return ���邤�N�Ȃ� true ���Ԃ����B
  //         1582�N�ȑO�̓����E�X��̂��߁A4�N�����ɉ[�N�ƂȂ�A
  //         1582�N����̓O���S���I��ł��邽�߁A400�N��3��A
  //         100�Ŋ���؂�邪400�Ŋ���؂�Ȃ��N�́A��O�ŕ��N�ƂȂ�B
  //         (����4�N�ȑO�͐��m����ۏ؂��Ȃ�)
  static bool is_leap(int y){
    return y<=1582 ? y%4==0 : (y%4==0 && y%100!=0) || y%400==0;
  }

  /*--- y�N m���̍Ō�̓���Ԃ����� ---*/
  // @param y �N
  // @param m ��
  // @return ���̌��̓���(����4�N�ȑO�͐��m����ۏ؂��Ȃ�)
  static int get_lastdate(int y,int m){
    if(m-- != 2){
      return mday[m];
    }
    return mday[m] + is_leap(y);
  }

  /*--- ���̃v���O�����Ōv�Z�\�Ȕ͈͂��ǂ�����Ԃ����� ---*/
  // ����4�N�����O�̏ꍇ�A1582�N10��5���`1582�N10��14���̏ꍇ�A
  // ���̂ق����݂��Ȃ����t(32���A0�� etc...)
  static bool is_calculable(const Date_t *dt){
    return 4<=dt->year && !(dt->year==1582&&dt->month==10&&4<dt->date&&dt->date<15) &&
           0<dt->month && dt->month<=12 && 0<dt->date && dt->date<=get_lastdate(dt->year,dt->month);
  }

  /*--- Date_t�\���̂𒼗񉻂��锟�� ---*/
  //[��]2001/9/10 �� 20010910
  static int dt_serialize(const Date_t *dt){
    if(!is_calculable(dt)){
      return 0;
    }
    return dt->year*10000 + dt->month*100 + dt->date;
  }

  /*--- Date_t�\���̂̕�����\����Ԃ����� ---*/
  //���̊֐��͒P��̕�����̈���g���܂킷�B
  //���̊֐��𕡐���Ăяo�����ꍇ�A���̂��тɂ��̕�����̈悪�㏑�������B
  //�������ۑ�����K�v������΁A�Ăяo�����ŃR�s�[����K�v������B
  static char* dt_to_string(const Date_t *dt){
    if(!is_calculable(dt)){
      return NULL;
    }
    static char retstr[11];
    sprintf(retstr,"%d/%d/%d",dt->year,dt->month,dt->date);
    return retstr;
  }

  /*--- Day_e�񋓌^�̕�����\����Ԃ����� ---*/
  static char* day_to_string(Day_e day){
    static char *ws[]={"��","��","��","��","��","�y","��"};
    static char errmsg[]="�v�Z�ł��܂���B";
    if(day<0 || 6<day ){
      return errmsg;
    }
    return ws[day];
  }

  /*--- zeller.c �ɋL�q ---*/
  extern char *day_s[];
  extern Day_e zeller(Date_t dt);
  extern char* day_to_str(int day);

  /*--- calc_days.c �ɋL�q ---*/
  extern int days_between(Date_t dt1, Date_t dt2);

#endif
