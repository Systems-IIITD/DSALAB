#include "../include/common.h"


// IMPLEMENTTAION of DIST

static double deg_to_rad(double deg)
{
  return (deg * PI) / 180;
}
static double rad_to_deg(double rad)
{
  return (rad * 180) / PI;
}

double distance(struct location *loc1, struct location *loc2)
{
  double dist;

  dist = (sin(deg_to_rad(loc1->lat)) * sin(deg_to_rad(loc2->lat))) +
		     (cos(deg_to_rad(loc1->lat)) * cos(deg_to_rad(loc2->lat)) *
					cos(deg_to_rad(loc1->lon - loc2->lon)));
  dist = acos(dist) * 6371;
  return dist;
}

// IMPLEMENTTAION of TRIES
struct __trie_node {
  char val;
	struct __trie_node *child;
  struct __trie_node *next;
};

static struct __trie_node *__trie_root = NULL;
static size_t total_allocations = 0;

static struct __trie_node* trie_allocate_node(char c, struct __trie_node *next)
{
  struct __trie_node *n;
  int i;

	n = (struct __trie_node*)malloc(sizeof(struct __trie_node));
  if (n == NULL) {
    printf("Out-of-memory\n");
    assert(0);
    return n;
  }

  n->val = c;
  n->child = NULL;
  n->next = next;
  return n;
}

static struct __trie_node* search_char(struct __trie_node *n, char c) {
  while (n && n->val != c) {
    n = n->next;
  }
  return n;
}

static int trie_insert(struct __trie_node *root, const char *word, int len)
{
  int i;
  struct __trie_node *n = root;
  struct __trie_node *next;
  int ret = 0;

  assert(len > 0);
  for (i = 0; i < len; i++) {
    if (!(next = search_char(n->child, word[i]))) {
      n->child = trie_allocate_node(word[i], n->child);
      next = n->child;
      ret = 1;
    }
    n = next;
  }
  return ret;
}

static int trie_search(struct __trie_node *root, const char *word, int len)
{
  int i;
  struct __trie_node *n = root;

  assert(len > 0);
  for (i = 0; i < len && n; i++) {
    n = search_char(n->child, word[i]);
  }
  return n != NULL;
}

// IMPLEMENTTAION OF MALLOC

struct obj_header {
  size_t magic;
  size_t size;
};

#define MAGIC_VALUE 0xABCD123456ABCD

static struct obj_header* get_header(void *ptr)
{
  struct obj_header *obj = (struct obj_header*)(((char*)ptr) - sizeof(struct obj_header));
  if (obj->magic != MAGIC_VALUE) {
    printf("invalid address: %p\n", ptr);
    assert(0);
    return NULL;
  }
  return obj;
}

void *__mymalloc(size_t size)
{
  struct obj_header *obj = (struct obj_header*)malloc(size + sizeof(struct obj_header));
  if (obj == NULL) {
     printf("allocation faild: size:%zd\n", size);
     return NULL;
  }
  obj->magic = MAGIC_VALUE;
  obj->size = size;
  total_allocations += size;
  return &obj[1];
}

void __myfree(void *ptr)
{
  struct obj_header *head = get_header(ptr);
  assert(total_allocations >= head->size);
  total_allocations -= head->size;
  free(head);
}

size_t __get_size(void *ptr)
{
  struct obj_header *head = get_header(ptr);
  if (head == NULL) {
    printf("unable to read size; are you not using allocate_memory API\n");
    assert(0);
  }
  return head->size;
}

void verify_size_insert(struct record *arr, int num_records)
{
  if (arr == NULL) {
    printf("record_arr null\n");
    assert(0);
  }
  size_t size = __get_size(arr) / sizeof(struct record);
  if (size < num_records) {
    printf("array size %zd * sizeof(struct record) too small for %d elements\n", 
      size, num_records);
    assert(0);
  }
  if (size >= 2 * num_records) {
    printf("array size %zd * sizeof(struct record) too large for %d elements\n", 
      size, num_records);
    assert(0);
  }
}

void verify_size_delete(struct record *arr, int num_records)
{
  if (arr == NULL) {
    printf("record_arr null\n");
    assert(0);
  }
  size_t size = __get_size(arr) / sizeof(struct record);
  if (size < num_records) {
    printf("array size %zd * sizeof(struct record) too small for %d elements\n", 
      size, num_records);
    assert(0);
  }
  if (size >= 4 * num_records) {
    printf("array size %zd * sizeof(struct record) too large for %d elements\n", 
      size, num_records);
    assert(0);
  }
}

void verify_memory_leak()
{
  if (total_allocations > 4 * sizeof(struct record)) {
    printf("%zd bytes are still allocated\n", total_allocations);
    printf("release memory that is not necessary\n");
    assert(0);
  }
}

#define MAX_RANDOM ((1ULL << 32) - 1)

static unsigned long long __seed = 0;

static unsigned __rand()
{
  __seed = (__seed * 1103515245 + 12345) & MAX_RANDOM;
  return (unsigned)__seed;
}

static char __names[][MAX_LEN] =
 {
   "Sonpari", "Kroor", "Hobo", "Swami",
   "Maya", "Tulsi", "Praful", "Monisha",
   "Hansa", "Jassi", "Ramola", "Rosesh",
   "Mussadi", "Anandi", "Prem", "Hema",
   "Rekha", "Jaya", "Sushma", "Rancho",
   "Baburao", "Chatur", "Vijay", "Gabbar",
   "Pushpa", "Raj", "Gogo", "Devdas",
   "Sardar", "Omkar", "Guddu", "Munna",
   "Uday", "Chhote", "Imran", "Meera",
   "Sunder", "Rani", "Najma", "Kashi",
   "Chand", "Jai", "Veeru", "Thakur",
   "Indra", "Jaspal", "Radha", "Devaki",
   "Komolika", "Dang", "Mogambo", "Kancha",
   "Raka", "Teja", "Shakal", "Jaikant",
   "Katya", "Ravi"
 };

void create_name(char name[MAX_LEN], int seed)
{
  __seed = seed;
  size_t const size = sizeof(__names)/sizeof(__names[0]);
  unsigned idx = __rand() % size;
  size_t len = strlen(__names[idx]);

  memcpy(name, __names[idx], len);
  name[len] = ' ';
  name[len+1] = '0' + (__rand() % 8);
  name[len+2] = '0' + (__rand() % 8);
  name[len+3] = '0' + (__rand() % 8);
  name[len+4] = '0' + (__rand() % 8);
  name[len+5] = '\0';
}

void create_uid(char uid[MAX_LEN], int seed, int verify)
{
  int i;
  __seed = seed;
  for (i = 0; i < MAX_LEN; i++) {
    uid[i] = __rand() % 127;
  }
  assert(!verify || trie_search(__trie_root, uid, MAX_LEN) == 1);
}

static int fast_uid(int seed)
{
	__seed = seed;
	return __rand() % 127;
}

void create_uid_new(char uid[MAX_LEN], int seed)
{
  int i;
  __seed = seed;
  for (i = 0; i < MAX_LEN; i++) {
    uid[i] = __rand() % 127;
  }
  if (__trie_root == NULL) {
    __trie_root = trie_allocate_node('\0', NULL);
  }
  assert(trie_insert(__trie_root, uid, MAX_LEN) == 1);
}

void create_record(struct record *r, int seed)
{
  memset(r, 0, sizeof(*r));
  create_name(r->name, seed);
  create_uid(r->uid, seed, 0);
  r->age = __rand() % 80;
}

void start_time(struct timeval *start)
{
  gettimeofday(start, 0);
}

unsigned long end_time(struct timeval *start)
{
	struct timeval end;
	unsigned long t;

  gettimeofday(&end, 0);
	t = ((end.tv_sec * 1000000) + end.tv_usec) - 
    ((start->tv_sec * 1000000) + start->tv_usec);
  return t/1000;
}


static char __posts[][MAX_MSG_LEN] =
 {
 	 "All I know it's a menatal hospital.",
	 "Obey protocol, do you understand?",
	 "Absolutely.",
	 "What the heck did you do.",
	 "Whathever can happen will happen.",
   "All work and no play makes Jack a dull boy.",
   "Maybe some kind of signal? I don't know.",
   "Carpe diem.",
   "There is no science without experiment.",
   "I don’t want to survive. I want to live.",
   "Take a seat.",
   "What about college?",
   "And things are getting better.",
   "We switched on the tractor.",
   "I have spoken.",
   "Earth is a planet.",
   "Don't underestimate the power of a common man.",
   "This is the way.",
   "Let's get out of here.",
   "This crew represents the best of humanity.",
   "It's gravity.",
   "I like those odds.",
   "I like recursion.",
   "Sit down!",
   "How many men?",
   "Weapons are the part of my religion.",
   "Do you understand this?",
   "Quick sort is a sorting algorithm.",
   "Nobody stumbles in here.",
   "There are many programming languages.",
   "It's a creed.",
   "What sort of anomaly?",
   "The training is nothing. The will is everything. The will to act.",
   "Driven by unshakable faith.",
   "Get busy living, or get busy dying.",
   "We are not meant to save the world.",
   "Mod galat nahi hote, insaan galat hote hain.",
   "Quantum physics is interesting.",
   "Not all who wander are lost.",
   "Good morning.",
   "How does an induction motor start?",
   "Hello!",
   "You are the same decaying organic matter as everything else.",
   "Nice to meet you.",
   "Even the smallest person can change the course of the future.",
   "List is a data structure.",
   "Is that a warmhole?",
   "Despair is only for those who see the end beyond all doubt.",
   "Tree is a data structure.",
   "Elementary, my dear Watson.",
   "We are a by-Product of a lifestyle obsession.",
   "Hence the bravery.",
   "My precious!",
   "A space station?",
   "If you hate a person, you hate something in him that is part of yourself.",
   "How far have you got?",
   "Just keep swimming.",
   "Out beyond ideas of wrongdoing and rightdoing there is a field. I'll meet you there.",
   "All izz well!",
   "Life was like a box of chocolates. You never know what you’re gonna get.",
   "Yesterday I was clever, so I wanted to change the world. Today I am wise, so I am changing myself.",
   "Mankind was born on earth.",
   "Don’t grieve. Anything you lose comes round in another form.",
   "You said ghost didn't exist.",
   "Silence is the language of god, all else is poor translation.",
   "Life is a race. If you don't run fast, you will be like broken anda.",
   "Be empty of worrying. Think of who created thought.",
   "Moon bada hi lool place hai.",
   "Good grammar is essential, Robin.",
   "Badges. We ain’t got no badges!",
   "Yo, Adrian.",
   "To infinity and beyond.",
   "There’s no place like home.",
   "What do you do for a living?",
   "What? Imagine that!",
   "We all wear masks.",
   "What a great idea!",
   "I'm the king of the world.",
   "Hope is a good thing, maybe the best of things. And no good thing ever dies.",
   "Houston, we have a problem.",
   "Just being honest.",
   "I found freedom. Losing all hope was freedom.",
   "We don't read and write poetry because it's cute. We read and write poetry because we are members of the human race.",
   "Come on, are you a man or an amoeba?",
   "A dream is not what you see in sleep.",  
   "Our lives are defined by opportunities, even the ones we miss.",
   "The things you own end up owning you.",
   "Don't think that I don't know that this assignment scares the hell out of you.",
 };


size_t *__msg_count_vid = NULL;
size_t *__msg_count_id = NULL;
size_t *__msg_alive = NULL;
size_t *__msg_dead = NULL;

void initialize_hash_tables(size_t size)
{
	const size_t scaled_size = MSG_SCALE * size * sizeof(size_t);

	__msg_count_id = malloc(size * sizeof(size_t));
	assert(__msg_count_id);
	memset(__msg_count_id, 0, size * sizeof(size_t));

	__msg_count_vid = malloc(scaled_size);
	assert(__msg_count_vid);
	memset(__msg_count_vid, 0, scaled_size);

	__msg_alive = malloc(scaled_size);
	assert(__msg_alive);
	memset(__msg_alive, 0, scaled_size);

	__msg_dead = malloc(scaled_size);
	assert(__msg_dead);
	memset(__msg_dead, 0, scaled_size);
}

static int get_vid(int id, int size) {
	const size_t max_vid = MSG_SCALE * size;

	if (__msg_count_id[id] != 0) {
  	__seed = id;
		id = __rand() % max_vid;
	}
	return id;
}

void create_msg(char msg[MAX_MSG_LEN], int id, int size)
{
  const int num_msgs = sizeof(__posts)/ sizeof(__posts[0]);
	int vid = get_vid(id, size);
	__seed = vid;
  int i1 = __rand() % num_msgs;
  int i2 = __rand() % num_msgs;
  int i3 = __rand() % num_msgs;
  int i4 = __rand() % num_msgs;
  int i5 = __rand() % num_msgs;

  int len = snprintf(msg, MAX_MSG_LEN, "%s %s %s %s %s", 
		__posts[i1], __posts[i2], __posts[i3], __posts[i4], __posts[i5]);
	if (len > MAX_MSG_LEN) {
		len = MAX_MSG_LEN - 1;
	}
  assert(msg[len] == '\0');
	int i;
	for (i = len-1; i > 0; i--) {
		if (msg[i] == '!' || msg[i] == '.' || msg[i] == '?') {
			break;
		}
		msg[i] = '\0';
	}
	__msg_count_vid[vid]++;
	__msg_count_id[id]++;
	__msg_alive[vid] += fast_uid(id);
}

void delete_msg(int id, int size)
{
  const int num_msgs = sizeof(__posts)/ sizeof(__posts[0]);
	if (__msg_count_id[id] > 0) {
		__msg_count_id[id]--;
		int vid = get_vid(id, size);
		__msg_alive[vid] -= fast_uid(id);
		__msg_dead[vid] += fast_uid(id);
	}
}


static int __cmp_name(char *name1, char *name2)
{
  int i;

  for (i = 0; i < MAX_LEN; i++) {
		if (name1[i] == '\0' && name2[i] == '\0') {
			return 0;
		}
    if (name1[i] > name2[i]) {
      return 1;
    }
    else if (name1[i] < name2[i]) {
      return -1;
    }
  }
	assert(0);
  return 0;
}

static int __cmp_uid(char *uid1, char *uid2)
{
  int i;

  for (i = 0; i < MAX_LEN; i++) {
    if (uid1[i] > uid2[i]) {
      return 1;
    }
    else if (uid1[i] < uid2[i]) {
      return -1;
    }
  }
  return 0;
}

void check_array_is_sorted_by_name(struct record *record_arr, size_t num_record, size_t chksum)
{
	assert(record_arr != NULL);
	if (num_record == 1) {
		return;
	}
	size_t i;
	size_t check_sum = 0;
	for (i = 0; i < num_record-1; i++) {
		check_sum += record_arr[i].uid[0];
		if (__cmp_name(record_arr[i+1].name, record_arr[i].name) == -1) {
			printf("array is not sorted\n");
			assert(0);
		}
	}
	check_sum += record_arr[num_record-1].uid[0];
	if (check_sum != chksum) {
		printf("Integrity of data is violated\n");
		assert(0);
	}
}

void check_array_is_sorted_by_uid(struct record *record_arr, size_t num_record, size_t chksum)
{
	assert(record_arr != NULL);
	if (num_record == 1) {
		return;
	}
	size_t i;
	size_t check_sum = 0;
	for (i = 0; i < num_record-1; i++) {
		check_sum += record_arr[i].uid[0];
		if (__cmp_uid(record_arr[i+1].uid, record_arr[i].uid) == -1) {
			printf("array is not sorted\n");
			assert(0);
		}
	}
	check_sum += record_arr[num_record-1].uid[0];
	if (check_sum != chksum) {
		printf("Integrity of data is violated\n");
		assert(0);
	}
}

void verify_chksum(struct record *record_arr, size_t num_record, size_t chksum)
{
	size_t check_sum = 0, i;
	for (i = 0; i < num_record; i++) {
		check_sum += record_arr[i].uid[0];
	}
	if (check_sum != chksum) {
		printf("Integrity of data is violated\n");
		assert(0);
	}
}
