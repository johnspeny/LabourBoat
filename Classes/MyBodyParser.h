#ifndef __MYBODYPARSER_H__
#define __MYBODYPARSER_H__

#include "cocos2d.h"
#include "rapidjson/document.h"
#include "box2d/box2d.h"
#include "GameVars.h"

USING_NS_CC;

class MyBodyParser
{
	MyBodyParser() {};
	rapidjson::Document doc;

public:
	static MyBodyParser* getInstance();
	bool parseJsonFile(const std::string& pFile);
	bool parse(unsigned char* buffer, long length);
	void clearCache();
	void bodyFromJson(cocos2d::Node* pNode
		, const std::string& name
		, b2FixtureDef* _fd,
		b2Body* _Body);
};

#endif // !__MYBODYPARSER_H__
