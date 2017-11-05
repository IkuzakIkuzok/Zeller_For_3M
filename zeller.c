/*�w�Дԍ�  15127      ����  �蓈  �E��      �����ԍ�  25*/
#include "teshi_date.h"

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
  int gamma = dt_serialize(&dt) >=15821015 ?
              5*large_c+large_c/4 :
              6*large_c+5;
  return (dt.date+(26*(dt.month+1)/10)+large_y+large_y/4+gamma+5)%7+1;
}

 char *day_s[] = {"��", "��", "��", "��", "��", "��", "�y" };
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
