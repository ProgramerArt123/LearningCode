#include "CodeLearning.h"

using namespace code_learning;

int main() {
	CodeLearning student;
	student.SetSplits(' ', '\n', '\r', '\t', ';', ',');
	student.SetIgnores(' ', '\n', '\r', '\t');
	{
		SourceFile code("Char.h");
		student.Learning(code);
	}
	{
		SourceFile code("Char.cpp");
		student.Learning(code);
	}
	{
		SourceFile code("Code.h");
		student.Learning(code);
	}
	{
		SourceFile code("Code.cpp");
		student.Learning(code);
	}
	{
		SourceFile code("CodeLearning.h");
		student.Learning(code);
	}
	{
		SourceFile code("CodeLearning.cpp");
		student.Learning(code);
	}
	{
		SourceFile code("Lexis.h");
		student.Learning(code);
	}
	{
		SourceFile code("Lexis.cpp");
		student.Learning(code);
	}
	{
		SourceFile code("SourceFile.h");
		student.Learning(code);
	}
	{
		SourceFile code("SourceFile.cpp");
		student.Learning(code);
	}
	{
		SourceFile code("main.cpp");
		student.Learning(code);
	}
	student.Summary();
	getchar();
	return 0;
}