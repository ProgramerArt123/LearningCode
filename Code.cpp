#include <cstring>
#include <iostream>
#include <boost/uuid/detail/md5.hpp>
#include <boost/algorithm/hex.hpp>
#include "Config.h"
#include "Lexis.h"
#include "Word.h"
#include "Code.h"

namespace code_learning {
	namespace code {
		Code::Code(const char *content, Config &cfg) :m_cfg(cfg) {
			"代码学习";
			int reLineCount = 0;
			size_t length = strlen(content);
			for (size_t index = 0; index < length; index++) {
				if (m_regions.empty()) {
					m_regions.push_back(std::unique_ptr<Region>(new Region));
				}
				char c = content[index];
				auto &lastRegion = m_regions.back();
				if (IsReLine(c)) {
					reLineCount++;
					if (!lastRegion->m_lines.empty()) {
						if (reLineCount >= 2) {
							lastRegion->m_lines.pop_back();
							m_regions.push_back(std::unique_ptr<Region>(new Region));
						}
						else {
							lastRegion->m_lines.push_back(std::unique_ptr<Line>(new Line));
						}
					}
				}
				else {
					reLineCount = 0;
					if (lastRegion->m_lines.empty()) {
						lastRegion->m_lines.push_back(std::unique_ptr<Line>(new Line));
					}
					auto &lastLine = lastRegion->m_lines.back();
					lastLine->m_content += c;
				}
			}
			for (auto &region : m_regions) {
				region->Decomposition(cfg);
			}
		}

		void Code::Statistics(ListMap<Frequency<statistics::Region>> &regions)const {
			for (auto &region : m_regions) {
				auto &result = regions[region->GetSignature()];
				result.m_element.Statistics(*region);
				result++;
			}
			regions.Sort();
		}

		void Line::Decomposition(Config &cfg) {
			size_t length = m_content.length();
			bool isPreSplit = false;
			for (size_t index = 0; index < length; index++) {
				isPreSplit = CheckEncoding(m_content.c_str(), index);
				if (index == length) {
					break;
				}
				char c = m_content[index];
				if (!isPreSplit && !m_lexes.empty()) {
					std::unique_ptr<Lexis> &last = m_lexes.back();
					if (!last->TryAppendChar(c)) {
						m_lexes.push_back(std::unique_ptr<Lexis>(new Lexis(c)));
					}
				}
				else {
					m_lexes.push_back(std::unique_ptr<Lexis>(new Lexis(c)));
				}
				isPreSplit = cfg.splits.end() != cfg.splits.find(c);
			}

			std::string name;
			name.append("[");
			for (const auto &lexis : m_lexes) {
				if (1 < name.length()) {
					name.append(",");
				}
				WORD_TYPE type = Word::JudgeWordType(std::string(lexis->begin(), lexis->end()));
				switch (type)
				{
				case code_learning::WORD_TYPE_NONE:
					name.append("WORD_TYPE_NONE");
					break;
				case code_learning::WORD_TYPE_SPACE:
					break;
				case code_learning::WORD_TYPE_SYMBOL:
					name.append("WORD_TYPE_SYMBOL");
					break;
				case code_learning::WORD_TYPE_DIGITAL:
					name.append("WORD_TYPE_DIGITAL");
					break;
				case code_learning::WORD_TYPE_ALPHABET:
					name.append("WORD_TYPE_ALPHABET");
					break;
				case code_learning::WORD_TYPE_NAME:
					name.append("WORD_TYPE_NAME");
					break;
				default:
					break;
				}
			}
			name.append("]");

			boost::uuids::detail::md5 md5;
			boost::uuids::detail::md5::digest_type digest;
			md5.process_bytes(name.c_str(), name.length());
			md5.get_digest(digest);
			const auto charDigest = reinterpret_cast<const char *>(&digest);
			char result[33]{ 0 };
			boost::algorithm::hex(charDigest, charDigest + sizeof(boost::uuids::detail::md5::digest_type), result);
			m_signature = result;
		}

		const std::string &Line::GetSignature()const {
			return m_signature;
		}

		bool Line::CheckEncoding(const char *content, size_t &index) {
			uint8_t highOne = CharHighOne(content[index]);
			bool isMulti = highOne;
			if (highOne) {//描述性对象
				m_lexes.push_back(std::unique_ptr<Lexis>(new Lexis()));
				std::unique_ptr<Lexis> &last = m_lexes.back();
				for (uint8_t one = 0; one < highOne; one++) {
					last->AppendChar(content[index++]);
				}
			}
			return isMulti;
		}
		void Region::Decomposition(Config &cfg) {
			std::string name;
			name.append("[");
			for (auto &line : m_lines) {
				if (1 < name.length()) {
					name.append(",");
				}
				line->Decomposition(cfg);
				name.append(line->GetSignature());
			}
			name.append("]");

			boost::uuids::detail::md5 md5;
			boost::uuids::detail::md5::digest_type digest;
			md5.process_bytes(name.c_str(), name.length());
			md5.get_digest(digest);
			const auto charDigest = reinterpret_cast<const char *>(&digest);
			char result[33]{ 0 };
			boost::algorithm::hex(charDigest, charDigest + sizeof(boost::uuids::detail::md5::digest_type), result);
			m_signature = result;
		}
		const std::string &Region::GetSignature() const{
			return m_signature;
		}
	}
}