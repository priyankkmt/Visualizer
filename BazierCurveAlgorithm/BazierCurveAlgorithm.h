// The following ifdef block is the standard way of creating macros which make exporting
// from a DLL simpler. All files within this DLL are compiled with the BAZIERCURVEALGORITHM_EXPORTS
// symbol defined on the command line. This symbol should not be defined on any project
// that uses this DLL. This way any other project whose source files include this file see
// BAZIERCURVEALGORITHM_API functions as being imported from a DLL, whereas this DLL sees symbols
// defined with this macro as being exported.


// This class is exported from the dll
class BAZIERCURVEALGORITHM_API CBazierCurveAlgorithm {
public:
	CBazierCurveAlgorithm(void);
	// TODO: add your methods here.
};

extern BAZIERCURVEALGORITHM_API int nBazierCurveAlgorithm;

BAZIERCURVEALGORITHM_API int fnBazierCurveAlgorithm(void);
