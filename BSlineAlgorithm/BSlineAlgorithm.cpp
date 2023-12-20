// BSlineAlgorithm.cpp : Defines the exported functions for the DLL.
//

#include "pch.h"
#include "framework.h"
#include "BSlineAlgorithm.h"


// This is an example of an exported variable
BSLINEALGORITHM_API int nBSlineAlgorithm=0;

// This is an example of an exported function.
BSLINEALGORITHM_API int fnBSlineAlgorithm(void)
{
    return 0;
}

// This is the constructor of a class that has been exported.
CBSlineAlgorithm::CBSlineAlgorithm()
{
    return;
}
