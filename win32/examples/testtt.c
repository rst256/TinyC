typedef struct {
	char * i;
} user_struct1;
typedef struct {
	char i;
} user_struct2;

typedef struct {
	 int i;
} user_type;

typedef enum {
	e1,e2,e3
} user_type2;
typedef enum {
	e1,e2,e3
} user_type3;

#define CHECK(EXPR) if(!(EXPR)) { printf("%s:%d: %s\n ", __FILE__, __LINE__, #EXPR); exit(0); }

#define TEST_TYPE_ID(T) {T tv; CHECK( typeid(tv) == typeid(T)) ; \
	printf("%30.30s type_id is %10.10d.\t %10.10d\t check for variable defined at line  %d\n", \
		#T, typeid(tv), typeid(T),__LINE__);}

int main(int argc, char *argv[]) {
	TEST_TYPE_ID(int);
	TEST_TYPE_ID(char);
	TEST_TYPE_ID(unsigned long);
	TEST_TYPE_ID(long);

TEST_TYPE_ID(user_type);
TEST_TYPE_ID(user_type2);
TEST_TYPE_ID(user_type3);
TEST_TYPE_ID(user_struct1);
TEST_TYPE_ID(user_struct2);
TEST_TYPE_ID(user_type);
TEST_TYPE_ID(static user_type);

user_type ut = {5};
user_type * ut_p = &ut;

printf("%s\n",  __func__ );
printf("%d\n",  ut.i );
printf("%d\n",  ut_p:>i );
	//printf("%s\n", tostr(typeof1(vv)) );
	return 0;
}