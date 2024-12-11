/******************
Name:
ID:
Assignment: ex3
*******************/

#include <stdio.h>
#include <stdlib.h>

#define NUM_OF_BRANDS 5
#define BRANDS_NAMES 15
#define NUM_OF_TYPES 4
#define TYPES_NAMES 10
#define DAYS_IN_YEAR 365
#define addOne  1
#define addAll  2
#define stats  3
#define print  4
#define insights  5
#define deltas  6
#define done  7


char brands[NUM_OF_BRANDS][BRANDS_NAMES] = {"Toyoga", "HyunNight", "Mazduh", "FolksVegan", "Key-Yuh"};
char types[NUM_OF_TYPES][TYPES_NAMES] = {"SUV", "Sedan", "Coupe", "GT"};

void printMenu();
void initializeValues(int arr[DAYS_IN_YEAR][NUM_OF_BRANDS][NUM_OF_TYPES]);
void insertDATA(int days[], int cube[DAYS_IN_YEAR][NUM_OF_BRANDS][NUM_OF_TYPES], int daysCounter);
void carBrandEmpty(int cube[DAYS_IN_YEAR][NUM_OF_BRANDS][NUM_OF_TYPES], int days[NUM_OF_BRANDS], int daysCount);
void brandByIndex(int index);
void typeByIndex(int index);
void printCase(int cube[DAYS_IN_YEAR][NUM_OF_BRANDS][NUM_OF_TYPES], int daysCounter);
int delta(int brand, int daysCounter, int cube[DAYS_IN_YEAR][NUM_OF_BRANDS][NUM_OF_TYPES]);

int main() {
    int cube[DAYS_IN_YEAR][NUM_OF_BRANDS][NUM_OF_TYPES];
    initializeValues(cube);
    int daysCounter = 1;
    int days[NUM_OF_BRANDS] = {0};
    int choice;
    printMenu();
    scanf(" %d", &choice);
    while(choice != done){
        switch(choice){
            case addOne:
                insertDATA(days,cube,daysCounter);
            break;

            case addAll:
                //Checking as long as there is a brand for which it has not been updated for that day
                //will activate the operation of entering the data and the operation of which brands are missing
                for (int i = 0; i < NUM_OF_BRANDS; i++) {
                    while (days[i]!=daysCounter) {
                        carBrandEmpty(cube,days,daysCounter);
                        insertDATA(days,cube,daysCounter);
                    }
                }
            //After everything is filled, we will upload our super days if it is not the last day that will not cause an explosion
            if (daysCounter<DAYS_IN_YEAR-1) {
                daysCounter++;
            }


            break;

            case stats:
                printf("What day would you like to analyze?\n");
                int number;
            scanf(" %d", &number);
            // Checking that the input meets the request
            while (number<=0 || number>(DAYS_IN_YEAR-1) || number>=daysCounter) {
                printf("Please enter a valid day.\n");
                printf("Which day would you like to analyze?\n");
                scanf(" %d", &number);
            }
            int sum =0;
            // Calculation of the total amount of all tapes of each brand on the requested day
                for (int i = 0; i < NUM_OF_BRANDS; i++) {
                    for (int j = 0; j < NUM_OF_TYPES; j++) {
                        sum = sum + cube[number][i][j];
                    }
                }
            printf("In day number %d:\n",number);
            printf("The sales total was %d\n",sum);
            int maxBrand = 0;
            int indexMax = 0;
            int newSumBrand = 0;
            for (int i = 0; i < NUM_OF_BRANDS; i++) {
                newSumBrand = 0;
                for (int j = 0; j < NUM_OF_TYPES; j++) {
                    // A scheme of the tapes of a certain brand
                    newSumBrand = newSumBrand + cube[number][i][j];
                }
                // If the amount of the tip is greater than the maximum amount, apply it
                if (newSumBrand>maxBrand) {
                    maxBrand = newSumBrand;
                    indexMax = i;
                }
            }
            printf("The best sold brand with %d sales was ",maxBrand);
            brandByIndex(indexMax);
            printf("\n");
            int maxType = 0;
            int indexMaxT = 0;
            int newSumType = 0;
            for (int i = 0; i < NUM_OF_TYPES; i++) {
                newSumType = 0;
                for (int j = 0; j < NUM_OF_BRANDS; j++) {
                    // Scheme of the brand of a certain tape
                    newSumType = newSumType + cube[number][j][i];
                }
                // If the amount of the brand is greater than the maximum amount, apply it
                if (newSumType>maxType) {
                    maxType = newSumType;
                    indexMaxT = i;
                }
            }
            printf("The best sold type with %d sales was ",maxType);
            typeByIndex(indexMaxT);
            printf("\n");
            break;

            case print:
                printf("*****************************************\n\n");
            printCase(cube,daysCounter);
            printf("\n*****************************************\n");
            break;

            case insights:
                int brandPrice = 0;
            int brandIndex = 0;
            int maxBrandPrice = 0;
            int typePrice = 0;
            int typeIndex = 0;
            int  maxTypePrice = 0;
            int dayPrice = 0;
            int dayIndex = 0;
            int dayMaxPrice = 0;
            for (int i = 0; i < NUM_OF_BRANDS; i++) {
                for (int j = 1; j < DAYS_IN_YEAR; j++) {
                    if (j == daysCounter)
                        break;
                    for (int k = 0; k < NUM_OF_TYPES; k++) {
                        brandPrice = brandPrice + cube[j][i][k];
                    }
                }
                if (brandPrice>maxBrandPrice) {
                    maxBrandPrice = brandPrice;
                    brandIndex = i;
                }
                brandPrice = 0;
            }
            for (int i = 0; i < NUM_OF_TYPES; i++) {
                for (int j = 1; j < DAYS_IN_YEAR; j++) {
                    if (j == daysCounter)
                        break;
                    for (int k = 0; k < NUM_OF_BRANDS; k++) {
                        typePrice = typePrice + cube[j][k][i];
                    }
                }
                if (typePrice>maxTypePrice) {
                    maxTypePrice = typePrice;
                    typeIndex = i;
                }
                typePrice = 0;
            }
            for (int i = 1; i < DAYS_IN_YEAR; i++) {
                if (i==daysCounter)
                    break;
                for (int j = 0; j < NUM_OF_BRANDS; j++) {
                    for (int k = 0; k < NUM_OF_TYPES; k++) {
                        dayPrice = dayPrice + cube[i][j][k];
                    }
                }
                if (dayPrice>dayMaxPrice) {
                    dayMaxPrice = dayPrice;
                    dayIndex = i;
                }
                dayPrice = 0;
            }
            printf ("The best-selling brand overall is ");
            brandByIndex(brandIndex);
            printf(": %d$\n",maxBrandPrice);
            printf ("The best-selling type of car is ");
            typeByIndex(typeIndex);
            printf(": %d$\n",maxTypePrice);
            printf ("The most profitable day was day number %d",dayIndex);
            printf(": %d$\n",dayMaxPrice);

            break;

            case deltas:
                delta(0,daysCounter,cube);
            delta(1,daysCounter,cube);
            delta(2,daysCounter,cube);
            delta(3,daysCounter,cube);
            delta(4,daysCounter,cube);
                break;

            default:
                printf("Invalid input\n");
        }
        printMenu();
        scanf(" %d", &choice);
    }
    printf("Goodbye!\n");
    return 0;
}




void printMenu(){
    printf("Welcome to the Cars Data Cube! What would you like to do?\n"
           "1.Enter Daily Data For A Brand\n"
           "2.Populate A Day Of Sales For All Brands\n"
           "3.Provide Daily Stats\n"
           "4.Print All Data\n"
           "5.Provide Overall (simple) Insights\n"
           "6.Provide Average Delta Metrics\n"
           "7.exit\n");
}
void initializeValues(int arr[DAYS_IN_YEAR][NUM_OF_BRANDS][NUM_OF_TYPES]) {
    for (int i = 0; i < DAYS_IN_YEAR; i++) {
        for (int j = 0; j < NUM_OF_BRANDS; j++) {
            for (int k = 0; k < NUM_OF_TYPES; k++) {
                arr[i][j][k] = -1;
            }
        }
    }
}
void insertDATA(int days[], int cube[DAYS_IN_YEAR][NUM_OF_BRANDS][NUM_OF_TYPES],int daysCounter) {
    int carBrand, sumSUV, sumSedan, sumCoupe, sumGT;
    scanf(" %d %d %d %d %d", &carBrand, &sumSUV, &sumSedan, &sumCoupe, &sumGT);
    // Checking if the brand's index meets the criteria
    if (0>carBrand || carBrand>4) {
        printf("This brand is not valid\n");
        return;
    }
    // Checking if there is already a value at this location
    for (int i = 0; i < NUM_OF_TYPES; i++) {
        if (cube[daysCounter][carBrand][i]!=-1) {
            printf("This brand is not valid\n");
            return;
        }
    }

    // Placement of the values we received after everything is good 0-3 as the amount of tapes
    cube[daysCounter][carBrand][0] = sumSUV;
    cube[daysCounter][carBrand][1] = sumSedan;
    cube[daysCounter][carBrand][2] = sumCoupe;
    cube[daysCounter][carBrand][3] = sumGT;
    // If we have successfully filled any brand we will raise it by one, but we know that it does not pass the original day
    if (days[carBrand]<daysCounter) {
        days[carBrand]++;
    }
    return;
}
void carBrandEmpty(int cube[DAYS_IN_YEAR][NUM_OF_BRANDS][NUM_OF_TYPES],int days[NUM_OF_BRANDS],int daysCount) {
    printf("No data for brands ");
    for (int i = 0 ; i < NUM_OF_BRANDS; i++) {
        // Checking if there is any brand day that is not as much as the normal day
            if (days[i]!=daysCount) {
                // If it was when i is zero then Toyoga is the missing one if it was in 2 then Unite is missing and so on
                //printf("%s ",brands[i]); i dont sure if i was allowed to use that
                if (i==0) {
                    printf("Toyoga ");
                }
                if (i==1) {
                    printf("HyunNight ");
                }
                if (i==2) {
                    printf("Mazduh ");
                }
                if (i==3) {
                    printf("FolksVegan ");
                }
                if (i==4) {
                    printf("Key-Yuh\n ");
                }
        }
    }
    printf("\nPlease complete the data. \n");
}
void brandByIndex(int index) {
    if (index==0)
        printf("Toyoga ");
    if (index==1)
        printf("HyunNight ");
    if (index==2)
        printf("Mazduh ");
    if (index==3)
        printf("FolksVegan ");
    if (index==4)
        printf("Key-Yuh");
}
void typeByIndex(int index) {
    if (index==0)
        printf("SUV");
    if (index==1)
        printf("Sedan");
    if (index==2)
        printf("Coupe");
    if (index==3)
        printf("GT");
}
void printCase(int cube[DAYS_IN_YEAR][NUM_OF_BRANDS][NUM_OF_TYPES],int daysCounter) {
        if (1==daysCounter) //If the days have just started then they are blank so there is no need to print anything
            return;
    for (int i = 0; i < NUM_OF_BRANDS; i++) {
        printf("sales for "); brandByIndex(i); printf(":\n");
        for (int j = 1; j < DAYS_IN_YEAR; j++) {
            printf("Day %d- ", j);
            for (int k = 0; k < NUM_OF_TYPES; k++) {
                typeByIndex(k); printf(": %d ",cube[j][i][k]);
            }
            printf("\n");
            if (j==daysCounter-1) //If I've reached the end of days to continue to the next brand
                break;
        }
        printf("\n");
    }
}
int delta (int brand,int daysCounter,int cube[DAYS_IN_YEAR][NUM_OF_BRANDS][NUM_OF_TYPES]) {
    int sumDay1 = 0;
    int sumDay2 = 0;
    int diffDays = 0;
    int count = 0;
    // First day test
            for (int k = 0; k < NUM_OF_TYPES; k++) {
                sumDay1 = sumDay1 + cube[1][brand][k];
            }
    // Checking the rest of the days and sensing the difference between each two
        for (int j = 2; j < DAYS_IN_YEAR; j++) {
            if (j==daysCounter)
                break;
            for (int k = 0; k < NUM_OF_TYPES; k++) {
                sumDay2 = sumDay2 + cube[j][brand][k];
            }
            count++;
            diffDays = diffDays + sumDay2 - sumDay1;
            sumDay1 = sumDay2;
            sumDay2 = 0;
        }
    printf("Brand:"); brandByIndex(brand); printf(", Average Delta: %f\n",(float)(diffDays)/(float)count);
}

