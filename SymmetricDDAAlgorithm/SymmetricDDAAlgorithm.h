// The following ifdef block is the standard way of creating macros which make exporting
// from a DLL simpler. All files within this DLL are compiled with the SYMMETRICDDAALGORITHM_EXPORTS
// symbol defined on the command line. This symbol should not be defined on any project
// that uses this DLL. This way any other project whose source files include this file see
// SYMMETRICDDAALGORITHM_API functions as being imported from a DLL, whereas this DLL sees symbols
// defined with this macro as being exported.


// This class is exported from the dll
class SYMMETRICDDAALGORITHM_API CSymmetricDDAAlgorithm {
public:
	CSymmetricDDAAlgorithm(void);
	// TODO: add your methods here.
};

extern SYMMETRICDDAALGORITHM_API int nSymmetricDDAAlgorithm;

SYMMETRICDDAALGORITHM_API int fnSymmetricDDAAlgorithm(void);