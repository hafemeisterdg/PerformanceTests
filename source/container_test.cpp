#include <performance!/container_test.h>

#include <unordered_map>
#include <list>

#define LIST_ITEM_COUNT 8000000

internal void linked_list_find_test();
internal void hashmap_find_test();

void container_test() {
	linked_list_find_test();
	hashmap_find_test();
}

internal void linked_list_find_test() {
	printf("Inserting %u items into linked list, this should be pretty fast! \n", LIST_ITEM_COUNT);

	std::list<u32> list;
	for (int i = 0; i < LIST_ITEM_COUNT; i++) {
		list.push_back(i);
	}

	u64 start_time;
	u64 end_time;

	// Find 50th test
	start_time = get_system_milliseconds();
	std::list<u32>::iterator it = std::find(list.begin(), list.end(), 50);
	end_time = get_system_milliseconds();
	printf("Linked List Found Element %u in %llu ms \n", *it, end_time - start_time);

	// Find midway test
	start_time = get_system_milliseconds();
	it = std::find(list.begin(), list.end(), LIST_ITEM_COUNT / 2);
	end_time = get_system_milliseconds();
	printf("Linked List Found Element %u in %llu ms \n", *it, end_time - start_time);

	// Find last test
	start_time = get_system_milliseconds();
	it = std::find(list.begin(), list.end(), LIST_ITEM_COUNT - 1);
	end_time = get_system_milliseconds();
	printf("Linked List Found Element %u in %llu ms \n", *it, end_time - start_time);
}

internal void hashmap_find_test() {
	printf("Inserting %u items into hashmap, this could take a bit insertion isn't the maps strong suit \n", LIST_ITEM_COUNT);
	std::unordered_map<u32, u32> map;

	for (int i = 0; i < LIST_ITEM_COUNT; i++) {
		map[i] = i;
	}

	u64 start_time;
	u64 end_time;

	// Find 50th test
	start_time = get_system_milliseconds();
	std::unordered_map<u32, u32>::iterator it = map.find(50);
	end_time = get_system_milliseconds();
	printf("Hash Map Found Element %u in %llu ms \n", it->second, end_time - start_time);

	// Find midway test
	start_time = get_system_milliseconds();
	it = map.find(LIST_ITEM_COUNT / 2);
	end_time = get_system_milliseconds();
	printf("Hash Map Found Element %u in %llu ms \n", it->second, end_time - start_time);

	// Find last test
	start_time = get_system_milliseconds();
	it = map.find(LIST_ITEM_COUNT - 1);
	end_time = get_system_milliseconds();
	printf("Hash Map Found Element %u in %llu ms \n", it->second, end_time - start_time);
}