extern "C" void* Malloc(unsigned int);
extern "C" void Free(void*);

void* operator new(unsigned int size)
{
	return Malloc(size);
}

void operator delete(void* p)
{
	Free(p);
}

void* operator new[](unsigned int size)
{
	return Malloc(size);
}

void operator delete[](void* p)
{
	Free(p);
}