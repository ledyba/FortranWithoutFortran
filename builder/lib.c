#if __LP64__
typedef unsigned long long intptr_t;
#else
typedef unsigned long intptr_t;
#endif
double fsqrt(double v)
{
	intptr_t d0;
	__asm__ (
		".intel_syntax noprefix;"
		"fld qword ptr [%0];"
		"fsqrt;"
		"fstp qword ptr [%0];"
		".att_syntax;"
		: "=&r"(d0)
		: "0"((intptr_t) &v)
		: "eax", "ecx"
	);
	return v;
}
double fpi()
{
	double v;
	intptr_t d0;
	__asm__ (
		".intel_syntax noprefix;"
		"fldpi;"
		"fstp qword ptr [%0];"
		".att_syntax;"
		: "=&r"(d0)
		: "0"((intptr_t) &v)
		: "eax", "ecx"
	);
	return v;
}
double fsin(double v)
{
	intptr_t d0;
	__asm__ (
		".intel_syntax noprefix;"
		"fld qword ptr [%0];"
		"fsin;"
		"fstp qword ptr [%0];"
		".att_syntax;"
		: "=&r"(d0)
		: "0"((intptr_t) &v)
		: "eax", "ecx"
	);
	return v;
}
double fcos(double v)
{
	intptr_t d0;
	__asm__ (
		".intel_syntax noprefix;"
		"fld qword ptr [%0];"
		"fcos;"
		"fstp qword ptr [%0];"
		".att_syntax;"
		: "=&r"(d0)
		: "0"((intptr_t) &v)
		: "eax", "ecx"
	);
	return v;
}
double fabs(double v)
{
	intptr_t d0;
	__asm__ (
		".intel_syntax noprefix;"
		"fld qword ptr [%0];"
		"fabs;"
		"fstp qword ptr [%0];"
		".att_syntax;"
		: "=&r"(d0)
		: "0"((intptr_t) &v)
		: "eax", "ecx"
	);
	return v;
}

