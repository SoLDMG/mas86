/*
 *   instr.h - Header file that specifies the decimal-represented instruction values.
 *  Copyright (C) 2014  Thijs van der Woude

 *  This program is free software: you can redistribute it and/or modify
 *  it under the terms of the GNU General Public License as published by
 *  the Free Software Foundation, either version 3 of the License, or
 *  (at your option) any later version.

 *  This program is distributed in the hope that it will be useful,
 *  but WITHOUT ANY WARRANTY; without even the implied warranty of
 *  MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 *  GNU General Public License for more details.

 *  You should have received a copy of the GNU General Public License
 *  along with this program.  If not, see <http://www.gnu.org/licenses/>.
 */

#ifndef INSTR
	#define CPUID1_VAL			15
		#define CPUID2_VAL		162
	#define PUSHA_VAL			96
	#define POPA_VAL			97
	#define NOP_VAL				144
	#define WAIT_VAL			155
	#define LODSB_VAL			172
	#define LODSW_VAL			173
	#define RET_VAL				195
	#define INT3_VAL			204
	#define INT_VAL				205
	#define FNOP1_VAL			217
		#define FNOP2_VAL		208
	#define FDECSTP1_VAL		217
		#define FDECSTP2_VAL	246
	#define FINCSTP1_VAL		217
		#define FINCSTP2_VAL	247
	#define PAUSE1_VAL			243
		#define PAUSE2_VAL		144
	#define PAUSE1_VAL			243
		#define PAUSE2_VAL		144
	#define HLT_VAL				244
	#define CLC_VAL				248
	#define STC_VAL				249
	#define CLI_VAL				250
	#define STI_VAL				251
	#define CLD_VAL				252
	#define STD_VAL				253
#endif
