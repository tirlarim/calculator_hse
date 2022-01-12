#include "is_smh.h"
#include <string.h>

int is_dig(const char* s){
    if (*s=='0' || *s=='1' || *s=='2' || *s=='3' || *s=='4' || *s=='5' || *s=='6' || *s=='7' || *s=='8' || *s=='9' || *s=='.')
        return 1;
    return 0;
}

int is_num(const WORD* word){
    for (int i=0;i<word->current;++i){
        if (!is_dig(&word->st[i])){
            return 0;
        }
    }
    return 1;
}

int is_op_or_bracket(const char* s){
    if (*s=='+' || *s=='-' || *s=='*' || *s=='/' || *s=='(' || *s==')' || *s=='^')
        return 1;
    return 0;
}

int is_function(const WORD* word){
    if (strcmp(word->st,"cos")==0 || strcmp(word->st,"sin")==0 || strcmp(word->st,"tg")==0 ||strcmp(word->st,"log")==0
        ||strcmp(word->st,"ln")==0 ||strcmp(word->st,"sqrt")==0 ||strcmp(word->st,"pow")==0 ||strcmp(word->st,"abs")==0 ||
        strcmp(word->st,"exp")==0 ||strcmp(word->st,"real")==0 ||strcmp(word->st,"imag")==0 ||strcmp(word->st,"mag")==0 ||
        strcmp(word->st,"phase")==0)
        return 1;
    return 0;
}

