#include "Description.h"
#include "Descriptions.h"
namespace code_learning {
	Descriptions::Descriptions(Config &cfg):
		m_cfg(cfg){

	}
	void Descriptions::AddDescription(const std::string &content) {
		m_descs.push_back(std::unique_ptr<Description>(
			new Description(content, m_cfg)));
	}
	Description &Descriptions::GetDescription(const std::string &content) {
		for (auto desc = m_descs.rbegin(); desc != m_descs.rend(); desc++) {
			if ((*desc)->m_content == content) {
				return **desc;
			}
		}
		throw "GetDescription";
	}
}