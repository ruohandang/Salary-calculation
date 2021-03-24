// This is a small program which could generate a weekly staff member
// earning report according to the informations from user's input
// It is designed by Ruohan Dang

// C libraries

#include <stdio.h>
#include <strings.h>


// Constant definitions

# define NAMELENGTH 15        // the namelength of first name or last name
# define PROJECTLENGTH 21     // the namelength of projrct name
# define OVERTIMERATE 1.5     // the overtime pay ratio
# define REGHOURS 40          // the regular hours during the period

// Global variable declarations

FILE *reportfile;             // output file

char project[PROJECTLENGTH];  // project name
char firstname[NAMELENGTH];   // first name of staff member
char lastname[NAMELENGTH];    // last name of staff member
char name [31];               // the display format of staff name in report

float RegWage;                // the hourly wage
float WorkHrs;                // totle hours worked per member
float RegHrs;                 //  regular hours worked
float OvertimeWage;           // overtime hourly wage
float OvertimeHrs;            // overtime hours worked
float gross;                  // income during the period
float total_RegHrs;           // accumulated - regular hours worked of all team members
float total_OvertimeHrs;      // accumulated - overtime hours worked of all team members
float PerOvertimeHrs;         // Percentage of Total Hours That Are Overtime
float total_RegWages;         // accumulated - total wages in regular hours of all member
float total_OvertimeWages;    // accumulated - total wages in overtime hours of all member
float total_Wages;            // accumulated - total wages of all member during the period

char answer;                  // answer to question about repeating the process
int count;                    // count of the number of conversation

// Function prototypes

void Process (void);          // includes information from the user input,
void Header (void);           // the header of the report, includes the project name
void Calculate (void);        // calculate the details that will display in report
void Summary (void);
int clear()  {
    while ((getchar())^'\n');
}

//*********************************************************
//                     MAIN FUNCTION
//*********************************************************

int main (void)
{
    reportfile = fopen("c:\\class\\rdang-er.txt", "w");    // out put the report

// Initialize accumulating variables

    count = 0;
    total_RegHrs = 0;
    total_OvertimeHrs = 0;
    total_RegWages = 0;
    total_OvertimeWages = 0;
    total_Wages = 0;

// Get information and Produce report

    Process();
    Summary();

    fclose(reportfile);
    return 0;
}

//-------------------------------------------------------------------------------------
// Process - Get information from the user input, produce header, details in the report
//-------------------------------------------------------------------------------------

void Process (void)
{

// Display some information and prompt user to input project name

    printf("NetworkHaus Information Technology, LLC\n");
    printf("Staff Earnings Report Generator\n\n");
    printf("Please enter the project name: ");
    gets(project);
    printf("\n\n");

// Header - prints a header on the report

    Header();

// Get information from user AND produces the detail line of the report to the disk file

    do {
        count++; // Increment the counting variable

        printf("Enter staff member #%d's first name: ", count);
        gets(firstname);
        printf("Enter staff member #%d's last name: ", count);
        gets(lastname);
        printf("Enter the hourly wage of %s %s: ", firstname, lastname);
        scanf("%f", &RegWage);
        printf("Enter total number of hours: ");
        scanf("%f", &WorkHrs);

        printf("\n");
        printf("Thank you. Process another employee? "); // ask for another time
        scanf("%s", &answer);
        clear();

        Calculate();

        fprintf(reportfile, "%-31s%4.1f ($%5.2f)%7.1f ($%5.2f)    $%7.2f\n", name, RegHrs, RegWage, OvertimeHrs, OvertimeWage, gross);

        printf("\n");


    } while (answer=='y' || answer=='Y' );

    printf("End of processing.\n");

}

//-----------------------------------------------
// Summary- - produce and report the summary part
//-----------------------------------------------

void Summary (void)
{

    fprintf(reportfile, "------------------------------------------------------------------------\n");
    fprintf(reportfile, "\n");
    fprintf(reportfile, "Total Regular Hours Worked: %-5.1f\n", total_RegHrs);
    fprintf(reportfile, "Total Overtime Hours Worked: %-5.1f\n", total_OvertimeHrs);
    fprintf(reportfile, "Percentage of Total Hours That Are Overtime: %4.1f%%\n", PerOvertimeHrs * 100);
    fprintf(reportfile, "\n");
    fprintf(reportfile, "Total Regular Wages: $%-8.2f\n", total_RegWages);
    fprintf(reportfile, "Total Overtime Wages: $%-8.2f\n", total_OvertimeWages);
    fprintf(reportfile, "\n");
    fprintf(reportfile, "Total Wages This Period: $%-8.2f\n", total_Wages);
}

// The header part of report, include a variable, so be called in function - process

void Header (void)
{
    fprintf(reportfile, "NetworkHaus Information Technology, LLC\n");
    fprintf(reportfile, "Weekly Staff Earnings Report\n");
    fprintf(reportfile, "\n");
    fprintf(reportfile, "Project: %s\n", project);
    fprintf(reportfile, "\n");
    fprintf(reportfile, "Staff Member                     Reg Hrs        Overtime Hrs       Gross\n");
    fprintf(reportfile, "------------------------------------------------------------------------\n");
}

// Calculate and produce details in report, be called in function - process

void Calculate (void)
{
        strcpy(name, lastname);
    strcat(name, ", ");
    strcat(name, firstname);


    if (WorkHrs <= REGHOURS) {
        RegHrs = WorkHrs;
        OvertimeHrs = 0;
    }
    else {
        RegHrs = REGHOURS;
        OvertimeHrs = WorkHrs - REGHOURS;
    }

    OvertimeWage = RegWage * OVERTIMERATE;

    gross = RegWage * RegHrs + OvertimeWage * OvertimeHrs;

    total_RegHrs = total_RegHrs + RegHrs;
    total_OvertimeHrs = total_OvertimeHrs + OvertimeHrs;

    PerOvertimeHrs = total_OvertimeHrs / ( total_RegHrs + total_OvertimeHrs);

    total_RegWages = total_RegWages + RegWage * RegHrs;
    total_OvertimeWages = total_OvertimeWages + OvertimeWage * OvertimeHrs;

    total_Wages = total_RegWages + total_OvertimeWages;
}
