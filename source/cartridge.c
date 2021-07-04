// ***************************************************************************
// vectrex cartridge init block
// ***************************************************************************

#include <vectrex.h>
#include "cartridge.h"

// ---------------------------------------------------------------------------
// game title

const struct cartridge_t game_header __attribute__((section(".cartridge"), used)) = 
{
	.copyright 		= "g GCE 2021\x80",
	.music 			= &Vec_Music_1,
	.title_height 	= -8,
	.title_width 	= 80,
	.title_y 		= 16,
	.title_x 		= -67,
	.title 			= "INSTIGATOR\x80" // note that \x00 is automatically appended!
};

// ***************************************************************************
// end of file
// ***************************************************************************
