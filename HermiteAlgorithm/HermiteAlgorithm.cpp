// HermiteAlgorithm.cpp : Defines the exported functions for the DLL.
//

#include "pch.h"
#include "framework.h"
#include "HermiteAlgorithm.h"


// This is an example of an exported variable
HERMITEALGORITHM_API int nHermiteAlgorithm=0;

// This is an example of an exported function.
HERMITEALGORITHM_API int fnHermiteAlgorithm(void)
{
    return 0;
}

// This is the constructor of a class that has been exported.
CHermiteAlgorithm::CHermiteAlgorithm()
{
    return;
}
