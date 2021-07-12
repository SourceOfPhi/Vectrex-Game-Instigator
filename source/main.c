// ***************************************************************************
// main
// ***************************************************************************

#include <vectrex.h>
#include "utils/vector.h"
#include "player.h"
#include "utils/controller.h"
#include "enemy.h"
#include "print/print.h"
#include "assert/assert.h"
#include "level.h"
#include "random.h"

// ---------------------------------------------------------------------------
// at system startup, a cold reset is performed
// cold reset: the vectrex logo is shown, all ram data is cleared
// if the reset button is pressed, then a warm reset is performed
// warm reset: skip vectrex logo and keep ram data
// after each reset, the game title screen is shown and then main() is called

extern enum levelState current_level_state;
extern struct GameStats stats;
extern unsigned int enemies_alive;
extern unsigned int enemies_left;
extern struct player hero;
extern struct rng_t rng;

int main(void)
{
	// local variables
	unsigned int error_code = 255;

	// seeds were chosen by pure intuition!
	init_rng(&rng, 115, 116, 22);

	// main loop
	do
	{
		level_init();
		level_play();

		if (current_level_state == LEVEL_LOST)
		{
			// Game over
			for (unsigned int delay = 0; delay < 250; delay++)
			{
				Wait_Recal();
				Intensity_5F();
				print_string(60, -100, "GAME OVER\x80");
				print_string(30, -100, "YOUR STATS\x80");
				print_string(0, -100, "LEVEL\x80");
				print_unsigned_int(0, 40, stats.level);
				print_string(-30, -100, "SCORE\x80");
				print_long_unsigned_int(-30, 17, stats.score);
			}

			// Prepare for next run
			stats.lifes = 5;
			stats.level = 0;
			stats.score = 0;
			enemies_alive = 0x00;
			enemies_left = 0;
			hero.pos = (struct vector_t){0, 0};
		}
		if (current_level_state == LEVEL_WON)
		{
			stats.level++;
		}

	} while (error_code);

	// if error_code is <= 0, then a warm reset will be performed,
	// otherwise a cold reset will be performed,
	// after the reset, the game title screen appears,
	// then main() is called
	return (int)error_code;
}

// ***************************************************************************
// end of file
// ***************************************************************************
