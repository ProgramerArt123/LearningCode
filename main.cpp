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
		algorithm::Event B(456, S);

		BOOST_ASSERT(P(A) == CERTAIN - P(!A) && "Complementary Events--1");
		BOOST_ASSERT(CERTAIN == P(A) + P(!A) && "Complementary Events--2");
		BOOST_ASSERT(CERTAIN - P(A) == P(!A) && "Complementary Events--3");

		BOOST_ASSERT(P(A - B) == P(A) - P(A&B) && "Intersection Events--1");
		BOOST_ASSERT(P(A - B) + P(A) == P(B&A) && "Intersection Events--2");
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