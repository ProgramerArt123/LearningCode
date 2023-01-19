#include <iostream>
#include "Code/Code.h"
#include "Code/Lexis.h"
#include "Glob.h"
#include "Code/Line.h"
#include "Block.h"

namespace code_learning {
	namespace statistics {
		Block::Block(const std::string &content, Glob &glob) :
			Composite<statistics::LexisFacade>(content, glob) {
		}
		void Block::Statistics(code::Element &element) {
			code::Block &block = static_cast<code::Block&>(element);
			m_signature = block.GetSignature();
			std::string preLexis;
			for (auto child = block.m_children.front().begin(); child != block.m_children.front().end(); ) {

				if (code::ELEMENT_TYPE_BLOCK == (*child)->GetType()) {
					
					child++;
					continue;
				}

				const std::shared_ptr<code::Lexis> &lexis = std::dynamic_pointer_cast<code::Lexis>(*child);

				if (lexis->IsSpace()) {
					child++;
					continue;
				}

				std::string description;
				while (lexis->IsMulti()) {
					description.append(std::string(lexis->begin(), lexis->end()));
					if (++child == block.m_children.front().end()) {
						break;
					}
				}
				if (!description.empty()) {
					m_descs.AddDescription(description);
					if (child != block.m_children.front().end()) {
						m_glob.m_generate.wrappers.insert(Wrapper(preLexis, std::string(lexis->begin(), lexis->end())));
						child++;
					}
					else {
						m_glob.m_generate.wrappers.insert(Wrapper(preLexis));
					}
					continue;
				}

				if (PeekWrap(child, block.m_children.front().end())) {
					m_children.front()->Count(m_wrapper.m_prefix);
					if (!preLexis.empty()) {
						m_children.front()->FrontCount(m_wrapper.m_prefix, preLexis);
						m_children.front()->BackCount(preLexis, m_wrapper.m_prefix);
					}
					while (true) {
						description.append(std::string(lexis->begin(), lexis->end()));
						child++;
						if (child == block.m_children.front().end()) {
							return;
						}
						if (PeekWrap(child, block.m_children.front().end())) {
							m_descs.AddDescription(description);
							break;
						}
					}
					m_children.front()->Count(preLexis = m_wrapper.m_suffix);
					continue;
				}

				const std::string lexisContent(lexis->begin(), lexis->end());
				m_children.front()->Count(lexisContent);
				if (1 == lexisContent.size() && IsSymmetry(lexisContent.front())) {
					m_symmetries[lexisContent.front()] ++;
				}
				if (!preLexis.empty()) {
					m_children.front()->FrontCount(lexisContent, preLexis);
					m_children.front()->BackCount(preLexis, lexisContent);
				}
				preLexis = lexisContent;
				child++;
			}
		}
		bool Block::PeekWrap(std::list<std::shared_ptr<code::Element>>::const_iterator &lexis,
			std::list<std::shared_ptr<code::Element>>::const_iterator end) {
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
		bool Block::PeekWrap(std::list<std::shared_ptr<code::Element>>::const_iterator &lexis,
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
		void Block::Summary()const {
			
		}
		
	}
}