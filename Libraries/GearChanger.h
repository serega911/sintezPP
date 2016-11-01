#pragma once

#include <vector>

#include "Link.h"
#include "Code.h"
#include "GlobalDefines.h"

NS_CORE_START

class GearChanger
{
private:

	TLinkArray									m_drivingElements;
	std::vector<TLinkArray>						m_drivingElementsForAllGears;
	size_t										m_gear;

public:

	GearChanger() = delete;
	GearChanger(const Code& code);

	TLinkArray									getDrivingElementsForGear() const;
	bool										next();

};

NS_CORE_END