/*==============================================================
| Write a program that asks the user for a 24-hour time. The program then displays the departure and arrival times for the flight whose departure time is closest to that entered by the user.
| Usage:  ./flight (then enter time in 24-hour format)
| Description of parameters:
|   hour:  hour of the day
|   minute:  minute of the time
|   quit: whether the user wants to quit
|   retval: return value of scanf
|   departure: departure time
|   arrival: arrival time
|   result: result of flight time
|   time: formatted time
----------------------------------------------------------------
*/

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

char *formatTime(int hour, int minute)
{
        char *time = malloc(6);
        if (hour < 12)
        {
                // Set 0 AM to 12 AM
                hour = hour == 0 ? 12 : hour;
                sprintf(time, "%d:%02d AM", hour, minute);
        }
        else
        {
                // Decrement 12 hours if PM
                hour = hour > 12 ? hour - 12 : hour;
                sprintf(time, "%d:%02d PM", hour, minute);
        }
        return time;
}

char **flightCheck(int hour, int minute)
{
        // Initialize departure and arrival times
        char departure[][8] = {"8:00", "9:43", "11:19", "12:47", "14:00", "15:45", "19:00", "21:45"};
        char arrival[][8] = {"10:16", "11:52", "13:31", "15:00", "16:08", "17:55", "21:20", "23:58"};
        char **result = malloc(2 * sizeof(char *));
        for (int i = 0; i < 8; i++)
        {
                // Split departure time into hour and minute
                int dHour = atoi(strtok(departure[i], ":"));
                int dMinute = atoi(strtok(NULL, ":"));
                int aHour = atoi(strtok(arrival[i], ":"));
                int aMinute = atoi(strtok(NULL, ":"));
                // Check if there is a flight that departs at or after the given time
                if (hour < dHour || (hour == dHour && minute < dMinute))
                {
                        result[0] = formatTime(dHour, dMinute);
                        result[1] = formatTime(aHour, aMinute);
                        return result;
                }
        }
        // If no flight is found, return empty array
        return result;
}

int main(void)
{
        int hour, minute, quit = 0, retval = 0;
        // while user does not want to quit
        while (!quit)
        {
                printf("Enter a time in 24-hour format: ");
                // Check for valid input
                if ("%d", scanf("%d:%d", &hour, &minute) != 2)
                {
                        printf("Invalid time format.\n");
                }
                // Check if flight is available
                if (flightCheck(hour, minute)[0] != NULL)
                {
                        printf("Closest departure time is %s, arriving at %s\n", flightCheck(hour, minute)[0], flightCheck(hour, minute)[1]);
                }
                else
                {
                        printf("No flight available.\n");
                }
                printf("Enter 1 to quit, 0 to continue: ");
                // Fix infinite loop caused by EOF
                // https://stackoverflow.com/questions/27616286/how-can-i-continue-the-loop-when-i-give-scanf-a-non-digit-as-input
                retval = scanf("%d", &quit);
                if (retval == 0)
                {
                        while (getchar() != '\n');
                        continue;
                }
        }
}
