#include "ti_msp_dl_config.h"
#include <ti/iqmath/include/IQmathLib.h>

//此处使用的结果实际应该大于-128，小于127.999 999 940， 如要扩大，应更改头文件中GLOBAL_IQ大小
_iq qa = 0, qb = 0, qc = 0;

float Qsqt(float num)
{
    qa = _IQ(num);
    qc = _IQsqrt(qa);
    return _IQtoF(qc);
}

float Qsin(float radius)
{
    qa = _IQ(radius);
    qc = _IQsin(qa);
    return _IQtoF(qc);
}

float Qcos(float radius)
{
    qa = _IQ(radius);
    qc = _IQcos(qa);
    return _IQtoF(qc);
}

float Qtan(float radius)
{
    qa = _IQ(radius);
    qb = _IQsin(qa);
    qc = _IQcos(qa);
    qc = _IQdiv(qb, qc);
    return _IQtoF(qc);
}

float Qasin(float radius)
{
    qa = _IQ(radius);
    qc = _IQasin(qa);
    return _IQtoF(qc);
}

float Qacos(float radius)
{
    qa = _IQ(radius);
    qc = _IQacos(qa);
    return _IQtoF(qc);
}

float Qatan(float radius)
{
    qa = _IQ(radius);
    qc = _IQatan(qa);
    return _IQtoF(qc);
}