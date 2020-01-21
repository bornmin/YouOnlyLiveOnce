#ifndef ALLENUM_HPP
#define ALLENUM_HPP

enum WEEK{
    SUNDAY = 0,//0은 써도되고 안써도 된다.
    MONDAY,//밑에있는 수들은 첫번째 설정한 값에서 1씩 추가되어 설정된다.즉 MONDAY는 1이된다.
    TUESDAY,
    WEDNESDAY,
    THURSDAY,
    FRIDAY,
    SATURDAY
};

enum QTTESTENUM{
    TEST_FIRST = 0,
    TEST_SECOND = 1,
    TEST_THIRD = 2
};

#endif // ALLENUM_HPP
