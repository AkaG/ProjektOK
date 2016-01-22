#pragma once

namespace Parameters {
	namespace Feromone_Table {
		const int		INITIAL_VALUE		= 1;
		const float		VAPORING			= 0.5;
		const float		ADDING_BONUS		= 3;
	}

	namespace Ants {
		const int		NUMBER				= 30;
		const float		TABLE_PROBABILITY	= 50; // im wi�cej tym d�u�ej random ma wi�ksze szanse
	}

	namespace Tasks {
		const int		NUMBER				= 50;

		namespace Length {
			const int	MIN					= 50;
			const int	MAX					= 150;
		}
	}
	namespace Iterations {
		const int NUMBER = 100;
	}
}