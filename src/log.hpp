#define DEBUG 1
#if DEBUG == 1
#define LOG(msg) std::cout << msg << "\n"
#else
#define LOG(msg)
#endif
