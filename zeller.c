/*ŠwĞ”Ô†  15127      –¼  è“ˆ  —E‘¾      ®—”Ô†  25*/
#include "teshi_date.h"

/*--- Zeller‚ÌŒö®‚ğ—p‚¢‚Ä,—j“ú‚ğ•Ô‚·”Ÿ” ---*/
// @param y ”N (‚½‚¾‚µ,4‚æ‚è¬‚³‚¢ê‡‚ÍƒGƒ‰[)
// @param m Œ
// @param d “ú
// @return Œ—j“ú(1)~“ú—j“ú(7)‚Å•Ô‚·BƒGƒ‰[‚Ìê‡‚Í,0‚ğ•Ô‚·B
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

 char *day_s[] = {"“ú", "Œ", "‰Î", "…", "–Ø", "‹à", "“y" };
/*--- —j“ú‚Ì•¶š—ñ•\Œ»‚ğ•Ô‚·”Ÿ” ---*/
char* day_to_str(int day){
  switch(day){
    case 0: return "ŒvZ‚Å‚«‚Ü‚¹‚ñB";
    case 1: return "Œ";
    case 2: return "‰Î";
    case 3: return "…";
    case 4: return "–Ø";
    case 5: return "‹à";
    case 6: return "“y";
    case 7: return "“ú";
    default:  return NULL;
  }
}
