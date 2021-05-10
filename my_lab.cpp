#include "my_lab.h"

#include <cstdlib>
pheap_blocks_freeness free_space{};
int find_free_blocks(const int n)
{
	int free_blocks_in_a_row = 0;
	for (int i = 0;i < 32;i++)
	{
		if (free_space.block[i] == false)
		{
			free_blocks_in_a_row++;
			if (free_blocks_in_a_row == n)
				return i - free_blocks_in_a_row + 1;
		}
		else
			free_blocks_in_a_row = 0;
	}
	return -1;
}

int div_up(const int x,const int y)
{
	return (x - 1) / y + 1;
}
char* palloc(int n)
{
	n = div_up(n, 16);
	static pheap a;
	if (a.heap == nullptr)
	{
		a.init();
	}
	static block* first_block_pointer = nullptr;
	if (first_block_pointer == nullptr)
	{
		first_block_pointer = new block(nullptr,a);
		first_block_pointer->next_block = new block(nullptr, a);
		auto current = first_block_pointer;
		auto next = first_block_pointer->next_block;
		for (int i = 1; i < 32; ++i)
		{
			next->next_block = new block(nullptr, a);
			current = next;
			next = current->next_block;
		}
		for (int i = 0; i < 32; i++)
			free_space.block[i] = false;
	}
	const int free_blocks_pointer = find_free_blocks(n);
	auto cur = first_block_pointer;
	int i = 0;
	while( i != free_blocks_pointer)
	{
		cur = cur->next_block;
		i++;
	}
	for (int j = 0; j < n; ++j)
	{
		free_space.block[free_blocks_pointer+j] = true;
	}
	a.m = &free_space;
	cur->space[0] = static_cast<char>(n);
	cur->space[1] = static_cast<char>(free_blocks_pointer);
	return cur->space+2;
}

void pfree(char* p)
{
	int blocks_quantity = p[-2];
	int block_number = p[-1];
	for (int i = 0; i < blocks_quantity; ++i)
		free_space.block[block_number+i] = false;
	p = nullptr;
}

void pheap::init()
{
	heap = new char[size];
}

char* pheap::new_block_alloc()
{
	if (blocks == 16)
		return nullptr;
	blocks++;
	return heap + 18 * blocks;
}

pheap::~pheap()
{
	delete[] heap;
}

block::block(block* next,pheap& heap)
{
	next_block = next;
	space = heap.new_block_alloc();
}
