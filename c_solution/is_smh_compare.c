#include "is_smh_compare.h"
#include <string.h>

int is_dig(const char* s){
    if (*s=='0' || *s=='1' || *s=='2' || *s=='3' || *s=='4' || *s=='5' || *s=='6' || *s=='7' || *s=='8' || *s=='9' || *s=='.')
        return 1;
    return 0;
}

int is_u_min(const char* s, const char* previous_s,int i){
    if ((*s=='-' && (*previous_s=='(' || i==0)) || *s=='u' && *previous_s=='-') return 1;
    return 0;
}

int is_num(const WORD* word){
    if (word->st[0]=='u') return 0;
    for (int i=0;i<word->current;++i){
        if (!is_dig(&word->st[i])){
            return 0;
        }
    }
    return 1;
}

int is_op_or_bracket(const char* s){
    if (*s=='+' || *s=='-' || *s=='*' || *s=='/' || *s=='^' || *s=='(' || *s==')')
        return 1;
    return 0;
}

int is_function(const WORD* word){
    if (strcmp(word->st,"cos")==0 || strcmp(word->st,"sin")==0 || strcmp(word->st,"tg")==0 ||strcmp(word->st,"log")==0
        ||strcmp(word->st,"ln")==0 ||strcmp(word->st,"sqrt")==0 ||strcmp(word->st,"pow")==0 ||strcmp(word->st,"abs")==0 ||
        strcmp(word->st,"exp")==0 ||strcmp(word->st,"real")==0 ||strcmp(word->st,"imag")==0 ||strcmp(word->st,"mag")==0 ||
        strcmp(word->st,"phase")==0 || (word->st[0]=='l' && word->st[1]=='o' && word->st[2]=='g') || (word->st[0]=='p' && word->st[1]=='o' && word->st[2]=='w'))
        return 1;
    return 0;
}

int is_const(const WORD* word){
    if (strcmp(word->st,"PI")==0 || strcmp(word->st,"e")==0 || strcmp(word->st,"j")==0)
        return 1;
    return 0;
}

int compare(const char* to, const char* vs){
    if ((*to=='-' || *to=='+') && (*vs=='/' || *vs=='*' || *vs=='^' || *vs=='-' || *vs=='+' || *vs=='u')) return 1;
    if ((*to=='/' || *to=='*') && (*vs=='/' || *vs=='*' || *vs=='^' || *vs=='u')) return 1;
    if (*to=='^' && (*vs=='^' || *vs=='u')) return 1;
    if (*to=='u' && *vs=='u') return 1;
    return 0;
}


