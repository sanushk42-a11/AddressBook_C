#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "contact.h"
#include "file.h"
#include "populate.h"

void listContacts(AddressBook *addressBook) 
{
    for(int i= 0;i<addressBook->contactCount;i++)
    {
            printf("Name  : %s\n",addressBook->contacts[i].name);
            printf("Phone : %s\n",addressBook->contacts[i].phone);
            printf("Email : %s\n",addressBook->contacts[i].email);
            printf("----------------------------------------------------------------\n");
    } 
}

void initialize(AddressBook *addressBook)
{
    addressBook->contactCount = 0;
    // populateAddressBook(addressBook);

    // Load contacts from file during initialization (After files)
    loadContactsFromFile(addressBook);
}

  
void saveAndExit(AddressBook *addressBook)
{
    saveContactsToFile(addressBook);// Save contacts to file

    printf("Contacts saved successfully\n");// Exit the program

    exit(EXIT_SUCCESS);
}


void createContact(AddressBook *addressBook)
{
	/* Define the logic to create a Contacts */
	int flag;
	printf("Enter the Name : ");
	do
	{
	 flag=0;
        scanf(" %[^\n]", addressBook->contacts[addressBook->contactCount].name);
        flag = validate_name(addressBook->contacts[addressBook->contactCount].name);
	if(flag == 0)
	{
	printf("The entered name is not valid,Please enter the correct name : ");	
	}
	}while(flag == 0);
    printf("Enter thr Phone number : ");	
    do
    {
	flag=0;
     scanf(" %[^\n]", addressBook->contacts[addressBook->contactCount].phone);
        flag = validate_phone(addressBook->contacts[addressBook->contactCount].phone,addressBook);
         if(flag == 1)
         {
        printf("The entered phone number is not having 10 digits,Please enter the 10 digits number : ");
         }
	 if(flag == 2)
         {
         printf("The entered number containing non digit chars,,Please enter the proper 10 digits number : ");
         }
	 if(flag == 3)
          {
          printf("The entered number is already present,,Please enter the unique number : ");
    }
         }while(flag != 0);	
	printf("Enter the email : ");
do
{
    flag = 0;
    scanf(" %[^\n]", addressBook->contacts[addressBook->contactCount].email);

    flag = validate_email(addressBook->contacts[addressBook->contactCount].email,addressBook);

    if(flag == 1)
    {
        printf("The email should contain only one @, please enter the correct email : ");
    }

    if(flag == 2)
    {
        printf("The email should have characters before @, please enter the correct email : ");
    }

    if(flag == 3)
    {
        printf("The email should have characters after @, please enter the correct email : ");
    }

    if(flag == 4)
    {
        printf("The email should contain . after @, please enter the correct email : ");
    }

    if(flag == 5)
    {
        printf("The email should have characters after ., please enter the correct email : ");
    }

    if(flag == 6)
    {
        printf("The email is already present, please enter a unique email : ");
    }

}while(flag != 0);
addressBook->contactCount++;
printf("The contact number added Successfully:::\n");
    }  

 
void searchContact(AddressBook *addressBook)
{
    int option = 0;
    int res;
    char str[30];

    printf("1. Search by Name\n");
    printf("2. Search by Phone number\n");
    printf("3. Search by Email\n");

    printf("Enter the option to search: ");
    scanf("%d", &option);

    switch(option)
    {
        case 1:
    do
    {
        printf("Enter the name to search: ");
        scanf(" %[^\n]", str);

        res = search_name(str, addressBook);

        if(res == 0)
        {
            printf("Please enter the correct name\n");
        }

    } while(res == 0);

    if(res == 2)
    {
        int choice;
        int found = 0;

        do
        {
            printf("Multiple contacts are with the same name\n");
            printf("1. Search using Phone number\n");
            printf("2. Search using Email\n");

            printf("Enter your choice: ");
            scanf("%d", &choice);

            if(choice == 1)
            {
                printf("Enter the phone number: ");
                scanf(" %[^\n]", str);

                res = search_phone(str, addressBook);

                if(res == 0)
                {
                    printf("Please enter the correct phone number\n");
                }
                else
                {
                    found = 1;
                }
            }

            else if(choice == 2)
            {
                printf("Enter the email: ");
                scanf(" %[^\n]", str);

                res = search_email(str, addressBook);

                if(res == 0)
                {
                    printf("Please enter the correct email\n");
                }
                else
                {
                    found = 1;
                }
            }

            else
            {
                printf("The entered option is wrong\n");
            }

        } while(found == 0);
    }

    break;

        case 2:
            printf("Enter the phone number to search: ");
            scanf(" %[^\n]", str);

            res = search_phone(str, addressBook);

            if(res == 0)
            {
                printf("Please enter the correct phone number\n");
            }
            else
            {
                printf("The contact has found successfully\n");
            }

            break;

        case 3:
            printf("Enter the email to search: ");
            scanf(" %[^\n]", str);

            res = search_email(str, addressBook);

            if(res == 0)
            {
                printf("Please enter the correct email\n");
            }
            else
            {
                printf("The contact has found successfully\n");
            }

            break;

        default:
            printf("The entered option is wrong\n");
    }
}



void editContact(AddressBook *addressBook)
{
    int option;
    int ret;
    int edit_option;
    int index = -1;
    int found;

    char str[50];
    char phone[20];
    char email[50];

    printf("1. Search by Name\n");
    printf("2. Search by Phone number\n");
    printf("3. Search by Email\n");

    printf("Enter the option to search: ");
    scanf("%d", &option);

    switch(option)
    {
        case 1:

            do
            {
                printf("Enter the name to search: ");
                scanf(" %[^\n]", str);

                ret = search_name(str, addressBook);

                if(ret == 0)
                {
                    printf("Please enter the correct name\n");
                }

            } while(ret == 0);

            if(ret == 1)
            {
                for(int i = 0; i < addressBook->contactCount; i++)
                {
                    int j = 0;

                    while(str[j] != '\0' && str[j] == addressBook->contacts[i].name[j])
                    {
                        j++;
                    }

                    if(str[j] == '\0' && addressBook->contacts[i].name[j] == '\0')
                    {
                        index = i;
                        break;
                    }
                }
            }

            else if(ret == 2)
            {
                found = 0;

                do
                {
                    printf("Multiple contacts are with the same name\n");
                    printf("1. Search using Phone number\n");
                    printf("2. Search using Email\n");

                    printf("Enter your choice: ");
                    scanf("%d", &option);

                    if(option == 1)
                    {
                        printf("Enter the phone number: ");
                        scanf(" %[^\n]", phone);

                        for(int i = 0; i < addressBook->contactCount; i++)
                        {
                            int j = 0;
                            int k = 0;

                            while(str[j] != '\0' && str[j] == addressBook->contacts[i].name[j])
                            {
                                j++;
                            }

                            while(phone[k] != '\0' && phone[k] == addressBook->contacts[i].phone[k])
                            {
                                k++;
                            }

                            if(str[j] == '\0' &&   addressBook->contacts[i].name[j] == '\0' && phone[k] == '\0' && addressBook->contacts[i].phone[k] == '\0')
                            {
                                index = i;
                                found = 1;
                                break;
                            }
                        }

                        if(found == 0)
                        {
                            printf("Please enter the correct phone number\n");
                        }
                    }

                    else if(option == 2)
                    {
                        printf("Enter the email: ");
                        scanf(" %[^\n]", email);

                        for(int i = 0; i < addressBook->contactCount; i++)
                        {
                            int j = 0;
                            int k = 0;

                            while(str[j] != '\0' &&  str[j] == addressBook->contacts[i].name[j])
                            {
                                j++;
                            }

                            while(email[k] != '\0' && email[k] == addressBook->contacts[i].email[k])
                            {
                                k++;
                            }

                            if(str[j] == '\0' && addressBook->contacts[i].name[j] == '\0' && email[k] == '\0' && addressBook->contacts[i].email[k] == '\0')
                            {
                                index = i;
                                found = 1;
                                break;
                            }
                        }

                        if(found == 0)
                        {
                            printf("Please enter the correct email\n");
                        }
                    }

                    else
                    {
                        printf("The entered option is wrong\n");
                    }

                } while(found == 0);
            }

            break;


        case 2:

            do
            {
                printf("Enter the phone number to search: ");
                scanf(" %[^\n]", str);

                ret = search_phone(str, addressBook);

                if(ret == 0)
                {
                    printf("Please enter the correct phone number\n");
                }

            } while(ret == 0);

            for(int i = 0; i < addressBook->contactCount; i++)
            {
                int j = 0;

                while(str[j] != '\0' && str[j] == addressBook->contacts[i].phone[j])
                {
                    j++;
                }

                if(str[j] == '\0' && addressBook->contacts[i].phone[j] == '\0')
                {
                    index = i;
                    break;
                }
            }

            break;


        case 3:

            do
            {
                printf("Enter the email to search: ");
                scanf(" %[^\n]", str);

                ret = search_email(str, addressBook);

                if(ret == 0)
                {
                    printf("Please enter the correct email\n");
                }

            } while(ret == 0);

            for(int i = 0; i < addressBook->contactCount; i++)
            {
                int j = 0;

                while(str[j] != '\0' && str[j] == addressBook->contacts[i].email[j])
                {
                    j++;
                }

                if(str[j] == '\0' && addressBook->contacts[i].email[j] == '\0')
                {
                    index = i;
                    break;
                }
            }

            break;


        default:
            printf("The entered option is wrong\n");
            return;
    }


    if(index == -1)
    {
        printf("Contact not found\n");
        return;
    }


    printf("Please select the option which you want to edit:\n");
    printf("1. Name\n");
    printf("2. Phone number\n");
    printf("3. Email\n");

    printf("Enter the option: ");
    scanf("%d", &edit_option);


    if(edit_option == 1)
{
    do
    {
        printf("Enter the name to edit: ");
        scanf(" %[^\n]", str);

        ret = validate_name(str);

        if(ret == 0)
        {
            printf("The entered name is not valid\n");
        }

    } while(ret == 0);

    int i = 0;

    while(str[i] != '\0')
    {
        addressBook->contacts[index].name[i] = str[i];
        i++;
    }

    addressBook->contacts[index].name[i] = '\0';

    printf("Name updated successfully\n");
}

else if(edit_option == 2)
{
    do
    {
        printf("Enter the phone number to edit: ");
        scanf(" %[^\n]", str);

        ret = validate_phone(str, addressBook);

        if(ret == 1)
        {
            printf("Phone number should contain 10 digits\n");
        }
        else if(ret == 2)
        {
            printf("Phone number should contain only digits\n");
        }
        else if(ret == 3 &&
                strcmp(str, addressBook->contacts[index].phone) != 0)
        {
            printf("The phone number is already present\n");
            ret = 3;
        }
        else
        {
            ret = 0;
        }

    } while(ret != 0);

    int i = 0;

    while(str[i] != '\0')
    {
        addressBook->contacts[index].phone[i] = str[i];
        i++;
    }

    addressBook->contacts[index].phone[i] = '\0';

    printf("Phone number updated successfully\n");
}

else if(edit_option == 3)
{
    do
    {
        printf("Enter the email to edit: ");
        scanf(" %[^\n]", str);

        ret = validate_email(str, addressBook);

        if(ret == 1)
        {
            printf("The email should contain only one @\n");
        }
        else if(ret == 2)
        {
            printf("The email should have characters before @\n");
        }
        else if(ret == 3)
        {
            printf("The email should have characters after @\n");
        }
        else if(ret == 4)
        {
            printf("The email should have characters between @ and .\n");
        }
        else if(ret == 5)
        {
            printf("The email should have characters after .\n");
        }
        else if(ret == 6 &&
                strcmp(str, addressBook->contacts[index].email) != 0)
        {
            printf("The email is already present\n");
            ret = 6;
        }
        else
        {
            ret = 0;
        }

    } while(ret != 0);

    int i = 0;

    while(str[i] != '\0')
    {
        addressBook->contacts[index].email[i] = str[i];
        i++;
    }

    addressBook->contacts[index].email[i] = '\0';

    printf("Email updated successfully\n");
}

else
{
    printf("Invalid edit option\n");
}

}


void deleteContact(AddressBook *addressBook)
{
/* Define the logic for deletecontact */
    int option;
    int index = -1;
    int count = 0;
    int choice;
    char str[50];
    char phone[20];
    char email[50];
    char confirm;

    printf("1. Search by Name\n");
    printf("2. Search by Phone number\n");
    printf("3. Search by Email\n");

    printf("Enter the option to search: ");
    scanf("%d", &option);

    switch(option)
{
    case 1:

        do
        {
            printf("Enter the name: ");
            scanf(" %[^\n]", str);

            count = 0;
            index = -1;

            for(int i = 0; i < addressBook->contactCount; i++)
            {
                if(strcmp(str, addressBook->contacts[i].name) == 0)
                {
                    count++;
                    index = i;
                }
            }

            if(count == 0)
            {
                printf("Please enter the correct name\n");
            }

        } while(count == 0);

        if(count > 1)
        {
            int found = 0;

            do
            {
                printf("Multiple contacts are with the same name\n");
                printf("1. Search using Phone number\n");
                printf("2. Search using Email\n");
                printf("Enter your choice: ");
                scanf("%d", &choice);

                if(choice == 1)
                {
                    printf("Enter the phone number: ");
                    scanf(" %[^\n]", phone);

                    found = 0;

                    for(int i = 0; i < addressBook->contactCount; i++)
                    {
                        if(strcmp(str, addressBook->contacts[i].name) == 0 &&
                           strcmp(phone, addressBook->contacts[i].phone) == 0)
                        {
                            index = i;
                            found = 1;
                            break;
                        }
                    }

                    if(found == 0)
                        printf("Please enter the correct phone number\n");
                }

                else if(choice == 2)
                {
                    printf("Enter the email: ");
                    scanf(" %[^\n]", email);

                    found = 0;

                    for(int i = 0; i < addressBook->contactCount; i++)
                    {
                        if(strcmp(str, addressBook->contacts[i].name) == 0 &&
                           strcmp(email, addressBook->contacts[i].email) == 0)
                        {
                            index = i;
                            found = 1;
                            break;
                        }
                    }

                    if(found == 0)
                        printf("Please enter the correct email\n");
                }

                else
                {
                    printf("The entered option is wrong\n");
                    found = 0;
                }

            } while(found == 0);
        }

        break;


    case 2:

        do
        {
            printf("Enter the phone number: ");
            scanf(" %[^\n]", str);

            index = -1;

            for(int i = 0; i < addressBook->contactCount; i++)
            {
                if(strcmp(str, addressBook->contacts[i].phone) == 0)
                {
                    index = i;
                    break;
                }
            }

            if(index == -1)
            {
                printf("Please enter the correct phone number\n");
            }

        } while(index == -1);

        break;


    case 3:

        do
        {
            printf("Enter the email: ");
            scanf(" %[^\n]", str);

            index = -1;

            for(int i = 0; i < addressBook->contactCount; i++)
            {
                if(strcmp(str, addressBook->contacts[i].email) == 0)
                {
                    index = i;
                    break;
                }
            }

            if(index == -1)
            {
                printf("Please enter the correct email\n");
            }

        } while(index == -1);

        break;


    default:
        printf("The entered option is wrong\n");
        return;
}

    if(index == -1)
    {
        printf("Contact not found\n");
        return;
    }

    printf("\nName  : %s\n", addressBook->contacts[index].name);
    printf("Phone : %s\n", addressBook->contacts[index].phone);
    printf("Email : %s\n", addressBook->contacts[index].email);

    printf("\nConfirm here do you want to delete the contact (Y/y): ");
    scanf(" %c", &confirm);

    if(confirm == 'Y' || confirm == 'y')
    {
        for(int i = index; i < addressBook->contactCount - 1; i++)
        {
            addressBook->contacts[i] = addressBook->contacts[i + 1];
        }

        addressBook->contactCount--;

        printf("The contact has deleted successfully\n");
    }
    else
    {
        printf("Contact deletion cancelled\n");
    }
}


int validate_name(char name[])
{
    int i = 0;

    while(name[i] != '\0')
    {
        if(!((name[i] >= 'A' && name[i] <= 'Z') ||
             (name[i] >= 'a' && name[i] <= 'z') ||
             name[i] == ' '))
        {
            return 0;
        }

        i++;
    }

    return 1;
}


int validate_phone(char phone[], AddressBook *addressBook)
{
    int i = 0;
    int count = 0;

    while(phone[i] != '\0')
    {
        count++;
        i++;
    }

    if(count != 10)
    {
        return 1;
    }

    i = 0;

    while(phone[i] != '\0')
    {
        if(phone[i] < '0' || phone[i] > '9')
        {
            return 2;
        }

        i++;
    }

    for(i = 0; i < addressBook->contactCount; i++)
    {
        int j = 0;

        while(phone[j] != '\0' &&
              phone[j] == addressBook->contacts[i].phone[j])
        {
            j++;
        }

        if(phone[j] == '\0' &&
           addressBook->contacts[i].phone[j] == '\0')
        {
            return 3;
        }
    }

    return 0;
}

int validate_email(char email[], AddressBook *addressBook)
{
    int i = 0;
    int at = 0;
    int dot = 0;

    while(email[i] != '\0')
    {
        if(email[i] == '@')
        {
            at++;
        }

        i++;
    }

    if(at != 1)
    {
        return 1;
    }

    i = 0;

    while(email[i] != '@')
    {
        i++;
    }

    if(i == 0)
    {
        return 2;
    }

    if(email[i + 1] == '\0')
    {
        return 3;
    }

    i++;

    while(email[i] != '\0')
    {
        if(email[i] == '.')
        {
            dot = 1;
            break;
        }

        i++;
    }

    if(dot == 0)
    {
        return 4;
    }

    if(email[i - 1] == '@')
    {
        return 4;
    }

    if(email[i + 1] == '\0')
    {
        return 5;
    }

    for(i = 0; i < addressBook->contactCount; i++)
    {
        int j = 0;

        while(email[j] != '\0' && email[j] == addressBook->contacts[i].email[j])
        {
            j++;
        }

        if(email[j] == '\0' && addressBook->contacts[i].email[j] == '\0')
        {
            return 6;
        }
    }

    return 0;
}


int search_name(char name[], AddressBook *addressBook)
{
    int count = 0;
    int index = -1;

    for(int i = 0; i < addressBook->contactCount; i++)
    {
        int j = 0;

        while(name[j] != '\0' && name[j] == addressBook->contacts[i].name[j])
        {
            j++;
        }

        if(name[j] == '\0' && addressBook->contacts[i].name[j] == '\0')
        {
            count++;
            index = i;
        }
    }

    if(count == 0)
    {
        return 0;
    }

    if(count > 1)
    {
        return 2;
    }

    printf("Name  : %s\n", addressBook->contacts[index].name);
    printf("Phone : %s\n", addressBook->contacts[index].phone);
    printf("Email : %s\n", addressBook->contacts[index].email);

    return 1;
}

int search_phone(char phone[], AddressBook *addressBook)
{
    int i;
    int j;

    for(i = 0; i < addressBook->contactCount; i++)
    {
        j = 0;

        while(phone[j] != '\0' && phone[j] == addressBook->contacts[i].phone[j])
        {
            j++;
        }

        if(phone[j] == '\0' && addressBook->contacts[i].phone[j] == '\0')
        {
            printf("Name  : %s\n", addressBook->contacts[i].name);
            printf("Phone : %s\n", addressBook->contacts[i].phone);
            printf("Email : %s\n", addressBook->contacts[i].email);

            return 1;
        }
    }

    return 0;
}

int search_email(char email[], AddressBook *addressBook)
{
    int i;
    int j;

    for(i = 0; i < addressBook->contactCount; i++)
    {
        j = 0;

        while(email[j] != '\0' && email[j] == addressBook->contacts[i].email[j])
        {
            j++;
        }

        if(email[j] == '\0' && addressBook->contacts[i].email[j] == '\0')
        {
            printf("Name  : %s\n", addressBook->contacts[i].name);
            printf("Phone : %s\n", addressBook->contacts[i].phone);
            printf("Email : %s\n", addressBook->contacts[i].email);

            return 1;
        }
    }

    return 0;
}
