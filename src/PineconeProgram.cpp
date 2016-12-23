#include "../h/PineconeProgram.h"
#include "../h/ErrorHandler.h"
#include "../h/Operator.h"
#include "../h/AllOperators.h"

void populatePineconeStdLib();
void lexString(string text, string filename, vector<Token>& tokens);
Action parseFunction(const vector<Token>& tokens, int left, int right, Type leftInType, Type rightInType);

extern Namespace stdLibNamespace;

PineconeProgram::PineconeProgram()
{
	
}

void PineconeProgram::cleanUp()
{
	globalFrame=StackFrame();
}

void PineconeProgram::resolveProgram(bool printOutput)
{
	AllOperators::init();
	populatePineconeStdLib();
	
	//initialProgramPopulation();
	
	//globalFrame.resolve(printOutput);
	
	lexString(inSource, inFileName, tokens);
	
	if (printOutput)
	{
		cout << endl << tableStringFromTokens(tokens, "lexer output") << endl;
	}
	
	//astRoot=parseFunction(tokens, 0, tokens.size()-1, Void, Void);
	
	astRoot=astNodeFromTokens(tokens);
	astRoot->setInput(stdLibNamespace, Void, Void);
	
	if (printOutput)
	{
		cout << endl << putStringInBox(astRoot->getString(), false, "parsed abstract syntax tree", 160) << endl;
	}
	
	if (astRoot)
	{
		try
		{
			actionRoot=astRoot->getAction();
			
			cout << endl << putStringInBox(actionRoot->toString(), false, "parsed action tree", 160) << endl;
		}
		catch (PineconeError err)
		{
			err.log();
		}
	}
	
	/*if (printOutput)
	{
		cout << endl << "C source code:\n" << astRoot->getCSource() << endl;
	}*/
	
}

void PineconeProgram::execute()
{
	free(actionRoot->execute(nullptr, nullptr));
}

