/*
 * This source file is part of ARK
 * For the latest info, see https://github.com/ArkNX
 *
 * Copyright (c) 2013-2019 ArkNX authors.
 *
 * Licensed under the Apache License, Version 2.0 (the "License"),
 * you may not use this file except in compliance with the License.
 * You may obtain a copy of the License at
 *
 *     http://www.apache.org/licenses/LICENSE-2.0
 *
 * Unless required by applicable law or agreed to in writing, software
 * distributed under the License is distributed on an "AS IS" BASIS,
 * WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
 * See the License for the specific language governing permissions and
 * limitations under the License.
 *
 */

#pragma once

#include "base/AFPlatform.hpp"
#include "base/AFMacros.hpp"

namespace ark {

class AFTimespan
{
public:
    using TimeDiff = int64_t;

    static const TimeDiff MILLISECONDS = 1L;
    static const TimeDiff SECOND_MS = 1000 * MILLISECONDS;
    static const TimeDiff MINUTE_MS = 60 * SECOND_MS;
    static const TimeDiff HOUR_MS = 60 * MINUTE_MS;
    static const TimeDiff DAY_MS = 24 * HOUR_MS;
    static const TimeDiff WEEK_MS = 7 * DAY_MS;
    const int MONTH_DAY[12] = {31, 28, 31, 30, 31, 30, 31, 31, 30, 31, 30, 31};

    AFTimespan()
        : span_(0)
    {
    }

    explicit AFTimespan(TimeDiff milliseconds)
        : span_(milliseconds)
    {
    }

    AFTimespan(int seconds, int milliseconds)
        : span_(TimeDiff(seconds) * SECOND_MS + milliseconds)
    {
    }

    AFTimespan(int days, int hours, int seconds, int milliseconds)
        : span_(TimeDiff(milliseconds) + TimeDiff(seconds) * SECOND_MS + TimeDiff(hours) * HOUR_MS +
                TimeDiff(days) * DAY_MS)
    {
    }

    AFTimespan(const AFTimespan& timespan)
        : span_(timespan.span_)
    {
    }

    ~AFTimespan() {}

    AFTimespan& operator=(const AFTimespan& timespan)
    {
        if (this != &timespan)
        {
            this->span_ = timespan.span_;
        }
        return *this;
    }

    AFTimespan& operator=(TimeDiff microseconds)
    {
        span_ = microseconds;
        return *this;
    }

    AFTimespan& assign(int days, int hours, int minutes, int seconds, int milliseconds = 0)
    {
        span_ = TimeDiff(milliseconds) + TimeDiff(seconds) * SECOND_MS + TimeDiff(hours) * HOUR_MS +
                TimeDiff(days) * DAY_MS;
        return *this;
    }

    AFTimespan& assign(int seconds, int milliseconds = 0)
    {
        span_ = TimeDiff(milliseconds) + TimeDiff(seconds) * SECOND_MS;
        return *this;
    }

    void swap(AFTimespan& timespan)
    {
        std::swap(span_, timespan.span_);
    }

    inline bool operator==(const AFTimespan& ts) const
    {
        return span_ == ts.span_;
    }

    inline bool operator!=(const AFTimespan& ts) const
    {
        return span_ != ts.span_;
    }

    inline bool operator>(const AFTimespan& ts) const
    {
        return span_ > ts.span_;
    }

    inline bool operator>=(const AFTimespan& ts) const
    {
        return span_ >= ts.span_;
    }

    inline bool operator<(const AFTimespan& ts) const
    {
        return span_ < ts.span_;
    }

    inline bool operator<=(const AFTimespan& ts) const
    {
        return span_ <= ts.span_;
    }

    inline bool operator==(TimeDiff milliseconds) const
    {
        return span_ == milliseconds;
    }

    inline bool operator!=(TimeDiff milliseconds) const
    {
        return span_ != milliseconds;
    }

    inline bool operator>(TimeDiff milliseconds) const
    {
        return span_ > milliseconds;
    }

    inline bool operator>=(TimeDiff milliseconds) const
    {
        return span_ >= milliseconds;
    }

    inline bool operator<(TimeDiff milliseconds) const
    {
        return span_ < milliseconds;
    }

    inline bool operator<=(TimeDiff milliseconds) const
    {
        return span_ <= milliseconds;
    }

    inline AFTimespan operator+(const AFTimespan& d) const
    {
        return AFTimespan(span_ + d.span_);
    }

    inline AFTimespan operator-(const AFTimespan& d) const
    {
        return AFTimespan(span_ - d.span_);
    }

    inline AFTimespan& operator+=(const AFTimespan& d)
    {
        span_ += d.span_;
        return *this;
    }

    inline AFTimespan& operator-=(const AFTimespan& d)
    {
        span_ -= d.span_;
        return *this;
    }

    inline AFTimespan operator+(TimeDiff milliseconds) const
    {
        return AFTimespan(span_ + milliseconds);
    }

    inline AFTimespan operator-(TimeDiff milliseconds) const
    {
        return AFTimespan(span_ - milliseconds);
    }

    inline AFTimespan& operator+=(TimeDiff milliseconds)
    {
        span_ += milliseconds;
        return *this;
    }

    inline AFTimespan& operator-=(TimeDiff milliseconds)
    {
        span_ -= milliseconds;
        return *this;
    }

    inline int days() const
    {
        return int(span_ / DAY_MS);
    }

    inline int hours() const
    {
        return int((span_ / HOUR_MS) % 24);
    }

    inline int totalHours() const
    {
        return int((span_ / HOUR_MS));
    }

    inline int minutes() const
    {
        return int((span_ / MINUTE_MS) % 60);
    }

    inline int totalMinutes() const
    {
        return int(span_ / MINUTE_MS);
    }

    inline int seconds() const
    {
        return int((span_ / SECOND_MS) % 60);
    }

    inline int totalSeconds() const
    {
        return int(span_ / SECOND_MS);
    }

    inline int milliseconds() const
    {
        return int(span_ % 1000);
    }

    inline TimeDiff totalMilliseconds() const
    {
        return span_;
    }

private:
    // milliseconds
    TimeDiff span_;
};

////////////////////////////////////////////////////////////////////////

class AFDateTime
{
public:
    enum Months
    {
        JANUARY = 1,
        FEBRUARY,
        MARCH,
        APRIL,
        MAY,
        JUNE,
        JULY,
        AUGUST,
        SEPTEMBER,
        OCTOBER,
        NOVEMBER,
        DECEMBER
    };

    enum DaysOfWeek
    {
        SUNDAY = 0,
        MONDAY,
        TUESDAY,
        WEDNESDAY,
        THURSDAY,
        FRIDAY,
        SATURDAY
    };

    // Monotonic UTC time value in microsecond resolution,
    // with base time midnight, January 1, 1970.
    using TimeVal = int64_t;
    // Difference between two TimeVal values in milliseconds.
    using TimeDiff = int64_t;

    static const TimeVal TIMEVAL_MIN = (std::numeric_limits<int64_t>::min)();
    static const TimeVal TIMEVAL_MAX = (std::numeric_limits<int64_t>::max)();

    // Creates a timestamp with the current time.
    AFDateTime()
    {
        Update();
    }

    // Creates a timestamp from the given time value
    //(milliseconds since midnight, January 1, 1970).
    AFDateTime(TimeVal tv)
        : ts_(tv)
    {
    }

    AFDateTime(int year, int month, int day, int hour = 0, int minute = 0, int second = 0, int tzd = 8)
    {
        struct tm tmp_tm;
        tmp_tm.tm_year = year - 1900;
        tmp_tm.tm_mon = month - 1;
        tmp_tm.tm_mday = day;
        tmp_tm.tm_hour = hour;
        tmp_tm.tm_min = minute;
        tmp_tm.tm_sec = second;
        tmp_tm.tm_isdst = -1;
        time_t time = std::mktime(&tmp_tm);
        ts_ = TimeVal(time * Resolution()) + tzd * AFTimespan::HOUR_MS;
    }

    // Copy constructor
    AFDateTime(const AFDateTime& other)
    {
        ts_ = other.ts_;
    }
    // Destroys the timestamp
    ~AFDateTime() = default;

    AFDateTime& operator=(const AFDateTime& other)
    {
        if (this != &other)
        {
            ts_ = other.ts_;
        }

        return *this;
    }

    AFDateTime& operator=(TimeVal& tv)
    {
        ts_ = tv;
        return *this;
    }

    void Update()
    {
        using namespace std::chrono;
        ts_ = duration_cast<milliseconds>(system_clock::now().time_since_epoch()).count();
    }

    /// Swaps the Timestamp with another one.
    void swap(AFDateTime& timestamp)
    {
        std::swap(ts_, timestamp.ts_);
    }

    bool operator==(const AFDateTime& ts) const
    {
        return ts_ == ts.ts_;
    }

    bool operator!=(const AFDateTime& ts) const
    {
        return ts_ != ts.ts_;
    }

    bool operator>(const AFDateTime& ts) const
    {
        return ts_ > ts.ts_;
    }

    bool operator>=(const AFDateTime& ts) const
    {
        return ts_ >= ts.ts_;
    }

    bool operator<(const AFDateTime& ts) const
    {
        return ts_ < ts.ts_;
    }

    bool operator<=(const AFDateTime& ts) const
    {
        return ts_ <= ts.ts_;
    }

    AFDateTime operator+(TimeDiff d) const
    {
        return AFDateTime(ts_ + d);
    }

    AFDateTime operator-(TimeDiff d) const
    {
        return AFDateTime(ts_ - d);
    }

    AFDateTime& operator+=(TimeDiff d)
    {
        ts_ += d;
        return *this;
    }

    AFDateTime& operator-=(TimeDiff d)
    {
        ts_ -= d;
        return *this;
    }

    AFDateTime operator+(const AFTimespan& span) const
    {
        return *this + span.totalMilliseconds();
    }

    AFDateTime operator-(const AFTimespan& span) const
    {
        return *this - span.totalMilliseconds();
    }

    TimeDiff operator-(const AFDateTime& ts) const
    {
        return ts_ - ts.ts_;
    }

    AFDateTime& operator+=(const AFTimespan& span)
    {
        return *this += span.totalMilliseconds();
    }

    AFDateTime& operator-=(const AFTimespan& span)
    {
        return *this -= span.totalMilliseconds();
    }

    // Returns the timestamp expressed in time_t.
    // ime_t base time is midnight, January 1, 1970.
    // Resolution is one second.
    std::time_t GetTime() const
    {
        return std::time_t(ts_ / Resolution());
    }

    // Returns the timestamp expressed in milliseconds
    // since the Unix epoch, midnight, January 1, 1970.
    TimeVal GetMilliseconds()
    {
        return ts_;
    }

    // Returns the time elapsed since the time denoted by
    // the timestamp. Equivalent to Timestamp() - *this.
    TimeDiff GetElapsed() const
    {
        AFDateTime now;
        return now - *this;
    }

    // Returns true diff the given interval has passed
    // since the time denoted by the timestamp.
    bool IsElapsed(TimeDiff interval) const
    {
        AFDateTime now;
        TimeDiff diff = now - *this;
        return diff >= interval;
    }

    // Returns the raw time value.
    // Same as epochMicroseconds().
    TimeVal Raw() const
    {
        return ts_;
    }

    // Returns utc tm data
    std::tm GetUTCTime() const
    {
        std::tm tm;
        time_t time = GetTime();
#ifdef ARK_PLATFORM_WIN
        gmtime_s(&tm, &time);
#else
        gmtime_r(&time, &tm);
#endif
        return tm;
    }

    // Return local tm data
    std::tm GetLocalTime() const
    {
        time_t time = GetTime();
        std::tm tm;
#ifdef ARK_PLATFORM_WIN
        localtime_s(&tm, &time);
#else
        localtime_r(&time, &tm);
#endif
        return tm;
    }

    // Returns the year.
    int GetYear() const
    {
        std::tm tm = GetUTCTime();
        return tm.tm_year + 1900;
    }

    // Returns the month (1 to 12).
    int GetMonth() const
    {
        std::tm tm = GetUTCTime();
        return tm.tm_mon + 1;
    }

    /// Returns the week number within the year.
    /// FirstDayOfWeek should be either SUNDAY (0) or MONDAY (1).
    /// The returned week number will be from 0 to 53. Week number 1 is the week
    /// containing January 4. This is in accordance to ISO 8601.
    ///
    /// The following example assumes that firstDayOfWeek is MONDAY. For 2005, which started
    /// on a Saturday, week 1 will be the week starting on Monday, January 3.
    /// January 1 and 2 will fall within week 0 (or the last week of the previous year).
    ///
    /// For 2007, which starts on a Monday, week 1 will be the week starting on Monday, January 1.
    /// There will be no week 0 in 2007.
    int GetWeekOfYear(int firstDayOfWeek = MONDAY) const
    {
        ARK_ASSERT_NO_EFFECT(firstDayOfWeek >= SUNDAY && firstDayOfWeek <= SATURDAY);

        // find the first firstDayOfWeek.
        int baseDay = 1;

        while (AFDateTime(GetYear(), 1, baseDay).GetDayOfWeek() != firstDayOfWeek)
            ++baseDay;

        //baseDay is the dayofYear of first firstDayOfWeek and from 1.
        //day as the dayOfYear of currentDay should also from 1.
        //otherwise (day-baseDay) fail to represent the gap_days between them.
        //GetDayOfYear start from 0
        //so day should plus one
        int day = GetDayOfYear();
        day++;
        int offs = baseDay <= 4 ? 0 : 1; //weekofYear of baseDay
        if (day < baseDay)
        {
            return offs;
        }
        else
        {
            return (day - baseDay) / 7 + 1 + offs;
        }
    }

    // Returns the day within the month (1 to 31).
    int GetDay(bool is_monday_first_day = true) const
    {
        std::tm tm = GetUTCTime();
        return tm.tm_mday;
    }

    // Returns the weekday (0 to 6, where
    // 0 = Sunday, 1 = Monday, ..., 6 = Saturday).
    int GetDayOfWeek(int firstDayOfWeek = MONDAY) const
    {
        std::tm tm = GetUTCTime();
        if (firstDayOfWeek == MONDAY)
        {
            return ((tm.tm_wday == 0) ? 7 : tm.tm_wday);
        }
        else
        {
            return tm.tm_wday;
        }
    }

    // Returns the number of the day in the year.
    // January 1 is 1, February 1 is 32, etc.
    int GetDayOfYear() const
    {
        std::tm tm = GetUTCTime();
        return tm.tm_yday;
    }

    // Returns the hour (0 to 23).
    int GetHour() const
    {
        std::tm tm = GetUTCTime();
        return tm.tm_hour;
    }

    // Returns the hour (0 to 12).
    int GethourAMPM() const
    {
        int hour = GetHour();

        if (hour < 1)
        {
            return 12;
        }
        else if (hour > 12)
        {
            return hour - 12;
        }
        else
        {
            return hour;
        }
    }

    /// Returns true if hour < 12;
    bool IsAM() const
    {
        return GetHour() < 12;
    }

    /// Returns true if hour >= 12.
    bool IsPM() const
    {
        return GetHour() >= 12;
    }

    /// Returns the minute (0 to 59).
    int GetMinute() const
    {
        std::tm tm = GetUTCTime();
        return tm.tm_min;
    }

    /// Returns the second (0 to 59).
    int GetSecond() const
    {
        std::tm tm = GetUTCTime();
        return tm.tm_sec;
    }

    bool IsLeapYear() const
    {
        int year = GetYear();
        return IsLeapYear(year);
    }

    bool SameMinute(TimeVal time)
    {
        AFDateTime xTime(time);
        return (xTime.GetMinute() == GetMinute() && xTime.GetHour() == GetHour() && xTime.GetDay() == GetDay() &&
                xTime.GetMonth() == GetMonth() && xTime.GetYear() == GetYear());
    }

    bool SameHour(TimeVal time)
    {
        AFDateTime xTime(time);
        return (xTime.GetHour() == GetHour() && xTime.GetDay() == GetDay() && xTime.GetMonth() == GetMonth() &&
                xTime.GetYear() == GetYear());
    }

    bool SameDay(TimeVal time)
    {
        AFDateTime xTime(time);
        return (xTime.GetDay() == GetDay() && xTime.GetMonth() == GetMonth() && xTime.GetYear() == GetYear());
    }

    bool SameMonth(TimeVal time)
    {
        AFDateTime xTime(time);
        return (xTime.GetMonth() == GetMonth() && xTime.GetYear() == GetYear());
    }

    bool SameYear(TimeVal time)
    {
        AFDateTime xTime(time);
        return (xTime.GetYear() == GetYear());
    }

    bool SameWeek(TimeVal time)
    {
        if (!SameYear(time))
        {
            return false;
        }

        if (SameDay(time))
        {
            return true;
        }

        AFDateTime xTime(time);
        return (GetWeekOfYear() == xTime.GetWeekOfYear());
    }

    std::string ToString()
    {
        std::tm tm = GetLocalTime(); // local time
        static char timeBuff[32] = {0};
        std::strftime(timeBuff, sizeof(timeBuff), "%Y/%m/%d %H:%M:%S", &tm);
        return std::string(timeBuff);
    }

    std::string ToISO8601String()
    {
        std::tm tm = GetUTCTime(); // UTC time
        static char timeBuff[64] = {0};
        std::strftime(timeBuff, sizeof(timeBuff), "%FT%TZ", &tm);
        return std::string(timeBuff);
    }
    static bool IsLeapYear(int year)
    {
        return (year % 4) == 0 && ((year % 100) != 0 || (year % 400) == 0);
    }

    // Returns the number of days in the given month
    // and year. Month is from 1 to 12.
    static int GetDaysOfMonth(int year, int month)
    {
        ARK_ASSERT_NO_EFFECT(month >= 1 && month <= 12);

        if (month < 1 || month > 12)
        {
            return -1;
        }

        static int daysOfMonthTable[] = {0, 31, 28, 31, 30, 31, 30, 31, 31, 30, 31, 30, 31};

        if (month == 2 && IsLeapYear(year))
            return 29;
        else
            return daysOfMonthTable[month];
    }

    // Checks if the given date and time is valid
    // all arguments are within a proper range).
    //
    // Returns true if all arguments are valid, false otherwise.
    static bool isValid(int year, int month, int day, int hour = 0, int minute = 0, int second = 0, int millisecond = 0)
    {
        return (year >= 0 && year <= 9999) && (month >= 1 && month <= 12) &&
               (day >= 1 && day <= GetDaysOfMonth(year, month)) && (hour >= 0 && hour <= 23) &&
               (minute >= 0 && minute <= 59) && (second >= 0 && second <= 60) &&
               (millisecond >= 0 && millisecond <= 999);
    }

    // Creates a timestamp static
    // Returns milliseconds
    static TimeVal GetNowTime()
    {
        AFDateTime now;
        return now.Raw();
    }

    // Creates a timestamp static
    // Returns seconds
    static int GetTimestamp()
    {
        AFDateTime now;
        return (int)now.GetTime();
    }

    static TimeDiff Resolution()
    {
        return 1000; // 1s = 1000 milliseconds
    }

private:
    // milliseconds
    TimeVal ts_;
};

inline void swap(AFDateTime& d1, AFDateTime& d2)
{
    d1.swap(d2);
}

} // namespace ark
