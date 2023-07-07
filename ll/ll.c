#include "ll.h"
#include <string.h>

/*
 * `const char *`
 */

int ll_append_str(struct str_elem **root, const char *const s,
                  struct str_elem ***result) {
  struct str_elem **insert = &*root;
  int rc = EXIT_SUCCESS;
  while (*insert)
    insert = &insert[0]->next;
  *insert = malloc(sizeof **insert);
  if (*insert == NULL)
    rc = ENOMEM;
  else {
    insert[0]->s = s, insert[0]->n = strlen(s), insert[0]->next = NULL;
    *result = insert;
  }
  return rc;
}

int ll_push_str(size_t *const ll_n, struct str_elem ***ll_root,
                const char *const s, struct str_elem ***result) {
  int rc = EXIT_SUCCESS;
  if (s != NULL) {
    (*ll_n)++;
    rc = ll_append_str(*ll_root, s, result);
  } else
    *result = *ll_root;
  return rc;
}

/*
 * `size_t`
 */

struct ll_size_t_elem **ll_size_t_elem_get_end(struct ll_size_t_elem **head) {
  while (*head)
    head = &(**head).next;
  return head;
}

int ll_size_t_elem_prepend(struct ll_size_t_elem **head, size_t value) {
  struct ll_size_t_elem *const new_elem = malloc(sizeof *new_elem);
  if (new_elem == NULL)
    return ENOMEM;
  new_elem->value = value, new_elem->next = NULL;
  *head = new_elem;
  return 0;
}

int ll_size_t_elem_append(struct ll_size_t_elem **head, size_t value) {
  return ll_size_t_elem_prepend(ll_size_t_elem_get_end(head), value);
}

void ll_size_t_elem_cleanup(struct ll_size_t_elem **head) {
  struct ll_size_t_elem *current = *head;
  while (current != NULL) {
    struct ll_size_t_elem *tmp = current;
    current = current->next;
    free(tmp);
  }
  *head = NULL;
}

int ll_size_t_list_append(struct ll_size_t_list *const sized_linked_list,
                          size_t value) {
  struct ll_size_t_elem **const cursor = &sized_linked_list->ll;
  const int rc = ll_size_t_elem_append(cursor, value);
  if (rc == 0)
    sized_linked_list->n++;
  return rc;
}

int ll_size_t_list_prepend(struct ll_size_t_list *const sized_linked_list,
                           size_t value) {
  struct ll_size_t_elem **const head = &sized_linked_list->ll;
  const int rc = ll_size_t_elem_prepend(head, value);
  if (rc == 0)
    sized_linked_list->n++;
  return rc;
}

void ll_size_t_cleanup(struct ll_size_t_list *const list) {
  ll_size_t_elem_cleanup(&list->ll);
  list->n = 0;
}

int ll_size_t_list_to_arr(struct ll_size_t_list *const list,
                          size_t ***const arr) {
  struct ll_size_t_elem *iterator = list->ll;
  size_t **const array = malloc((list->n + 1) * sizeof *array);
  if (array == NULL)
    return ENOMEM;

  {
    size_t i = 0;
    for (; i < list->n; i++, iterator = iterator->next) {
      size_t *p = malloc(sizeof(p));
      if (p == NULL)
        return ENOMEM;
      *p = iterator->value;
      (array)[i] = p;
    }
    array[i] = NULL;
  }
  *arr = array;
  return 0;
}

void arr_size_t_cleanup(size_t **arr) {
  size_t **size_t_it;

  for (size_t_it = arr; *size_t_it != NULL; size_t_it++)
    if (size_t_it != NULL)
      free(*size_t_it);
  if (arr != NULL)
    free(arr);
}

/*
 * `az_span`
 */

struct az_span_elem **az_span_list_end(struct az_span_elem **span_elem) {
  while (*span_elem)
    span_elem = &(**span_elem).next;
  return span_elem;
}

int az_span_list_prepend(struct az_span_elem **span_elem, const az_span span,
                         struct az_span_elem ***result) {
  int rc = EXIT_SUCCESS;
  if (*span_elem == NULL) {
    *result = NULL, rc = EINVAL;
  } else {
    struct az_span_elem *new_span_elem = malloc(sizeof *new_span_elem);
    if (new_span_elem == NULL)
      *result = NULL, rc = ENOMEM;
    else {
      new_span_elem->span = span;
      new_span_elem->next = *span_elem;
      *span_elem = new_span_elem;
      *result = &new_span_elem->next;
    }
  }
  return rc;
}

int az_span_list_append(struct az_span_elem **p, const az_span span,
                        struct az_span_elem ***result) {
  return az_span_list_prepend(az_span_list_end(p), span, result);
}

int az_span_list_push(uint32_t *ll_n, struct az_span_elem ***ll_root,
                      const az_span span) {
  int rc = az_span_list_append(*ll_root, span, ll_root);
  if (rc == EXIT_SUCCESS)
    (*ll_n)++;
  return rc;
}

void az_span_elem_cleanup(struct az_span_elem **az_span_element) {
  if (az_span_element == NULL)
    return;

  {
    struct az_span_elem *cur = *az_span_element;
    while (cur != NULL) {
      struct az_span_elem *tmp = cur;
      cur = cur->next;
      free(tmp);
    }
  }
  *az_span_element = NULL;
}

void az_span_list_cleanup(struct az_span_list *size_t_ll) {
  struct az_span_elem *list = (struct az_span_elem *)size_t_ll->list;
  az_span_elem_cleanup(&list);
  size_t_ll->list = NULL, size_t_ll->size = 0;
}
