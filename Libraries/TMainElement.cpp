#include "TMainElement.h"


const int										pss::TMainElement::s_numberOfMainElements = 3;

pss::TMainElement::TMainElement()
{
	m_mainElement = eMainElements::SUN_GEAR;
}

pss::TMainElement::TMainElement(eMainElements mainElement)
{
	set(mainElement);
}

pss::TMainElement::eMainElements pss::TMainElement::get() const
{
	return m_mainElement;
}

void pss::TMainElement::set(eMainElements mainElement)
{
	m_mainElement = mainElement;
}

void pss::TMainElement::operator++()
{
		m_mainElement = eMainElements(int(m_mainElement)+1);
}

bool pss::TMainElement::end()
{
	if (m_mainElement > eMainElements::CARRIER)
		return false;
	else
		return true;
}

std::ostream& pss::operator<<(std::ostream& out, const TMainElement & mainElement)
{
	out << int(mainElement.m_mainElement);
	return out;
}