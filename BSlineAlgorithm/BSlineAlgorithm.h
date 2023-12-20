// The following ifdef block is the standard way of creating macros which make exporting
// from a DLL simpler. All files within this DLL are compiled with the BSLINEALGORITHM_EXPORTS
// symbol defined on the command line. This symbol should not be defined on any project
// that uses this DLL. This way any other project whose source files include this file see
// BSLINEALGORITHM_API functions as being imported from a DLL, whereas this DLL sees symbols
// defined with this macro as being exported.


// This class is exported from the dll
class BSLINEALGORITHM_API CBSlineAlgorithm {
public:
	CBSlineAlgorithm(void);
	// TODO: add your methods here.
};

extern BSLINEALGORITHM_API int nBSlineAlgorithm;

BSLINEALGORITHM_API int fnBSlineAlgorithm(void);
