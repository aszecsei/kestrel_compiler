#include "testCodeGen.h"
#include "../environment.h"
#include "../linklst.h"
#include "../CodeGen.h"
class EnvironmentMock : public Environment {
	
public:
	static uint32_t s_argc;
	static uint32_t s_argv;
	static uint32_t s_localvmain;
	static uint32_t s_localv2main;
	static uint32_t s_localrmain;
};

uint32_t EnvironmentMock::s_argc = 0;
uint32_t EnvironmentMock::s_argv = 1;
uint32_t EnvironmentMock::s_localvmain = 2;
uint32_t EnvironmentMock::s_localv2main = 3;
uint32_t EnvironmentMock::s_localrmain = 4;

void EmptyMainFunc(Tester* t) {
	EnvironmentMock env;
	List<uint32_t> lstParams;
	lstParams.Add(EnvironmentMock::s_argc);
	lstParams.Add(EnvironmentMock::s_argv);
	CodeGenNode* pGenHead = CodeGen::StartFunc("main", lstParams, &env); //int main(int argc, const char* argv[]) {}
	unsigned int lenCode = 1024;
	char *szCode = NULL;
	unsigned int lenReq = 0;
	bool completeGen = false;
	while(!completeGen)
	{
		free(szCode);
		szCode = (char *)malloc(lenCode * sizeof(char));
		lenReq = CodeGen::EndFunc(pGenHead, &env, szCode, lenCode);
		completeGen = (lenReq <= lenCode);
		lenCode = lenReq;
	}

	printf("EmptyMainFunc:\n\s", szCode);
	free(szCode);
		
}

void MainFuncWith2LocalVariables(Tester* t) {
	EnvironmentMock env;
	List<uint32_t> lstParams;
	lstParams.Add(EnvironmentMock::s_argc);
	lstParams.Add(EnvironmentMock::s_argv);
	CodeGenNode* pGenHead = CodeGen::StartFunc("main", lstParams, &env); //int main(int argc, const char* argv[]) {
	CodeGenNode* pSucceed = pGenHead;
	pSucceed = CodeGen::StackPush(pSucceed, EnvironmentMock::s_localvmain, &env);
	pSucceed = CodeGen::StackPush(pSucceed, EnvironmentMock::s_localv2main, &env);
	unsigned int lenCode = 1024;
	char *szCode = NULL;
	unsigned int lenReq = 0;
	bool completeGen = false;
	while(!completeGen)
	{
		free(szCode);
		szCode = (char *)malloc(lenCode * sizeof(char));
		lenReq = CodeGen::EndFunc(pGenHead, &env, szCode, lenCode);
		completeGen = (lenReq <= lenCode);
		lenCode = lenReq;
	}

	printf("MainFuncWith2LocalVariables:\n\s", szCode);
	free(szCode);
}

void MainFuncWith2LocalVariablesAddition(Tester* t) {
	EnvironmentMock env;
	List<uint32_t> lstParams;
	lstParams.Add(EnvironmentMock::s_argc);
	lstParams.Add(EnvironmentMock::s_argv);
	CodeGenNode* pGenHead = CodeGen::StartFunc("main", lstParams, &env); //int main(int argc, const char* argv[]) {
	CodeGenNode* pSucceed = pGenHead;
	pSucceed = CodeGen::StackPush(pSucceed, EnvironmentMock::s_localvmain, &env);
	pSucceed = CodeGen::StackPush(pSucceed, EnvironmentMock::s_localv2main, &env);
	pSucceed = CodeGen::Add(pSucceed, EnvironmentMock::s_localvmain, EnvironmentMock::s_localv2main, &env);
	unsigned int lenCode = 1024;
	char *szCode = NULL;
	unsigned int lenReq = 0;
	bool completeGen = false;
	while(!completeGen)
	{
		free(szCode);
		szCode = (char *)malloc(lenCode * sizeof(char));
		lenReq = CodeGen::EndFunc(pGenHead, &env, szCode, lenCode);
		completeGen = (lenReq <= lenCode);
		lenCode = lenReq;
	}

	printf("MainFuncWith2LocalVariablesAddition:\n\s", szCode);
	free(szCode);
}

void MainFuncWith2LocalVariablesAdditionReturn(Tester* t) {
	EnvironmentMock env;
	List<uint32_t> lstParams;
	lstParams.Add(EnvironmentMock::s_argc);
	lstParams.Add(EnvironmentMock::s_argv);
	CodeGenNode* pGenHead = CodeGen::StartFunc("main", lstParams, &env); //int main(int argc, const char* argv[]) {
	CodeGenNode* pSucceed = pGenHead;
	pSucceed = CodeGen::StackPush(pSucceed, EnvironmentMock::s_localvmain, &env);
	pSucceed = CodeGen::StackPush(pSucceed, EnvironmentMock::s_localv2main, &env);
	pSucceed = CodeGen::StackPush(pSucceed, EnvironmentMock::s_localrmain, &env);

	pSucceed = CodeGen::Add(pSucceed, EnvironmentMock::s_localrmain, EnvironmentMock::s_localvmain, EnvironmentMock::s_localv2main, &env);
	pSucceed = CodeGen::Return(pSucceed, EnvironmentMock::s_localrmain, &env);
	

	unsigned int lenCode = 1024;
	char *szCode = NULL;
	unsigned int lenReq = 0;
	bool completeGen = false;
	while(!completeGen)
	{
		free(szCode);
		szCode = (char *)malloc(lenCode * sizeof(char));
		lenReq = CodeGen::EndFunc(pGenHead, &env, szCode, lenCode);
		completeGen = (lenReq <= lenCode);
		lenCode = lenReq;
	}

	printf("MainFuncWith2LocalVariablesAddition:\n\s", szCode);
	free(szCode);
}

void buildCodeGenTests(Tester *t) {
	EmptyMainFunc(t);
}