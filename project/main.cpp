
#include <iostream>
#include <cstring>

using namespace std;

extern "C"
{
  // Fuer Linux:
  int32_t cpuid0(char* buff);
  int32_t cpuid1(unsigned int* buff);
  int32_t cpuid7(unsigned int* buff);
  
  // Fuer Windows:
  int32_t cpuid0_win(char* buff);
  int32_t cpuid1_win(unsigned int* buff);
  int32_t cpuid7_win(unsigned int* buff);
  uint32_t ASM_rdrand();
}

enum CPUREG: int
{
    EAX,
    EBX,
    ECX,
    EDX
};

 
static void getCpuidLevel1()
{  

  // 
  // CPUID Level 1 (eax=1)
  //   
  uint32_t buff[4];  
  memset(buff, 0, 16);  
#ifdef _WIN32
  uint32_t cpuid1out = cpuid1_win(buff);
#else
  uint32_t cpuid1out = cpuid1(buff);
#endif

	cout << "\nCPUID level 1:" << endl;

  //**************************************************************************
  //
  // ECX
  //
  //**************************************************************************

    // ECX
    enum CPUID1_ECX
    {
        D_SSE3   = 1<<0,
        D_SSSE3  = 1<<9,
        D_SSE41  = 1<<19,
        D_SSE42  = 1<<20,
        D_AVX    = 1<<28,
        D_RDRAND = 1<<30
    };

  if (buff[CPUREG::ECX] & CPUID1_ECX::D_AVX)
  {
    cout << "    AVX" << endl;
  }
    if (buff[CPUREG::ECX] & CPUID1_ECX::D_RDRAND)
  {
    cout << "    RDRAND" << endl;
  }
  if (buff[CPUREG::ECX] & CPUID1_ECX::D_SSE41)
  {
    cout << "    SSE 4.1"<< endl;
  }  
  if (buff[CPUREG::ECX] & CPUID1_ECX::D_SSE42)
  {
    cout << "    SSE 4.2"<< endl;
  }
  if (buff[CPUREG::ECX] & CPUID1_ECX::D_SSE3)
  {
    cout << "    SSE 3"<< endl;
  }

  //**************************************************************************
  //
  // EDX
  //
  //**************************************************************************

    enum CPUID1_EDX
    {
        D_FPU     = 1<<0,
        D_BITS64  = 1<<6,
        D_MMX     = 1<<23,
        D_SSE     = 1<<25,
        D_SSE2    = 1<<26,
        D_HTT     = 1<<28,
        D_3DNOWP  = 1<<30,
        D_3DNOW   = 1<<31
    };

  if (buff[CPUREG::EDX] & CPUID1_EDX::D_FPU)
  {
    cout << "    FPU" << endl;
  }
  if (buff[CPUREG::EDX] & CPUID1_EDX::D_MMX)
  {
    cout << "    MMX" << endl;
  }
  if (buff[CPUREG::EDX] & CPUID1_EDX::D_SSE)
  {
    cout << "    SSE" << endl;
  }
  if (buff[CPUREG::EDX] & CPUID1_EDX::D_SSE2)
  {
    cout << "    SSE2" << endl;
  }
  if (buff[CPUREG::EDX] & CPUID1_EDX::D_HTT)
  {
    cout << "    HTT" << endl;
  }
  if (buff[CPUREG::EDX] & CPUID1_EDX::D_3DNOW)
  {
    cout << "    3DNOW" << endl;
  }
  if (buff[CPUREG::EDX] & CPUID1_EDX::D_3DNOWP)
  {
    cout << "    3DNOW+" << endl;
  } 
}  

//**************************************************************************
//
// main
//
//**************************************************************************

static void getCpuidLevel0()
{  
    // 
    // CPUID Level 0 (eax=1)
    // Fuer Bedeutung der CPU-Level siehe:
    // https://www.sandpile.org/x86/cpuid.htm    
    // 

    char buff0[16];  
      memset(buff0, 0, 16);
    #ifdef _WIN32  
      uint32_t cpuid0out = cpuid0_win(buff0);
    #else  
      uint32_t cpuid0out = cpuid0(buff0);
    #endif
    
	cout << "\nCPUID level 0:" << endl;
    cout << "    " << buff0 << endl;


}

//**************************************************************************
//
// getCpuidLevel7
//
//**************************************************************************

static void getCpuidLevel7()
{  
  // 
  // CPUID Level 7 (eax=7)
  //   
  uint32_t buff[16];  
  memset(buff, 0, 16);  
#ifdef _WIN32
  uint32_t cpuid7out = cpuid7_win(buff);
#else
  uint32_t cpuid7out = cpuid7(buff);
#endif 

    enum CPUID7_EDX
    {
        D_AVX512VL  = 1<<31,
        D_AVX512BW  = 1<<30,
        D_AVX512CD  = 1<<28,
        D_AVX512ER  = 1<<27,
        D_AVX512PF  = 1<<26,
        D_AVX512IFMA= 1<<21,
        D_RDSEED    = 1<<18,
        D_AVX512DQ  = 1<<17,
        D_AVX512F   = 1<<16
    };

	cout << "\nCPUID level 7:" << endl;
    if (buff[CPUREG::EDX] & D_AVX512VL)   cout << "    AVX512VL" << endl;
    if (buff[CPUREG::EDX] & D_AVX512BW)   cout << "    AVX512BW" << endl;
    if (buff[CPUREG::EDX] & D_AVX512CD)   cout << "    AVX512CD" << endl;
    if (buff[CPUREG::EDX] & D_AVX512PF)   cout << "    AVX512PF" << endl;
    if (buff[CPUREG::EDX] & D_AVX512IFMA) cout << "    AVX512IFMA" << endl;
    if (buff[CPUREG::EDX] & D_RDSEED)     cout << "    RDSEED" << endl;
    if (buff[CPUREG::EDX] & D_AVX512DQ)   cout << "    AVX512DQ" << endl;
    if (buff[CPUREG::EDX] & D_AVX512F)    cout << "    AVX512F" << endl;

}

//**************************************************************************
//
// asmRand
//
//**************************************************************************

static void asmRand()
{
  cout << "\nASM_rdrand:" << endl;  
  for (int i = 0; i < 5; i++)
  {
    cout << "    " <<  ASM_rdrand() << endl;
  }
}

//**************************************************************************
//
// main
//
//**************************************************************************


int main(int argc, char* argv[])
{
   

  if (sizeof(void*) != 8)
  {
    cout << "****** not a 64 bit system! Program cannot run.";
  }
  else
  {
    cout << "Features:" << endl;
    getCpuidLevel0();
    getCpuidLevel1();
    getCpuidLevel7();
    asmRand();
  }
  
  return 0; 
}

