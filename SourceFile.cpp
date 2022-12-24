#include <fstream>
#include <sstream>
#include "Config.h"
#include "SourceFile.h"

namespace code_learning {

	SourceFile::SourceFile(const char *fileName) {
		std::ifstream source(fileName);
		if (source.is_open()) {
			std::stringstream buffer;
			buffer << source.rdbuf();
			m_content = buffer.str();
		}
	}
	void SourceFile::Scan(const Config &cfg) {
		m_code.reset(new Code(m_content.c_str(), cfg));
	}
	std::list<std::unique_ptr<Lexis>>::const_iterator SourceFile::begin() const {
		return m_code->GetLexes().begin();
	}
	std::list<std::unique_ptr<Lexis>>::const_iterator SourceFile::end() const {
		return m_code->GetLexes().end();
	}
	Wrapper SourceFile::PeekWrap(std::list<std::unique_ptr<Lexis>>::const_iterator &lexis, const Config &cfg) const{
		for (const auto &wrap : cfg.wrappers) {
			bool isMatching = true;
			auto cursor = lexis;
			for (const auto &c : wrap.m_prefix) {
				if (c != *(*cursor)->begin()) {
					isMatching = false;
					break;
				}
				cursor++;
				if (cursor == end()) {
					lexis = cursor;
					return Wrapper();
				}
			}
			if (isMatching) {
				lexis = cursor;
				return wrap;
			}
		}
		return Wrapper();
	}
	bool SourceFile::PeekWrap(std::list<std::unique_ptr<Lexis>>::const_iterator &lexis, const std::string &wrap)const {
		bool isMatching = true;
		auto cursor = lexis;
		for (const auto &c : wrap) {
			if (cursor == end()) {
				throw "SourceFile::PeekWrap";
			}
			if (c != *(*cursor)->begin()) {
				isMatching = false;
				break;
			}
			cursor++;
		}
		if (isMatching) {
			lexis = cursor;
			return true;
		}
		return false;
	}
}

