#include <iostream>
#include <stdlib.h>
#include <cstring>
#include <iomanip>
#include <conio.h>
#include <fstream>
#pragma warning(disable : 4996)
using namespace std;
struct Phone
{
    char Name[15];
    char Group[15];
    char Tel[12];
    Phone* next;
};
Phone* Start_ptr = NULL;
Phone* current = NULL;
void Select(int);       // which choice user select
void Add_new();
void Print_all();
void Menu1();
void Menu2();
void Edit_current();
void Delete_current();
void Tel_or_name(int);
void Write_to_file();
void Sort_name(int);
Phone* Search(char*, int);
enum MENU { ADD = 1, SEARCH_NAME, SEARCH_NO, SORT_NAME, SORT_FAMIL, SHOW_ALL, SAVE, EXIT };
int main()
{
    int choice;
    do
    {
        Menu1();
        cin >> choice;
        system("cls");
        Select(choice);
    } while (choice != EXIT);
    Write_to_file();
    cout << "Thank you" << endl;
}
/*===================Select=======================*/
void Select(int choose)
{
    switch (choose)
    {
    case ADD:
        Add_new();
        break;
    case SEARCH_NAME:
        Tel_or_name(1);
        break;
    case SEARCH_NO:
        Tel_or_name(2);
        break;
    case SORT_NAME:
        Sort_name(1);
        break;
    case SORT_FAMIL:
        Sort_name(2);
        break;
    case SHOW_ALL:
        Print_all();
        break;
    case SAVE:
        Write_to_file();
        cout << "Data will be saved automatically when your work finished." << endl;
        getch();
        break;
    case EXIT:
        return;
    default:
        cout << "Select again :" << endl;
    }
    return;
}
/*====================Main_Menu=======================*/
void Menu1()
{
    system("cls");
    cout << "1.  Add New Phone"
        << "\n2.  Search for Name"
        << "\n3.  Search for Number"
        << "\n4.  Sort by Name"
        << "\n5.  Sort by Group"
        << "\n6.  Show all list"
        << "\n7.  Save data"
        << "\n8.  Exit"
        << "\n\nYour choice : ";
}
/*=================Add_new=====================*/
void Add_new()
{
    Phone* temp = new Phone;
    Phone* temp2 = Start_ptr;
    system("cls");
    cout << "Enter the name : ";
    cin >> temp->Name;
    cout << "Group : ";
    cin >> temp->Group;
    cout << "Phone number : ";
    cin >> temp->Tel;
    temp->next = NULL;
    if (Start_ptr == NULL)
    {
        Start_ptr = temp;
    }
    else
    {
        while (temp2->next != NULL)
        {
            temp2 = temp2->next;
        }
        temp2->next = temp;
    }
    return;
}
/*==============Print_all=======================*/
void Print_all()
{
    Phone* temp = Start_ptr;
    char show[200];
    if (Start_ptr == NULL)
    {
        cout << "No contact(s) has been added !" << endl;
        getch();
        return;
    }
    else
    {
        cout << "\nName               Group             Phone       "
            << "\n____________    _____________     ______________" << endl;
        do
        {
            strcpy(show, "");
            strcat(show, temp->Name);
            strcat(show, "             ");
            strcat(show, temp->Group);
            strcat(show, "            ");
            strcat(show, temp->Tel);
            show[0] = toupper(show[0]);
            cout << show << endl;
            temp = temp->next;
        } while (temp != NULL);
    }
    getch();
}
/*=================Search=======================*/
Phone* Search(char* temp_search, int choice)
{
    if (Start_ptr == NULL)      //if list is empty
    {
        cout << "No contact(s) has been added !" << endl;
        return NULL;
    }
    /* Search by name */
    if (choice == 1)
    {
        while (current != NULL && strcmp(current->Name, temp_search) != 0)
        {
            current = current->next;
        }
    }
    /* Search by tel */
    if (choice == 2)
    {
        while (current != NULL && strcmp(current->Tel, temp_search) != 0)
        {
            current = current->next;
        }
    }
    if (current != NULL)   //if record found
    {
        cout << "Record found" << endl
            << current->Name << " " << "(" << current->Group << ")" << " : " << current->Tel << endl;
        return current;
    }
    else     //if record not found
    {
        cout << "Record NOT found" << endl;
        current = Start_ptr;
        return NULL;
    }
}
/*====================Delete_current====================*/
void Delete_current()
{
    Phone* temp = NULL;
    Phone* prev = NULL;
    if (current == Start_ptr)     // if it's the first node
    {
        temp = Start_ptr;
        Start_ptr = Start_ptr->next;   //if we have only one node, start_ptr will point to NULL
        delete temp;
        temp = NULL;
    }
    else             //if it's in the middle of list or the last node
    {
        prev = Start_ptr;
        while (prev->next != current)
        {
            prev = prev->next;
        }
        prev->next = current->next;       // if it's the last node prev will point to NULL
        delete current;
        current = Start_ptr;
    }
}
/*=================Tel_or_name================*/
void Tel_or_name(int choose)
{
    Phone* temp_del = NULL;
    char temp_search[15];
    int choice;
    current = Start_ptr;
    cout << "Enter the " << (choose == 1 ? "name" : "tel") << " to search : ";
    cin >> temp_search;
    temp_del = Search(temp_search, choose);
    while (temp_del != NULL)
    {
        Menu2();
        cin >> choice;
        switch (choice)
        {
        case 1: current = current->next;
            temp_del = Search(temp_search, choose); break;
        case 2: Delete_current(); break;
        case 3: Edit_current();   break;
        case 4: return;
        }
    }
    getch();
}
/*====================Sub-menu=======================*/
void Menu2()
{
    cout << "\n1.  Find next"
        << "\n2.  Delete current person"
        << "\n3.  Edit current person"
        << "\n4.  continue" << endl
        << "\nYour choice : ";
}
/*==============Edit_Current_Contact=============================*/
void Edit_current()
{
    strcpy(current->Name, "");
    strcpy(current->Group, "");
    cout << "Enter the name : ";
    cin >> current->Name;
    cout << "Family : ";
    cin >> current->Group;
    cout << "Phone number : ";
    cin >> current->Tel;
    system("cls");
}
/*==============Write_to_file=============================*/
void Write_to_file()
{
    Phone* temp = Start_ptr;
    ofstream outFile("Data.dat", ios::out);
    if (!outFile)
    {
        cerr << "Error ocured during writing to file." << endl;
        getch();
    }
    while (temp != NULL)
    {
        outFile << temp->Name << " " << temp->Group << " " << temp->Tel;
        if (temp->next != NULL)
        {
            outFile << endl;
        }
        temp = temp->next;
    }
    outFile.close();
    cout << "Data saved successfully." << endl;
}
/*================Sort_name=================================*/
void Sort_name(int choice)
{
    if (Start_ptr == NULL)
    {
        cout << "The contact list is empty!" << endl;
    }
    int counter = 1;      //to determine the size of list
    Phone* temp = Start_ptr;
    while (temp->next != NULL)
    {
        temp = temp->next;
        counter++;
    }
    Phone* sort[1000];
    sort[0] = Start_ptr;
    for (int cnt = 1; cnt < counter; cnt++)
    {
        sort[cnt] = sort[cnt - 1]->next;
    }
    sort[counter] = NULL;
    /* bubble sort */
    for (int i = 0; i < counter; i++)
    {
        for (int j = 0; j < counter - i - 1; j++)
        {
            /* Sort by name */
            if (choice == 1)
            {
                if (strcmp(sort[j]->Name, sort[j + 1]->Name) > 0)
                {
                    Phone* temp2 = sort[j];
                    sort[j] = sort[j + 1];
                    sort[j + 1] = temp2;
                }
            }
            /* Sort by family */
            else
            {
                if (strcmp(sort[j]->Group, sort[j + 1]->Group) > 0)
                {
                    Phone* temp2 = sort[j];
                    sort[j] = sort[j + 1];
                    sort[j + 1] = temp2;
                }
            }
        }
    }
    /* Showing sorted list */
    char show[100];
    int index = 0;
    cout << "\nName                    Group                  Phone       "
        << "\n_____________     _____________________     ________________" << endl;
    do
    {
        strcpy(show, "");
        strcat(show, sort[index]->Name);
        strcat(show, "                     ");
        strcat(show, sort[index]->Group);
        strcat(show, "                        ");
        strcat(show, sort[index]->Tel);
        show[0] = toupper(show[0]);
        cout << show << endl;
        index++;
    } while (sort[index] != NULL);
    getch();
}