/**
 * \file TileCar.cpp
 *
 * \author Helena Narowski
 */

#include "stdafx.h"
#include "TileCar.h"


using namespace std;
using namespace Gdiplus;


/**
 * Constructor
 *\param city The city that's passed in
 */
CTileCar::CTileCar(CCity *city) : CTile(city)
{
}


/**
 * Destructor
 */
CTileCar::~CTileCar()
{
}

/** \brief Save this item to an XML node
* \param node The node we are going to be a child of
* \returns Pointer to the crated node
*/
std::shared_ptr<xmlnode::CXmlNode> CTileCar::XmlSave(const std::shared_ptr<xmlnode::CXmlNode> &node)
{
	auto itemNode = CTile::XmlSave(node);

	itemNode->SetAttribute(L"type", L"transportation");
	itemNode->SetAttribute(L"file", GetFile());

	return itemNode;
}


/**
* brief Load the attributes for an item node.
* \param node The Xml node we are loading the item from
*/
void CTileCar::XmlLoad(const std::shared_ptr<xmlnode::CXmlNode> &node)
{
	CTile::XmlLoad(node);

	SetImage(node->GetAttributeValue(L"file", L""));

}