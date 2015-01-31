#define r2(pr,...) r##pr( __VA_ARGS__) 

#define r_h(n, ...) int n##_num; r2(1, __VA_ARGS__) 
#define r1(p,...) r_h(p, __VA_ARGS__) 

r1(n1, n2, n3);