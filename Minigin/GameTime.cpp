#include "GameTime.h"

float aze::GameTime::GetElapsed() const
{
    return m_Elapsed;
}

void aze::GameTime::SetElapsed(float elapsed)
{
    m_Elapsed = elapsed;
}
