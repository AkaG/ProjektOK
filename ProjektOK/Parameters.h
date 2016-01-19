#pragma once

namespace Parameters {
	namespace Feromone_Table {
		const int		INITIAL_VALUE		= 1;
		const float		VAPORING			= 5;
		const float		ADDING_BONUS		= 2;
	}

	namespace Ants {
		const int		NUMBER				= 25;
		const float		TABLE_PROBABILITY	= 1.5; // im wiêcej tym d³u¿ej random ma wiêksze szanse
	}

	namespace Tasks {
		const int		NUMBER				= 5;

		namespace Length {
			const int	MIN					= 50;
			const int	MAX = 150;
		}
	}
	namespace Iterations {
		const int NUMBER = 10;
	}
}