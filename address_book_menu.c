#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>

#include "address_book.h"
#include "address_book_menu.h"
#include "address_book_fops.h"

void menu_header(const char *str) {
    printf("==== Address Book ====\n");
    if (str && *str != '\0') {
        printf("== %s ==\n", str);
    }
}

void main_menu(void) {
    menu_header("Main Menu");
    printf("0. Exit\n");
    printf("1. Add Contact\n");
    printf("2. Search Contact\n");
    printf("3. Edit Contact\n");
    printf("4. Delete Contact\n");
    printf("5. List Contacts\n");
    printf("6. Save\n");
    printf("Enter option: ");
}

Status add_contacts(AddressBook *address_book) {
    if (address_book->count >= MAX_CONTACTS) {
        printf("Address book full!\n");
        return e_fail;
    }

    ContactInfo *new_contact = &address_book->list[address_book->count];
    new_contact->si_no = address_book->count + 1;

    printf("Enter name: ");
    fgets(new_contact->name, NAME_LEN, stdin);
    new_contact->name[strcspn(new_contact->name, "\n")] = '\0';

    printf("Enter phone: ");
    fgets(new_contact->phone_numbers[0], NUMBER_LEN, stdin);
    new_contact->phone_numbers[0][strcspn(new_contact->phone_numbers[0], "\n")] = '\0';

    printf("Enter email: ");
    fgets(new_contact->email_addresses[0], EMAIL_ID_LEN, stdin);
    new_contact->email_addresses[0][strcspn(new_contact->email_addresses[0], "\n")] = '\0';

    address_book->count++;
    printf("Contact added.\n");
    return e_success;
}

Status search_contact(AddressBook *address_book) {
    char name[NAME_LEN];
    printf("Enter name to search: ");
    fgets(name, NAME_LEN, stdin);
    name[strcspn(name, "\n")] = '\0';

    for (int i = 0; i < address_book->count; i++) {
        if (strcmp(address_book->list[i].name, name) == 0) {
            printf("Found: %s, %s, %s\n",
                address_book->list[i].name,
                address_book->list[i].phone_numbers[0],
                address_book->list[i].email_addresses[0]);
            return e_success;
        }
    }

    printf("Contact not found.\n");
    return e_no_match;
}

Status delete_contact(AddressBook *address_book) {
    char name[NAME_LEN];
    printf("Enter name to delete: ");
    fgets(name, NAME_LEN, stdin);
    name[strcspn(name, "\n")] = '\0';

    for (int i = 0; i < address_book->count; i++) {
        if (strcmp(address_book->list[i].name, name) == 0) {
            for (int j = i; j < address_book->count - 1; j++) {
                address_book->list[j] = address_book->list[j + 1];
            }
            address_book->count--;
            printf("Contact deleted.\n");
            return e_success;
        }
    }

    printf("Contact not found.\n");
    return e_no_match;
}

Status list_contacts(AddressBook *address_book, const char *title, int *index, const char *msg, Modes mode) {
    if (address_book->count == 0) {
        printf("No contacts to display.\n");
        return e_fail;
    }

    printf("==== Contact List ====\n");
    for (int i = 0; i < address_book->count; i++) {
        ContactInfo *c = &address_book->list[i];
        printf("%d: %s | %s | %s\n", c->si_no, c->name, c->phone_numbers[0], c->email_addresses[0]);
    }
    return e_success;
}

Status edit_contact(AddressBook *address_book) {
    char name[NAME_LEN];
    printf("Enter name to edit: ");
    fgets(name, NAME_LEN, stdin);
    name[strcspn(name, "\n")] = '\0';

    for (int i = 0; i < address_book->count; i++) {
        ContactInfo *c = &address_book->list[i];
        if (strcmp(c->name, name) == 0) {
            printf("Editing contact: %s\n", c->name);

            printf("Enter new name (or press enter to keep the same): ");
            char buffer[NAME_LEN];
            fgets(buffer, NAME_LEN, stdin);
            if (buffer[0] != '\n') {
                buffer[strcspn(buffer, "\n")] = '\0';
                strcpy(c->name, buffer);
            }

            printf("Enter new phone (or press enter to keep the same): ");
            fgets(buffer, NUMBER_LEN, stdin);
            if (buffer[0] != '\n') {
                buffer[strcspn(buffer, "\n")] = '\0';
                strcpy(c->phone_numbers[0], buffer);
            }

            printf("Enter new email (or press enter to keep the same): ");
            fgets(buffer, EMAIL_ID_LEN, stdin);
            if (buffer[0] != '\n') {
                buffer[strcspn(buffer, "\n")] = '\0';
                strcpy(c->email_addresses[0], buffer);
            }

            printf("Contact updated.\n");
            return e_success;
        }
    }

    printf("Contact not found.\n");
    return e_no_match;
}

Status menu(AddressBook *address_book) {
    int option;
    char input[10];

    do {
        main_menu();
        fgets(input, sizeof(input), stdin);
        option = atoi(input);

        switch (option) {
            case e_add_contact:
                add_contacts(address_book);
                break;
            case e_search_contact:
                search_contact(address_book);
                break;
            case e_edit_contact:
                edit_contact(address_book);
                break;
            case e_delete_contact:
                delete_contact(address_book);
                break;
            case e_list_contacts:
                list_contacts(address_book, "List", NULL, "", e_list);
                break;
            case e_save:
                save_file(address_book);
                break;
            case e_exit:
                return e_success;
            default:
                printf("Invalid option.\n");
        }
    } while (option != e_exit);

    return e_success;
}
