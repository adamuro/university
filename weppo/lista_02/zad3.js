/* Program wykonuje operacje na zmiennych różnych typów, wykorzystując luźne typowanie w javasripcie */

//           1                 2                    3                                  4
console.log( (![] + [])[+[]] + (![] + [])[+ !+[]] + ([![]] + [][[]])[+ !+[] + [+[]]] + (![] + [])[!+[] + !+[]] );
// 1: ![] = false, false + [] = "false", +[] = 0, "false"[0] = "f"
// 2: ![] = false, false + [] = "false", +[] = 0, !0 = true, +true = 1, "false"[1] = "a"
// 3: ![] = false, [][[]] = undefined, [false] + undefined = "falseundefined", !+[] = true, [+[]] = [0], true + [0] = "10", +"10" = 10, "falseundefined"[10] = "i"
// 4: ![] = false, false + [] = "false", +[] = 0, !0 = true, true + true = 2, "false"[2] = "l"