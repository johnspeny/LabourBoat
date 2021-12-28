#include "MyBodyParser.h"

MyBodyParser* MyBodyParser::getInstance()
{
	static MyBodyParser* myBodyParser = nullptr;
	if (nullptr == myBodyParser)
	{
		myBodyParser = new MyBodyParser;
	}
	return myBodyParser;
}

bool MyBodyParser::parseJsonFile(const std::string& pFile)
{
	auto content = FileUtils::getInstance()->getDataFromFile(pFile);
	bool result = parse(content.getBytes(), content.getSize());
	return result;
}

bool MyBodyParser::parse(unsigned char* buffer, long length)
{
	bool result = false;
	std::string js((const char*)buffer, length);
	doc.Parse<0>(js.c_str());
	if (!doc.HasParseError())
	{
		result = true;
	}
	return result;
}

void MyBodyParser::clearCache()
{
	doc.SetNull();
}

void MyBodyParser::bodyFromJson(cocos2d::Node* pNode
    , const std::string& name
    , b2FixtureDef* _fd,
    b2Body* _Body)
{
    GameVars::initVars();

    rapidjson::Value& bodies = doc["rigidBodies"];
    if (bodies.IsArray())
    {

        for (int i = 0; i < bodies.Size(); ++i)
        {

            if (0 == strcmp(name.c_str(), bodies[i]["name"].GetString()))
            {
                rapidjson::Value& bd = bodies[i];
                if (bd.IsObject())
                {


                    float width = pNode->getContentSize().width;
                    float offx = -pNode->getAnchorPoint().x * pNode->getContentSize().width;
                    float offy = -pNode->getAnchorPoint().y * pNode->getContentSize().height;

                    Point origin(bd["origin"]["x"].GetDouble(), bd["origin"]["y"].GetDouble());
                    rapidjson::Value& polygons = bd["polygons"];

                    for (int i = 0; i < polygons.Size(); ++i)
                    {
                        int pcount = polygons[i].Size();
                        Point* points = new Point[pcount];
                        b2Vec2* vertices = new b2Vec2[pcount];
                        for (int pi = 0; pi < pcount; ++pi)
                        {
                            points[pi].x = offx + width * polygons[i][pcount - 1 - pi]["x"].GetDouble();
                            points[pi].y = offy + width * polygons[i][pcount - 1 - pi]["y"].GetDouble();
                            vertices[pi].Set(points[pi].x / GameVars::PTM_Ratio, points[pi].y / GameVars::PTM_Ratio);
                        }

                        b2PolygonShape* polygonShape = new b2PolygonShape();
                        polygonShape->Set(vertices, pcount);
                        _fd->shape = polygonShape;
                        _Body->CreateFixture(_fd);

                        delete[] points;
                        delete[] vertices;
                    }

                    rapidjson::Value& circles = bd["circles"];
                    int sz = circles.Size();
                    for (int i = 0; i < circles.Size(); ++i)
                    {
                        int pcount = circles.Size();
                        Point* points = new Point[pcount];
                        b2Vec3* vertices = new b2Vec3[pcount];

                        for (int pi = 0; pi < pcount; ++pi)
                        {
                            points[pi].x = offx + width * circles[pcount - 1 - pi]["cx"].GetDouble();
                            points[pi].y = offy + width * circles[pcount - 1 - pi]["cy"].GetDouble();
                            float radius = (width * circles[pcount - 1 - pi]["r"].GetDouble()) / GameVars::PTM_Ratio;
                            vertices[pi].Set(points[pi].x / GameVars::PTM_Ratio, points[pi].y / GameVars::PTM_Ratio, radius);
                        }

                        b2CircleShape* pcircleShape = new b2CircleShape();
                        pcircleShape->m_radius = vertices[0].z;
                        _fd->shape = pcircleShape;
                        _Body->CreateFixture(_fd);

                        delete[] points;
                        delete[] vertices;
                    }

                }
                else
                {
                    CCLOGWARN("body: %s not found!", name.c_str());
                }
                break;
            }



        }
    }
	
}
