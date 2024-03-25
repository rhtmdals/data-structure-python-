#include <stdio.h>
#include <stdlib.h>
#include <string.h>

// Define ListNode structure
typedef struct ListNode {
    char* item;
    struct ListNode* next;
    struct ListNode* prev;
} ListNode;

// Define LinkedListBasic structure
typedef struct {
    ListNode* head;
    ListNode* tail;
    int numItems;
} LinkedListBasic;

// Function prototypes for LinkedListBasic
LinkedListBasic* createLinkedList();
void append(LinkedListBasic* list, char* newItem);
void removeTail(LinkedListBasic* list);
int size(LinkedListBasic* list);
int count(LinkedListBasic* list, char* x);
void printList(LinkedListBasic* list);
void removeItem(LinkedListBasic* list, char* x);
void destroyLinkedList(LinkedListBasic* list);

// CacheSimulator structure
typedef struct {
    int cache_slots;
    int cache_hit;
    int tot_cnt;
    LinkedListBasic* cache_list;
} CacheSimulator;

// Function prototypes for CacheSimulator
CacheSimulator* createCacheSimulator(int cache_slots);
void do_sim(CacheSimulator* cache_sim, char* page);
void print_stats(CacheSimulator* cache_sim);
void destroyCacheSimulator(CacheSimulator* cache_sim);

int main() {
    FILE* data_file = fopen("C:/Users/kevin/OneDrive/문서/GitHub/data-structure-python-/lru_sim/linkbench.trc", "r");
    if (data_file == NULL) {
        fprintf(stderr, "Error opening file\n");
        return 1;
    }
    char line[100]; // Assuming max line length is 100 characters
    while (fgets(line, sizeof(line), data_file)) {
        // Do something with each line
        // For now, let's just print it
        printf("%s", line);
    }
    fclose(data_file);
    return 0;
}

// Implementations of LinkedListBasic functions

LinkedListBasic* createLinkedList() {
    LinkedListBasic* list = (LinkedListBasic*)malloc(sizeof(LinkedListBasic));
    list->head = (ListNode*)malloc(sizeof(ListNode));
    list->tail = (ListNode*)malloc(sizeof(ListNode));
    list->tail->prev = list->head;
    list->head->next = list->tail;
    list->numItems = 0;
    return list;
}

void append(LinkedListBasic* list, char* newItem) {
    ListNode* newNode = (ListNode*)malloc(sizeof(ListNode));
    newNode->item = strdup(newItem); // Duplicate the string
    newNode->next = list->head->next;
    list->head->next->prev = newNode;
    list->head->next = newNode;
    newNode->prev = list->head;
    list->numItems++;
}

void removeTail(LinkedListBasic* list) {
    if (list->numItems > 0) {
        ListNode* prevNode = list->tail->prev->prev;
        free(list->tail->prev->item); // Free the duplicated string
        free(list->tail->prev);
        prevNode->next = list->tail;
        list->tail->prev = prevNode;
        list->numItems--;
    }
}

int size(LinkedListBasic* list) {
    return list->numItems;
}

int count(LinkedListBasic* list, char* x) {
    ListNode* curr = list->head->next;
    while (curr != NULL) {
        if (strcmp(curr->item, x) == 0) {
            return 1;
        }
        curr = curr->next;
    }
    return 0;
}

void printList(LinkedListBasic* list) {
    ListNode* curr = list->head->next;
    while (curr != NULL) {
        printf("%s ", curr->item);
        curr = curr->next;
    }
    printf("\n");
}

void removeItem(LinkedListBasic* list, char* x) {
    ListNode* curr = list->head->next;
    while (curr != NULL) {
        if (strcmp(curr->item, x) == 0) {
            ListNode* prevNode = curr->prev;
            ListNode* nextNode = curr->next;
            free(curr->item);
            free(curr);
            prevNode->next = nextNode;
            nextNode->prev = prevNode;
            list->numItems--;
            return;
        }
        curr = curr->next;
    }
}

void destroyLinkedList(LinkedListBasic* list) {
    ListNode* curr = list->head;
    while (curr != NULL) {
        ListNode* temp = curr;
        curr = curr->next;
        free(temp->item);
        free(temp);
    }
    free(list);
}

// Implementations of CacheSimulator functions

CacheSimulator* createCacheSimulator(int cache_slots) {
    CacheSimulator* cache_sim = (CacheSimulator*)malloc(sizeof(CacheSimulator));
    cache_sim->cache_slots = cache_slots;
    cache_sim->cache_hit = 0;
    cache_sim->tot_cnt = 1;
    cache_sim->cache_list = createLinkedList();
    return cache_sim;
}

void do_sim(CacheSimulator* cache_sim, char* page) {
    if (count(cache_sim->cache_list, page) > 0) {
        removeItem(cache_sim->cache_list, page);
        append(cache_sim->cache_list, page);
        cache_sim->cache_hit++;
        cache_sim->tot_cnt++;
    } else {
        if (size(cache_sim->cache_list) < cache_sim->cache_slots) {
            append(cache_sim->cache_list, page);
        } else {
            removeTail(cache_sim->cache_list);
            append(cache_sim->cache_list, page);
        }
        cache_sim->tot_cnt++;
    }
}

void print_stats(CacheSimulator* cache_sim) {
    printf("cache_slot = %d, cache_hit = %d, hit ratio = %f\n",
           cache_sim->cache_slots, cache_sim->cache_hit,
           (float)cache_sim->cache_hit / cache_sim->tot_cnt);
}

void destroyCacheSimulator(CacheSimulator* cache_sim) {
    destroyLinkedList(cache_sim->cache_list);
    free(cache_sim);
}
