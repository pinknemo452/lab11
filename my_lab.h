#ifndef MY_LAB_H
#define MY_LAB_H
char* palloc(int n);
void pfree(char* p);
union pheap_blocks_freeness
{
	bool block[32];
	unsigned int word;
};
class pheap
{
	
public:
	void init();
	char* heap = nullptr;
	const int size = 18 * 32;
	char* new_block_alloc();
	int blocks = 0;
	const pheap_blocks_freeness* m;
	friend void pfree(char* p);
	~pheap();
};
class block
{
public:
	block(block* next,pheap& heap);
	const int size = 16;
	block* next_block;
	char* space;
};
#endif

