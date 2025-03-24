#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "address_book.h"

Status load_file(AddressBook *address_book) {
    address_book->fp = fopen(DEFAULT_FILE, "r");
    if (!address_book->fp) {
        address_book->fp = fopen(DEFAULT_FILE, "w");
        if (!address_book->fp) return e_fail;
        fclose(address_book->fp);
        return e_success;
    }

    address_book->count = 0;
    while (fscanf(address_book->fp, "%d,%31[^,],%31[^,],%31[^\n]",
        &address_book->list[address_book->count].si_no,
        address_book->list[address_book->count].name,
        address_book->list[address_book->count].phone_numbers[0],
        address_book->list[address_book->count].email_addresses[0]) == 4) {
        address_book->count++;
    }

    fclose(address_book->fp);
    return e_success;
}

Status save_file(AddressBook *address_book) {
    address_book->fp = fopen(DEFAULT_FILE, "w");
    if (!address_book->fp) return e_fail;

    for (int i = 0; i < address_book->count; i++) {
        ContactInfo *c = &address_book->list[i];
        fprintf(address_book->fp, "%d,%s,%s,%s\n",
            c->si_no, c->name, c->phone_numbers[0], c->email_addresses[0]);
    }

    fclose(address_book->fp);
    return e_success;
}
