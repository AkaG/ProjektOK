#pragma once

namespace Parameters {
	namespace Feromone_Table {
		const int		INITIAL_VALUE		= 1;
		const float		VAPORING			= 5;
		const float		ADDING_BONUS		= 0.5;
	}

	namespace Ants {
		const int		NUMBER				= 25;
		const float		TABLE_PROBABILITY	= 1; // im wiêcej tym d³u¿ej random ma wiêksze szanse
	}

	namespace Tasks {
		const int		NUMBER				= 50;

		namespace Length {
			const int	MIN					= 50;
			const int	MAX					= 500;
		}
	}
	namespace Iterations {
		const int NUMBER = 100;
	}
}