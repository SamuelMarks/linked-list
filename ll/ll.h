#ifndef LL_H
#define LL_H

#ifdef __cplusplus
extern "C" {
#else
#include <stdlib.h>
#endif /* __cplusplus */

#include <ll_export.h>

#if defined(_WIN32) || defined(__WIN32__) || defined(__WINDOWS__)
#include <BaseTsd.h>
typedef SSIZE_T ssize_t;
#endif
#include <errno.h>

#include <c_str_span.h>

/*
 * `const char *`
 */

struct str_elem {
  const char *s;
  size_t n;
  struct str_elem *next;
};

extern LL_EXPORT int ll_append_str(struct str_elem **root, const char *s,
                                   struct str_elem ***result);

/*
extern LL_EXPORT const char *make_slice(const char *s, size_t i,
                                           size_t *start_index);
*/
extern LL_EXPORT int ll_push_str(size_t *ll_n, struct str_elem ***ll_root,
                                 const char *s, struct str_elem ***);

/*
 * `size_t`
 */

struct ll_size_t_elem {
  size_t value;
  struct ll_size_t_elem *next;
};

struct ll_size_t_list {
  size_t n;
  struct ll_size_t_elem *ll;
};

extern LL_EXPORT struct ll_size_t_elem **
ll_size_t_elem_get_end(struct ll_size_t_elem **head);

extern LL_EXPORT int ll_size_t_elem_prepend(struct ll_size_t_elem **head,
                                            size_t value);

extern LL_EXPORT int ll_size_t_elem_append(struct ll_size_t_elem **head,
                                           size_t value);

extern LL_EXPORT void ll_size_t_elem_cleanup(struct ll_size_t_elem **head);

extern LL_EXPORT int
ll_size_t_list_append(struct ll_size_t_list *sized_linked_list,
                      struct ll_size_t_elem **cursor, size_t value);

extern LL_EXPORT int
ll_size_t_list_prepend(struct ll_size_t_list *sized_linked_list,
                       struct ll_size_t_elem **head, size_t value);

extern LL_EXPORT void ll_size_t_cleanup(struct ll_size_t_list **list);

extern LL_EXPORT int ll_size_t_list_to_arr(struct ll_size_t_list **list,
                                           size_t **arr);

/*
 * `az_span`
 */

struct az_span_elem {
  az_span span;
  struct az_span_elem *next;
};

/* List structure requiring manual bookkeeping for size */
struct az_span_list {
  uint32_t size;
  const struct az_span_elem *list;
};

extern LL_EXPORT struct az_span_elem **az_span_list_end(struct az_span_elem **);

extern LL_EXPORT int az_span_list_prepend(struct az_span_elem **, az_span,
                                          struct az_span_elem ***);

extern LL_EXPORT int az_span_list_append(struct az_span_elem **, az_span,
                                         struct az_span_elem ***);

extern LL_EXPORT int az_span_list_push(uint32_t *, struct az_span_elem ***,
                                       az_span);

extern LL_EXPORT void az_span_elem_cleanup(struct az_span_elem **);

extern LL_EXPORT void az_span_list_cleanup(struct az_span_list *);

#ifdef __cplusplus
} /* extern "C" */
#endif /* __cplusplus */

#endif /* !LL_H */
