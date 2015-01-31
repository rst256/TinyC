//+---------------------------------------------------------------------------
//
//  dll.c - Windows DLL example - dynamically linked part
//
//#define DLL_EXPORT __declspec(dllexport)
#ifdef SRH_DICT_LIMIT
#define SRH_DICT_LPG && count < SRH_DICT_LIMIT
#else
#define SRH_DICT_LPG 
#endif

#include<stdio.h>
#include<stdlib.h>
// DICT_CELL_COUNT должно быть простым числом!
#define DICT_CELL_COUNT 30011
 
char* szWordAr[ DICT_CELL_COUNT ];
unsigned int uWordArSize = 0;
 
#define WORD_IDX_BAD (( unsigned int )-1)
 
unsigned int uWordIdxByHashAr[ DICT_CELL_COUNT ]; // необходимо инициализировать элементы значением WORD_IDX_BAD

#define STRIDE_1 17
#define STRIDE_2 13
 
typedef struct {
	char* kwords[ DICT_CELL_COUNT ]; 
	unsigned int count, stride_1, stride_2; //... = 0, 17, 13
	unsigned int kword_idx_by_hash[ DICT_CELL_COUNT ]; //uWordIdxByHashAr[*]=WORD_IDX_BAD
} hash_list_t;
typedef hash_list_t * hash_list_pt;

// ‘ункци€ GetWordIdx( .. ) возвращает индекс слова pcszWord в массиве szWordAr.
// »ли WORD_IDX_BAD если слова pcszWord в словаре szWordAr нет.
unsigned int GetWordIdx( const char* const pcszWord ){
	unsigned int uHash1 = 0, uHash2 = 0, uHash1p, uHash2p;
	const unsigned char* cbtWordCharCur = ( const unsigned char* )pcszWord;
 
	//if(uWordArSize+1 >= DICT_CELL_COUNT) return WORD_IDX_BAD;
    // ¬ычислим два хеша слова pcszWord:
    // uHash1 лежит в диапазоне [ 0 .. DICT_CELL_COUNT - 1 ]
    // uHash2 лежит в диапазоне [ 1 .. DICT_CELL_COUNT - 1 ]
    do
      {
        uHash1 *= STRIDE_1; uHash1 += ( STRIDE_2 * *cbtWordCharCur );
        uHash2 *= STRIDE_2; uHash2 += ( STRIDE_1 * *cbtWordCharCur );
	printf("loop1 %c %5p: %5u, %5u\n", *cbtWordCharCur, cbtWordCharCur-pcszWord, uHash2p, uHash2);

      }
    while( *( cbtWordCharCur++ ) ); // NB: инкремент!
 
    // #1: cbtWordCharCur указывает на символ за посл. '\0' в pcszWord,
    // будет использовано в #2
 
    uHash1 %= DICT_CELL_COUNT;
    uHash2 %= ( DICT_CELL_COUNT - 1 ); ++uHash2;

    uHash1p = uHash1;
    uHash2p = uHash2;

    while( uWordIdxByHashAr[ uHash1 ] != WORD_IDX_BAD  SRH_DICT_LPG)
      {
        if ( !strcmp( pcszWord, szWordAr[ uWordIdxByHashAr[ uHash1 ] ] ) )
          return uWordIdxByHashAr[ uHash1 ];
 	printf("loop2 : (%2u, %2u)\t", uHash1, uHash2);

        uHash1 += uHash2; uHash1 %= DICT_CELL_COUNT;
 	printf("(%2u, %2u)\n", uHash1, uHash2);

      }
if(uHash1p != uHash1)
	printf("\t\t\t\t\t\t\t\t\t\t-------new idx %2u, uHash1: %4u=>%4u \n", uWordArSize+1, uHash1p, uHash1);
if(uHash2p != uHash2)
	printf("\t\t\t\t\t\t\t\t\t\t-------new idx %2u, uHash2: %4u=>%4u \n", uWordArSize+1, uHash2p, uHash2);


    strcpy(
      szWordAr[
        uWordIdxByHashAr[ uHash1 ] = // NB: присвоение!
          uWordArSize
      ] = // NB: присвоение!
        ( char* )malloc(
          // длина pcszWord плюс 1:
          ( const char* )cbtWordCharCur - // #2: используем значение cbtWordCharCur из #1
            pcszWord
        ),
      pcszWord
    );
 
    return uWordArSize++; // NB: инкремент!
} // unsigned int GetOrAddWordIdx( const char* const pcszWord )

unsigned int GetOrAddWordIdx( const char* const pcszWord )
  {
    unsigned int uHash1 = 0, uHash2 = 0;
 
    const unsigned char* cbtWordCharCur = ( const unsigned char* )pcszWord;
 
    // ¬ычислим два хеша слова pcszWord:
    // uHash1 лежит в диапазоне [ 0 .. DICT_CELL_COUNT - 1 ]
    // uHash2 лежит в диапазоне [ 1 .. DICT_CELL_COUNT - 1 ]
 
    do
      {
        uHash1 *= STRIDE_1; uHash1 += ( STRIDE_2 * *cbtWordCharCur );
        uHash2 *= STRIDE_2; uHash2 += ( STRIDE_1 * *cbtWordCharCur );
      }
    while( *( cbtWordCharCur++ ) ); // NB: инкремент!
 
    // #1: cbtWordCharCur указывает на символ за посл. '\0' в pcszWord,
    // будет использовано в #2
 
    uHash1 %= DICT_CELL_COUNT;
    uHash2 %= ( DICT_CELL_COUNT - 1 ); ++uHash2;
 
    while( uWordIdxByHashAr[ uHash1 ] != WORD_IDX_BAD  )
      {
        if ( !strcmp( pcszWord, szWordAr[ uWordIdxByHashAr[ uHash1 ] ] ) )
          return uWordIdxByHashAr[ uHash1 ];
 
        uHash1 += uHash2; uHash1 %= DICT_CELL_COUNT;
      }
 
    strcpy(
      szWordAr[
        uWordIdxByHashAr[ uHash1 ] = // NB: присвоение!
          uWordArSize
      ] = // NB: присвоение!
        ( char* )malloc(
          // длина pcszWord плюс 1:
          ( const char* )cbtWordCharCur - // #2: используем значение cbtWordCharCur из #1
            pcszWord
        ),
      pcszWord
    );
 
    return uWordArSize++; // NB: инкремент!
  } // unsigned int GetOrAddWordIdx( const char* const pcszWord )

#ifndef DLL_EXPORT
#define AddStrWord(W) \
	printf("GetWordIdx(%50s) => %u\tword total: %u\n", W, GetWordIdx(W), uWordArSize)
#define AddWord(S) AddStrWord(#S)

int main(void)
{
	unsigned int i;
	printf("------------------    Test start...\n");
	for(i=0; i< DICT_CELL_COUNT; ++i)
		uWordIdxByHashAr[ i ] = WORD_IDX_BAD;

	printf("------------------    First add word...\n");
	AddWord(dog);
	AddWord(doger);
	AddStrWord("doger man");
	AddStrWord("doger man like loooong string.");
	AddStrWord("doger man like loooong string. Very looooooong.");
	AddWord(cat);
	AddWord(dot);
	AddWord(code);

	printf("------------------    Try add word again...\n");
	AddWord(dog);
	AddWord(doger);
	AddStrWord("doger man");
	AddStrWord("doger man like loooong string.");
	AddStrWord("doger man like loooong string. Very looooooong.");
	AddWord(cat);
	AddWord(dot);
	AddWord(code);
	
	printf("------------------    Add some new word...\n");
	AddWord(human);
	AddWord(geroin);

	printf("------------------    Try add this new word again...\n");
	AddWord(human);
	AddWord(geroin);

	printf("------------------    Try add all exists word again, and one new...\n");
	AddStrWord("human");
	AddWord(geroin);
	AddWord(new);
	AddWord(dog);
	AddWord(doger);
	AddStrWord("doger man");
	AddStrWord("doger man like loooong string.");
	AddStrWord("doger man like loooong string. Very looooooong.");
	AddWord(cat);
	AddWord(dot);
	AddWord(code);

	return 0;
}

#else

DLL_EXPORT void HelloWorld (void)
{
    //MessageBox (0, "Hello World!", "From DLL", MB_ICONINFORMATION);
}

#endif