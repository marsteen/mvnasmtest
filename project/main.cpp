
#include <iostream>
#include <cstring>

using namespace std;

extern "C"
{
  __int32_t cpuid0(char* buff);
  __int32_t cpuid1(unsigned int* buff);
  unsigned int ASM_rdrand();
}

 

int main(int argc, char* argv[])
{
  char buff0[16];  
  memset(buff0, 0, 16);
  unsigned int cpuid0out = cpuid0(buff0);
  
  unsigned int buff1[4];  
  memset(buff1, 0, 16);
  unsigned int cpuid1out = cpuid1(buff1);
  
  
  
  
  cout << "sizeof(void*)=" << sizeof(void*) << endl;
  //cout << "cpuid0=" << cpuid0out << endl;
  cout << "buff0=" << buff0 << endl;
  cout << "eax=" << buff1[0] << endl;
  cout << "ebx=" << buff1[1] << endl;
  cout << "ecx=" << buff1[2] << endl;
  cout << "edx=" << buff1[3] << endl;
  
// EDX  
#define CPUID1_FPU     1   
#define CPUID1_64      1<<6
#define CPUID1_MMX     1<<23
#define CPUID1_SSE     1<<25
#define CPUID1_SSE2    1<<26
#define CPUID1_HTT     1<<28
#define CPUID1_3DNOWP  1<<30
#define CPUID1_3DNOW   1<<31
  
  
// EBX  
#define CPUID1_AVX512F  1<<16

// ECX
#define CPUID1_SSE3   1<<0
#define CPUID1_SSE41  1<<19
#define CPUID1_SSE42  1<<20
#define CPUID1_AVX    1<<28
#define CPUID1_RDRAND 1<<30
  
  
  cout << "Features:" << endl;
  
  // EBX
  
  if (buff1[1] & CPUID1_AVX)
  {
    cout << "  AVX" << endl;
  }
  
  // ECX
  
  if (buff1[2] & CPUID1_AVX512F)
  {
    cout << "  AVX512F" << endl;
  }
  if (buff1[2] & CPUID1_RDRAND)
  {
    cout << "  RDRAND" << endl;
  }
  if (buff1[2] & CPUID1_SSE41)
  {
    cout << "  SSE 4.1"<< endl;
  }  
  if (buff1[2] & CPUID1_SSE42)
  {
    cout << "  SSE 4.2"<< endl;
  }
  if (buff1[2] & CPUID1_SSE3)
  {
    cout << "  SSE 3"<< endl;
  }

  // EDX
  
  if (buff1[3] & CPUID1_FPU)
  {
    cout << "  FPU" << endl;
  }
  if (buff1[3] & CPUID1_MMX)
  {
    cout << "  MMX" << endl;
  }
  if (buff1[3] & CPUID1_SSE)
  {
    cout << "  SSE" << endl;
  }
  if (buff1[3] & CPUID1_SSE2)
  {
    cout << "  SSE2" << endl;
  }
  if (buff1[3] & CPUID1_HTT)
  {
    cout << "  HTT" << endl;
  }
  if (buff1[3] & CPUID1_3DNOW)
  {
    cout << "  3DNOW" << endl;
  }
  if (buff1[3] & CPUID1_3DNOWP)
  {
    cout << "  3DNOW+" << endl;
  }
  
  for (int i = 0; i < 100; i++)
  {
    cout << "ASM_rdrand()=" <<  ASM_rdrand() << endl;
  }
  
  
  return 0; 
}
