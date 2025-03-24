#ifndef ADDRESS_BOOK_H
#define ADDRESS_BOOK_H

#include <stdio.h>

#define DEFAULT_FILE "address_book.csv"

#define NAME_LEN 32
#define NUMBER_LEN 32
#define EMAIL_ID_LEN 32

#define PHONE_NUMBER_COUNT 5
#define EMAIL_ID_COUNT 5
#define MAX_CONTACTS 100

typedef enum {
    e_add,
    e_search,
    e_edit,
    e_delete,
    e_list,
} Modes;

typedef enum {
    e_fail = -10,
    e_back,
    e_success,
    e_no_match,
    e_new_line,
} Status;

typedef enum {
    e_exit,
    e_add_contact,
    e_search_contact,
    e_edit_contact,
    e_delete_contact,
    e_list_contacts,
    e_save
} MenuFeatures;

typedef struct {
    char name[NAME_LEN];
    char phone_numbers[PHONE_NUMBER_COUNT][NUMBER_LEN];      // ✅ fixed: array of strings
    char email_addresses[EMAIL_ID_COUNT][EMAIL_ID_LEN];      // ✅ fixed: array of strings
    int si_no;
} ContactInfo;

typedef struct {
    ContactInfo list[MAX_CONTACTS];
    int count;
    FILE *fp;
} AddressBook;

#endif
