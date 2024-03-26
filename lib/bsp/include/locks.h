// Modification by penguinencounter of kendryte-standalone-sdk.
// Licensed under the Apache Licence 2.0
// See the bundled LICENSE file, or https://www.apache.org/licenses/LICENSE-2.0
// for details

#ifndef LOCKS_H
#define LOCKS_H

typedef long _lock_t;

typedef struct
{
  _lock_t *lock;
  long counter;
  unsigned long core;
} reculock_t;

static inline long lock_trylock(_lock_t *lock);
static inline void lock_lock(_lock_t *lock);
static inline void lock_unlock(_lock_t *lock);
static reculock_t *get_reculock(_lock_t *lock);
static reculock_t *get_free_reculock(void);
static reculock_t *reculock_init(_lock_t *lock);
static void reculock_deinit(_lock_t *lock);
static inline int reculock_trylock(_lock_t *lock);
static inline void reculock_lock(_lock_t *lock);
static inline void reculock_unlock(_lock_t *lock);
void _lock_init(_lock_t *lock);
void _lock_init_recursive(_lock_t *lock);
void _lock_close(_lock_t *lock);
void _lock_close_recursive(_lock_t *lock);
void _lock_acquire(_lock_t *lock);
void _lock_acquire_recursive(_lock_t *lock);
int _lock_try_acquire(_lock_t *lock);
int _lock_try_acquire_recursive(_lock_t *lock);
void _lock_release(_lock_t *lock);
void _lock_release_recursive(_lock_t *lock);

#endif //LOCKS_H
