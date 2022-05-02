#include "calendar.h"
#include "event.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

/* Initalize the Calendar */

int init_calendar(const char *name, int days, int (*comp_func) 
	(const void *ptr1, const void *ptr2), void (*free_info_func) (void *ptr), 
	Calendar ** calendar) {

	Calendar *new_cal;

/* Checking conditions */

	if(calendar == NULL || name == NULL || days < 1) {

		return FAILURE;

	}

/* Mem Alloc */

	new_cal = malloc(sizeof(Calendar));

	if(new_cal == NULL) {

		return FAILURE;

	}

	new_cal->name = malloc(strlen(name) + 1);

	if(new_cal->name == NULL) {

		return FAILURE;

	}

	strcpy(new_cal->name, name);

	new_cal->events = calloc(days, sizeof(Event *));

	if(new_cal->events == NULL) {

		return FAILURE;

	}

	new_cal->days = days;
	new_cal->total_events = 0;
	new_cal->comp_func = comp_func;
	new_cal->free_info_func = free_info_func;

	*calendar = new_cal;

	return SUCCESS;

}

/* Print Calendar */

int print_calendar(Calendar *calendar, FILE *output_stream, int print_all) {

	int i;
	Event *event;

/* Checking Conditions */

	if(calendar == NULL || output_stream == NULL) {
	
		return FAILURE;

	} else {

		if(print_all != 0) {

			fprintf(output_stream, "Calendar's Name: \"%s\"\n",
				 calendar->name);
			fprintf(output_stream, "Days: %d\n", calendar->days);
			fprintf(output_stream, "Total Events: %d\n\n", 
				calendar->total_events);

		} 

		fprintf(output_stream, "**** Events ****\n");

		if(calendar->total_events > 0) {

/* Printing and iterating through each day */

			for(i = 0; i < calendar->days; i++) {

				fprintf(output_stream, "Day %d\n", i + 1);

				event = calendar->events[i];

				while(event != NULL) {

					fprintf(output_stream, "Event's Name:\"%s\",", event->name); 
					fprintf(output_stream, "Start_time: %d,", event->start_time);
					fprintf(output_stream, "Duration: %d\n", event->duration_minutes); 

					event = event->next;

				}

			}

		}

		return SUCCESS;

	}

}

/* Adding an event */

int add_event(Calendar *calendar, const char *name, 
	int start_time, int duration_minutes, void *info, int day) {

	Event *prev = NULL, *curr, *to_add;

/* Checking Conditions */

	if(calendar == NULL || name == NULL || start_time > 2400 || 
		start_time < 0 || duration_minutes <= 0 ||day < 1 || 
		day > calendar->days || find_event(calendar, name, NULL) == SUCCESS ||
		calendar->comp_func == NULL) { 

		return FAILURE;

	}

/* Mem Alloc */

	to_add = malloc(sizeof(Event));

	if(to_add == NULL) {

		return FAILURE;

	} 

	to_add->name = malloc(strlen(name) + 1);

	if(to_add->name == NULL) {

		return FAILURE;

	}

	strcpy(to_add->name, name);
	to_add->start_time = start_time;
	to_add->duration_minutes = duration_minutes;
	to_add->info = info;

	curr = calendar->events[day - 1];

/* Insert Node */

	while(curr != NULL && calendar->comp_func(to_add, curr) > 0) {

		prev = curr;
		curr = curr->next;

	}

	to_add->next = curr;

	if(prev == NULL) {

		calendar->events[day - 1] = to_add;

	} else {

		prev->next = to_add;

	}

	calendar->total_events++;

	return SUCCESS;

} 

/* Find an event */

int find_event(Calendar *calendar, const char *name, Event **event) {

	int i = 0, result = FAILURE;

/* Checking Conditions */

	if(calendar == NULL || name == NULL) {

		return FAILURE;

	} 

/* Iterate throuh each day and by calling find event in day and if found
 * exit the loop using break */

	for(i = 0; i < calendar->days; i++) {

		result = find_event_in_day(calendar, name, (i + 1), event);

		if(result == SUCCESS) {

			break;

		}

	}

	return result;

}

/* Find an event in a day */

int find_event_in_day(Calendar *calendar, const char *name, int day, Event **event) {

	Event *events;
	
/* Checking Conditions */

	if(calendar == NULL || name == NULL || day < 1 || day > calendar->days) {

		return FAILURE;

	}

	events = calendar->events[day - 1];

/* Iterate through linked list to find event and if found return SUCCESS */
 
	while(events != NULL) {

		if(strcmp(name, events->name) == 0) {

			if(event != NULL) {

				*event = events;

			}

			return SUCCESS;

		} 

		events = events->next;

	}

	return FAILURE;

}

/* Remove an event in a calendar */

int remove_event(Calendar *calendar, const char *name) {

	Event *prev = NULL, *curr;
	int i, found = FAILURE;

/* Checking Conditions */

	if(calendar == NULL || name == NULL) {

		return FAILURE;

	}

/* Find what day event occurs in  and if found 
 * return SUCCESS else return FAILURE*/

	for(i = 1; i <= calendar->days; i++) {

		found = find_event_in_day(calendar, name, i, NULL);

		if(found == SUCCESS) {

			break;

		}

	}

	if(found == FAILURE) {

		return FAILURE;

	}

/* Delete Node from Linked List */

	curr = calendar->events[i - 1];

	while(curr != NULL && strcmp(curr->name, name) != 0) {

		prev = curr;
		curr = curr->next;

	}

	if(prev == NULL) {

		calendar->events[i - 1] = curr->next;

	} else {

		prev->next = curr->next;

	}

	if(curr->info != NULL && calendar->free_info_func != NULL) {

		calendar->free_info_func(curr->info);

	}

	free(curr->name);
	free(curr);

	calendar->total_events--;

	return SUCCESS;

}

/* Return a void pointer of information for event */

void *get_event_info(Calendar *calendar, const char *name) {

	Event *found;

/* Checking Conditions */

	if(find_event(calendar, name, &found) == FAILURE) {

		return NULL;

	} else {

		return found->info;

	}

} 

/* Clear the calendar by clearing each day */

int clear_calendar(Calendar *calendar) {

	int i;

/* Checking Conditions */

	if(calendar == NULL) {

		return FAILURE;

	}

/* Iterate through each day and clear each day */

	for(i = 1; i <= calendar->days; i++) {

		clear_day(calendar, i);

	}

	return SUCCESS;

}

/* Clear each day by calling remove event */

int clear_day(Calendar *calendar, int day) {

	Event *event, *temp;

/* Checking Conditions */

	if(calendar == NULL || day < 1 || day > calendar->days) {

		return FAILURE;

	}

	event = calendar->events[day - 1];

/* Using temp pointer to avoid using dangling pointers ad free mem */

	while(event != NULL) {

		temp = event->next;
		remove_event(calendar, event->name);
		event = temp;

	}

	return SUCCESS;

}	

/* Clear All memory related to caendar */

int destroy_calendar(Calendar *calendar) {

/* Checking Conditions */

	if(calendar == NULL) {

		return FAILURE;

	}	

/* Clear calendar first and then free all mem */

	clear_calendar(calendar);

	free(calendar->events);
	free(calendar->name);
	free(calendar);

	return SUCCESS;

}
