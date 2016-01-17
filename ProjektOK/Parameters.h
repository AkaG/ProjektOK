#pragma once

namespace Parameters {
	namespace Feromone_Table {
		const int		INITIAL_VALUE		= 1;
		const float		VAPORING			= 5;
	}

	namespace Ants {
		const int		NUMBER				= 25;
		const float		TABLE_PROBABILITY	= 1000; // im wi�cej tym d�u�ej random ma wi�ksze szanse
	}

	namespace Tasks {
		const int		NUMBER				= 100;

		namespace Length {
			const int	MIN					= 25;
			const int	MAX					= 100;
		}
	}
}