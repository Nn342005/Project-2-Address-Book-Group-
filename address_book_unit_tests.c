#include "address_book.h"
#include "address_book_fops.h"
#include "address_book_menu.h"
#include "unity.h"

void setUp(void)
{
    // Initialize resources for tests here
}

void tearDown(void)
{
    // Clean up resources after each test
}

int main(void)
{
    UNITY_BEGIN();

    // Run Test functions
    RUN_TEST(test_add_contact); // Can break down tests into add name, add phone, add email, for example
    RUN_TEST(test_search_contact);
    RUN_TEST(test_edit_contact);
    RUN_TEST(test_delete_contact);
    RUN_TEST(test_list_contacts);
    RUN_TEST(test_save_file);
    RUN_TEST(test_exit_program);

    return UNITY_END();
}