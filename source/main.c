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

// start of program code
//extern const struct packet_t (*const numbers[])[];
//extern const struct packet_t explosion_shape[];

// Array to store all enemies in game
//struct enemy enemies[8] = {};
// Field to store which enemies are alive, one bit each
//unsigned int enemies_alive = 0x00;

// Live total of the player
//int lifes = 5;

/*void insertNewEnemy(const struct enemy *const en, const unsigned int pos)
{
	assert(pos < 8);
	enemies[pos] = *en;
	enemies_alive |= 1 << pos;
}*/

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

		/*Wait_Recal();
		// ------  PROCESS INPUT AND HANDLE ENTITIES ------
		// Handle player
		player_update(&hero);

		// Handle enemies
		for (unsigned int i = 0; i < 8; i++)
		{
			if (enemies_alive & (1 << i))
				enemy_update(&(enemies[i]));
		}

		if (lifes <= 0)
		{
			assert(0);
		}

		// ------  DRAW ------
		// Draw player
		player_draw(&hero);

		// Draw enemies
		for (unsigned int i = 0; i < 8; i++)
		{
			if (enemies_alive & (1 << i))
				enemy_draw(&(enemies[i]));
		}

		// Draw life total
		Reset0Ref();
		dp_VIA_t1_cnt_lo = 110;
		Moveto_d(100, 100);
		dp_VIA_t1_cnt_lo = 8;
		Intensity_5F();
		Draw_VLp((void *)numbers[lifes - 1]);
		*/
		/*
		Reset0Ref();
		Dot_d(0,0);
		
		Reset0Ref();
		dp_VIA_t1_cnt_lo = 110;
		Dot_d(-120, -120);
		Reset0Ref();
		Dot_d(120, 120);
		Reset0Ref();
		Dot_d(120, -120);
		Reset0Ref();
		Dot_d(-120, 120);*/
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
