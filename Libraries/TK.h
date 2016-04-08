#pragma once
#include <vector>
#include <fstream>

#include "../Libraries/IContainer.h"

namespace pss
{
	class TK: public IContainer
	{
	private:
		bool									m_isFinded;
		std::vector<double>						m_K;
		std::vector<int>						m_combi;
		std::vector<double>						m_kValues;

		void									pushIntervalToValues(double beg, double end, double dk);
		bool									pss::TK::inDia(const double & val);
	public:
		TK() = delete;
		TK(double beginNegative, double endNegative, double beginPositive, double endPositive, double dK);
		TK(double begin, double end, double dK);
		const double								operator[](int i) const;
		bool									next();
		void									print() const;
		int										size() const override;
		void									setFinded();
		bool									getFinded();
		void									writeToFile(std::ofstream& file) const override;
		void									loadFromFile(std::ifstream&) override;
	};
}