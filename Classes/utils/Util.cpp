#include "Util.h"
#include <stdarg.h>
#include "rapidjson\pointer.h"
#include <time.h>
#include <fstream>
#include "cocostudio/CocoStudio.h"
#include "ui/CocosGUI.h"

namespace JsonUtils
{
	rapidjson::Pointer getPoint(const char* format, ...) {
#define CC_MAX_STRING_LENGTH_JSON (1024*100)
		std::string ret;

		va_list ap;
		va_start(ap, format);

		char* buf = (char*)malloc(CC_MAX_STRING_LENGTH_JSON);
		if (buf != nullptr)
		{
			vsnprintf(buf, CC_MAX_STRING_LENGTH_JSON, format, ap);
			ret = buf;
			free(buf);
		}
		va_end(ap);

		rapidjson::Pointer pointer(ret.c_str());
		return pointer;
	}
}

namespace DateUtils
{
	long currentTimestamp() {
		time_t timep;
		time(&timep);
		return timep;
	}

	std::string formatTimestamp(const char* format, long timestamp) {
		std::string ret;
		time_t timep = timestamp;
		struct tm *ptr;
		ptr = localtime(&timep);
		char ch[80];
		strftime(ch, 80, format, ptr);
		ret = ch;
		return ret;
	}
}


namespace MeFileUtils
{
	void writeStringToFile(const std::string str, const std::string file) {
		std::ofstream out(file);
		if (out.is_open()) {
			out << str;
			out.close();
		}
	}
}

namespace MeNodeUtil
{
	Node* seekFromRootByName(cocos2d::Node* root, std::string name) {
		if (!root) return nullptr;
		if (root->getName() == name) return root;
		const auto& children = root->getChildren();
		for (auto& child : children) {
			Node* p_node = dynamic_cast<Node*>(child);
			if (p_node) {
				Node* node = seekFromRootByName(p_node, name);
				if (node) return node;
			}
		}
		return nullptr;
	}
};