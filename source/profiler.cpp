#include <performance!/profiler.h>

#include <chrono>
#include <unordered_map>

typedef struct Profiler_Frame {
	u64 milliseconds_start;
	u64 milliseconds_end;
} Profiler_Frame;

u64 get_system_milliseconds() {
	return std::chrono::duration_cast<std::chrono::milliseconds>(std::chrono::system_clock::now().time_since_epoch()).count();
}