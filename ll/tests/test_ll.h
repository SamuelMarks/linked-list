#ifndef LL_TESTS_TEST_LL_H
#define LL_TESTS_TEST_LL_H

#include <greatest.h>

#include <ll.h>

TEST x_size_t_ll() {
  struct ll_size_t_list *my_size_t_ll;

  static const size_t values[] = {5, 6, 10, 44};
  size_t i;
  int rc = EXIT_SUCCESS;
  {
    my_size_t_ll = malloc(sizeof *my_size_t_ll);
    if (my_size_t_ll == NULL)
      return ENOMEM;
    struct ll_size_t_elem **current_pointer = &my_size_t_ll->ll;
    struct ll_size_t_elem *iterator;

    for (i = 0; i < sizeof values / sizeof *values; ++i) {
      rc = ll_size_t_list_append(my_size_t_ll, current_pointer, values[i]);
      if (rc != EXIT_SUCCESS)
        goto cleanup;
    }

    ASSERT_EQ(i, 4);
    ASSERT_EQ(i, my_size_t_ll->n);

    for (i = 0, iterator = my_size_t_ll->ll; iterator != NULL;
         iterator = iterator->next, ++i)
      ASSERT_EQ(iterator->value, values[i]);
  }

  ASSERT_EQ(i, sizeof values / sizeof *values);

  {
    size_t *my_size_t_arr = NULL, *my_size_t_iterator;
    ll_size_t_list_to_arr(&my_size_t_ll, &my_size_t_arr);

    for (i = 0; i < sizeof values / sizeof *values; ++i)
      ASSERT_EQ(my_size_t_arr[i], values[i]);

    ASSERT_EQ(i, 4);

    for (i = 0, my_size_t_iterator = my_size_t_arr; my_size_t_iterator != NULL;
         my_size_t_iterator++, ++i) {
      printf("*my_size_t_iterator (%ld) == values[%ld] (%ld)\n",
             *my_size_t_iterator, i, values[i]);
      ASSERT_EQ(*my_size_t_iterator, values[i]);
    }
    ASSERT_EQ(i, 4);

    free(my_size_t_arr);
  }

cleanup:
  ll_size_t_cleanup(&my_size_t_ll);
  ASSERT_EQ(my_size_t_ll, NULL);
  /* return rc; */

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
