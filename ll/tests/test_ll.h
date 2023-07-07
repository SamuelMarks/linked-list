#ifndef LL_TESTS_TEST_LL_H
#define LL_TESTS_TEST_LL_H

#include <greatest.h>

#include <ll.h>

TEST x_size_t_ll() {
  struct ll_size_t_list my_size_t_ll = {0};

  const size_t values[] = {5, 6, 10, 44};
  const size_t *values_cursor;
  size_t i;
  int rc = EXIT_FAILURE;
  {
    struct ll_size_t_elem *iterator;

    for (i = 0; i < sizeof values / sizeof *values; ++i) {
      rc = ll_size_t_list_append(&my_size_t_ll, values[i]);
      if (rc != 0)
        goto cleanup;
    }

    ASSERT_EQ(i, 4);
    ASSERT_EQ(i, my_size_t_ll.n);

    for (values_cursor = values, iterator = my_size_t_ll.ll; iterator != NULL;
         iterator = iterator->next, values_cursor++)
      ASSERT_EQ(iterator->value, *values_cursor);
  }

  ASSERT_EQ(i, sizeof values / sizeof *values);
  ASSERT_EQ(values_cursor - values, sizeof values / sizeof *values);

  {
    size_t **my_size_t_arr, **my_size_t_iterator;
    ll_size_t_list_to_arr(&my_size_t_ll, &my_size_t_arr);

    for (i = 0; i < sizeof values / sizeof *values; ++i)
      ASSERT_EQ(my_size_t_arr[i][0], values[i]);

    ASSERT_EQ(i, 4);

    for (i = 0, my_size_t_iterator = my_size_t_arr; *my_size_t_iterator != NULL;
         my_size_t_iterator++, ++i)
      ASSERT_EQ(**my_size_t_iterator, values[i]);
    ASSERT_EQ(i, 4);

    arr_size_t_cleanup(my_size_t_arr);
  }

cleanup:
  ll_size_t_cleanup(&my_size_t_ll);
  ASSERT_EQ(my_size_t_ll.ll, NULL);
  ASSERT_EQ(my_size_t_ll.n, 0);

  switch (rc) {
  case EXIT_SUCCESS:
    PASS();
    break;
  default:
    FAIL();
  }
}

TEST x_az_span_ll() {
  struct az_span_elem *full_ll = NULL;
  struct az_span_elem **ll_cur_ptr = &full_ll, *iter;

  struct az_span_list *ll = calloc(1, sizeof *ll);

  const az_span l[] = {AZ_SPAN_FROM_STR("foo"), AZ_SPAN_FROM_STR("bar")};
  size_t i;

  ll->size = 0;

  for (i = 0; i < sizeof l / sizeof l[0]; i++)
    az_span_list_push(&ll->size, &ll_cur_ptr, l[i]);

  ll->list = full_ll;

  ASSERT_EQ(i, 2);

  for (iter = (struct az_span_elem *)ll->list, i = 0; iter != NULL;
       iter = iter->next, i++)
    ASSERT_FALSE(!az_span_is_content_equal(iter->span, l[i]));

  ASSERT_EQ(i, sizeof l / sizeof l[0]);

  az_span_list_cleanup(ll);

  ASSERT_EQ(ll->list, NULL);
  ASSERT_EQ(ll->size, 0);

  PASS();
}

SUITE(ll_suite) {
  RUN_TEST(x_size_t_ll);
  /*RUN_TEST(x_az_span_ll);*/
}

#endif /* !LL_TESTS_TEST_LL_H */
