// function prototype declarations

void cleo1(void);
double cleo2(double, double);
char *cleo3(char *);


// pointers to these functions

void (* f1)(void);
double (* f2)(double, double);
char *(* f3)(char *);


// function that takes ptr to a function with two arguments of type
// double that returns a value of type double

double run_func_double(double (*g)(), double, double);
