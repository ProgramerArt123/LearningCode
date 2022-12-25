#include "Line.h"

namespace code_learning {
	Line::Line(const std::string &content, const Config &cfg) :
		Element(content, cfg), m_adjacencies(cfg) {
	}
	void Line::AppendWord(const std::string &content) {
		m_adjacencies[content];
	}
}