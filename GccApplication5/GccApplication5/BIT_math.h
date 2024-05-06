#ifndef BIT_MATH_H
#define BIT_MATH_H

#define SET_BIT(Var,BitNo)       Var = Var | (1 << BitNo)
#define CLEAR_BIT(Var,BitNo)     Var = Var & ~(1 << BitNo)
#define GET_BIT(Var,BitNo)       (Var >> BitNo & 1)
#define ASSIGN_BYTE(Var,Value)    Var = Value

#endif