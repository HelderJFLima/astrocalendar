// Functions used in works with time, calendars and astronomy.
//

#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include "linalg.c"
#include "astrocalendar.h"

#define PI 3.141592653589793
#define X 0												// To use in arrays of coordinates
#define Y 1
#define Z 2
#define ERRMSS01 "NULL date informed!"					// Common error messages
#define ERRMSS02 "NULL deg informed!"
#define ERRMSS03 "inexistent position informed!"
#define ERRMSS04 "NULL coord informed!"
#define ERRMSS05 "invalid hour value informed!"
#define ERRMSS06 "NULL hour informed!"
#define ERRMSS07 "NULL coordinate informed!"
#define ERRMSS08 "NULL array informed!"
#define ERRMSS09 "the length of array is insufficient!"
// Last function number: 73

struct date
{
	int d;

	int m;

	long y;
};

struct degree
{
	int hd;

	int min;

	double sec;
};

struct coord
{
	Hdeg *a;

	Hdeg *b;
};

// In-Out functions:

Date* create_date(void)				// Creates a date variable.
{
	Date *date;

	date = malloc(sizeof(Date));

	if (date == NULL)
	{
		error_message_ac(1, "insufficient memory to allocate the date!");

		exit(1);
	}

	return date;
}

Hdeg* create_deg(void)				// Creates a variable for angle (degree) or time (hour).
{
	Hdeg *deg;

	deg = malloc(sizeof(Hdeg));

	if (deg == NULL)
	{
		error_message_ac(2, "insufficient memory to allocate the deg!");

		exit(2);
	}

	return deg;
}

Coord* create_coord(void)			// Creates a variable for astronomical or geographical coordinates.
{
	Coord* crd;

	crd = malloc(sizeof(Coord));

	if (crd == NULL)
	{
		error_message_ac(3, "insufficient memory to allocate the coordinates!");

		exit(3);
	}

	crd->a = create_deg();

	crd->b = create_deg();

	return crd;
}

void free_date(Date *date)			// Deallocates the memory space used for a date variable.
{
	if (date != NULL)
		free(date);
}

void free_deg(Hdeg *deg)			// Deallocates the memory space used for a variable of angle or time.
{
	if (deg != NULL)
		free(deg);
}

void free_coord(Coord *crd)			// Deallocates the memory space used for a variable of coordinates.
{
	if (crd != NULL)
	{
		free_deg(crd->a);

		free_deg(crd->b);

		free(crd);
	}
}

void type_date(Date *date)			// Gets a date from stdin.
{
	short i = 0;

	if (date == NULL)
	{
		error_message_ac(4, ERRMSS01);

		return;
	}

	printf("\nEnter a date:");

	do
	{
		printf("\n\nday: ");

		scanf(" %d", &date->d);

		printf("\nmonth: ");

		scanf(" %d", &date->m);

		printf("\nyear: ");

		scanf(" %li", &date->y);

		if (is_valid_date(date))
			i++;
		else
		{
			error_message_ac(4, "the date is invalid!");

			printf("\nEnter a valid date:");
		}

	} while (i == 0);
}

void type_deg(Hdeg *deg)			// Gets an angle or time value from stdin.
{
	short i = 0;

	if (deg == NULL)
	{
		error_message_ac(5, ERRMSS02);

		return;
	}

	printf("\nEnter a value of hours or degrees:");

	do
	{
		printf("\n\nhours/degrees: ");

		scanf(" %d", &deg->hd);

		printf("\nminutes: ");

		scanf(" %d", &deg->min);

		printf("\nseconds: ");

		scanf(" %lf", &deg->sec);

		if (is_valid_deg(deg))
			i++;
		else
		{
			error_message_ac(5, "the value informed is invalid!");

			printf("\nEnter a valid value:");
		}

	} while (i == 0);
}

void insert_in_date(long a, Date *dat, int pos)			// Inserts a value of day, month or year into a date.
{
	if (dat == NULL)
	{
		error_message_ac(6, ERRMSS01);

		return;
	}

	switch (pos)
	{
		case 0:
			dat->d = (int) a;
			break;

		case 1:
			dat->m = (int) a;
			break;

		case 2:
			dat->y = a;
			break;

		default:
		{
			error_message_ac(6, ERRMSS03);

			printf("\nThe value of 'pos' must be between '0' and '2'.\n");

			return;
		}
	}
}

long get_from_date(Date *dat, int pos)		// Gets a value of day, month or year from a date.
{
	if (dat == NULL)
	{
		error_message_ac(7, ERRMSS01);

		return 0;
	}

	switch (pos)
	{
		case 0:
			return (long) dat->d;

		case 1:
			return (long) dat->m;

		case 2:
			return dat->y;

		default:
		{
			error_message_ac(7, ERRMSS03);

			printf("\nThe value of 'pos' must be between '0' and '2'.\n");

			return 0;
		}
	}
}

void insert_in_deg(double a, Hdeg *deg, int pos)	// Inserts a value of hour/degree, minutes or seconds into a Hdeg.
{
	if (deg == NULL)
	{
		error_message_ac(8, ERRMSS02);

		return;
	}

	switch (pos)
	{
		case 0:
			deg->hd = (int) a;
			break;

		case 1:
			deg->min = (int) a;
			break;

		case 2:
			deg->sec = a;
			break;

		default:
		{
			error_message_ac(8, ERRMSS03);

			printf("\nThe value of 'pos' must be between '0' and '2'.\n");

			return;
		}
	}
}

double get_from_deg(Hdeg *deg, int pos)			// Gets a value of hour/degree, minutes or seconds from a Hdeg.
{
	if (deg == NULL)
	{
		error_message_ac(9, ERRMSS02);

		return 0;
	}

	switch (pos)
	{
		case 0:
			return (double) deg->hd;

		case 1:
			return (double) deg->min;

		case 2:
			return deg->sec;

		default:
		{
			error_message_ac(9, ERRMSS03);

			printf("\nThe value of 'pos' must be between '0' and '2'.\n");

			return 0;
		}
	}
}

void insert_in_coord(double a, Coord *crd, int pos1, int pos2)	// Inserts a value of hour/degree, minutes or seconds
{																// into a Coord.
	if (crd == NULL)
	{
		error_message_ac(10, ERRMSS04);

		return;
	}

	switch (pos1)
	{
		case 0:
			insert_in_deg(a, crd->a, pos2);
			break;

		case 1:
			insert_in_deg(a, crd->b, pos2);
			break;

		default:
		{
			error_message_ac(10, ERRMSS03);

			printf("\nThe value of 'pos1' must be '0' or '1'.\n");

			return;
		}
	}
}

double get_from_coord(Coord *crd, int pos1, int pos2)	// Gets a value of hour/degree, minutes or seconds from a Coord.
{
	if (crd == NULL)
	{
		error_message_ac(11, ERRMSS04);

		return 0;
	}

	switch (pos1)
	{
		case 0:
			return get_from_deg(crd->a, pos2);

		case 1:
			return get_from_deg(crd->b, pos2);

		default:
		{
			error_message_ac(11, ERRMSS03);

			printf("\nThe value of 'pos1' must be '0' or '1'.\n");

			return 0;
		}
	}
}

void put_deg_into_coord(Hdeg *deg, Coord *crd, int pos)		// Inserts a sexagesimal value into a Coord.
{
	if (deg == NULL)
	{
		error_message_ac(12, ERRMSS02);

		return;
	}
	else if (crd == NULL)
	{
		error_message_ac(12, ERRMSS04);

		return;
	}

	switch (pos)
	{
		case 0:
		{
			over_copy_deg(deg, crd->a);		// Copy of the deg

			if ( !is_valid_deg(crd->a) )
				correct_deg(crd->a);

			break;
		}

		case 1:
		{
			over_copy_deg(deg, crd->b);

			if ( !is_valid_deg(crd->b) )
				correct_deg(crd->b);

			break;
		}
		
		default:
		{
			error_message_ac(12, ERRMSS03);

			printf("\nThe value of 'pos' must be '0' or '1'.\n");

			return;
		}
	}
}

Hdeg* get_deg_from_coord(Coord *crd, int pos)		// Gets a sexagesimal value from a Coord.
{
	Hdeg *deg;

	if (crd == NULL)
	{
		error_message_ac(13, ERRMSS04);

		return NULL;
	}

	switch (pos)
	{
		case 0:
			deg = copy_deg(crd->a);			// Copy of the deg
			break;

		case 1:
			deg = copy_deg(crd->b);
			break;
			
		default:
		{
			error_message_ac(13, ERRMSS03);

			printf("\nThe value of 'pos' must be '0' or '1'.\n");

			return NULL;
		}
	}

	return deg;
}

void over_get_deg_from_coord(Coord *crd, int pos, Hdeg *deg)	// Does the same as 'get_deg_from_coord' but saves the
{																// result in a pre-existing deg.
	if (crd == NULL)
	{
		error_message_ac(14, ERRMSS04);

		return;
	}
	else if (deg == NULL)
	{
		error_message_ac(14, ERRMSS02);

		return;
	}

	switch (pos)
	{
		case 0:
			over_copy_deg(crd->a, deg);			// Copy of the deg
			break;

		case 1:
			over_copy_deg(crd->b, deg);
			break;

		default:
		{
			error_message_ac(14, ERRMSS03);

			printf("\nThe value of 'pos' must be '0' or '1'.\n");

			return;
		}
	}
}

void print_date(Date *date)			// Shows the date in the format 'dd/mm/yyyy'.
{
	if (date == NULL)
	{
		error_message_ac(15, "NULL date informed to print!");

		return;
	}

	printf(" %d/%d/%li ", date->d, date->m, date->y);
}

void print_deg(Hdeg *deg)			// Shows an angle value in sexagesimal format.
{
	if (deg == NULL)
	{
		error_message_ac(16, "NULL deg informed to print!");

		return;
	}

	if (deg->hd == 0)
	{
		if (deg->min == 0)
			printf(" %lf\" ", deg->sec);
		else
			printf(" %d\' %lf\" ", deg->min, deg->sec);
	}
	else
		printf(" %d%c %d\' %lf\" ", deg->hd, 248, deg->min, deg->sec);
}

void print_hour(Hdeg *deg)			// Shows an hour value in sexagesimal format.
{
	if (deg == NULL)
	{
		error_message_ac(17, "NULL hour informed to print!");

		return;
	}
	else if (!is_valid_24hour(deg))
	{
		error_message_ac(17, ERRMSS05);

		return;
	}

	if (deg->hd == 0)
	{
		if (deg->min == 0)
			printf(" %lfs ", deg->sec);
		else
			printf(" %dmin %lfs ", deg->min, deg->sec);
	}
	else
		printf(" %dh %dmin %lfs ", deg->hd, deg->min, deg->sec);
}

void print_complete_deg(Hdeg *deg)		// Shows an angle value in complete sexagesimal format.
{
	if (deg == NULL)
	{
		error_message_ac(18, "NULL deg informed to print!");

		return;
	}

	printf(" %d%c %d\' %lf\" ", deg->hd, 248, deg->min, deg->sec);
}

void print_complete_hour(Hdeg *deg)		// Shows an hour value in complete sexagesimal format.
{
	if (deg == NULL)
	{
		error_message_ac(19, "NULL hour informed to print!");

		return;
	}
	else if (!is_valid_24hour(deg))
	{
		error_message_ac(19, ERRMSS05);

		return;
	}

	printf(" %dh %dmin %lfs ", deg->hd, deg->min, deg->sec);
}

static void error_message_ac(int nmbr, char *mssg)	// Shows an error message indicating the function from where it came.
{
	if (mssg == NULL)
	{
		error_message_ac(0, "NULL string informed!");

		return;
	}
	
	printf("\n\n** Error **\n** [AC%04d]: %s **\n\a", nmbr, mssg);
}

// Copy functions:

Date* copy_date(Date *dat)		// Copies a date as a new one.
{
	Date *cdat;

	if (dat == NULL)
	{
		error_message_ac(20, ERRMSS01);

		return NULL;
	}

	cdat = create_date();

	cdat->d = dat->d;

	cdat->m = dat->m;

	cdat->y = dat->y;

	return cdat;
}

void over_copy_date(Date *cpy, Date *pst)		// Copies a date in a pre-existing one, overwriting it.
{
	if (cpy == NULL || pst == NULL)
	{
		error_message_ac(21, ERRMSS01);

		return;
	}

	pst->d = cpy->d;

	pst->m = cpy->m;

	pst->y = cpy->y;
}

Hdeg* copy_deg(Hdeg *deg)		// Copies a deg as a new one.
{
	Hdeg *cdeg;

	if (deg == NULL)
	{
		error_message_ac(22, ERRMSS02);

		return NULL;
	}

	cdeg = create_deg();

	cdeg->hd = deg->hd;

	cdeg->min = deg->min;

	cdeg->sec = deg->sec;

	return cdeg;
}

void over_copy_deg(Hdeg *cpy, Hdeg *pst)		// Copies a deg in a pre-existing one, overwriting it.
{
	if (cpy == NULL || pst == NULL)
	{
		error_message_ac(23, ERRMSS02);

		return;
	}

	pst->hd = cpy->hd;

	pst->min = cpy->min;

	pst->sec = cpy->sec;
}

Coord* copy_coord(Coord *crd)	// Copies a coord as a new one.
{
	Coord *ccrd;

	if (crd == NULL)
	{
		error_message_ac(24, ERRMSS04);

		return NULL;
	}

	ccrd = create_coord();

	ccrd->a = copy_deg(crd->a);

	ccrd->b = copy_deg(crd->b);

	return ccrd;
}

void over_copy_coord(Coord *cpy, Coord *pst)	// Copies a coord in a pre-existing one, overwriting it.
{
	if (cpy == NULL || pst == NULL)
	{
		error_message_ac(25, ERRMSS04);

		return;
	}

	over_copy_deg(cpy->a, pst->a);

	over_copy_deg(cpy->b, pst->b);
}

// Checking functions:

int is_leap_year(long year)			// Determines if the year is a leap year or not.
{
	if (year % 4 == 0)
	{
		if (year % 100 == 0)
		{
			if (year % 400 == 0)
			{
				return 1;
			}
			else
				return 0;
		}
		else
			return 1;
	}
	else
		return 0;
}

int is_valid_date(Date *date)		// Tests if the date is a valid date.
{
	if (date == NULL)
	{
		error_message_ac(26, ERRMSS01);

		return 0;
	}

	if (date->m > 12 || date->m <= 0)	// Inexistent month
		return 0;
	else
	{
		if (date->m % 2 != 0)			// Odd month
		{
			if (date->m <= 7)				// From January to July
			{
				if (date->d > 31 || date->d <= 0)
					return 0;
				else
					return 1;
			}
			else							// September or November
			{
				if (date->d > 30 || date->d <= 0)
					return 0;
				else
					return 1;
			}
		}
		else							// Even month
		{
			if (date->m > 6)				// From August to December
			{
				if (date->d > 31 || date->d <= 0)
					return 0;
				else
					return 1;
			}
			else
			{
				if (date->m != 2)			// April or June
				{
					if (date->d > 30 || date->d <= 0)
						return 0;
					else
						return 1;
				}
				else						// February
				{
					if (is_leap_year(date->y))  // Leap year
					{
						if (date->d > 29 || date->d <= 0)
							return 0;
						else
							return 1;
					}
					else						// Common year
					{
						if (date->d > 28 || date->d <= 0)
							return 0;
						else
							return 1;
					}
				}
			}
		}
	}
}

int is_valid_deg(Hdeg *deg)			// Tests if the value is corret in the sexagesimal format.
{
	if (deg == NULL)
	{
		error_message_ac(27, ERRMSS02);

		return 0;
	}

	if (deg->hd != 0)
	{
		if (deg->min < 0 || deg->min >= 60)
			return 0;

		else if (deg->sec < 0 || deg->sec >= 60)
			return 0;
		else
			return 1;
	}
	else								// The signal must be on the first non-null part of the number.
	{
		if (deg->min <= -60 || deg->min >= 60)
			return 0;

		if (deg->min != 0)
		{
			if (deg->sec < 0 || deg->sec >= 60)
				return 0;
			else
				return 1;
		}
		else
		{
			if (deg->sec <= -60 || deg->sec >= 60)
				return 0;
			else
				return 1;
		}
	}
}

int is_valid_12hour(Hdeg *hour)		// Tests if the time is corret in the 12-hour format.
{
	if (hour == NULL)
	{
		error_message_ac(28, ERRMSS06);

		return 0;
	}

	if ( is_valid_deg(hour) )
	{
		if (hour->hd <= 0 || hour->hd > 12)
			return 0;

		else if (hour->min < 0 || hour->sec < 0)
			return 0;

		else
			return 1;
	}
	else
		return 0;
}

int is_valid_24hour(Hdeg *hour)		// Tests if the time is corret in the 24-hour format.
{
	if (hour == NULL)
	{
		error_message_ac(29, ERRMSS06);

		return 0;
	}

	if ( is_valid_deg(hour) )
	{
		if (hour->hd < 0 || hour->hd >= 24)
			return 0;

		else if (hour->min < 0 || hour->sec < 0)
			return 0;

		else
			return 1;
	}
	else
		return 0;
}

int is_valid_right_ascension(Hdeg *ra)		// Tests if the coordinate is corret in the right ascension format.
{
	if (ra == NULL)
	{
		error_message_ac(30, ERRMSS07);

		return 0;
	}

	return is_valid_24hour(ra);
}

int is_valid_declination(Hdeg *dec)		// Tests if the coordinate is corret in the declination format.
{
	if (dec == NULL)
	{
		error_message_ac(31, ERRMSS07);

		return 0;
	}

	if ( is_valid_deg(dec) )
	{
		if (dec->hd < -90 || dec->hd > 90)
			return 0;

		else if (dec->hd == -90 || dec->hd == 90)
		{
			if (dec->min > 0 || dec->sec > 0)
				return 0;
			else
				return 1;
		}
		else
			return 1;
	}
	else
		return 0;
}

int is_valid_hour_angle(Hdeg *ha)		// Tests if the coordinate is corret in the hour angle format.
{
	if (ha == NULL)
	{
		error_message_ac(32, ERRMSS07);

		return 0;
	}

	if ( is_valid_deg(ha) )
	{
		if (ha->hd <= -12 || ha->hd > 12)	// Hour angle range defined excluding the value -12 but including +12.
			return 0;

		else if (ha->hd == 12)
		{
			if (ha->min > 0 || ha->sec > 0)
				return 0;
			else
				return 1;
		}
		else
			return 1;
	}
	else
		return 0;
}

int is_valid_azimuth(Hdeg *azm)			// Tests if the coordinate is corret in the azimuth format.
{
	if (azm == NULL)
	{
		error_message_ac(33, ERRMSS07);

		return 0;
	}

	if ( is_valid_deg(azm) )
	{
		if (azm->hd < 0 || azm->hd >= 360)
			return 0;

		else if (azm->min < 0 || azm->sec < 0)
			return 0;

		else
			return 1;
	}
	else
		return 0;
}

int is_valid_altitude(Hdeg *alt)		// Tests if the coordinate is corret in the altitude format.
{
	if (alt == NULL)
	{
		error_message_ac(34, ERRMSS07);

		return 0;
	}

	return is_valid_declination(alt);		// The range is the same of the declination format.
}

int month_has_31days(int mnth)		// Tests if the month has 31 days or not.
{
	if (mnth < 1 || mnth > 12)
	{
		error_message_ac(35, "invalid month informed!");

		return -1;
	}

	if (mnth <= 7)						// Until July
	{
		if (mnth % 2 != 0)
			return 1;
		else
			return 0;
	}
	else								// After July
	{
		if (mnth % 2 == 0)
			return 1;
		else
			return 0;
	}
}

// Conversion functions:

double decimal_deg(Hdeg *deg)		// Converts sexagesimal format to decimal.
{
	double dec;

	if (deg == NULL)
	{
		error_message_ac(36, ERRMSS02);

		return 0;
	}

	dec = (double) abs(deg->hd) + abs(deg->min) / 60.0 + fabs(deg->sec) / 3600.0;	// Turns to decimal.

	if (deg->hd < 0 || deg->min < 0 || deg->sec < 0)		// Corrects the signal.
		dec = - dec;

	return dec;
}

Hdeg* sexagesimal_deg(double decd)		// Converts decimal format to sexagesimal.
{
	double frac, tmp1, tmp2;

	Hdeg *sexd;

	sexd = create_deg();

	frac = fabs( modf(decd, &tmp1) );		// Breaks into fractional and integral parts.

	sexd->hd = (int) tmp1;					// Gets the integral part.

	tmp1 = 60 * frac;						// Turns the fractional part into minutes.

	frac = modf(tmp1, &tmp2);				// Repeats the process with minutes and seconds.

	sexd->min = (int) tmp2;

	sexd->sec = 60 * frac;

	if (decd < 0 && sexd->hd == 0)			// Corrects the signal.
	{
		if (sexd->min != 0)
			sexd->min = - sexd->min;
		else
			sexd->sec = - sexd->sec;
	}

	if ( !is_valid_deg(sexd) )				// Corrects the format if necessary.
		correct_deg(sexd);

	return sexd;
}

void over_sexagesimal_deg(double decd, Hdeg *sexd)		// Converts decimal format to sexagesimal and saves
{														// the result in a pre-existing Hdeg.
	double frac, tmp1, tmp2;

	if (sexd == NULL)
	{
		error_message_ac(37, ERRMSS02);

		return;
	}

	frac = fabs( modf(decd, &tmp1) );	// Breaks into fractional and integral parts.

	sexd->hd = (int) tmp1;				// Gets the integral part.

	tmp1 = 60 * frac;					// Turns the fractional part into minutes.

	frac = modf(tmp1, &tmp2);			// Repeats the process with minutes and seconds.

	sexd->min = (int) tmp2;

	sexd->sec = 60 * frac;

	if (decd < 0 && sexd->hd == 0)		// Corrects the signal.
	{
		if (sexd->min != 0)
			sexd->min = -sexd->min;
		else
			sexd->sec = -sexd->sec;
	}

	if ( !is_valid_deg(sexd) )			// Corrects the format if necessary.
		correct_deg(sexd);
}

double hour_to_decdeg(Hdeg *hour)		// Converts a time format coordinate into decimal degree coordinate.
{
	double decd;

	if (hour == NULL)
	{
		error_message_ac(38, ERRMSS06);

		return 0;
	}

	decd = decimal_deg(hour);				// Converts into decimal format.

	decd *= 360 / 24;						// Converts into degrees.

	return decd;
}

Hdeg* decdeg_to_hour(double decd)		// Converts a decimal degree coordinate into time format coordinate.
{
	double tmp;

	Hdeg *hour;

	tmp = decd * 24 / 360;					// Converts into hours.

	hour = sexagesimal_deg(tmp);			// Converts into sexagesimal format.

	return hour;
}

void over_decdeg_to_hour(double decd, Hdeg *hour)		// Does the same as 'decdeg_to_hour' but saves the result
{														// in a pre-existing Hdeg.
	double tmp;

	if (hour == NULL)
	{
		error_message_ac(39, ERRMSS06);

		return;
	}

	tmp = decd * 24 / 360;					// Converts into hours.

	over_sexagesimal_deg(tmp, hour);		// Converts into sexagesimal format.
}

Hdeg* hour_to_sexdeg(Hdeg *hour)		// Converts a time format coordinate into sexagesimal degree coordinate.
{
	double tmp;

	Hdeg *sexd;

	if (hour == NULL)
	{
		error_message_ac(40, ERRMSS06);

		return NULL;
	}

	tmp = hour_to_decdeg(hour);				// Converts into decimal degree format.

	sexd = sexagesimal_deg(tmp);			// Converts into sexagesimal format.

	return sexd;
}

void over_hour_to_sexdeg(Hdeg *hour, Hdeg *sexd)	// Does the same as 'hour_to_sexdeg' but saves the result
{													// in a pre-existing Hdeg.
	double tmp;

	if (hour == NULL || sexd == NULL)
	{
		error_message_ac(41, ERRMSS02);

		return;
	}

	tmp = hour_to_decdeg(hour);				// Converts into decimal degree format.

	over_sexagesimal_deg(tmp, sexd);		// Converts into sexagesimal format.
}

Hdeg* sexdeg_to_hour(Hdeg *sexd)		// Converts a sexagesimal degree coordinate into time format coordinate.
{
	double tmp;
	
	Hdeg* hour;

	if (sexd == NULL)
	{
		error_message_ac(42, ERRMSS07);

		return NULL;
	}

	tmp = decimal_deg(sexd);				// Converts into decimal degree format.

	hour = decdeg_to_hour(tmp);				// Converts into time format.

	return hour;
}

void over_sexdeg_to_hour(Hdeg *sexd, Hdeg *hour)	// Does the same as 'sexdeg_to_hour' but saves the result
{													// in a pre-existing Hdeg.
	double tmp;

	if (sexd == NULL || hour == NULL)
	{
		error_message_ac(43, ERRMSS02);

		return;
	}

	tmp = decimal_deg(sexd);				// Converts into decimal degree format.

	over_decdeg_to_hour(tmp, hour);			// Converts into time format.
}

double decdeg_to_radian(double deg)		// Converts an angle in degrees (decimal) into radians.
{
	double rad;

	rad = deg * PI / 180;

	return rad;
}

double sexdeg_to_radian(Hdeg *deg)	// Converts an angle in degrees (sexagesimal) into radians.
{
	double rad, tmp;

	if (deg == NULL)
	{
		error_message_ac(44, ERRMSS02);

		return 0;
	}

	tmp = decimal_deg(deg);				// Converts into decimal angle.

	rad = decdeg_to_radian(tmp);		// Converts into radians.

	return rad;
}

double radian_to_decdeg(double rad)	// Converts an angle in radians into degrees (decimal).
{
	double deg;

	deg = 180 * rad / PI;

	return deg;
}

Hdeg* radian_to_sexdeg(double rad)		// Converts an angle in radians into degrees (sexagesimal).
{
	double deg;

	Hdeg *sexd;

	deg = radian_to_decdeg(rad);			// Converts into degrees.

	sexd = sexagesimal_deg(deg);			// Turns to sexagesimal format.

	return sexd;
}

Array* coord_to_decdeg_array(Coord *crd)	// Converts a Coord structure of sexagesimal degs into an array of decimal degs.
{
	Array *adeg;

	if (crd == NULL)
	{
		error_message_ac(45, ERRMSS04);

		return NULL;
	}

	adeg = create_array(2);						// Creates an array of two elements.

	insert_in_array( decimal_deg(crd->a), adeg, X );	// Conversion and insertion

	insert_in_array( decimal_deg(crd->b), adeg, Y );

	return adeg;
}

void over_coord_to_decdeg_array(Coord *crd, Array *arr)	// Does the same as 'coord_to_decdeg_array' but saves the result
{														// in a pre-existing array.
	if (crd == NULL)
	{
		error_message_ac(46, ERRMSS04);

		return;
	}
	else if (arr == NULL)
	{
		error_message_ac(46, ERRMSS08);

		return;
	}
	else if ( length_of_array(arr) < 2 )
	{
		error_message_ac(46, ERRMSS09);

		return;
	}

	insert_in_array( decimal_deg(crd->a), arr, X );		// Conversion and insertion

	insert_in_array( decimal_deg(crd->b), arr, Y );
}

Coord* decdeg_array_to_coord(Array *arr)	// Converts an array of decimal degs into a Coord structure of sexagesimal degs.
{
	Coord *crd;

	if (arr == NULL)
	{
		error_message_ac(47, ERRMSS08);

		return NULL;
	}
	else if ( length_of_array(arr) < 2 )
	{
		error_message_ac(47, ERRMSS09);

		return NULL;
	}

	crd = create_coord();

	crd->a = sexagesimal_deg( get_from_array(arr, X) );		// Conversion and insertion

	crd->b = sexagesimal_deg( get_from_array(arr, Y) );

	return crd;
}

void over_decdeg_array_to_coord(Array *arr, Coord *crd) // Does the same as 'decdeg_array_to_coord' but saves the result
{														// in a pre-existing Coord.

	if (arr == NULL)
	{
		error_message_ac(48, ERRMSS08);

		return;
	}
	else if (crd == NULL)
	{
		error_message_ac(48, ERRMSS04);

		return;
	}
	else if ( length_of_array(arr) < 2 )
	{
		error_message_ac(48, ERRMSS09);

		return;
	}

	over_sexagesimal_deg( get_from_array(arr, X), crd->a );		// Conversion and insertion

	over_sexagesimal_deg( get_from_array(arr, Y), crd->b );
}

Array* eq_coord_to_decdeg_array(Coord *crd)		// Converts a Coord structure of sexagesimal equatorial coordinates into
{												// an array of decimal degs.
	Array *darr;

	if (crd == NULL)
	{
		error_message_ac(67, ERRMSS04);

		return NULL;
	}

	darr = create_array(2);

	insert_in_array( hour_to_decdeg(crd->a), darr, X );		// Conversion and insertion

	insert_in_array( decimal_deg(crd->b), darr, Y );

	return darr;
}

void over_eq_coord_to_decdeg_array(Coord *crd, Array *darr)		// Does the same as 'eq_coord_to_decdeg_array' but
{																// saves the result in a pre-existing Array.
	if (crd == NULL)
	{
		error_message_ac(68, ERRMSS04);

		return;
	}
	else if (darr == NULL)
	{
		error_message_ac(68, ERRMSS08);

		return;
	}
	else if ( length_of_array(darr) < 2 )
	{
		error_message_ac(68, ERRMSS09);

		return;
	}

	insert_in_array( hour_to_decdeg(crd->a), darr, X );		// Conversion and insertion

	insert_in_array( decimal_deg(crd->b), darr, Y );
}

Coord* decdeg_arr_to_eq_coord(Array *darr)		// Converts an array of decimal degs into a Coord structure of sexagesimal
{												// equatorial coordinates.
	Coord *crd;

	if (darr == NULL)
	{
		error_message_ac(69, ERRMSS08);

		return NULL;
	}
	else if ( length_of_array(darr) < 2 )
	{
		error_message_ac(69, ERRMSS09);

		return NULL;
	}

	crd = create_coord();

	crd->a = decdeg_to_hour( get_from_array(darr, X) );			// Conversion and insertion

	crd->b = sexagesimal_deg( get_from_array(darr, Y) );

	return crd;
}

void over_decdeg_arr_to_eq_coord(Array *darr, Coord *crd)		// Does the same as 'decdeg_arr_to_eq_coord' but saves
{																// the result in a pre-existing Coord.
	if (darr == NULL)
	{
		error_message_ac(70, ERRMSS08);

		return;
	}
	else if (crd == NULL)
	{
		error_message_ac(70, ERRMSS04);

		return;
	}
	else if ( length_of_array(darr) < 2 )
	{
		error_message_ac(70, ERRMSS09);

		return;
	}

	crd->a = decdeg_to_hour( get_from_array(darr, X) );			// Conversion and insertion

	crd->b = sexagesimal_deg( get_from_array(darr, Y) );
}

Array* decdeg_arr_to_rad_arr(Array *arr)		// Converts an array of decimal degs into an array of radians.
{
	Array *rarr;
	
	if (arr == NULL)
	{
		error_message_ac(49, ERRMSS08);

		return NULL;
	}
	else if ( length_of_array(arr) < 2 )
	{
		error_message_ac(49, ERRMSS09);

		return NULL;
	}

	rarr = create_array(2);

	insert_in_array( decdeg_to_radian( get_from_array(arr, X) ), rarr, X );		// Conversion and insertion

	insert_in_array( decdeg_to_radian( get_from_array(arr, Y) ), rarr, Y );

	return rarr;
}

void over_decdeg_arr_to_rad_arr(Array *darr, Array *rarr)	// Does the same as 'decdeg_arr_to_rad_arr' but saves the
{															// result in a pre-existing array.
	if (darr == NULL || rarr == NULL)
	{
		error_message_ac(50, ERRMSS08);

		return;
	}
	else if ( length_of_array(darr) < 2 || length_of_array(rarr) < 2 )
	{
		error_message_ac(50, ERRMSS09);

		return;
	}

	insert_in_array( decdeg_to_radian( get_from_array(darr, X) ), rarr, X );	// Conversion and insertion

	insert_in_array( decdeg_to_radian( get_from_array(darr, Y) ), rarr, Y );
}

Array* rad_arr_to_decdeg_arr(Array *arr)		// Converts an array of radians into an array of decimal degs.
{
	Array *darr;

	if (arr == NULL)
	{
		error_message_ac(51, ERRMSS08);

		return NULL;
	}
	else if ( length_of_array(arr) < 2 )
	{
		error_message_ac(51, ERRMSS09);

		return NULL;
	}

	darr = create_array(2);

	insert_in_array( radian_to_decdeg( get_from_array(arr, X) ), darr, X );		// Conversion and insertion

	insert_in_array( radian_to_decdeg( get_from_array(arr, Y) ), darr, Y );

	return darr;
}

void over_rad_arr_to_decdeg_arr(Array *rarr, Array *darr)	// Does the same as 'rad_arr_to_decdeg_arr' but saves the
{															// result in a pre-existing array.
	if (rarr == NULL || darr == NULL)
	{
		error_message_ac(52, ERRMSS08);

		return;
	}
	else if ( length_of_array(rarr) < 2 || length_of_array(darr) < 2 )
	{
		error_message_ac(52, ERRMSS09);

		return;
	}

	insert_in_array( radian_to_decdeg( get_from_array(rarr, X) ), darr, X );	// Conversion and insertion

	insert_in_array( radian_to_decdeg( get_from_array(rarr, Y) ), darr, Y );
}

// Arithmetic functions:

void correct_deg(Hdeg *deg)		// Corrects a sexagesimal value with minutes or seconds greater than 60.
{
	int incr, sgn = 0;

	if (deg == NULL)
	{
		error_message_ac(53, ERRMSS02);

		return;
	}

	if (deg->hd < 0)									// Checks the signals of the numbers.
		sgn++;
	
	if (deg->min < 0)
		sgn++;

	if (deg->sec < 0)
		sgn++;

	if (sgn > 1)
	{
		error_message_ac(53, "too many negative values in the deg informed!");

		return;
	}

	if ( fabs(deg->sec) >= 60 )							// Corrects the seconds.
	{
		if (deg->sec < 0)
		{
			incr = (int) floor( fabs(deg->sec) / 60.0 );

			deg->min -= incr;

			deg->sec = fabs(deg->sec) - 60.0 * incr;
		}
		else if (deg->min < 0)
		{
			incr = (int) floor( deg->sec / 60.0 );

			deg->min -= incr;

			deg->sec -= 60.0 * incr;
		}
		else
		{
			incr = (int) floor( deg->sec / 60.0 );

			deg->min += incr;

			deg->sec -= 60.0 * incr;
		}
	}

	if ( abs(deg->min) >= 60 )							// Corrects the minutes.
	{
		if (deg->min < 0)
		{
			incr = abs(deg->min) / 60.0;

			deg->hd -= incr;

			deg->min = abs(deg->min) - 60.0 * incr;
		}
		else if (deg->hd < 0)
		{
			incr = deg->min / 60.0;

			deg->hd -= incr;

			deg->min -= 60.0 * incr;
		}
		else
		{
			incr = deg->min / 60;

			deg->hd += incr;

			deg->min -= 60 * incr;
		}
	}
}

// Calendar functions:

int day_number(Date *date)				// Gives the day number of a given date.
{
	int n;

	if (date == NULL)
	{
		error_message_ac(54, ERRMSS01);

		return 0;
	}

	n = 30 * (date->m - 1) + date->d;			// Assumes that every month has 30 days.

	if (date->m == 3)							// Corrects the difference of days accumulated along the year.
		n--;

	else if (date->m == 2 || date->m == 6 || date->m == 7)
		n++;

	else if (date->m == 8)
		n += 2;

	else if (date->m == 9 || date->m == 10)
		n += 3;

	else if (date->m == 11 || date->m == 12)
		n += 4;

	if ( date->m > 2 && is_leap_year(date->y) )	// Corrects the difference of the leap year day.
		n++;

	return n;
}

int cycle28_day_of_week(int num, int epch)		// Gives the first day of week of a year in a 28-year solar cycle.
{													// The 'epoch' is the first day of week of the first year of the cycle.
	int day, p;

	if (num < 0 || num > 27)				// The year considered is a number between 0 and 27.
	{
		error_message_ac(55, "inexistent 28-cycle number informed!");

		return -1;
	}

	if (num % 4 == 0)						// Leap year inside the cycle.
		day = ( 5 * (num / 4) + epch ) % 7;
	else
	{
		p = ( 5 * (num / 4) + epch ) % 7;

		day = (p + num % 4 + 1) % 7;		// Considers the last leap year and adds the years' changes after it.
	}

	return day;
}

int gregorian_cycle28_epoch(int year)	// Gives the first day of week of the 28-year cycle that
{										// begins after a year multiple of 100 in Gregorian Calendar.
	int e, ep, epch;

	if (year % 100 != 0)
	{
		error_message_ac(56, "year not multiple of 100 informed!");

		return -1;
	}

	if (year % 400 != 0)
	{
		e = ( 60 * (year / 400) + 6 ) % 7;			// Finds the first day of week (FDW) of the last year multiple of 400. 

		ep = ( year - 400 * (year / 400) ) / 100;	// Calculates how many hundreds have passed since then.

		epch = (20 * ep + e) % 7;					// Corrects the FDW of the actual year.
	}
	else
		epch = ( 60 * (year / 400) + 6 ) % 7;

	return epch;
}

int gregorian_first_day_of_year(int year)	// Gives the first day of week of a year in Gregorian Calendar.
{
	int day, epch, hndr, num;

	hndr = year - year % 100;					// The hundreds of the year

	if ( hndr / 28 == year / 28  &&  hndr % 400 != 0  &&  year % 100 != 0 )	// Years that are affected by changes caused by
	{																		// the years multiple of 100.
		if (year - hndr <= 4)						// Years immediately after one multiple of 100
		{
			epch = gregorian_cycle28_epoch(hndr - 100);		// Finds the first day of week (FDW) of the last year multiple of 100.

			num = hndr % 28;

			day = ( cycle28_day_of_week(num, epch) + (year - hndr) ) % 7;	// Corrects the FDW of the actual year.
		}
		else
		{
			epch = gregorian_cycle28_epoch(hndr - 100);

			num = hndr % 28;

			epch = ( cycle28_day_of_week(num, epch) + 4 ) % 7;	// Assumes a 28-year cycle beginning in the year multiple of 100.

			num = year - hndr - 4;

			day = cycle28_day_of_week(num, epch);				// Determines the FDW of the given year.
		}
	}
	else if (year % 100 == 0 && year % 400 != 0)	// Years multiple of 100 but not of 400
	{
		num = year % 28;								// Determines the position of the year in a 28-years cycle.

		epch = gregorian_cycle28_epoch(hndr - 100);

		day = cycle28_day_of_week(num, epch);
	}
	else											// Any year that is not multiple of 100 but could be multiple of 400
	{
		num = year % 28;								// Determines the position of the year in a 28-years cycle.

		epch = gregorian_cycle28_epoch(hndr);			// Calculates the FDW of the 28-year cycle that begins after the last year multiple of 100.

		day = cycle28_day_of_week(num, epch);			// Determines the FDW of the given year.
	}

	return day;
}

int gregorian_day_of_week(Date *date)	// Gives the day of week of a given date in Gregorian Calendar.
{
	int day;

	if (date == NULL)
	{
		error_message_ac(57, ERRMSS01);

		return -1;
	}
	else if (date->y < 1582)				// Ignores the dates before the first official day of the Gregorian Calendar.
	{
		error_message_ac(57, "the Gregorian Calendar has begun on 15/10/1582.");

		return -1;
	}
	else if (date->y == 1582)
	{
		if (date->m < 10)
		{
			error_message_ac(57, "the Gregorian Calendar has begun on 15/10/1582.");

			return -1;
		}
		else if (date->m == 10 && date->d < 15)
		{
			error_message_ac(57, "the Gregorian Calendar has begun on 15/10/1582.");

			return -1;
		}
	}

	day = gregorian_first_day_of_year(date->y);	// Determines the first day of week of the year.

	day += day_number(date) - 1;				// Adds the number of days passed since the first one.

	day = day % 7;								// Converts into day of week.

	return day;
}

Date* catholic_easter_date(int year)	// Calculates the Catholic Easter date for a given year.
{
	int a, b, c, d;

	Date *date;

	if (year <= 0)
	{
		error_message_ac(58, "year less than 1 informed!");

		return NULL;
	}

	date = create_date();

	date->y = year;

	a = year / 100;							// Calculates the Easter Date (integer divisions).
												// Algorithm by J. -M. Oudin (1940),
	b = year - 19 * (year / 19);				// apud S. O. Kepler; M. F. O. Saraiva (2004).

	c = (a - 17) / 25;

	d = a - a / 4 - (a - c) / 3 + 19 * b + 15;

	d = d - 30 * (d / 30);

	d = d - (d / 28) * ( 1 - (d / 28) * ( 29 / (d + 1) ) * ( (21 - b) / 11 ) );

	b = year + year / 4 + d + 2 - a + a / 4;

	b = b - 7 * (b / 7);

	c = d - b;

	date->m = 3 + (c + 40) / 44;

	date->d = c + 28 - 31 * (date->m / 4);

	return date;
}

double julian_date(Hdeg *utc, Date *date)	// Gives the Julian Date.
{
	int tmp1;
	double jd, tmp2;

	if (utc == NULL)
	{
		error_message_ac(59, "NULL utc informed!");

		return 0;
	}
	else if (date == NULL)
	{
		error_message_ac(59, ERRMSS01);

		return 0;
	}
	else if ( !is_valid_24hour(utc) )
	{
		error_message_ac(59, ERRMSS05);

		return 0;
	}

	tmp1 = - ( 7 * ( date->y + (date->m + 9) / 12 ) ) / 4;			// Calculates the Julian Date at Greenwich's noon.
																		// Algorithm by Fliegel and Van Flandern (1968),
	tmp1 -= ( 3 * ( ( date->y + (date->m - 9) / 7 ) / 100 + 1 ) ) / 4;	// apud H. Karttunen et al. (2017).

	tmp1 += 275 * date->m / 9;

	jd = 367 * (double) date->y + (double) tmp1 + date->d + 1721029;

	tmp2 = (double) utc->hd / 24 + (double) utc->min / 1440 + utc->sec / 86400;	// Calculates the fractional part of day.

	if (utc->hd > 12)											// Adds the fractional part.
		jd += tmp2 - 0.5;

	else if (utc->hd < 12)
		jd -= 0.5 - tmp2;
	else
	{
		if (utc->min > 0)
			jd += tmp2 - 0.5;
		else
		{
			if (utc->sec > 0)
			{
				jd += tmp2 - 0.5;
			}
		}
	}

	if (date->y < 0)											// Corrections for negative years
	{
		if (date->y % 4 == 0 && date->m >= 3 || date->y % 4 == -1 && date->m <= 2)
			jd += 1.0;

		else if (date->y % 4 != 0 && date->y % 4 != -1)
			jd += 1.0;

		if (date->y == -100 && date->m <= 2)
			jd += 1.0;

		else if (date->y < -100)
		{
			if (date->y == -199 && date->m <= 2 || date->y < -199)
				jd += 1.0;

			if (date->y % 100 == 0 && date->m <= 2)
				jd += 1.0;

			else if (date->y % 100 < 0 && date->y % 100 > -99)
				jd += 1.0;

			else if (date->y % 100 == -99 && date->m >= 3)
				jd += 1.0;

			if (date->y <= -400)
			{
				if (date->y % 400 == 0 && date->m <= 2)
					jd -= 1.0;

				else if (date->y % 400 < 0 && date->y % 400 > -199)
					jd -= 1.0;

				else if (date->y % 400 == -199 && date->m >= 3)
					jd -= 1.0;
			}
		}
	}

	return jd;
}

void jd_to_date(double jd, Date *date, Hdeg *hour)	// Converts Julian Date into normal date and time format.
{
	int a, b, c, d;
	double frac, tmp1, tmp2;

	if (jd <= 0)
	{
		error_message_ac(60, "invalid Julian Date informed!");

		return;
	}
	else if (date == NULL)
	{
		error_message_ac(60, ERRMSS01);

		return;
	}
	else if (hour == NULL)
	{
		error_message_ac(60, ERRMSS06);

		return;
	}

	frac = modf(jd, &tmp1);				// Breaks into fractional and integral parts.

	a = (int) tmp1 + 68569;				// Calculates the date.
											// Algorithm found in H. Karttunen et al. (2017).
	b = (4 * a) / 146097;

	c = a - (146097 * b + 3) / 4;

	a = ( 4000 * (c + 1) ) / 1461001;

	d = c - (1461 * a) / 4 + 31;

	c = (80 * d) / 2447;

	date->d = d - (2447 * c) / 80;			// Day

	d = c / 11;

	date->m = c + 2 - 12 * d;				// Month

	date->y = 100 * (b - 49) + a + d;		// Year

										// Calculates the time.

	if (frac >= 0.5)						// If it's midnight or after.
	{
		if ( month_has_31days(date->m) )		// Corrections of the date if it's the last day of month or not.
		{
			if (date->d == 31)
			{
				if (date->m != 12)
				{
					date->d = 1;

					date->m++;
				}
				else
				{
					date->d = 1;

					date->m = 1;

					date->y++;
				}
			}
			else
				date->d++;
		}
		else
		{
			if ( date->d == 30 || (date->m == 2 && date->d == 29) )
			{
				date->d = 1;

				date->m++;
			}
			else if (date->d == 28 && date->m == 2)
			{
				if ( is_leap_year(date->y) )
					date->d++;
				else
				{
					date->d = 1;

					date->m++;
				}
			}
			else
				date->d++;
		}

		frac = (frac - 0.5) * 24;				// Hour

		tmp1 = modf(frac, &tmp2);

		hour->hd = (int) tmp2;

		frac = tmp1;
	}
	else									// If it's before midnight.
	{
		frac *= 24;								// Hour

		tmp1 = modf(frac, &tmp2);

		hour->hd = (int) tmp2 + 12;

		frac = tmp1;
	}

	frac *= 60;								// Minutes

	tmp1 = modf(frac, &tmp2);

	hour->min = (int) tmp2;

	hour->sec = 60 * tmp1;					// Seconds
}

// Astronomy functions:

Array* position_vector(Array *darr)		// Determines a unit vector pointing in the direction of the coordinates.
{										// (Coordinates of decimal degrees)
	double si[2], co[2];

	Array *arr;

	if (darr == NULL)
	{
		error_message_ac(61, ERRMSS08);

		return NULL;
	}
	else if ( length_of_array(darr) < 2 )
	{
		error_message_ac(61, ERRMSS09);

		return NULL;
	}

	arr = decdeg_arr_to_rad_arr(darr);			// Converts degree coordinates into radians coordinates.

	si[X] = sin( get_from_array(arr, X) );		// Calculates the sine and cosine of the coordinates.

	si[Y] = sin( get_from_array(arr, Y) );

	co[X] = cos( get_from_array(arr, X) );

	co[Y] = cos( get_from_array(arr, Y) );

	free_array(arr);							// Erases the memory space and

	arr = create_array(3);						// creates an array for the position coordinates.

	insert_in_array( co[X] * co[Y], arr, X );	// Calculates the unit position vector.

	insert_in_array( si[X] * co[Y], arr, Y );

	insert_in_array( si[Y], arr, Z );

	return arr;
}

void over_position_vector(Array *darr, Array *pos)		// Does the same as 'position_vector' but saves the result
{														// in a pre-existing Array.
	double si[2], co[2];

	Array* rad;

	if (darr == NULL || pos == NULL)
	{
		error_message_ac(62, ERRMSS08);

		return;
	}
	else if ( length_of_array(darr) < 2 || length_of_array(pos) < 3 )
	{
		error_message_ac(62, ERRMSS09);

		return;
	}

	rad = decdeg_arr_to_rad_arr(darr);			// Converts degree coordinates into radians coordinates.

	si[X] = sin( get_from_array(rad, X) );		// Calculates the sine and cosine of the coordinates.

	si[Y] = sin( get_from_array(rad, Y) );

	co[X] = cos( get_from_array(rad, X) );

	co[Y] = cos( get_from_array(rad, Y) );

	free_array(rad);

	insert_in_array( co[X] * co[Y], pos, X );	// Calculates the unit position vector.

	insert_in_array( si[X] * co[Y], pos, Y );

	insert_in_array( si[Y], pos, Z );
}

Array* pos_vector_to_decdeg_arr(Array *pos)	// Determines the degree coordinates corresponding to a unit position vector.
{
	double nrm, px, py, pz, tmp;

	Array *arr;

	if (pos == NULL)
	{
		error_message_ac(63, ERRMSS08);

		return NULL;
	}
	else if ( length_of_array(pos) < 3 )
	{
		error_message_ac(63, ERRMSS09);

		return NULL;
	}

	nrm = euclidean_norm(pos);					// Calculates the euclidean norm of the vector.

	if (nrm == 0)
	{
		error_message_ac(63, "null vector!");

		return NULL;
	}

	arr = create_array(2);

	px = get_from_array(pos, X);

	py = get_from_array(pos, Y);

	pz = get_from_array(pos, Z);

	if (px != 0)								// Calculates the first coordinate (Right Ascension or Azimuth).
	{
		if (py != 0)
		{
			tmp = atan(py / px);

			if ( px < 0 && py > 0 || px < 0 && py < 0 )		// Corrects the quadrant.
				tmp += PI;

			else if ( px > 0 && py < 0 )
				tmp += 2 * PI;
		}
		else if (px > 0)
			tmp = 0;

		else if (px < 0)
			tmp = PI;
	}
	else if (py > 0)
		tmp = PI / 2;

	else if (py < 0)
		tmp = 3 * PI / 2;
	else
		tmp = 0;

	insert_in_array(tmp, arr, X);

	if (nrm == 1)								// Calculates the second coordinate (Declination or Altitude).
		tmp = asin(pz);
	else
		tmp = asin(pz / nrm);

	insert_in_array(tmp, arr, Y);

	over_rad_arr_to_decdeg_arr(arr, arr);		// Converts radians coordinates into degree coordinates.

	return arr;
}

void over_pos_vector_to_decdeg_arr(Array *pos, Array *darr)		// Does the same as 'pos_vector_to_decdeg_arr' but saves
{																// the result in a pre-existing Array.
	double nrm, px, py, pz, tmp;

	Array* rad;

	if (pos == NULL || darr == NULL)
	{
		error_message_ac(64, ERRMSS08);

		return;
	}
	else if ( length_of_array(pos) < 3 || length_of_array(darr) < 2 )
	{
		error_message_ac(64, ERRMSS09);

		return;
	}

	nrm = euclidean_norm(pos);					// Calculates the euclidean norm of the vector.

	if (nrm == 0)
	{
		error_message_ac(64, "null vector!");

		return;
	}

	rad = create_array(2);

	px = get_from_array(pos, X);

	py = get_from_array(pos, Y);

	pz = get_from_array(pos, Z);

	if (px != 0)								// Calculates the first coordinate (Right Ascension or Azimuth).
	{
		if (py != 0)
		{
			tmp = atan(py / px);

			if ( px < 0 && py > 0 || px < 0 && py < 0 )		// Corrects the quadrant.
				tmp += PI;

			else if ( px > 0 && py < 0 )
				tmp += 2 * PI;
		}
		else if (px > 0)
			tmp = 0;

		else if (px < 0)
			tmp = PI;
	}
	else if (py > 0)
		tmp = PI / 2;

	else if (py < 0)
		tmp = 3 * PI / 2;
	else
		tmp = 0;

	insert_in_array(tmp, rad, X);

	if (nrm == 1)								// Calculates the second coordinate (Declination or Altitude).
		tmp = asin(pz);
	else
		tmp = asin(pz / nrm);

	insert_in_array(tmp, rad, Y);

	over_rad_arr_to_decdeg_arr(rad, darr);		// Converts radians coordinates into degree coordinates.

	free_array(rad);
}

Array* precession_auxiliar_angles(double time)	// Calculates auxiliar angles used for precession.
{
	Array *ang, *coef;

	ang = create_array(3);							// Array of angles

	coef = create_array(4);							// Coefficients for the polynomial

	insert_in_array(0, coef, 0);

	insert_in_array(2306.2181, coef, 1);				// Algorithm and values found in H. Karttunen et al. (2017).

	insert_in_array(0.30188, coef, 2);

	insert_in_array(0.017998, coef, 3);

	insert_in_array( polynomial_function(time, coef), ang, 0 );	// Calculates the first angle and repeats the process
																// for the other two.
	insert_in_array(1.09468, coef, 2);

	insert_in_array(0.018203, coef, 3);

	insert_in_array( polynomial_function(time, coef), ang, 1 );

	insert_in_array(2004.3109, coef, 1);

	insert_in_array(-0.42665, coef, 2);

	insert_in_array(-0.041833, coef, 3);

	insert_in_array( polynomial_function(time, coef), ang, 2 );

	free_array(coef);

	insert_in_array( decdeg_to_radian( ang->a[0] / 3600 ), ang, 0 );	// Converts into radians.

	insert_in_array( decdeg_to_radian( ang->a[1] / 3600 ), ang, 1 );

	insert_in_array( decdeg_to_radian( ang->a[2] / 3600 ), ang, 2 );

	return ang;
}

Matrix* precession_matrix(Array *ang)		// Determines the matrix used for precession.
{
	double si[3], co[3], tmp;

	Matrix *pmat;

	if (ang == NULL)
	{
		error_message_ac(65, ERRMSS08);

		return NULL;
	}
	else if ( length_of_array(ang) < 3 )
	{
		error_message_ac(65, ERRMSS09);

		return NULL;
	}

	si[X] = sin( get_from_array(ang, X) );

	si[Y] = sin( get_from_array(ang, Y) );

	si[Z] = sin( get_from_array(ang, Z) );

	co[X] = cos( get_from_array(ang, X) );

	co[Y] = cos( get_from_array(ang, Y) );

	co[Z] = cos( get_from_array(ang, Z) );

	pmat = create_matrix(3, 3);

	tmp = co[X] * co[Y] * co[Z] - si[X] * si[Y];	// Calculates the matrix elements one by one.

	insert_in_matrix(tmp, pmat, 0, 0);

	tmp = - si[X] * co[Y] * co[Z] - si[Y] * co[X];		// Algorithm found in H. Karttunen et al. (2017).

	insert_in_matrix(tmp, pmat, 0, 1);

	tmp = - si[Z] * co[Y];

	insert_in_matrix(tmp, pmat, 0, 2);

	tmp = si[Y] * co[X] * co[Z] + si[X] * co[Y];

	insert_in_matrix(tmp, pmat, 1, 0);

	tmp = - si[X] * si[Y] * co[Z] + co[X] * co[Y];

	insert_in_matrix(tmp, pmat, 1, 1);

	tmp = - si[Y] * si[Z];

	insert_in_matrix(tmp, pmat, 1, 2);

	tmp = si[Z] * co[X];

	insert_in_matrix(tmp, pmat, 2, 0);

	tmp = - si[X] * si[Z];

	insert_in_matrix(tmp, pmat, 2, 1);

	tmp = co[Z];

	insert_in_matrix(tmp, pmat, 2, 2);

	return pmat;
}

Array* precession_J2000(Array *darr, double jd)		// Precess the coordinates of an object with standard epoch J2000.0.
{
	double tcent;

	Array *aux, *pos;
	Matrix *trns;

	if (darr == NULL)
	{
		error_message_ac(66, ERRMSS08);

		return NULL;
	}
	else if ( length_of_array(darr) < 2 )
	{
		error_message_ac(66, ERRMSS09);

		return NULL;
	}
	else if (jd <= 0)
	{
		error_message_ac(66, "invalid Julian Date informed!");

		return NULL;
	}

	pos = position_vector(darr);				// Determines the corresponding position vector.

	tcent = (jd - 2451545.0) / 36525.0;			// Fraction of century elapsed since 1/1/2000 12:00 UTC

	aux = precession_auxiliar_angles(tcent);	// Angles used to calculate the precession matrix

	trns = precession_matrix(aux);				// Precession matrix

	free_array(aux);

	aux = matrix_times_array(trns, pos);		// Multiplies the precession matrix by the position vector.

	free_array(pos);

	free_matrix(trns);

	pos = pos_vector_to_decdeg_arr(aux);		// Calculates the new coordinates.

	free_array(aux);

	return pos;
}

Matrix* nutation_matrix(double jd)		// Determines the matrix used for nutation.
{
	double c1, c2, eps, deps, dpsi, t;

	Array *coef;
	Matrix *nut;
	
	if (jd <= 0)
	{
		error_message_ac(71, "invalid Julian Date informed!");

		return NULL;
	}

	t = jd - 2451545.0;						// Algorithm found in H. Karttunen et al. (2017).

	coef = create_array(4);					// Coefficients for the polynomial

	insert_in_array( (23 + 26 / 60 + 21.448 / 3600), coef, 0 );

	insert_in_array( (-46.815 / 3600), coef, 1 );

	insert_in_array( (-0.00059 / 3600), coef, 2 );

	insert_in_array( (0.001813 / 3600), coef, 3 );

	eps = polynomial_function( (t / 36525.0), coef );

	free_array(coef);

	c1 = 125 - 0.05295 * t;

	c2 = 200.9 + 1.97129 * t;

	c1 = decdeg_to_radian(c1);				// Converts to radian.

	c2 = decdeg_to_radian(c2);

	dpsi = -0.0048 * sin(c1) - 0.0004 * sin(c2);

	deps = 0.0026 * cos(c1) + 0.0002 * cos(c2);

	eps += deps;

	eps = decdeg_to_radian(eps);			// Converts to radian.

	deps = decdeg_to_radian(deps);

	dpsi = decdeg_to_radian(dpsi);

	nut = create_identity_matrix(3);		// Nutation matrix with the main diagonal filled

	c1 = dpsi * cos(eps);

	c2 = dpsi * sin(eps);

	insert_in_matrix(-c1, nut, 0, 1 );		// Fills the other elements.

	insert_in_matrix(-c2, nut, 0, 2 );

	insert_in_matrix(c1, nut, 1, 0);

	insert_in_matrix(-deps, nut, 1, 2);

	insert_in_matrix(c2, nut, 2, 0);

	insert_in_matrix(deps, nut, 2, 1);

	return nut;
}

Array* nutation_J2000(Array *darr, double jd)	// Corrects the coordinates of an object with nutation
{												// for standard epoch J2000.0.
	Array *new, *pos;
	Matrix *nut;

	if (darr == NULL)
	{
		error_message_ac(72, ERRMSS08);

		return NULL;
	}
	else if ( length_of_array(darr) < 2 )
	{
		error_message_ac(72, ERRMSS09);

		return NULL;
	}
	else if (jd <= 0)
	{
		error_message_ac(72, "invalid Julian Date informed!");

		return NULL;
	}

	pos = position_vector(darr);			// Determines the corresponding position vector.

	nut = nutation_matrix(jd);				// Calculates the nutation matrix.

	new = matrix_times_array(nut, pos);		// New position vector

	free_array(pos);

	free_matrix(nut);

	pos = pos_vector_to_decdeg_arr(new);	// Calculates the new coordinates.

	return pos;
}

void aberration_correction(Array *darr, double jd)	// Corrects the coordinates of an object with annual aberration.
{
	double ar, dec, dar, ddec, g, lambda;

	if (darr == NULL)
	{
		error_message_ac(73, ERRMSS08);

		return;
	}
	else if ( length_of_array(darr) < 2 )
	{
		error_message_ac(73, ERRMSS09);

		return;
	}
	else if (jd <= 0)
	{
		error_message_ac(73, "invalid Julian Date informed!");

		return;
	}

	g = 357.528 + 0.9856 * (jd - 2451545.0);			// Calculates the ecliptic longitude of the Sun.

	g = decdeg_to_radian(g);							// Algorithm found in H. Karttunen et al. (2017).

	lambda = 280.46 + 0.985647 * (jd - 2451545.0) + 1.915 * sin(g) + 0.02 * sin(2 * g);

	lambda = decdeg_to_radian(lambda);

	ar = decdeg_to_radian( get_from_array(darr, 0) );	// Calculates the aberration.

	dec = decdeg_to_radian( get_from_array(darr, 1) );

	dar = ( -20.5 * sin(ar) * sin(lambda) - 18.8 * cos(ar) * cos(lambda) ) / cos(dec);

	ddec = 20.5 * cos(ar) * sin(dec) * sin(lambda) + 18.8 * sin(ar) * sin(dec) * cos(lambda) - 8.1 * cos(dec) * cos(lambda);

	dar /= 3600;										// Turns the values into degrees.

	ddec /= 3600;

	ar = radian_to_decdeg(ar) + dar;					// Adds the aberration to the coordinates.

	dec = radian_to_decdeg(dec) + ddec;

	insert_in_array(ar, darr, 0);

	insert_in_array(dec, darr, 1);
}











void auxf(Matrix *mat)	// Auxiliar test function.
{
//	printf("\n\nAuxiliar vector:");

//	printf("\n\nPosition vector:");

	printf("\n\nPrecession matrix:");

//	print_array(arr);

	print_matrix(mat);
}




// Bibliography:
// 
// 
// H. Karttunen; P. Kröger et al: Fundamental Astronomy, 6th ed., Springer-Verlag 2017.
//
// S. O. Kepler; M. F. O. Saraiva: Astronomia & Astrofísica, 2th ed., Livraria da Física 2004.