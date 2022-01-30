// Functions used in works with time, calendars and astronomy.
// The library 'linalg.h' is required for these functions.
//


// Type exported for date
//
typedef struct date Date;

// Type exported for angles and time
// (Use degrees or hours in sexagesimal format)
//
typedef struct degree Hdeg;

// Type exported for astronomical or geographical coordinates.
//
typedef struct coord Coord;


//
// In-Out functions:
//


// Creates a date variable.
//
Date* create_date(void);

// Creates a variable for angle (degree) or time (hour).
//
Hdeg* create_deg(void);

// Creates a variable for astronomical or geographical coordinates.
//
Coord* create_coord(void);

// Deallocates the memory space used for a date variable.
//
void free_date(Date *date);

// Deallocates the memory space used for a variable of angle or time.
//
void free_deg(Hdeg *deg);

// Deallocates the memory space used for a variable of coordinates.
//
void free_coord(Coord *crd);

// Gets a date from stdin.
//
void type_date(Date *date);

// Gets an angle or time value from stdin.
//
void type_deg(Hdeg *deg);

// Inserts a value of day, month or year into a date.
// The value of 'pos' must be:
// '0 - day', '1 - month' or '2 - year'.
//
void insert_in_date(long a, Date *dat, int pos);

// Gets a value of day, month or year from a date.
// The value of 'pos' must be:
// '0 - day', '1 - month' or '2 - year'.
// Returns '0' if 'dat' is NULL or 'pos' does not exist.
//
long get_from_date(Date *dat, int pos);

// Inserts a value of hour/degree, minutes or seconds into a Hdeg.
// The value of 'pos' must be:
// '0 - hour/degree', '1 - minutes' or '2 - seconds'.
//
void insert_in_deg(double a, Hdeg *deg, int pos);

// Gets a value of hour/degree, minutes or seconds from a Hdeg.
// The value of 'pos' must be:
// '0 - hour/degree', '1 - minutes' or '2 - seconds'.
// Returns '0' if 'deg' is NULL or 'pos' does not exist.
//
double get_from_deg(Hdeg *deg, int pos);

// Inserts a value of hour/degree, minutes or seconds into a Coord.
// The value of 'pos1' must be:
// '0 - first coordinate' or '1 - second coordinate'.
// The value of 'pos2' must be:
// '0 - hour/degree', '1 - minutes' or '2 - seconds'.
//
void insert_in_coord(double a, Coord *crd, int pos1, int pos2);

// Gets a value of hour/degree, minutes or seconds from a Coord.
// The value of 'pos1' must be:
// '0 - first coordinate' or '1 - second coordinate'.
// The value of 'pos2' must be:
// '0 - hour/degree', '1 - minutes' or '2 - seconds'.
// Returns '0' if 'crd' is NULL or if 'pos1'
// or 'pos2' does not exist.
//
double get_from_coord(Coord *crd, int pos1, int pos2);

// Inserts a sexagesimal value into a Coord.
// The value of 'pos' must be:
// '0 - first coordinate' or '1 - second coordinate'.
//
void put_deg_into_coord(Hdeg *deg, Coord *crd, int pos);

// Gets a sexagesimal value from a Coord.
// The value of 'pos' must be:
// '0 - first coordinate' or '1 - second coordinate'.
// Returns NULL if 'crd' is NULL or 'pos' does not exist.
//
Hdeg* get_deg_from_coord(Coord *crd, int pos);

// Does the same as 'get_deg_from_coord' but saves the result in
// a pre-existing deg.
// The value of 'pos' must be:
// '0 - first coordinate' or '1 - second coordinate'.
//
void over_get_deg_from_coord(Coord *crd, int pos, Hdeg *deg);

// Shows the date in the format 'dd/mm/yyyy'.
//
void print_date(Date *date);

// Shows an angle value in sexagesimal format.
//
void print_deg(Hdeg *deg);

// Shows an hour value in sexagesimal format.
//
void print_hour(Hdeg *deg);

// Shows an angle value in complete sexagesimal format.
//
void print_complete_deg(Hdeg *deg);

// Shows an hour value in complete sexagesimal format.
//
void print_complete_hour(Hdeg *deg);

// Shows an error message indicating the function from where it came.
//
static void error_message_ac(int nmbr, char *mssg);


//
// Copy functions:
//


// Copies a date as a new one.
// Returns NULL if 'dat' is NULL.
//
Date* copy_date(Date *dat);

// Copies a date in a pre-existing one, overwriting it.
//
void over_copy_date(Date *cpy, Date *pst);

// Copies a deg as a new one.
// Returns NULL if 'deg' is NULL.
//
Hdeg* copy_deg(Hdeg *deg);

// Copies a deg in a pre-existing one, overwriting it.
//
void over_copy_deg(Hdeg *cpy, Hdeg *pst);

// Copies a coord as a new one.
// Returns NULL if 'crd' is NULL.
//
Coord* copy_coord(Coord *crd);

// Copies a coord in a pre-existing one, overwriting it.
//
void over_copy_coord(Coord *cpy, Coord *pst);


//
// Checking functions:
//


// Determines if the year is a leap year or not.
// Returns '1' or '0' in each case.
//
int is_leap_year(long year);

// Tests if the date is a valid date.
// Returns '1' or '0' if that is true or false.
//
int is_valid_date(Date *date);

// Tests if the value is corret in the sexagesimal format.
// Returns '1' or '0' if that is true or false.
//
int is_valid_deg(Hdeg *deg);

// Tests if the time is corret in the 12-hour format.
// Returns '1' or '0' if that is true or false.
//
int is_valid_12hour(Hdeg *hour);

// Tests if the time is corret in the 24-hour format.
// Returns '1' or '0' if that is true or false.
//
int is_valid_24hour(Hdeg *hour);

// Tests if the coordinate is corret in the right ascension format.
// Returns '1' or '0' if that is true or false.
//
int is_valid_right_ascension(Hdeg *ra);

// Tests if the coordinate is corret in the declination format.
// Returns '1' or '0' if that is true or false.
//
int is_valid_declination(Hdeg *dec);

// Tests if the coordinate is corret in the hour angle format.
// Returns '1' or '0' if that is true or false.
//
int is_valid_hour_angle(Hdeg *ha);

// Tests if the coordinate is corret in the azimuth format.
// Returns '1' or '0' if that is true or false.
//
int is_valid_azimuth(Hdeg *azm);

// Tests if the coordinate is corret in the altitude format.
// Returns '1' or '0' if that is true or false.
//
int is_valid_altitude(Hdeg *alt);

// Tests if the month has 31 days or not.
// Returns '1' or '0' if that is true or false.
// Returns a negative number if the month informed does not exist.
//
int month_has_31days(int mnth);


//
// Conversion functions:
//


// Converts sexagesimal format to decimal.
// Returns '0' if the deg informed is null.
//
double decimal_deg(Hdeg *deg);

// Converts decimal format to sexagesimal.
//
Hdeg* sexagesimal_deg(double decd);

// Converts decimal format to sexagesimal and saves the result in a pre-existing Hdeg.
//
void over_sexagesimal_deg(double decd, Hdeg *sexd);

// Converts a time format coordinate into decimal degree coordinate.
// Returns '0' if 'hour' is NULL.
//
double hour_to_decdeg(Hdeg *hour);

// Converts a decimal degree coordinate into time format coordinate.
//
Hdeg* decdeg_to_hour(double decd);

// Does the same as 'decdeg_to_hour' but saves the result
// in a pre-existing Hdeg.
//
void over_decdeg_to_hour(double decd, Hdeg *hour);

// Converts a time format coordinate into sexagesimal degree coordinate.
// Returns NULL if 'hour' is NULL.
//
Hdeg* hour_to_sexdeg(Hdeg *hour);

// Does the same as 'hour_to_sexdeg' but saves the result
// in a pre-existing Hdeg.
//
void over_hour_to_sexdeg(Hdeg *hour, Hdeg *sexd);

// Converts a sexagesimal degree coordinate into time format coordinate.
// Returns NULL if 'sexd' is NULL.
//
Hdeg* sexdeg_to_hour(Hdeg *sexd);

// Does the same as 'sexdeg_to_hour' but saves the result
// in a pre-existing Hdeg.
//
void over_sexdeg_to_hour(Hdeg *sexd, Hdeg *hour);

// Converts an angle in degrees (decimal) into radians.
//
double decdeg_to_radian(double deg);

// Converts an angle in degrees (sexagesimal) into radians.
// Returns '0' if the deg informed is null.
//
double sexdeg_to_radian(Hdeg *deg);

// Converts an angle in radians into degrees (decimal).
//
double radian_to_decdeg(double rad);

// Converts an angle in radians into degrees (sexagesimal).
//
Hdeg* radian_to_sexdeg(double rad);

// Converts a Coord structure of sexagesimal degs into an array of decimal degs.
// Returns NULL if 'crd' is NULL.
//
Array* coord_to_decdeg_array(Coord *crd);

// Does the same as 'coord_to_decdeg_array' but saves the result
// in a pre-existing array.
//
void over_coord_to_decdeg_array(Coord *crd, Array *arr);

// Converts an array of decimal degs into a Coord structure of sexagesimal degs.
// Returns NULL if 'arr' is NULL or if it has less than two elements.
//
Coord* decdeg_array_to_coord(Array *arr);

// Does the same as 'decdeg_array_to_coord' but saves the result
// in a pre-existing Coord.
//
void over_decdeg_array_to_coord(Array *arr, Coord *crd);

// Converts a Coord structure of sexagesimal equatorial coordinates into
// an array of decimal degs.
// Returns NULL if 'crd' is NULL.
//
Array* eq_coord_to_decdeg_array(Coord *crd);

// Does the same as 'eq_coord_to_decdeg_array' but saves the result
// in a pre-existing Array.
//
void over_eq_coord_to_decdeg_array(Coord *crd, Array *darr);

// Converts an array of decimal degs into a Coord structure of sexagesimal
// equatorial coordinates.
// Returns NULL if 'darr' is NULL or if it has less than two elements.
//
Coord* decdeg_arr_to_eq_coord(Array *darr);

// Does the same as 'decdeg_arr_to_eq_coord' but saves the result
// in a pre-existing Coord.
//
void over_decdeg_arr_to_eq_coord(Array *darr, Coord *crd);

// Converts an array of decimal degs into an array of radians.
// Returns NULL if 'arr' is NULL or if it has less than two elements.
//
Array* decdeg_arr_to_rad_arr(Array *arr);

// Does the same as 'decdeg_arr_to_rad_arr' but saves the result
// in a pre-existing array.
//
void over_decdeg_arr_to_rad_arr(Array *darr, Array *rarr);

// Converts an array of radians into an array of decimal degs.
// Returns NULL if 'arr' is NULL or if it has less than two elements.
//
Array* rad_arr_to_decdeg_arr(Array *arr);

// Does the same as 'rad_arr_to_decdeg_arr' but saves the result
// in a pre-existing array.
//
void over_rad_arr_to_decdeg_arr(Array *rarr, Array *darr);


//
// Arithmetic functions:
//


// Corrects a sexagesimal value with minutes or seconds greater than 60.
//
void correct_deg(Hdeg *deg);


//
// Calendar functions:
//


// Gives the day number of a given date.
// Returns '0' if the date informed is null.
//
int day_number(Date *date);

// Gives the first day of week of a year in a 28-year solar cycle.
// Returns 0, 1, 2, ..., 6 for Sunday, Monday etc.
// Returns a negative number if the day informed is not in the cycle.
//
int cycle28_day_of_week(int num, int epch);

// Gives the first day of week of the 28-year cycle that begins after a year multiple of 100 in Gregorian Calendar.
// Returns an integer from '0' to '6'.
// Returns a negative number if the year informed is not multiple of 100.
//
int gregorian_cycle28_epoch(int year);

// Gives the first day of week of a year in Gregorian Calendar.
// Returns 0, 1, 2, ..., 6 for Sunday, Monday etc.
//
int gregorian_first_day_of_year(int year);

// Gives the day of week of a given date in Gregorian Calendar.
// Returns 0, 1, 2, ..., 6 for Sunday, Monday etc.
// Returns a negative number if the day informed is not in the Gregorian Calendar.
//
int gregorian_day_of_week(Date *date);

// Calculates the Catholic Easter date for a given year.
// The year must be greater than or equal to 1.
//
Date* catholic_easter_date(int year);

// Gives the Julian Date.
// Returns '0' if the time or the date are null
// or the hour value is invalid.
//
double julian_date(Hdeg *utc, Date *date);

// Converts Julian Date into normal date and time format.
//
void jd_to_date(double jd, Date *date, Hdeg *hour);


//
// Astronomy functions:
//


// Determines a unit vector pointing in the direction of the coordinates.
// The coordinates informed to function must be of decimal degrees.
// Returns NULL if 'darr' is NULL or if it has less than two elements.
//
Array* position_vector(Array *darr);

// Does the same as 'position_vector' but saves the result
// in a pre-existing Array.
//
void over_position_vector(Array *darr, Array *pos);

// Determines the degree coordinates corresponding to a unit position vector.
// Returns NULL if 'pos' is NULL or if it has less than three elements.
//
Array* pos_vector_to_decdeg_arr(Array *pos);

// Does the same as 'pos_vector_to_decdeg_arr' but saves the result
// in a pre-existing Array.
//
void over_pos_vector_to_decdeg_arr(Array *pos, Array *darr);

// Calculates auxiliar angles used for precession.
// The time informed must be the fraction of century elapsed
// since J2000.0 epoch.
//
Array* precession_auxiliar_angles(double time);

// Determines the matrix used for precession.
// The array informed must contain the auxiliar angles calculated
// by the function 'precession_auxiliar_angles'.
// Returns NULL if 'ang' is NULL or has less than 3 elements.
//
Matrix* precession_matrix(Array *ang);

// Precess the coordinates of an object with standard epoch J2000.0.
// It's necessary to inform the coordinates (decimal degrees) and
// the time of observation in Julian Date.
// Returns NULL if 'darr' is NULL or has less than 2 elements, or
// if 'jd' is invalid.
//
Array* precession_J2000(Array *darr, double jd);

// Determines the matrix used for nutation.
// Returns NULL if 'jd' is invalid.
//
Matrix* nutation_matrix(double jd);

// Corrects the coordinates of an object with nutation for standard
// epoch J2000.0.
// It's necessary to inform the coordinates (decimal degrees) and
// the time of observation in Julian Date.
// Returns NULL if 'darr' is NULL or has less than 2 elements, or
// if 'jd' is invalid.
//
Array* nutation_J2000(Array *darr, double jd);

// Corrects the coordinates of an object with annual aberration.
// It's necessary to inform the coordinates (decimal degrees) and
// the time of observation in Julian Date.
// Returns NULL if 'darr' is NULL or has less than 2 elements, or
// if 'jd' is invalid.
//
void aberration_correction(Array *darr, double jd);







// Auxiliar test function.
//
void auxf(Matrix *mat);