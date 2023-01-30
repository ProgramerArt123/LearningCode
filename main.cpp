#include <boost/assert.hpp>
#include "Statistics/CodeLearning.h"
#include "Code/SourceFile.h"
#include "Code/SourceFileBatch.hpp"
#include "Code/SourcePath.h"
#include "Code/Code.h"
#include "Algorithm/Set.hpp"
#include "Algorithm/Event.h"

using namespace code_learning;

int main() {
	{
#include "Algorithm/Probability.h"
		algorithm::SampleSpace S;
		algorithm::Event A(123, S);
		algorithm::Probability P;
		BOOST_ASSERT(P(A) == CERTAIN - P(!A) && "Complementary Events");
	}
	statistics::CodeLearning student("CPP");
	student.SetSplits(' ', '\n', '\r', '\t', ';', ',');
	student.SetIgnores(' ', '\n', '\r', '\t');
	code::SourcePath samples(".");
	samples.AddSuffixNames(".h", ".hpp", ".cpp", ".cc", ".cxx", ".c++", ".cp", ".c");
	student.Learning(samples);
	code::Code code("int main(){return 0;}");
	student.Learning(code);
	getchar();
	return 0;
}