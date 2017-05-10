#include "catch.hpp"
#include <iostream>

#include "../src/ui/animatedvalue.h"

TEST_CASE( "Test animated value defaults", "[animatedvalue]" )
{
    AnimatedValue val;

    val.start();

    REQUIRE(val.value() == 0.0f);
    val.update(0.1f);
    REQUIRE(val.value() == 0.0f);
}

TEST_CASE( "Test animated value start and stop", "[animatedvalue]" )
{
    AnimatedValue val;

    val.from(3.0f).to(6.0f).in(2.0).start();

    REQUIRE(val.value() == 3.0f);
    val.update(1.0f);
    REQUIRE(val.value() == 4.5f);
    val.update(1.0f);
    REQUIRE(val.value() == 6.0f);

    val.stop();
    REQUIRE(val.value() == 6.0f);

    val.start();
    REQUIRE(val.value() == 3.0f);
}

TEST_CASE( "Test animated value start and resume", "[animatedvalue]" )
{
    AnimatedValue val;

    val.from(3.0f).to(6.0f).in(2.0).start();
    REQUIRE(val.value() == 3.0f);

    val.update(1.0f);
    val.stop();
    REQUIRE(val.value() == 4.5f);

    // Since we are stopped, nothing will happen to the value
    val.update(1.0f);
    REQUIRE(val.value() == 4.5f);

    // Resuming will not change the value eigther
    val.resume();
    REQUIRE(val.value() == 4.5f);

    // but in "running" state we do change the value on update
    val.update(1.0f);
    REQUIRE(val.value() == 6.0f);
}

TEST_CASE( "Test animated value reverse", "[animatedvalue]" )
{
    AnimatedValue val;

    val.from(3.0f).to(6.0f).in(2.0).start();
    REQUIRE(val.value() == 3.0f);

    val.reverse();
    REQUIRE(val.value() == 6.0f);
}
