// SymmetricDDAAlgorithm.cpp : Defines the exported functions for the DLL.
//

#include "pch.h"
#include "framework.h"
#include "SymmetricDDAAlgorithm.h"


// This is an example of an exported variable
SYMMETRICDDAALGORITHM_API int nSymmetricDDAAlgorithm=0;

// This is an example of an exported function.
SYMMETRICDDAALGORITHM_API int fnSymmetricDDAAlgorithm(void)
{
    return 0;
}

// This is the constructor of a class that has been exported.
CSymmetricDDAAlgorithm::CSymmetricDDAAlgorithm()
{
    return;
}
