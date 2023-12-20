// BazierCurveAlgorithm.cpp : Defines the exported functions for the DLL.
//

#include "pch.h"
#include "framework.h"
#include "BazierCurveAlgorithm.h"


// This is an example of an exported variable
BAZIERCURVEALGORITHM_API int nBazierCurveAlgorithm=0;

// This is an example of an exported function.
BAZIERCURVEALGORITHM_API int fnBazierCurveAlgorithm(void)
{
    return 0;
}

// This is the constructor of a class that has been exported.
CBazierCurveAlgorithm::CBazierCurveAlgorithm()
{
    return;
}
