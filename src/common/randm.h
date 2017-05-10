#ifndef RANDM_H
#define RANDM_H

class RandomNumberGenerator
{
    int _seed;
    int _index;
public:
    RandomNumberGenerator();
    virtual ~RandomNumberGenerator();

    void setSeed(int seed);
    int generate_random_int(int max = 255);
    int operator () (int max = 255);
    void reset();
};

#endif // RANDM_H
