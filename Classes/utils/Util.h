#ifndef __YUEMA_UTIL_H__
#define __YUEMA_UTIL_H__
#include <string>
#include <stdarg.h>
#include "rapidjson\pointer.h"
#include "cocos2d.h"
#include "ui/CocosGUI.h"

#define FULL_DATE_FORMAT "%Y-%m-%d %H:%M:%S"
#define SHORT_TIME_FORMAT "%H:%M"

namespace JsonUtils
{
	rapidjson::Pointer getPoint(const char* format, ...);
}

namespace DateUtils
{
	long currentTimestamp();

	std::string formatTimestamp(const char* format, long timestamp);
}

namespace MeFileUtils
{
	void writeStringToFile(const std::string str, const std::string file);
}

namespace MeNodeUtil
{
	cocos2d::Node* seekFromRootByName(cocos2d::Node* root, std::string name);
};

#endif // __YUEMA_UTIL_H__