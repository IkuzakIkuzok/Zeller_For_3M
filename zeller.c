/*�w�Дԍ�  15127      ����  �蓈  �E��      �����ԍ�  25*/
#include "teshi_date.h"

/*--- Zeller�̌�����p����,�j����Ԃ����� ---*/
// @param y �N (������,4��菬�����ꍇ�̓G���[)
// @param m ��
// @param d ��
// @return ���j��(0)~���j��(6)�ŕԂ��B�G���[�̏ꍇ��,-1��Ԃ��B
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
