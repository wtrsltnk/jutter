#include "randm.h"

static int __random_cache[] = {
     14,	205,	188,	 87,	159,	143,	 28,	181,	 54,	 58,
    161,	 50,	119,	114,	255,	 80,	130,	 60,	 53,	70,
    113,	  2,	123,	 67,	214,	208,	146,	 35,	186,	  7,
    222,	 71,	 76,	  9,	141,	 97,	123,	 83,	215,	 68,
    220,	 82,	186,	  4,	197,	 44,	200,	192,	 85,	209,
    216,	  8,	 34,	221,	161,	 43,	123,	240,	 47,	218,
    209,	  7,	 52,	150,	 17,	209,	216,	 88,	 17,	148,
     63,	131,	 14,	 86,	222,	203,	153,	  0,	102,	 26,
    119,	 20,	119,	122,	246,	244,	239,	  8,	 14,	153,
    215,	112,	185,	250,	 14,	106,	142,	187,	199,	142
};

RandomNumberGenerator::RandomNumberGenerator()
    : _seed(1), _index(0)
{ }

RandomNumberGenerator::~RandomNumberGenerator()
{ }

void RandomNumberGenerator::setSeed(int seed)
{
    this->_seed = seed;
    this->reset();
}

int RandomNumberGenerator::generate_random_int(int max)
{
    return (__random_cache[(this->_seed * this->_index++) % 100] % max);
}

int RandomNumberGenerator::operator () (int max)
{
    return this->generate_random_int(max);
}

void RandomNumberGenerator::reset()
{
    this->_index = 0;
}
