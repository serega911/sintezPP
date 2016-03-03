#include "../Libraries/TI.h"
#include <iostream>

pss::TI::TI(const std::vector<float>& i, float eps)
{
	m_i = i;
	m_eps = eps;
}

pss::TI::TI():
TI({},0.01)
{
}

int pss::TI::size() const
{
	return m_i.size();
}

const float pss::TI::operator[](int i) const
{
	return m_i.at(i);
}

void pss::TI::operator=(const TI& obj)
{
	m_i = obj.m_i;
	m_eps = obj.m_eps;
}

void pss::TI::push_back(float value)
{
	m_i.push_back(value);
}

void pss::TI::print()
{
	std::cout << "eps = " << m_eps << std::endl;
	for (auto& it: m_i)
		std::cout << it << ' ';
	std::cout << std::endl;
}

bool pss::TI::operator==(const pss::TI& obj)
{
		if (m_i.size() <= obj.size())
		{
			for (auto& it : m_i)
			{
				bool finded = false;
				for (auto& jt : obj.m_i)
				{
					if (abs(it - jt) <= m_eps)
						finded = true;
				}
				if (finded == false)
					return false;
			}
			return true;
		}
		else if (m_i.size() > obj.size())
		{
			for (auto& it : obj.m_i)
			{
				bool finded = false;
				for (auto& jt : m_i)
				{
					if (abs(it - jt) <= m_eps)
						finded = true;
				}
				if (finded == false)
					return false;
			}
			return true;
		}
}
