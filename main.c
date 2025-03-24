#include "address_book.h"
#include "address_book_menu.h"
#include "address_book_fops.h"

int main() {
    AddressBook book = { .count = 0 };
    load_file(&book);
    menu(&book);
    save_file(&book);
    return 0;
}
