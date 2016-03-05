#pragma once

namespace Core
{

enum class ErrorCode
{
    NoError = 0,
    Unclassified = 1,
    Network = 2,
    Parse = 3,
    Database = 4,
    Authorization = 5
};

}
