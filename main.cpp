#include <iostream>
#include "CodeLearning.h"
#include "SourceFile.h"

using namespace code_learning;

int main() {
	std::cout << "代码学习" << std::endl;
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
		SourceFile code("FrequencyWords.h");
		student.Learning(code);
	}
	{
		SourceFile code("FrequencyWords.cpp");
		student.Learning(code);
	}
	{
		SourceFile code("Config.h");
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