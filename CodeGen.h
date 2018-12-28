
#ifndef CODEGEN_H
#define CODEGEN_H

#include <string>
#include <iostream>
#include <fstream>
#include "linklst.h"
#include <stdint.h>
#include <sstream>
#include "symboltable.h"

class Environment;
//it is a node of a graph for generating code, the graph data structure mimics the control follow diagram depicted by any higher level languages
//each node will corresponds to one or more assembly instructions after the code is generated
class CodeGenNode {
public:
	const char* m_label;
	List<CodeGenNode* > m_succeeds;
};


//this class wraps a set of functions for generating code, the caller of the functions need be aware of the variables or constants which are specified by the identifiers
//and the operations in pseudo assembly level, i.e. in this level the caller of the functions would not care about registers or stacks but about the arithmetic and logic operations
//and the control flow depicted by the high level language code, the control flow starts with StartFunc, and terminated with EndFunc, once the control flow is terminated,
//then the corresponding assembly instruction code could be generated, for more detail please refer file testCodeGen.cpp.
class CodeGen {
public:
	static void Prologue(std::string infileName, std::string fileName);
	static void Epilogue();

	static CodeGenNode* StartFunc(const char* funcName, const List<uint32_t>& lstParamIds, const Environment* env);
	static CodeGenNode* StackPop(CodeGenNode *preceed, uint32_t id, const Environment* evn);
	static CodeGenNode* StackPush(CodeGenNode *preceed, uint32_t id, const Environment* evn);
	static CodeGenNode* Add(CodeGenNode *preceed, uint32_t id, uint32_t id2, const Environment* evn);
	static CodeGenNode* Add(CodeGenNode *preceed, uint32_t idr, uint32_t id1, uint32_t id2, const Environment* evn);
	static CodeGenNode* Sub(CodeGenNode *preceed, uint32_t idr, uint32_t id1, uint32_t id2, const Environment* evn);
	static CodeGenNode* Mul(CodeGenNode *preceed, uint32_t idr, uint32_t id1, uint32_t id2, const Environment* evn);
	static CodeGenNode* Div(CodeGenNode *preceed, uint32_t idr, uint32_t id1, uint32_t id2, const Environment* evn);
	static CodeGenNode* Mod(CodeGenNode *preceed, uint32_t idr, uint32_t id1, uint32_t id2, const Environment* evn);
	static CodeGenNode* Return(CodeGenNode *preceed, uint32_t id, const Environment* evn);
	static CodeGenNode* Less(CodeGenNode* preceed, uint32_t id1, uint32_t id2, const Environment* env);
	static CodeGenNode* Merge(List<CodeGenNode* >& branches, const Environment* env);
        static CodeGenNode* CallFunc(const char* funcName, const Environment* env);
	static unsigned int EndFunc(CodeGenNode* head, const Environment* env, char* szCode, unsigned int lenCode);
	static CodeGenNode *PutString(uint32_t stringPoolHandle, bool newLine);

private:
	static std::ofstream outputFile;
	static std::ostringstream bufferedOutput;

	static void Constants();
	static uint32_t NewLabel();
};


#endif //CODEGEN_H
