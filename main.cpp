#include <boost/assert.hpp>
#include "Statistics/CodeLearning.h"
#include "Code/SourceFile.h"
#include "Code/SourceFileBatch.hpp"
#include "Code/SourcePath.h"
#include "Code/Code.h"
#include "Algorithm/Set.hpp"
#include "Algorithm/Event.h"
#include "Algorithm/IndependentEvent.h"

using namespace code_learning;

int main() {
	{
#include "Algorithm/Probability.h"
		srand(time(0));
		algorithm::SampleSpace S;
		int random = rand();
		algorithm::Event A(random, S);
		algorithm::Probability P;
		algorithm::Event B(456, S);
		algorithm::Event C(0, S);
		C.m_samples.m_samples.AddRanges(algorithm::Range(666, 888));
		algorithm::SampleSpace S2(100);
		algorithm::SampleSpace S3(100);
		algorithm::SampleSpace S4(100);
		algorithm::IndependentEvent D(10, S2);
		algorithm::IndependentEvent E(20, S3);
		algorithm::IndependentEvent F(30, S4);

		BOOST_ASSERT(P(A) == CERTAIN - P(!A) && "Complementary Events--1");
		BOOST_ASSERT(CERTAIN == P(A) + P(!A) && "Complementary Events--2");
		BOOST_ASSERT(CERTAIN - P(A) == P(!A) && "Complementary Events--3");

		BOOST_ASSERT(P(A - B) == P(A) - P(A&B) && "Difference Events--1");
		BOOST_ASSERT(P(A) - P(A - B) ==  P(B&A) && "Difference Events--2");

		BOOST_ASSERT(P(A + B) == P(A) + P(B) - P(B&A) && "Unions Events--1");
		BOOST_ASSERT(P(B + A) + P(A&B) == P(B) + P(A) && "Unions Events--2");

		BOOST_ASSERT(P(B + C) == P(B) + P(C) && "Disjoint Events--1");
		BOOST_ASSERT(P(C + B) - P(B) ==  P(C) && "Disjoint Events--2");

		BOOST_ASSERT(P(D&E) == P(D)*P(E) && "Independent Events--1");
		BOOST_ASSERT(P(D&E&F) == P(D)*P(E)*P(F) && "Independent Events--2");
		BOOST_ASSERT(P(D&(E&F)) == P(D)*P(E)*P(F) && "Independent Events--3");
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