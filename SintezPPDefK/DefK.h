#pragma once

#include <vector>
#include "../Libraries/TK.h"
#include "../Libraries/TI.h"
#include "../Libraries/TGearBox.h"
#include "../Libraries/GlobalDefines.h"

NS_ARI_START

	class DefK
	{
	public:

		NS_CORE TK								findK( const NS_CORE TGearBox& gearBox );
		void									run();

	private:

		void									readInitialData();

		void									checkAllInitialKValues( const NS_CORE TGearBox& gearBox, NS_CORE TK& ret );
		void									checkAllRatiosPermutations( const NS_CORE TGearBox& gearBox, const NS_CORE TK& initial, NS_CORE TK& ret );
	};

NS_ARI_END