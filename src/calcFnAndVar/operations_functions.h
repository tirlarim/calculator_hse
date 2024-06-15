#ifndef MAIN_C_OPERATIONS_FUNCTIONS_H
#define MAIN_C_OPERATIONS_FUNCTIONS_H
#include <complex.h>
#define comp double complex

comp u(comp a);
comp mag(comp a);
comp phase(comp a);
comp cabsd(comp a);
comp creald(comp a);
comp cimagd(comp a);
comp clog10(comp a);
comp empty(comp a);

comp full_log(comp a,comp b);
comp plus(comp a, comp b);
comp minus(comp a, comp b);
comp multiplication(comp a, comp b);
comp division(comp a, comp b);
comp exponentiation(comp a, comp b);



#endif
