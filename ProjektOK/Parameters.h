#pragma once

namespace Parameters {
	namespace Feromone_Table {
		const int		INITIAL_VALUE		= 200;
		const float		VAPORING			= 5;
		const float		ADDING_BONUS		= 200;
	}

	namespace Ants {
		const int		NUMBER				= 25;
		const float		TABLE_PROBABILITY	= 10;// im wi�cej tym d�u�ej random ma wi�ksze szanse
	}

	namespace Tasks {
		const int		NUMBER				= 50;

		namespace Length {
			const int	MIN					= 50;
			const int	MAX					= 250;
		}
	}
	namespace Iterations {
		const int NUMBER = 100;
	}
}