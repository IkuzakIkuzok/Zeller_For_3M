/*�w�Дԍ�  15127      ����  �蓈  �E��      �����ԍ�  25*/
#include <stdio.h>
#include <stdbool.h>

typedef struct Date{
  int year;
  int month;
  int date;
}Date_t;

const int mday[12] = {31,28,31,30,31,30,31,31,30,31,30,31};

/*--- ���邤�N���蔟�� ---*/
// @param y �N
// @return ���邤�N�Ȃ� true ���Ԃ����B
//         1582�N�ȑO�̓����E�X��̂��߁A4�N�����ɉ[�N�ƂȂ�A
//         1582�N����̓O���S���I��ł��邽�߁A400�N��3��A
//         100�Ŋ���؂�邪400�Ŋ���؂�Ȃ��N�́A��O�ŕ��N�ƂȂ�B
//         (����4�N�ȑO�͐��m����ۏ؂��Ȃ�)
bool is_leap(int y){
  return y<=1582 ? y%4==0 : y%4==0 && y%100!=0 || y%400==0;
}

/*--- y�N m���̍Ō�̓���Ԃ����� ---*/
// @param y �N
// @param m ��
// @return ���̌��̓���(����4�N�ȑO�͐��m����ۏ؂��Ȃ�)
int get_lastdate(int y,int m){
  if(m-- != 2){
    return mday[m];
  }
  return mday[m] + is_leap(y);
}

/*--- y�N m���̓�����Ԃ����� ---*/
// @param y �N
// @param m ��
// @return ���̌��̓���(����4�N�ȑO�͐��m����ۏ؂��Ȃ�)
//         1582�N10���ȊO�� get_lastdate�Ɠ����l��Ԃ��B
int get_dates(int y, int m){
  return y==1582&&m==10 ? mday[--m]-10 : get_lastdate(y,m);
}

/*--- ���̃v���O�����Ōv�Z�\�Ȕ͈͂��ǂ�����Ԃ����� ---*/
bool is_calculable(const Date_t *dt){
  return 4<=dt->year && !(dt->year==1582&&dt->month==10&&4<dt->date&&dt->date<15) &&
         0<dt->month && dt->month<=12 && 0<dt->date && dt->date<=get_lastdate(dt->year,dt->month);
}

/*--- Zeller�̌�����p����,�j����Ԃ����� ---*/
// @param y �N (������,4��菬�����ꍇ�̓G���[)
// @param m ��
// @param d ��
// @return ���j��(1)~���j��(7)�ŕԂ��B�G���[�̏ꍇ��,0��Ԃ��B
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

/*--- �j���̕�����\����Ԃ����� ---*/
char* day_to_str(int day){
  switch(day){
    case 0: return "�v�Z�ł��܂���B";
    case 1: return "��";
    case 2: return "��";
    case 3: return "��";
    case 4: return "��";
    case 5: return "��";
    case 6: return "�y";
    case 7: return "��";
    default:  return NULL;
  }
}

int main(void){
  int y, m ,d;
  printf("���t�����(yyyy/mm/dd):");
  scanf("%d/%d/%d",&y,&m,&d);
  Date_t dt = {y,m,d};
  printf("%s\n",day_to_str(zeller(dt)));
  return 0;
}
