#include "catch.hpp"
#include <iostream>

#include "../src/common/highscore.h"

TEST_CASE( "Test indexOf and sortByPoints", "[highscore]" ) {
    std::list<DriveScore> scores;
    DriveScore t;

    for (int i = 0; i < 10; i++)
    {
        auto drive = DriveScore();
        drive._id = i;
        drive._name = "name";
        drive._level = "level";
        drive._attempts = 5;
        drive._completions = 5;
        drive._points = i;
        drive._touchdown = true;
        scores.push_back(drive);

        if (i == 3) t = drive;
    }

    REQUIRE(scores.front()._points == 0);
    REQUIRE(HighScore::indexOf(scores, t) == 3);

    HighScore::sortByPoints(scores);
    REQUIRE(scores.front()._points == 9);
    REQUIRE(HighScore::indexOf(scores, t) == 6);
}

TEST_CASE( "Test sortByPoints order on time, completions and attempts", "[highscore]" ) {

    std::list<DriveScore> scores;

    auto drive1 = DriveScore();
    drive1._points = 100;
    drive1._timeInSeconds = 10;
    drive1._attempts = 5;
    drive1._completions = 5;
    scores.push_back(drive1);

    auto drive2 = DriveScore();
    drive2._points = 111;
    drive2._timeInSeconds = 10;
    drive2._attempts = 5;
    drive2._completions = 5;
    scores.push_back(drive2);

    HighScore::sortByPoints(scores);
    REQUIRE(HighScore::indexOf(scores, drive2) == 0);
    REQUIRE(HighScore::indexOf(scores, drive1) == 1);

    auto drive3 = DriveScore();
    drive3._points = 111;
    drive3._timeInSeconds = 5;
    drive3._attempts = 5;
    drive3._completions = 5;
    scores.push_back(drive3);

    HighScore::sortByPoints(scores);
    REQUIRE(HighScore::indexOf(scores, drive3) == 0);
    REQUIRE(HighScore::indexOf(scores, drive2) == 1);
    REQUIRE(HighScore::indexOf(scores, drive1) == 2);
}
