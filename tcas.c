#include <stdlib.h>
#include <stdio.h>

int Cur_Vertical_Sep;
int High_Confidence;
int Two_of_Three_Reports_Valid;
int Own_Tracked_Alt;
int Own_Tracked_Alt_Rate;
int Other_Tracked_Alt;
int Alt_Layer_Value;
int Up_Separation;
int Down_Separation;
int Other_RAC;
int Other_Capability;
int Climb_Inhibit;

int Positive_RA_Alt_Thresh_0;
int Positive_RA_Alt_Thresh_1;
int Positive_RA_Alt_Thresh_2;
int Positive_RA_Alt_Thresh_3;

void print_args() {
    printf("\nargs: ");
    printf("%d\n", Cur_Vertical_Sep);
    printf(" ");
    printf("%d\n", High_Confidence);
    printf(" ");
    printf("%d\n", Two_of_Three_Reports_Valid);
    printf(" ");
    printf("%d\n", Own_Tracked_Alt);
    printf(" ");
    printf("%d\n", Own_Tracked_Alt_Rate);
    printf(" ");
    printf("%d\n", Other_Tracked_Alt);
    printf(" ");
    printf("%d\n", Alt_Layer_Value);
    printf(" ");
    printf("%d\n", Up_Separation);
    printf(" ");
    printf("%d\n", Down_Separation);
    printf(" ");
    printf("%d\n", Other_RAC);
    printf(" ");
    printf("%d\n", Other_Capability);
    printf(" ");
    printf("%d\n", Climb_Inhibit);
    printf(" ");
    printf("\n");
}

int Own_Below_Threat()
{
    return (Own_Tracked_Alt < Other_Tracked_Alt);
}

int Own_Above_Threat()
{
    return (Other_Tracked_Alt < Own_Tracked_Alt);
}

void initialize()
{
    High_Confidence = 32767;
    Other_Capability = 0;
    
    Climb_Inhibit = 1;
    Cur_Vertical_Sep = 16684;
    Own_Tracked_Alt_Rate = 450;
    
    Positive_RA_Alt_Thresh_0 = 16434;
    Positive_RA_Alt_Thresh_1 = 0;
    Positive_RA_Alt_Thresh_2 = 0;
    Positive_RA_Alt_Thresh_3 = 0;
}

int Positive_RA_Alt_Thresh(int Alt)
{
    int res = 0;
    //printf("in Positive_RA_Alt_Thresh\n");

    if(Alt == 0) {
        res = Positive_RA_Alt_Thresh_0;
        //printf("branch 0\n");
    }
    else if(Alt == 1) {
        res = Positive_RA_Alt_Thresh_1;
        //printf("branch 1\n");

    }
    else if( Alt == 2) {
        res = Positive_RA_Alt_Thresh_2;
        //printf("branch 2\n");
    }
    else if(Alt == 3) {
        res = Positive_RA_Alt_Thresh_3;
        //printf("branch 3\n");
    }
    return res;
}

int ALIM ()
{
    return Positive_RA_Alt_Thresh(Alt_Layer_Value);
}

int Inhibit_Biased_Climb ()
{
    return Climb_Inhibit ? Up_Separation + 100 : Up_Separation;
}

int Non_Crossing_Biased_Climb()
{
    int upward_preferred;
    int upward_crossing_situation;
    int result;
    
    upward_preferred = Inhibit_Biased_Climb() > Down_Separation;

    if (upward_preferred)
    {
        result = !(Own_Below_Threat()) || ((Own_Below_Threat()) && (!(Down_Separation >= ALIM())));
        printf("#1 A: %d B: %d\n", Own_Below_Threat(), (Down_Separation >= ALIM()));
    }
    else
    {
        result = Own_Above_Threat() && (Cur_Vertical_Sep >= 300 ) && (Up_Separation >= ALIM());
            printf("#2 A: %d B: %d C: %d\n", Own_Above_Threat(), (Cur_Vertical_Sep >= 300),  (Up_Separation >= ALIM()));
    }
    
    return result;
}

int Non_Crossing_Biased_Descend()
{
    int upward_preferred;
    int upward_crossing_situation;
    int result;
    
    upward_preferred = Inhibit_Biased_Climb() > Down_Separation;
    
    if (upward_preferred)
    {
        result = Own_Below_Threat() && (Cur_Vertical_Sep >= 300) && (Down_Separation >= ALIM());
        printf("#3 A: %d B: %d C: %d\n", Own_Below_Threat(), (Cur_Vertical_Sep >= 300), (Down_Separation >= ALIM()));
    }
    else
    {
        result = !(Own_Above_Threat()) || ((Own_Above_Threat()) && (Up_Separation >= ALIM()));
        printf("#4 A: %d B: %d C: %d\n", !(Own_Above_Threat()), ((Own_Above_Threat()), (Up_Separation >= ALIM())));
    }
    
    return result;
}

int alt_sep_test()
{
    int enabled, tcas_equipped, intent_not_known;
    int need_upward_RA = 0;
    int need_downward_RA = 0;
    
    int alt_sep;
    
    enabled = High_Confidence && (Own_Tracked_Alt_Rate <= 600) && (Cur_Vertical_Sep > 600);
    printf("#5 A: %d B: %d C: %d\n", High_Confidence, (Own_Tracked_Alt_Rate <= 600), (Cur_Vertical_Sep > 600));
    tcas_equipped = Other_Capability == 1 ;
    intent_not_known = Two_of_Three_Reports_Valid && Other_RAC == 0 ;
    printf("#6 A: %d B: %d\n", Two_of_Three_Reports_Valid, Other_RAC == 0);
    
    alt_sep = 0 ;
    
    printf("#9 A: %d B: %d C: %d\n", enabled, tcas_equipped, intent_not_known);
    if (enabled && ((tcas_equipped && intent_not_known) || !tcas_equipped))
    {
        need_upward_RA = Non_Crossing_Biased_Climb() && Own_Below_Threat();
        printf("#7 A: %d B: %d\n", Non_Crossing_Biased_Climb(), Own_Below_Threat());

        need_downward_RA = Non_Crossing_Biased_Descend() && Own_Above_Threat();
        printf("#8 A: %d B: %d\n", Non_Crossing_Biased_Descend(), Own_Above_Threat());
        
        if(need_upward_RA && need_downward_RA) {
            // i think this is unreachable
            alt_sep = 0;
        }
        else {
            if (need_upward_RA) {
                alt_sep = 1;
            }
            else if (need_downward_RA) {
                alt_sep = 2;
            }
            else {
                alt_sep = 0 ;
            }
        }
    }
    
    return alt_sep;
}

int main(int argc, char *argv[])
{
    if(argc < 13)
    {
        fprintf(stderr, "Error: Command line arguments are\n");
        fprintf(stderr, "Cur_Vertical_Sep, High_Confidence, Two_of_Three_Reports_Valid\n");
        fprintf(stderr, "Own_Tracked_Alt, Own_Tracked_Alt_Rate, Other_Tracked_Alt\n");
        fprintf(stderr, "Alt_Layer_Value, Up_Separation, Down_Separation\n");
        fprintf(stderr, "Other_RAC, Other_Capability, Climb_Inhibit\n");
        exit(1);
    }
    initialize();
    Cur_Vertical_Sep = atoi(argv[1]);
    High_Confidence = atoi(argv[2]);
    Two_of_Three_Reports_Valid = atoi(argv[3]);
    Own_Tracked_Alt = atoi(argv[4]);
    Own_Tracked_Alt_Rate = atoi(argv[5]);
    Other_Tracked_Alt = atoi(argv[6]);
    Alt_Layer_Value = atoi(argv[7]);
    Up_Separation = atoi(argv[8]);
    Down_Separation = atoi(argv[9]);
    Other_RAC = atoi(argv[10]);
    Other_Capability = atoi(argv[11]);
    Climb_Inhibit = atoi(argv[12]);

    fprintf(stderr, "%d\n", alt_sep_test());
}
