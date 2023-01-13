#include <iostream>
#include "Code/Code.h"
#include "Code/Lexis.h"
#include "Glob.h"
#include "Code/Line.h"
#include "Line.h"

namespace code_learning {
	namespace statistics {
		Line::Line(const std::string &content, Glob &glob) :
			Composite<statistics::Lexis, statistics::Lexis>(content, glob) {
		}
		void Line::Statistics(code::Line &line) {
			m_signature = line.GetSignature();
			const std::shared_ptr<ListMap<Frequency<statistics::Lexis>>> &lexes = m_children.front();
			std::string preLexis;
			for (auto lexis = line.m_children.front().begin(); lexis != line.m_children.front().end(); ) {
				if ((*lexis)->IsSpace()) {
					lexis++;
					continue;
				}

				std::string description;
				while ((*lexis)->IsMulti()) {
					description.append(std::string((*lexis)->begin(), (*lexis)->end()));
					if (++lexis == line.m_children.front().end()) {
						break;
					}
				}
				if (!description.empty()) {
					m_descs.AddDescription(description);
					if (lexis != line.m_children.front().end()) {
						m_glob.m_generate.wrappers.insert(Wrapper(preLexis, std::string((*lexis)->begin(), (*lexis)->end())));
						lexis++;
					}
					else {
						m_glob.m_generate.wrappers.insert(Wrapper(preLexis));
					}
					continue;
				}

				if (PeekWrap(lexis, line.m_children.front().end())) {
					(*lexes)[m_wrapper.m_prefix]++;
					if (!preLexis.empty()) {
						(*lexes)[m_wrapper.m_prefix].m_front.Count(preLexis);
						(*lexes)[preLexis].m_back.Count(m_wrapper.m_prefix);
					}
					while (true) {
						description.append(std::string((*lexis)->begin(), (*lexis)->end()));
						lexis++;
						if (lexis == line.m_children.front().end()) {
							return;
						}
						if (PeekWrap(lexis, line.m_children.front().end())) {
							m_descs.AddDescription(description);
							break;
						}
					}
					(*lexes)[preLexis = m_wrapper.m_suffix]++;
					continue;
				}

				const std::string lexisContent((*lexis)->begin(), (*lexis)->end());
				(*lexes)[lexisContent]++;
				if (1 == lexisContent.size() && IsSymmetry(lexisContent.front())) {
					m_symmetries[lexisContent.front()] ++;
				}
				if (!preLexis.empty()) {
					(*lexes)[lexisContent].m_front.Count(preLexis);
					(*lexes)[preLexis].m_back.Count(lexisContent);
				}
				preLexis = lexisContent;
				lexis++;
			}
		}
		bool Line::PeekWrap(std::list<std::shared_ptr<code::Lexis>>::const_iterator &lexis,
			std::list<std::shared_ptr<code::Lexis>>::const_iterator end)  {
			for (const auto &wrap : m_glob.m_generate.wrappers) {
				bool isMatching = true;
				auto cursor = lexis;
				for (const auto &c : wrap.m_prefix) {
					if (c != *(*cursor)->begin()) {
						isMatching = false;
						break;
					}
					cursor++;
					if (cursor == end) {
						return false;
					}
				}
				if (isMatching) {
					lexis = cursor;
					m_wrapper = wrap;
					return true;
				}
			}
			return false;
		}
		bool Line::PeekWrap(std::list<std::shared_ptr<code::Lexis>>::const_iterator &lexis,
			std::list<std::shared_ptr<code::Lexis>>::const_iterator end)const {
			bool isMatching = true;
			auto cursor = lexis;
			for (const auto &c : m_wrapper.m_suffix) {
				if (cursor == end) {
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
		void Line::Summary()const {
			std::cout << "+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++" << std::endl;
			std::cout << "Line:" << std::endl;
			std::cout << "Key:" << m_signature << std::endl;
			std::cout << "Content:" << m_content << std::endl;
			std::cout << "Lexiss:[";
			for (const auto &lexis : *m_children.front()) {
				std::cout << lexis->m_element.GetContent() << ':' << lexis->GetCount() << '\t';
			}
			std::cout << "]";
			std::cout << std::endl << "-------------------------------------------------" << std::endl;
			if (m_descs.begin() != m_descs.end()) {
				std::cout << "Descs:<";
				for (const auto &desc : m_descs) {
					std::cout << desc->m_content << std::endl;
				}
				std::cout << ">";
			}
			std::cout << "+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++" << std::endl;
		}
	}
}