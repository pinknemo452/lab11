#include "my_lab.h"
int main()
{
	char* word = palloc(16);
	
	word[0] = 'h';
	word[15] = 'e';
	char* word2 = palloc(17);
	word2[0] = 'e';
	pfree(word2);
	return 0;
}