#pragma once

#include <chrono>
#include <iostream>
#include <string>



class LogDuration
{
public:
    explicit LogDuration(const std::string& message);
    virtual ~LogDuration();

private:
    std::string message_;
    std::chrono::steady_clock::time_point start_;
};


#define UNIQ_ID_FINAL(line_number) _local_var_##line_number
#define UNIQ_ID_INTERMEDIATE(line_number) UNIQ_ID_FINAL(line_number)
#define UNIQ_ID UNIQ_ID_INTERMEDIATE(__LINE__)

#define LOG_DURATION(message) LogDuration UNIQ_ID(message);



// ---------------------------------------------------


/*struct TotalDuration
{
    std::string message;
    std::chrono::steady_clock::duration value;

    explicit TotalDuration(const std::string& msg = "");
    virtual ~TotalDuration();
};



class AddDuration
{
public:
    explicit AddDuration(std::chrono::steady_clock::duration& dest);
    explicit AddDuration(TotalDuration& dest);
    virtual ~AddDuration();

private:
    std::chrono::steady_clock::duration& add_to;
    std::chrono::steady_clock::time_point start;
};



#define ADD_DURATION(value) \
    AddDuration UNIQ_ID(__LINE__){value};

*/


// -------------------------------------------------------










/*
using namespace std;
using namespace chrono;

struct TotalDuration
{
    string message;
    steady_clock::duration value;
    explicit TotalDuration(const string& msg = "")
        : message(msg + ": ")
        , value(0)
    {
    }

    ~TotalDuration()
    {
        ostringstream os;
        os << message
           << duration_cast<milliseconds>(value).count()
           << " ms" << endl;
        cerr << os.str();
    }
};


class AddDuration
{
public:
    explicit AddDuration(steady_clock::duration& dest)
        : add_to(dest)
        , start(steady_clock::now())
    {
    }

    explicit AddDuration(TotalDuration& dest)
        : AddDuration(dest.value)
    {
    }

    ~AddDuration()
    {
        add_to += steady_clock::now() - start;
    }

private:
    steady_clock::duration& add_to;
    steady_clock::time_point start;
};

#define ADD_DURATION(value) \
    AddDuration UNIQ_ID(__LINE__){value};
*/
