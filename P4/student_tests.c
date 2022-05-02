#include <stdio.h>
#include <stdlib.h>
#include "event.h"
#include "calendar.h"
#include "my_memory_checker_216.h"

/*****************************************************/
/* In this file you will provide tests for your      */
/* calendar application.  Each test should be named  */
/* test1(), test2(), etc. Each test must have a      */
/* brief description of what it is testing (this     */
/* description is important).                        */
/*                                                   */
/* You can tell whether any test failed if after     */
/* executing the students tests, you executed        */
/* "echo $?" on the command line and you get a value */
/* other than 0.  "echo $?" prints the status of     */
/* the last command executed by the shell.           */ 
/*                                                   */
/* Notice that main just calls test1(), test2(), etc.*/
/* and once one fails, the program eventually        */
/* return EXIT_FAILURE; otherwise EXIT_SUCCESS will  */
/* be returned.                                      */
/*****************************************************/

static int comp_minutes(const void *ptr1, const void *ptr2) {

	return ((Event *)ptr1)->duration_minutes - ((Event *)ptr2)->duration_minutes;

}

/* Description here: This test checks ...  */

static int test1() {

	int days = 7;
	Calendar *calendar;

	printf("***** Practice Test*****\n");

	if (init_calendar("Spr", days, comp_minutes, NULL, &calendar) == SUCCESS) {

		if (print_calendar(calendar, stdout, 1) == SUCCESS) {
			
			printf("\n");
			return destroy_calendar(calendar);

		}
	}
    
	return FAILURE;

}

static int test2() {

	Calendar *calendar, *calendar_one, *calendar_two;

	printf("*****Initialize Calendar*****\n");

	init_calendar("First", 12, comp_minutes, NULL, &calendar);

	printf("Name: %s\n", (calendar)->name);
	printf("Days: %d\n", (calendar)->days);
	printf("Total Events: %d\n", (calendar)->total_events);
	
	if(init_calendar(NULL, 12, comp_minutes, NULL, &calendar_one) == FAILURE) {

		printf("Name Null == PASS\n");

	}

	if(init_calendar("Start", -12, comp_minutes, NULL, &calendar_two) == FAILURE) {

		printf("Day Negative Null == PASS\n");

	}

	if(init_calendar("Start", 12, comp_minutes, NULL, NULL) == FAILURE) {

		printf("Calendar NUll == PASS\n");

	}

	 destroy_calendar(calendar);

	printf("\n");

	return SUCCESS;

}

static int test3() {

	Calendar *calendar;

	printf("*****Test print with no events*****\n");

	init_calendar("Test without Events", 21, comp_minutes, NULL, &calendar);

	print_calendar(calendar, stdout, 0);

	printf("\n");

	print_calendar(calendar, stdout, 1);

	if(print_calendar(NULL, stdout, 0) == FAILURE) {

		printf("Null Calendar == PASS\n");

	} 

	if(print_calendar(calendar, NULL, 0) == FAILURE) {

		printf("Null Output Stream == PASS\n");

	}

	printf("\n");

	destroy_calendar(calendar);

	return SUCCESS;

}

static int test4() {

	Calendar *calendar, *calendar_t;

	printf("***** Test Add Event *****\n");

	init_calendar("Add Events", 4, comp_minutes, NULL, &calendar);
	init_calendar("Test to FAIL", 4, NULL, NULL, &calendar_t);

	add_event(calendar, "Event", 900, 60, NULL, 1);

	if(add_event(NULL, "Event 0", 900, 60, NULL, 1) == FAILURE) {

		printf("Calendar Null == PASS\n");

	}

	if(add_event(calendar, NULL, 900, 60, NULL, 1) == FAILURE) {

		printf("Name Null == PASS\n");

	}

	if(add_event(calendar, "Event 2", -900, 60, NULL, 1) == FAILURE) {

		printf("Start time less than 0== PASS\n");

	}

	if(add_event(calendar, "Event 3", 3900, 60, NULL, 1) == FAILURE) {

		printf("Start time greater than 2400 == PASS\n");

	}

	if(add_event(calendar, "Event 4", 900, -60, NULL, 1) == FAILURE)  {

		printf("Duration is less than 0 == PASS\n");

	}

	if(add_event(calendar, "Event 5", 900, 60, NULL, 0) == FAILURE)  {

		printf("Day is less than 1 == PASS\n");

	}

	if(add_event(calendar, "Event 6", 900, 60, NULL, 99) == FAILURE)  {

		printf("Day is greater than number possible == PASS\n");

	}

	if(add_event(calendar, "Event", 900, 60, NULL, 1) == FAILURE)  {

		printf("Event already exists == PASS\n");

	}

	if(add_event(calendar_t, "Event 8", 900, 60, NULL, 1) == FAILURE)  {

		printf("Comp_func is null == PASS\n");

	}

	if(add_event(calendar, "Event 9", 900, 0, NULL, 1) == FAILURE)  {

		printf("Duration is 0 == PASS\n");

	}

	add_event(calendar, "Event 4", 900, 60, NULL, 3);
	add_event(calendar, "Event 3", 1300, 620, NULL, 3);
	add_event(calendar, "Event 2", 1530, 160, NULL, 3);
	add_event(calendar, "Event 1", 1700, 60, NULL, 3);

	print_calendar(calendar, stdout, 1);

	printf("\n");

	destroy_calendar(calendar);

	return SUCCESS;

}
 
static int test5() {

	Calendar *calendar;
	Event *event = NULL, *not_null;

	printf("***** Testing Find event *****\n");

	init_calendar("First", 4, comp_minutes, NULL, &calendar);
	add_event(calendar, "Event 0", 900, 60, NULL, 1);
	add_event(calendar, "Event 1", 1300, 620, NULL, 2);
	add_event(calendar, "Event 2", 1530, 160, NULL, 3);
	add_event(calendar, "Event 3", 1700, 60, NULL, 3);
	add_event(calendar, "Event 4", 900, 60, NULL, 3);
	add_event(calendar, "Event 5", 1300, 620, NULL, 3);
	add_event(calendar, "Event 6", 1530, 160, NULL, 3);
	add_event(calendar, "Event 7", 1700, 60, NULL, 3);

	if(find_event(NULL, "e", NULL) == FAILURE) {

		printf("Calendar Null == PASS\n");

	}

	if(find_event(calendar, NULL, NULL) == FAILURE) {

		printf("Name Null == PASS\n");

	}

	if(find_event(calendar, "Event 0", &event) == SUCCESS && event == NULL) {

		printf("Event found Successfully and Event is NULL\n");

	} 

	if(find_event(calendar, "Event 8", &event) == FAILURE && event == NULL) {

		printf("Event not found Successfully and Event is NULL\n");

	} 


	if(find_event(calendar, "Event 0", &not_null) == SUCCESS && not_null != NULL) {

		printf("Event found Successfully and Event isn't  NULL\n");

	} 

	printf("***** Test Find Event in Day  *****\n");

	if(find_event_in_day(NULL, "e", 2, NULL) == FAILURE) {

		printf("Calendar Null == PASS\n");

	}

	if(find_event_in_day(calendar, NULL, 1, NULL) == FAILURE) {

		printf("Name Null == PASS\n");

	}

	if(find_event_in_day(calendar, "Event 0", 0, NULL) == FAILURE) {

		printf("Day is 0 == PASS\n");

	}

	if(find_event_in_day(calendar, "Event 0", 8, NULL) == FAILURE) {

		printf("Day is greator than amount possible == PASS\n");

	}

	if(find_event_in_day(calendar, "Event 0", 1, &event) == SUCCESS && event == NULL) {

		printf("Event found Successfully and Event is NULL\n");

	} 

	if(find_event_in_day(calendar, "Event 3", 1, &event) == FAILURE && event == NULL) {

		printf("Event not found Successfully and Event is NULL\n");

	} 


	if(find_event_in_day(calendar, "Event 0", 1, &not_null) == SUCCESS && not_null != NULL) {

		printf("Event found Successfully and Event isn't  NULL\n");

	} 

	if(find_event_in_day(calendar, "Event 7", 2, NULL) == FAILURE) {

		printf("Event not found correctly\n");

	}

	if(find_event_in_day(calendar, "Event 7", 3, NULL) == SUCCESS) {

		printf("Event found correctly\n");

	}

	destroy_calendar(calendar);

	return SUCCESS;

}

static int test6() {

	Calendar *calendar;
	void *found;
	char x[15] = "I love CMSC";

	printf("***** Test get info pointer *****\n");

	init_calendar("First", 1, comp_minutes, NULL, &calendar);

	add_event(calendar, "E", 900, 120, x, 1);

	if(get_event_info(calendar, "Ea") == NULL) {

		printf("Event not found successfully\n");

	}

	found = get_event_info(calendar, "E");

	printf("%s\n",(char *) found);

	printf("\n");

	destroy_calendar(calendar);

	return SUCCESS;

}

static int test7() {

	Calendar *calendar;

	printf("***** Test Remove *****\n");

	init_calendar("First", 4, comp_minutes, NULL, &calendar);
	add_event(calendar, "Event 0", 900, 60, NULL, 1);
	add_event(calendar, "Event 1", 1300, 620, NULL, 2);
	add_event(calendar, "Event 2", 1530, 160, NULL, 3);
	add_event(calendar, "Event 3", 1700, 60, NULL, 4);
	add_event(calendar, "Event 4", 900, 60, NULL, 4);
	add_event(calendar, "Event 5", 1300, 620, NULL, 1);
	add_event(calendar, "Event 6", 1530, 160, NULL, 3);
	add_event(calendar, "Event 7", 1700, 60, NULL, 3);

	print_calendar(calendar, stdout, 1);

	printf("\n*****After removing 0, 5, 6, 4 *****\n");

	remove_event(calendar, "Event 0");
	remove_event(calendar, "Event 5");
	remove_event(calendar, "Event 6");
	remove_event(calendar, "Event 4");

	print_calendar(calendar, stdout, 1);

	destroy_calendar(calendar);

	return SUCCESS;

}

static int test8() {

	Calendar *calendar;

	printf("***** Test Clear Day *****\n");

	init_calendar("First", 4, comp_minutes, NULL, &calendar);
	add_event(calendar, "Event 0", 900, 60, NULL, 4);
	add_event(calendar, "Event 1", 1300, 620, NULL, 2);
	add_event(calendar, "Event 2", 1530, 160, NULL, 4);
	add_event(calendar, "Event 3", 1700, 60, NULL, 4);
	add_event(calendar, "Event 4", 900, 60, NULL, 4);
	add_event(calendar, "Event 5", 1300, 620, NULL, 4);
	add_event(calendar, "Event 6", 1530, 160, NULL, 3);
	add_event(calendar, "Event 7", 1700, 60, NULL, 3);

	print_calendar(calendar, stdout, 1);

	clear_day(calendar, 4);

	print_calendar(calendar, stdout, 1);

	destroy_calendar(calendar);

	return SUCCESS;

}
 
static int test9() {

	Calendar *calendar;

	printf("***** Test Clear Calendar *****\n");

	init_calendar("First", 4, comp_minutes, NULL, &calendar);
	add_event(calendar, "Event 0", 900, 60, NULL, 4);
	add_event(calendar, "Event 1", 1300, 620, NULL, 2);
	add_event(calendar, "Event 2", 1530, 160, NULL, 4);
	add_event(calendar, "Event 3", 1700, 60, NULL, 4);
	add_event(calendar, "Event 4", 900, 60, NULL, 4);
	add_event(calendar, "Event 5", 1300, 620, NULL, 4);
	add_event(calendar, "Event 6", 1530, 160, NULL, 3);
	add_event(calendar, "Event 7", 1700, 60, NULL, 3);

	print_calendar(calendar, stdout, 1);

	clear_calendar(calendar);

	print_calendar(calendar, stdout, 1);

	destroy_calendar(calendar);

	return SUCCESS;

}

static int test0() {

	Calendar *calendar;

	printf("***** Destroy Calendar *****\n");

	init_calendar("First", 12, comp_minutes, NULL, &calendar);

	add_event(calendar, "Event 0", 900, 60, NULL, 4);
	add_event(calendar, "Event 1", 1300, 620, NULL, 2);
	add_event(calendar, "Event 2", 1530, 160, NULL, 4);
	add_event(calendar, "Event 3", 1700, 60, NULL, 4);
	add_event(calendar, "Event 4", 900, 60, NULL, 4);
	add_event(calendar, "Event 5", 1300, 620, NULL, 4);
	add_event(calendar, "Event 6", 1530, 160, NULL, 3);
	add_event(calendar, "Event 7", 1700, 60, NULL, 3);

	destroy_calendar(calendar);

	return SUCCESS;

}	



int main() {

	int result = SUCCESS;

	/***** Starting memory checking *****/
	start_memory_check();
	/***** Starting memory checking *****/

	if (test1() == FAILURE) result = FAILURE;
	if (test2() == FAILURE) result = FAILURE;
	if (test3() == FAILURE) result = FAILURE;
	if (test4() == FAILURE) result = FAILURE;
	if (test5() == FAILURE) result = FAILURE;
	if (test6() == FAILURE) result = FAILURE;
	if (test7() == FAILURE) result = FAILURE;
	if (test8() == FAILURE) result = FAILURE;
	if (test9() == FAILURE) result = FAILURE;
	if (test0() == FAILURE) result = FAILURE;

	/****** Gathering memory checking info *****/
	stop_memory_check();
	/****** Gathering memory checking info *****/
   
	if (result == FAILURE) {

		exit(EXIT_FAILURE);

	}

	return EXIT_SUCCESS;

}
