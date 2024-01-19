#include <stdio.h>
#include <string.h>
#include <math.h>
#include <stdlib.h>
#include <time.h>
int numRes = 2;
struct Restaurant
{
    char name[100];
    char ResAdd[100];
    char menu[5][50];
    float menuprice[5];
    float foodsertime[5];
    char ResSpecial[50];
    float ResSpecialPrice;
    float ResSpecialSertime;
    char DaySpecial[50];
    float DaySpecialPrice;
    float DaySpecialSertime;
};
struct Order
{
    char username[50];
    int userphone;
    char useraddress[100];
    char foodlist[50][50];
    int quantity[50];
    char ordertime[50];
    float delTime;
};
struct Restaurant Restaurants[2] = {
    {"res a",
     "abc, sitaburdi",
     {"xab", "ybc", "cd", "de", "ef"},
     {1.0, 2.0, 3.0, 4.0, 5.0},
     {11.0, 12.0, 13.0, 14.0, 15.0},
     "abc def",
     8.0,
     18.0,
     "zdef ghi",
     10.0,
     20.0},
    {"res b",
     "mno, sitaburdi",
     {"ab", "no", "cd", "pq", "ef"},
     {2.0, 3.0, 7.0, 5.0, 6.0},
     {12.0, 13.0, 17.1, 15.0, 16.0},
     "abc mno",
     18.0,
     28.0,
     "def pqr",
     12.0,
     22.0}};
void getMinTime(char fooditem[], int qty)
{
    for (int i = 0; i < numRes; i++)
    {
        for (int j = 0; j < 5; j++)
        {
            if (strcmp(fooditem, Restaurants[i].menu[j]) == 0)
            {
                printf("Restaurant Name:- %s\n", Restaurants[i].name);
                printf("Restaurant Address- %s\n", Restaurants[i].ResAdd);
                printf("Delivery Time %f Minutes\n", Restaurants[i].foodsertime[j] * qty);
            }
            else if (strcmp(fooditem, Restaurants[i].DaySpecial) == 0)
            {
                printf("Restaurant Name:- %s\n", Restaurants[i].name);
                printf("Restaurant Address- %s\n", Restaurants[i].ResAdd);
                printf("Delivery Time %f Minutes\n", Restaurants[i].DaySpecialSertime * qty);
            }
            else if (strcmp(fooditem, Restaurants[i].ResSpecial) == 0)
            {
                printf("Restaurant Name:- %s\n", Restaurants[i].name);
                printf("Restaurant Address- %s\n", Restaurants[i].ResAdd);
                printf("Delivery Time %f Minutes\n", Restaurants[i].ResSpecialSertime * qty);
            }
            else
            {
                printf("this food item is not in available in any restaurant");
            }
        }
    }
}
void getitemavailability(char fooditem[])
{
    for (int i = 0; i < numRes; i++)
    {
        for (int j = 0; j < 5; j++)
        {
            if (strcmp(fooditem, Restaurants[i].menu[j]) == 0)
            {
                printf("Restaurant Name:- %s\n", Restaurants[i].name);
                printf("Food Item Name:- %s\n", Restaurants[i].menu[j]);
                printf("Price:- %f\n", Restaurants[i].menuprice[j]);
                printf("___________________________________________");
            }
            else if (strcmp(fooditem, Restaurants[i].DaySpecial) == 0)
            {
                printf("Restaurant Name:- %s\n", Restaurants[i].name);
                printf("Food Item Name:- %s\n", Restaurants[i].ResAdd);
                printf("Price:- %f\n", Restaurants[i].DaySpecialPrice);
                printf("___________________________________________");
            }
            else if (strcmp(fooditem, Restaurants[i].ResSpecial) == 0)
            {
                printf("Restaurant Name:- %s\n", Restaurants[i].name);
                printf("Food Item Name:- %s\n", Restaurants[i].ResAdd);
                printf("Price:- %f\n", Restaurants[i].ResSpecialPrice);
                printf("___________________________________________");
            }
            else
            {
                printf("this food item is not in available in any restaurant");
            }
        }
    }
}
void placeorder(char fooditems[][50], int quantity[], char username[], int userphone, char useradd[])
{
    int orderID = rand();
    struct Order order;
    strcpy(order.username, username);
    order.userphone = userphone;
    strcpy(order.useraddress, useradd);
    int numitems = 5;
    float deltime = 0.0;
    for (int i = 0; i < numitems; i++)
    {
        strcpy(order.foodlist[i], fooditems[i]);
        order.quantity[i] = quantity[i];
    }
    for (int j = 0; j < numitems; j++)
    {
        for (int k = 0; k < numRes; k++)
        {
            for (int l = 0; l < 5; l++)
            {
                if (strcmp(fooditems[j], Restaurants[k].menu[l]) == 0)
                {
                    deltime+= quantity[j]*Restaurants[k].foodsertime[l];
                }
                else if (strcmp(fooditems[j], Restaurants[k].DaySpecial) == 0)
                {
                    deltime+= quantity[j]*Restaurants[k].DaySpecialSertime;
                }
                else if (strcmp(fooditems[j], Restaurants[k].ResSpecial) == 0)
                {
                    deltime+= quantity[j]*Restaurants[k].ResSpecialSertime;
                }
            }
        }
    }
    order.delTime = deltime;
    time_t t = time(NULL);
    strcpy(order.ordertime, ctime(&t));
}
void getItemListInSortedOrder(struct Restaurant Reslist)
{
    char temp[50];
    for(int i=0;i<4;i++)
    {
        for(int j=0;j<4-i;j++)
        {
            if(strcmp(Reslist.menu[j],Reslist.menu[j+1])>0)
            {
                strcpy(temp,Reslist.menu[j]);
                strcpy(Reslist.menu[j],Reslist.menu[j+1]);
                strcpy(Reslist.menu[j+1],temp);
            }
        }
    }
    printf("MENU:-\n");
    for (int k = 0; k < 5; k++)
    {
        printf("%s\n",Reslist.menu[k]);
    }
    
}
void getItemListInAreaSortedOrder(char Area[])
{
    for (int i = 0; i < numRes; i++)
    {
        char *p = strstr(Restaurants[i].ResAdd,Area);
        if(p != NULL)
        {
            printf("Restaurant: %s\n",Restaurants[i].name);
            getItemListInSortedOrder(Restaurants[i]);
            printf("today's special:\n");
            printf("%s\t%f\n", Restaurants[i].DaySpecial,Restaurants[i].DaySpecialPrice);
            printf("Restaurant's Special:\n");
            printf("%s\t%f\n", Restaurants[i].ResSpecial,Restaurants[i].ResSpecialPrice);
             printf("\n_____________________________\n");
        }
    }
}
// void getAllSpecialItemListinSortedOrder(struct Restaurant ResList[])
// {
//     for(int i=0;i<numRes-1;i++)
//     {
//         for(int j=0;j<numRes-i-1;j++)
//         {
//             if(strcmp(Reslist[j].menu,Reslist[j+1].menu)>0)
//             {
//                 strcpy(temp,Reslist[j].menu);
//                 strcpy(Reslist[j].menu,Reslist[j+1].menu);
//                 strcpy(Reslist[j+1],temp);
//             }
//         }
//     }
    
// } 
void getItemofDayListinSortedOrder(char Area[])
{
    struct Restaurant Reslist[numRes];
    int x=0;
    for (int i = 0; i < numRes; i++)
    {
        char *p = strstr(Restaurants[i].ResAdd,Area);
        if(p != NULL)
        {
            Reslist[x]=Restaurants[i];
            x++;
        }
    }
    struct Restaurant temp;
    for (int j = 0; j < x-1; j++)
    {
        for (int k = 0; k < x-j-1; k++)
        {
            if(strcmp(Reslist[k].DaySpecial,Reslist[k+1].DaySpecial)>0)
            {
                temp = Reslist[k];
                Reslist[k] = Reslist[k+1];
                Reslist[k+1] = temp;
            }
        }  
    }
    for (int l = 0; l < x; l++)
    {
        printf("Restaurant: %s\n",Reslist[l].name);
        printf("%s\t%f",Reslist[l].DaySpecial,Reslist[l].DaySpecialPrice);
        printf("\n_____________________________\n");
    }
}
void getCommonItem(struct Restaurant Reslist[])
{
    int f=0;
    for (int i = 0; i < numRes-1; i++)
    {
        for(int j = 0;j<5;j++)
        {
            for(int k=i+1;k<numRes;k++)
            {
                for (int l = 0; l < 5; l++)
                {
                    if(strcmp(Reslist[i].menu[j],Reslist[k].menu[l])==0)
                    {
                        printf("\n%s\t PRICE\n",Reslist[i].menu[j]);
                        printf("%s\t",Reslist[i].name);
                        printf("%f\t\n",Reslist[i].menuprice[j]);
                        printf("%s\t",Reslist[k].name);
                        printf("%f",Reslist[k].menuprice[l]);
                        printf("\n_____________________________\n");
                        f=1;
                    }
                }
                
            }
        }
    }
    if(f==0)
        printf("No items common in any restaurants");
}
void getAllUniqueItem(struct Restaurant ResList[])
{
    // printf("Day Unique Item\tRestaurent Unique Item\tRestaurant\tAddress");
    for (int i = 0; i < numRes; i++)
    {
        printf("Restaurant: %s\n",ResList[i].name);
        printf("Address: %s\n",ResList[i].ResAdd);
        printf("Today's Special: %s\t%f\n",ResList[i].DaySpecial,ResList[i].DaySpecialPrice);
        printf("Restaurant Special: %s\t%f",ResList[i].ResSpecial,ResList[i].ResSpecialPrice);
        printf("\n_____________________________\n");
    }
}
int main()
{
    char area[50] = "sitaburdi";
    getItemofDayListinSortedOrder(area);
}