typedef enum _Test {
    TestNone = 0,
    TestA,
    TestB,
    TestC,
    TestD,
    TestE
} Test;

#pragma pack(push, 1)

struct _InnerStructure
{
    char a;
    long b;
    Test t;
} InnerStructure;

#pragma pack(pop)

typedef struct _TestStructure
{
    InnerStructure inner;

    struct _A {
        unsigned int a;
        unsigned int b;
        unsigned int c;
    } A;

    union {
		struct
		{
			unsigned d : 1;
			unsigned e : 1;
			unsigned f : 1;
		} B;
		unsigned _def;
	};

	union {
		uint64_t ghi;
		struct
		{
			uint16_t g;
			uint16_t h;
			uint16_t i;
		};
	} C;

    union D {
		uint64_t jkm;
		struct
		{
			uint16_t j;
			uint16_t k;
			uint16_t m;
		};
	};

	struct
	{
		uint32_t n : 1;
		uint32_t p : 2;
		uint32_t q : 3;
	} E;

    struct F
	{
		uint32_t r : 4;
		uint32_t s : 8;
		uint32_t t : 16;
	};

} TestStructure;
