#include "CodeGen.h"
#include "environment.h"

#define outputTabbed(code) (CodeGen::outputFile << "\t" << code << "\n")
#define outputUntabbed(code) (CodeGen::outputFile << code << "\n")
#define outputTabbedToBuffer(code) (CodeGen::bufferedOutput << "\t" << code << "\n")
#define outputUntabbedToBuffer(code) (CodeGen::bufferedOutput << code << "\n")

struct StringConst {
	uint32_t label;
	uint32_t stringPoolHandle;
};

std::ofstream CodeGen::outputFile;
std::ostringstream CodeGen::bufferedOutput;

uint32_t nextFreeLabel = 0;
vector<StringConst> constants;

void CodeGen::Prologue(std::string infileName, std::string fileName) {
	CodeGen::outputFile.open(fileName.c_str());

	outputTabbed(".arch armv6");
	outputTabbed(".eabi_attribute 27, 3");
	outputTabbed(".eabi_attribute 28, 1");
	outputTabbed(".fpu vfp");
	outputTabbed(".eabi_attribute 20, 1");
	outputTabbed(".eabi_attribute 21, 1");
	outputTabbed(".eabi_attribute 23, 3");
	outputTabbed(".eabi_attribute 24, 1");
	outputTabbed(".eabi_attribute 25, 1");
	outputTabbed(".eabi_attribute 26, 2");
	outputTabbed(".eabi_attribute 30, 6");
	outputTabbed(".eabi_attribute 34, 1");
	outputTabbed(".eabi_attribute 18, 4");
	outputTabbed(".file\t\"" << infileName << "\"");
	outputTabbed(".section\t.rodata");
	outputTabbed(".align\t2");
}

void CodeGen::Epilogue() {
	// Done generating the main code, but output the constants before the main code
	CodeGen::Constants();
	CodeGen::outputFile << CodeGen::bufferedOutput.str();

	// Output all of the labels for the constants before the end
	for(int i = 0; i < constants.size(); i++) {
		outputUntabbed(".L" << constants[i].label << ":");
		outputTabbed(".word\t.LC" << i);
	}

	outputTabbed(".size\tmain, .-main");
	outputTabbed(".ident\t\"GCC: (Debian 4.6.3-14+rpi1) 4.6.3\"");
	outputTabbed(".section\t.note.GNU-stack,\"\",%progbits");

	CodeGen::outputFile.close();
}

void CodeGen::Constants() {
	// Output all of the constants in the string pool so we can use them later
	for(int i = 0; i < constants.size(); i++) {
		outputUntabbed(".LC" << i << ":");
		outputTabbed(".ascii\t\"" << symbol_get(constants[i].stringPoolHandle) << "\\000\"");
		outputTabbed(".align\t2");
	}

	outputTabbed(".global\tmain");
	outputTabbed(".type\tmain, %function");
}

uint32_t CodeGen::NewLabel() {
	outputUntabbedToBuffer(".L" << nextFreeLabel << ":");
	nextFreeLabel++;
	return nextFreeLabel - 1;
}

CodeGenNode* CodeGen::StartFunc(const char* funcName, const List<uint32_t>& lstParamIds, const Environment* env) {
    outputUntabbedToBuffer(funcName << ":");
    outputTabbedToBuffer("@ args = 0, pretend = 0, frame = 8");
    outputTabbedToBuffer("@ frame_needed = 1, uses_anonymous_args = 0");
    // Push the stack
    CodeGen::StackPush(NULL, 0, env);
	outputTabbedToBuffer("stmfd\tsp!, {fp, lr}");
    outputTabbedToBuffer("add\tfp, sp, #4");
    outputTabbedToBuffer("sub\tsp, sp, #8");
    return NULL;
}
CodeGenNode* CodeGen::StackPush(CodeGenNode *preceed, uint32_t id, const Environment* evn) {
    outputTabbedToBuffer("stmfd\tsp!, {fp, lr}");
    return NULL;
}
CodeGenNode* CodeGen::StackPop(CodeGenNode *preceed, uint32_t id, const Environment* evn) {
    outputTabbedCode("sub\tsp, fp, #4");
    outputTabbedCode("ldmfd\tsp!, {fp, pc}");
    return NULL;
}
CodeGenNode* CodeGen::Add(CodeGenNode *preceed, uint32_t id, uint32_t id2, const Environment* evn) {
    return NULL;
}
CodeGenNode* CodeGen::Add(CodeGenNode *preceed, uint32_t idr, uint32_t id1, uint32_t id2, const Environment* evn) {
	outputTabbedToBuffer("add\tr3, r2, r3");
	//=BUG= need to organize registers when doing operation
	return NULL;
}
CodeGenNode* CodeGen::Sub(CodeGenNode *preceed, uint32_t idr, uint32_t id1, uint32_t id2, const Environment* evn) {
	outputTabbedToBuffer("sub\tr3, r2, r3");
	//=BUG= need to organize registers when doing operation
	return NULL;
}
CodeGenNode* CodeGen::Mul(CodeGenNode *preceed, uint32_t idr, uint32_t id1, uint32_t id2, const Environment* evn) {
	outputTabbedToBuffer("mul\tr3, r2, r3");
	//=BUG= need to organize registers when doing operation
	return NULL;
}
CodeGenNode* CodeGen::Div(CodeGenNode *preceed, uint32_t idr, uint32_t id1, uint32_t id2, const Environment* evn) {
	outputTabbedToBuffer("div\tr3, r2, r3");
	//=BUG= need to organize registers when doing operation
	return NULL;
}
CodeGenNode* CodeGen::Mod(CodeGenNode *preceed, uint32_t idr, uint32_t id1, uint32_t id2, const Environment* evn) {
	// =BUG= MODULUS IS NOT SUPPORTED
	//=BUG= need to organize registers when doing operation
	return NULL;
}
CodeGenNode* CodeGen::Return(CodeGenNode *preceed, uint32_t id, const Environment* evn) {
    // RETURN
    // sub	sp, fp, #4
    // ldmfd	sp!, {fp, pc}
    outputTabbedToBuffer("sub\tsp, fp, #4");
    outputTabbedToBuffer("ldmfd\tsp!, {fp, pc}");
	return NULL;
}
CodeGenNode* CodeGen::Less(CodeGenNode* preceed, uint32_t id1, uint32_t id2, const Environment* env) {
    return NULL;
}
CodeGenNode* CodeGen::Merge(List<CodeGenNode* >& branches, const Environment* env) {
    return NULL;
}
CodeGenNode* CodeGen::CallFunc(const char* funcName, const Environment* env) {
    outputTabbedToBuffer("bl\tfuncName");
	return NULL;
}

CodeGenNode * CodeGen::PutString(uint32_t stringPoolHandle, bool newLine) {
	StringConst sc;
	sc.label = nextFreeLabel;
	sc.stringPoolHandle = stringPoolHandle;
	constants.push_back(sc);

	outputTabbedToBuffer("ldr\tr0, .L" << nextFreeLabel);
	if(newLine) {
		outputTabbedToBuffer("bl\tputs");
	} else {
		outputTabbedToBuffer("bl\tprintf");
	}

	nextFreeLabel++;

	return NULL;
}
unsigned int CodeGen::EndFunc(CodeGenNode* head, const Environment* env, char* szCode, unsigned int lenCode)
{
    return 0;
}