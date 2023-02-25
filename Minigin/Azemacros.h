#pragma once
#ifndef AZEBAN_MACROS
#define AZEBAN_MACROS

#define UNREFERENCED_PARAMETER(P)          (P)

namespace aze
{
    template <typename T>
    bool is_uninitialized(const std::weak_ptr<T>& weak) 
    {
        // https://stackoverflow.com/questions/45507041/how-to-check-if-weak-ptr-is-empty-non-assigned
        using wt = std::weak_ptr<T>;
        return !weak.owner_before(wt{}) && !wt{}.owner_before(weak);
    }
}

#endif