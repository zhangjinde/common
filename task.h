/* This API specifies the task data structure. It is in C so we can
 * easily construct tasks from other languages like Python. The datastructures
 * are also defined in such a way that memory is contiguous and all pointers
 * are relative, so that we can memcpy the datastructure and ship it over the
 * network without serialization and deserialization */
 
 #include <stddef.h>
 #include <stdint.h>
 #include "common.h"

typedef unique_id function_id;

typedef struct task_spec_impl task_spec;

/* If argument is passed by value or reference. */
enum arg_type {
  ARG_BY_REF,
  ARG_BY_VAL
};

/* Construct and modify task specifications. */

/* Allocating and initializing a task. */
task_spec *alloc_task_spec(function_id func_id, int64_t num_args, int64_t num_returns, int64_t args_value_size);

/* Getting the number of arguments and returns. */
int64_t task_num_args(task_spec* spec);
int64_t task_num_returns(task_spec* spec);

/* Getting task arguments. */
int8_t task_arg_type(task_spec *spec, int64_t arg_index);
unique_id *task_arg_id(task_spec *spec, int64_t arg_index);
uint8_t *task_arg_val(task_spec *spec, int64_t arg_index);
int64_t task_arg_length(task_spec *spec, int64_t arg_index);

/* Setting task arguments. Note that this API only allows you to set the
 * arguments in their order of appearance. */
int64_t task_args_add_ref(task_spec *spec, unique_id arg_id);
int64_t task_args_add_val(task_spec *spec, uint8_t *data, int64_t length);

/* Getting and setting return arguments. Tasks return by reference for now. */
unique_id *task_return(task_spec* spec, int64_t ret_index);

/* Freeing the task datastructure. */
void free_task_spec(task_spec *spec);

/* Write the task specification to a file or socket. */
int send_task(int fd, task_spec *spec);

/* Read the task specification from a file or socket. It is the user's
 * responsibility to free the task after it has been used. */
task_spec *recv_task(int fd);
