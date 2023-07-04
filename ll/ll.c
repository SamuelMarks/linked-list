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

struct size_t_elem **size_t_list_end(struct size_t_elem **size_t_elem) {
  while (*size_t_elem)
    size_t_elem = &(*size_t_elem)->next;
  return size_t_elem;
}

int size_t_list_prepend(struct size_t_elem **size_t_elem, const size_t lu,
                        struct size_t_elem ***result) {
  if (*size_t_elem == NULL) {
    *result = NULL;
    return EINVAL;
  }

  {
    struct size_t_elem *new_size_t_elem = malloc(sizeof *new_size_t_elem);
    if (new_size_t_elem == NULL) {
      *result = NULL;
      return ENOMEM;
    }

    new_size_t_elem->lu = lu;
    new_size_t_elem->next = *size_t_elem;
    *size_t_elem = new_size_t_elem;
    *result = &new_size_t_elem->next;
  }
  return EXIT_SUCCESS;
}

int size_t_list_append(struct size_t_elem **p, const size_t lu,
                       struct size_t_elem ***result) {
  return size_t_list_prepend(size_t_list_end(p), lu, result);
}

int size_t_list_push(uint32_t *ll_n, struct size_t_elem ***ll_root,
                     const size_t lu, struct size_t_elem ***result) {
  int rc = size_t_list_append(*ll_root, lu, result);
  if (rc != EXIT_SUCCESS) {
    rc = size_t_list_append(*ll_root, lu, ll_root);
    if (rc == EXIT_SUCCESS)
      (*ll_n)++;
  }
  return rc;
}

void size_t_elem_cleanup(struct size_t_elem **size_t_elem) {
  if (*size_t_elem == NULL)
    return;
  struct size_t_elem *cur = *size_t_elem;
  while (cur != NULL) {
    struct size_t_elem *tmp = cur;
    cur = cur->next;
    free(tmp);
  }
  *size_t_elem = NULL;
}

void size_t_list_cleanup(struct size_t_list *size_t_ll) {
  struct size_t_elem *list = (struct size_t_elem *)size_t_ll->list;
  size_t_elem_cleanup(&list);
  size_t_ll->list = NULL;
  size_t_ll->size = 0;
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
