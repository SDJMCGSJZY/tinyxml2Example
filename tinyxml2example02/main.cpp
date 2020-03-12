#include <iostream>
#include"tinyxml2.h"
#include <map>
using namespace std;
using namespace tinyxml2;

//���Ĵ��룬�ݹ�ʵ�ֶ�ȡxml�Ľڵ�
void GetElementValue(XMLElement *element , std::map<std::string, std::string> &itemID_value_map)
{
	for (XMLElement* currenteleElement = element->FirstChildElement(); currenteleElement; currenteleElement = currenteleElement->NextSiblingElement())
	{
		XMLElement* tmpele = currenteleElement;
		if (currenteleElement->GetText() != NULL)
		{
			cout << "ItemID = " << currenteleElement->Attribute("ItemID") << "---Value = " << currenteleElement->GetText() << endl;
			itemID_value_map[currenteleElement->Attribute("ItemID")] = currenteleElement->GetText();
		}
		//�жϸýڵ��Ƿ�Ϊ�գ������Ϊ��������ݹ�
		if (!tmpele->NoChildren())
			GetElementValue(tmpele,itemID_value_map);
	}
}

//�ݹ��ȡxml�ļ��еĽڵ㣬���ұ��浽map��
std::map<std::string,std::string> CycleReadAllNode(std::string xmlPath) 
{
	static std::map<std::string, std::string> itemID_value_map;
	itemID_value_map.clear();

	tinyxml2::XMLDocument xml;
	if (xml.LoadFile(xmlPath.c_str()) != XML_SUCCESS)
	{
		return itemID_value_map; //return empty map
	}
	tinyxml2::XMLElement* rootNode = xml.RootElement();
	if (rootNode == NULL) {
		return itemID_value_map; //return empty map
	}
	GetElementValue(rootNode, itemID_value_map);
	return itemID_value_map;
}


int main()
{
	std::map<std::string, std::string>  maps = CycleReadAllNode("ElectronicProduct.xml");
	//����map
	cout << "-----------------------begin ѭ�������ڵ�------------------------" << endl;
	std::map<std::string, std::string>::iterator iter;
	for (iter = maps.begin(); iter != maps.end(); iter++)
	{
		std::cout << "itemId = " << (iter->first).c_str() << "-------value = " << (iter->second).c_str() << std::endl;
	}
	cout << "-----------------------end   ѭ�������ڵ�------------------------" << endl;
    return 0;
}