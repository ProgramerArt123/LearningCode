#include <iostream>
#include "Code/Code.h"
#include "Code/Lexis.h"
#include "Glob.h"
#include "Code/Line.h"
#include "Line.h"

namespace code_learning {
	namespace statistics {
		Line::Line(const std::string &content, Glob &glob) :
			Composite(content, glob) {
		}
		void Line::Statistics(const code::Element &element) {
			m_signature = element.GetSignature();
			SetChildrenCount(element.GetChildrenCount());
			std::string preLexis;
			for (auto child = element.GetChild(0)->begin(); child != element.GetChild(0)->end(); ) {
				
				if ((*child)->IsSpace()) {
					child++;
					continue;
				}

				std::string description;
				while ((*child)->IsMulti()) {
					description.append(std::string((*child)->begin(), (*child)->end()));
					if (++child == element.GetChild(0)->end()) {
						break;
					}
				}
				if (!description.empty()) {
					m_descs.AddDescription(description);
					if (child != element.GetChild(0)->end()) {
						m_glob.m_generate.wrappers.insert(Wrapper(preLexis, std::string((*child)->begin(), (*child)->end())));
						child++;
					}
					else {
						m_glob.m_generate.wrappers.insert(Wrapper(preLexis));
					}
					continue;
				}

				if (PeekWrap(child, element.GetChild(0)->end())) {
					m_children.front()->Count(**child, m_wrapper.m_prefix);
					if (!preLexis.empty()) {
						m_children.front()->FrontCount(**child, m_wrapper.m_prefix, preLexis);
						m_children.front()->BackCount(**child, preLexis, m_wrapper.m_prefix);
					}
					while (true) {
						description.append(std::string((*child)->begin(), (*child)->end()));
						child++;
						if (child == element.GetChild(0)->end()) {
							return;
						}
						if (PeekWrap(child, element.GetChild(0)->end())) {
							m_descs.AddDescription(description);
							break;
						}
					}
					m_children.front()->Count(**child, preLexis = m_wrapper.m_suffix);
					continue;
				}

				const std::string lexisContent((*child)->begin(), (*child)->end());
				m_children.front()->Count(**child, lexisContent);
				if (1 == lexisContent.size() && code::IsSymmetry(lexisContent.front())) {
					m_symmetries[lexisContent.front()] ++;
				}
				if (!preLexis.empty()) {
					m_children.front()->FrontCount(**child, lexisContent, preLexis);
					m_children.front()->BackCount(**child, preLexis, lexisContent);
				}
				preLexis = lexisContent;
				child++;
			}
		}
		bool Line::PeekWrap(std::list<std::shared_ptr<code::Element>>::const_iterator &lexis,
			std::list<std::shared_ptr<code::Element>>::const_iterator end)  {
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
		bool Line::PeekWrap(std::list<std::shared_ptr<code::Element>>::const_iterator &lexis,
			std::list<std::shared_ptr<code::Element>>::const_iterator end)const {
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
				std::cout << lexis->GetContent() << ':' << lexis->GetCount() << '\t';
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