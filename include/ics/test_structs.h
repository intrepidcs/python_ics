
typedef struct _TestStructure
{
    union {
		struct
		{
			unsigned first : 1;
			unsigned second : 1;
			unsigned third : 1;
		} AnonUnionStruct;
		unsigned AnonUnionflags;
	};

	union {
		uint64_t word;
		struct
		{
			uint16_t first;
			uint16_t second;
			uint16_t third;
		};
	} NamedUnionWithAnonStruct;

    union NamedUnionWithAnonStruct2 {
		uint64_t word;
		struct
		{
			uint16_t first;
			uint16_t second;
			uint16_t third;
		};
	};

	struct
	{
		uint32_t first : 1;
		uint32_t second : 1;
		uint32_t third : 1;
		uint32_t fourth : 1;
		uint32_t fifth : 1;
		uint32_t sixth : 1;
		uint32_t seventh : 26;
	} NamedStruct;

    struct NamedStruct2
	{
		uint32_t first : 1;
		uint32_t second : 1;
		uint32_t third : 1;
		uint32_t fourth : 1;
		uint32_t fifth : 1;
		uint32_t sixth : 1;
		uint32_t seventh : 26;
	};
} TestStructure;