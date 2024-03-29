#include "GameTime.h"

float aze::GameTime::GetElapsed() const
{
    return m_Elapsed;
}

void aze::GameTime::SetElapsed(float elapsed)
{
    m_Elapsed = elapsed;
}

float aze::GameTime::GetFixedTimeStep() const
{
    return m_FixedTimeStep;
}

void aze::GameTime::SetFixedTimeStep(float fixedTimeStep)
{
    m_FixedTimeStep = fixedTimeStep;
}
