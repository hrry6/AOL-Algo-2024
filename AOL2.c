#include <stdio.h>
#include <string.h>

typedef struct{
    char location1[30];
    char location2[30];
    int price;
    int room;
    int bathroom;
    int carPark;
    char type[30];
    char furnish[30];
} Hotel;

void displayData()
{
    int numberOfData;
    FILE *file = fopen("file.csv", "r");

    if(file == NULL)
    {
        printf("error");
        return;
    }

    printf("Number of rows: ");
    scanf("%d", &numberOfData);
    getchar();
    
    Hotel data[numberOfData];

    // Location 1,Location 2,Price,Rooms,Bathrooms,CarParks,Type,Furnish
    char category[8][20];
    
    fscanf(file,"%[^,],%[^,],%[^,],%[^,],%[^,],%[^,],%[^,],%s\n", category[0], category[1], category[2], category[3], category[4], category[5], category[6], category[7]);
    strcpy(category[0], "Location");
    strcpy(category[1], "City");

    for(int i = 0; i < numberOfData; i++)
    {
        if(fscanf(file, "%[^,],%[^,],%d,%d,%d,%d,%[^,],%s\n", 
                data[i].location1, data[i].location2, 
                &data[i].price,&data[i].room, &data[i].bathroom, &data[i].carPark, 
                data[i].type, data[i].furnish) != 8)
                {
                    numberOfData = i;
                    break;
                }
    }

    if(numberOfData > 0)
    {
        printf("Data found. Detail of data:\n");
        printf("%-15s %-15s %-15s %-10s %-10s %-10s %-10s %-10s\n", category[0], category[1], category[2], category[3], category[4], category[5], category[6], category[7]);

        for(int i = 0; i < numberOfData; i++)
        {
            printf("%-15s %-15s %-15d %-10d %-10d %-10d %-10s %-10s\n", data[i].location1, data[i].location2, data[i].price, data[i].room,data[i].bathroom, data[i].carPark, data[i].type, data[i].furnish);
        }
    }else
    {
        printf("Data not Found.");
    }

    printf("\n");
    fclose(file);
}

void searchData()
{
    int numberOfData = 0;
    char dataFind[20];
    char category[8][20], column[20], tempC[20];
    int categoryIndex = -1;
    Hotel data[1000], temp;
    FILE *file = fopen("file.csv", "r");

    if(file == NULL)
    {
        printf("error");
        return;
    }

    // Location 1,Location 2,Price,Rooms,Bathrooms,CarParks,Type,Furnish
    fscanf(file,"%[^,],%[^,],%[^,],%[^,],%[^,],%[^,],%[^,],%s\n", category[0], category[1], category[2], category[3], category[4], category[5], category[6], category[7]);
    strcpy(category[0], "Location");
    strcpy(category[1], "City");

    while(categoryIndex < 0 ||  categoryIndex > 7)
    {
        printf("Choose column: ");
        scanf("%[^\n]", column);
        getchar();

        for(int i = 0; i < 8; i++)
        {
            if(strcmp(column, category[i]) == 0)
            {
                categoryIndex = i;
                break;
            } 
        }
        if(categoryIndex < 0 ||  categoryIndex > 7) printf("Column not found\n");
    }

    printf("What data do you want to find? ");
    scanf("%s", dataFind);
    getchar();

    while(fscanf(file, "%[^,],%[^,],%d,%d,%d,%d,%[^,],%s\n", temp.location1, temp.location2, &temp.price,&temp.room, &temp.bathroom, &temp.carPark, temp.type, temp.furnish) == 8)
    {
        switch(categoryIndex)
        {
            case 0:
                if(strcmp(temp.location1, dataFind) == 0) data[numberOfData++] = temp;
                break;
            case 1:
                if(strcmp(temp.location2, dataFind) == 0) data[numberOfData++] = temp;
                break;
            case 2:
                sprintf(tempC, "%d", temp.price);
                if(strcmp(tempC, dataFind) == 0) data[numberOfData++] = temp;
                break;
            case 3:
                sprintf(tempC, "%d", temp.room);
                if(strcmp(tempC, dataFind) == 0) data[numberOfData++] = temp;
                break;
            case 4:
                sprintf(tempC, "%d", temp.bathroom);
                if(strcmp(tempC, dataFind) == 0) data[numberOfData++] = temp;
                break;
            case 5:
                sprintf(tempC, "%d", temp.carPark);
                if(strcmp(tempC, dataFind) == 0) data[numberOfData++] = temp;
                break;
            case 6:
                if(strcmp(temp.type, dataFind) == 0) data[numberOfData++] = temp;
                break;
            case 7:
                if(strcmp(temp.furnish, dataFind) == 0) data[numberOfData++] = temp;
                break;
        }
    }

    if(numberOfData > 0)
    {
        printf("Data found. Detail of data:\n");
        printf("%-15s %-15s %-15s %-10s %-10s %-10s %-10s %-10s\n", category[0], category[1], category[2], category[3], category[4], category[5], category[6], category[7]);

        for(int i = 0; i < numberOfData; i++)
        {
            printf("%-15s %-15s %-15d %-10d %-10d %-10d %-10s %-10s\n", data[i].location1, data[i].location2, data[i].price, data[i].room,data[i].bathroom, data[i].carPark, data[i].type, data[i].furnish);
        }
    } else
    {
        printf("Not Found");
    }

    printf("\n");

    fclose(file);
}

void sortData() {
    int numberOfData = 10000, categoryIndex = -1;
    FILE *file = fopen("file.csv", "r");
    char category[8][20], column[20], sortOption[5];
    Hotel data[numberOfData], temp;

    if (file == NULL) {
        printf("Error opening file.\n");
        return;
    }

    fscanf(file, "%[^,],%[^,],%[^,],%[^,],%[^,],%[^,],%[^,],%s\n",
           category[0], category[1], category[2],
           category[3], category[4], category[5],
           category[6], category[7]);

    strcpy(category[0], "Location");
    strcpy(category[1], "City");

    for (int i = 0; i < numberOfData; i++) {
        if (fscanf(file, "%[^,],%[^,],%d,%d,%d,%d,%[^,],%s\n",
                   data[i].location1,
                   data[i].location2,
                   &data[i].price,
                   &data[i].room,
                   &data[i].bathroom,
                   &data[i].carPark,
                   data[i].type,
                   data[i].furnish) != 8) {
            numberOfData = i;
            break;
        }
    }
    
    fclose(file);

    while (categoryIndex < 0 || categoryIndex > 7) {
        printf("Choose column: ");
        scanf("%[^\n]", column);
        getchar();

        for (int i = 0; i < 8; i++) {
            if (strcmp(category[i], column) == 0) {
                categoryIndex = i;
                break;
            }
        }

        if (categoryIndex < 0 || categoryIndex > 7)
            printf("Column not found\n");
    }

    while (strcmp(sortOption, "asc") != 0 && strcmp(sortOption, "desc") != 0) {
        printf("Sort ascending or descending? ");
        scanf("%s", sortOption);
        getchar();

        if (strcmp(sortOption, "asc") != 0 && strcmp(sortOption, "desc") != 0)
            printf("Error input\n");
    }


    for (int i = 0; i < numberOfData - 1; i++) {
        int swap = 0;
        for (int j = 0; j < numberOfData - i - 1; j++) {
            int condition = 0;

            switch (categoryIndex) {
                case 0:
                    condition = strcmp(data[j].location1, data[j + 1].location1);
                    break;
                case 1:
                    condition = strcmp(data[j].location2, data[j + 1].location2);
                    break;
                case 2:
                    condition = data[j].price - data[j + 1].price;
                    break;
                case 3:
                    condition = data[j].room - data[j + 1].room;
                    break;
                case 4:
                    condition = data[j].bathroom - data[j + 1].bathroom;
                    break;
                case 5:
                    condition = data[j].carPark - data[j + 1].carPark;
                    break;
                case 6:
                    condition = strcmp(data[j].type, data[j + 1].type);
                    break;
                case 7:
                    condition = strcmp(data[j].furnish, data[j + 1].furnish);
                    break;
            }

            if ((strcmp(sortOption, "asc") == 0 && condition > 0) ||
                (strcmp(sortOption, "desc") == 0 && condition < 0)) {
                temp = data[j];
                data[j] = data[j + 1];
                data[j + 1] = temp;
                swap = 1;
            }
        }
        
        if (swap == 0) break;
    }

    printf("Data found. Detail of data:\n");
    printf("%-15s %-15s %-15s %-10s %-10s %-10s %-10s %-10s\n",
           category[0], category[1],
           category[2], category[3],
           category[4], category[5],
           category[6], category[7]);
    
    for (int i = 0; i < 10; i++) {
        printf("%-15s %-15s %-15d %-10d %-10d %-10d %-10s %-10s\n",
               data[i].location1,
               data[i].location2,
               data[i].price,
               data[i].room,
               data[i].bathroom,
               data[i].carPark,
               data[i].type,
               data[i].furnish);
    }
}


void exportData()
{
    char fileName[20], category[8][20];
    printf("File name: ");
    scanf("%[^\n]", fileName);
    getchar();
    strcat(fileName, ".csv");

    FILE *fileRead = fopen("file.csv", "r");
    FILE *fileWrite = fopen(fileName, "w");


    while (fscanf(fileRead, "%[^,],%[^,],%[^,],%[^,],%[^,],%[^,],%[^,],%s\n", 
                  category[0], category[1], category[2], category[3], 
                  category[4], category[5], category[6], category[7]) == 8)
    {
        fprintf(fileWrite, "%s,%s,%s,%s,%s,%s,%s,%s\n", 
                category[0], category[1], category[2], category[3], 
                category[4], category[5], category[6], category[7]);
    }

    fclose(fileRead);
    fclose(fileWrite);
    printf("Data successfully written to file %s!\n", fileName);
}


int main()
{
    while(1)
    {
        int userChoice = 0;
        printf("What do you want to do?\n1. Display data\n2. Search Data\n3. Sort Data\n4. Export Data\n5. Exit\nYour choice: ");
        scanf("%d", &userChoice);
        getchar();
    
        if(userChoice == 1) displayData();
        else if(userChoice == 2) searchData();
        else if(userChoice == 3) sortData();
        else if(userChoice == 4) exportData();
        else if(userChoice == 5) break;
        else printf("Tolong masukkan nilai sesuai input");
                
        printf("\n");
    }
    return 0;
}