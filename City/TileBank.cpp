#include "stdafx.h"
#include "TileBank.h"

#include "stdafx.h"
#include "TileBank.h"

using namespace std;
using namespace Gdiplus;

/// Image of the bank
const wstring Bank = L"bank.png";


/** Constructor
* \param city The city this is a member of
*/
CTileBank::CTileBank(CCity *city) : CTile(city)
{
	SetImage(Bank);
}

/**
* \brief Destructor
*/
CTileBank::~CTileBank()
{
}

/** \brief Save this item to an XML node
* \param node The node we are going to be a child of
* \returns Allocated node
*/
std::shared_ptr<xmlnode::CXmlNode> CTileBank::XmlSave(const std::shared_ptr<xmlnode::CXmlNode> &node)
{
	auto itemNode = CTile::XmlSave(node);

	itemNode->SetAttribute(L"type", L"bank");
	itemNode->SetAttribute(L"file", GetFile());

	return itemNode;
}

/**
* brief Load the attributes for an item node.
* \param node The Xml node we are loading the item from
*/
void CTileBank::XmlLoad(const std::shared_ptr<xmlnode::CXmlNode> &node)
{
	CTile::XmlLoad(node);

	SetImage(node->GetAttributeValue(L"file", L""));
}
