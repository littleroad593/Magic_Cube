#include <iostream>
using namespace std;

char cube[6][3][3], tcube[6][3][3]; //三维数组储存54个色块 
char f, b, l, r, u, d; //储存中心色块 
int num = 0, optime = 0;

void storecube()
{
    for (int k = 0; k < 6; k++)
        for (int i = 0; i < 3; i++)
            for (int j = 0; j < 3; j++)
                tcube[k][i][j] = cube[k][i][j];
} //存储魔方状态

void store_back_cube()
{
    for (int k = 0; k < 6; k++)
        for (int i = 0; i < 3; i++)
            for (int j = 0; j < 3; j++)
                cube[k][i][j] = tcube[k][i][j];
} //释放魔方状态

void setcenter()
{
    f = cube[0][1][1];
    r = cube[1][1][1];
    b = cube[2][1][1];
    l = cube[3][1][1];
    u = cube[4][1][1];
    d = cube[5][1][1];
} //标记中心面

void changevision()
{
    char tmp[3][3];
    for (int i = 0; i < 3; i++)
        for (int j = 0; j < 3; j++)
        {
            tmp[i][j] = cube[1][i][j];
            cube[1][i][j] = cube[3][i][j];
            cube[3][i][j] = cube[2][i][j];
            cube[2][i][j] = tmp[i][j];
        }
} //初始面顺序转换

void change_back_vision()
{
    char tmp[3][3];
    for (int i = 0; i < 3; i++)
        for (int j = 0; j < 3; j++)
        {
            tmp[i][j] = cube[1][i][j];
            cube[1][i][j] = cube[2][i][j];
            cube[2][i][j] = cube[3][i][j];
            cube[3][i][j] = tmp[i][j];
        }
} //初始面顺序转回

void changefront()
{
    storecube();
    for (int i = 0; i < 3; i++)
        for (int j = 0; j < 3; j++)
            tcube[4][i][j] = cube[4][2 - j][i];
    for (int i = 0; i < 3; i++)
        for (int j = 0; j < 3; j++)
            tcube[5][2 - j][i] = cube[5][i][j];
    for (int i = 0; i < 3; i++)
        for (int j = 0; j < 3; j++)
        {
            tcube[0][i][j] = cube[1][i][j];
            tcube[1][i][j] = cube[2][i][j];
            tcube[2][i][j] = cube[3][i][j];
            tcube[3][i][j] = cube[0][i][j];
        }
    store_back_cube();
    setcenter();
    optime++;
    if (optime >= 4)
        optime = optime - 4;
} //将魔方视角顺时针转动

void change_back_front()
{
    storecube();
    for (int i = 0; i < 3; i++)
        for (int j = 0; j < 3; j++)
            tcube[5][i][j] = cube[5][2 - j][i];
    for (int i = 0; i < 3; i++)
        for (int j = 0; j < 3; j++)
            tcube[4][2 - j][i] = cube[4][i][j];
    for (int i = 0; i < 3; i++)
        for (int j = 0; j < 3; j++)
        {
            tcube[0][i][j] = cube[3][i][j];
            tcube[1][i][j] = cube[0][i][j];
            tcube[2][i][j] = cube[1][i][j];
            tcube[3][i][j] = cube[2][i][j];
        }
    store_back_cube();
    setcenter();
    optime--;
    if (optime < 0)
        optime = optime + 4; // optime记录视角转换次数，便于确定原状态下如何操作 
} //将魔方视角逆时针转动

// 下面是12个旋转操作及函数转换表 
void F()
{
    storecube();
    for (int i = 0; i < 3; i++)
        for (int j = 0; j < 3; j++)
            tcube[0][i][j] = cube[0][2 - j][i];
    for (int j = 0; j < 3; j++)
    {
        tcube[5][0][j] = cube[1][2 - j][0];
        tcube[1][j][0] = cube[4][2][j];
        tcube[4][2][j] = cube[3][2 - j][2];
        tcube[3][j][2] = cube[5][0][j];
    }
    store_back_cube();
    cout << 'F' << ' ';
}

void Fi()
{
    storecube();
    for (int i = 0; i < 3; i++)
        for (int j = 0; j < 3; j++)
            tcube[0][2 - j][i] = cube[0][i][j];
    for (int j = 0; j < 3; j++)
    {
        tcube[1][2 - j][0] = cube[5][0][j];
        tcube[4][2][j] = cube[1][j][0];
        tcube[3][2 - j][2] = cube[4][2][j];
        tcube[5][0][j] = cube[3][j][2];
    }
    store_back_cube();
    cout << "Fi" << ' ';
}

void B()
{
    storecube();
    for (int i = 0; i < 3; i++)
        for (int j = 0; j < 3; j++)
            tcube[2][i][j] = cube[2][2 - j][i];
    for (int j = 0; j < 3; j++)
    {
        tcube[3][j][0] = cube[4][0][2 - j];
        tcube[4][0][j] = cube[1][j][2];
        tcube[1][j][2] = cube[5][2][2 - j];
        tcube[5][2][j] = cube[3][j][0];
    }
    store_back_cube();
    cout << 'B' << ' ';
}

void Bi()
{
    storecube();
    for (int i = 0; i < 3; i++)
        for (int j = 0; j < 3; j++)
            tcube[2][2 - j][i] = cube[2][i][j];
    for (int j = 0; j < 3; j++)
    {
        tcube[4][0][2 - j] = cube[3][j][0];
        tcube[1][j][2] = cube[4][0][j];
        tcube[5][2][2 - j] = cube[1][j][2];
        tcube[3][j][0] = cube[5][2][j];
    }
    store_back_cube();
    cout << "Bi" << ' ';
}

void L()
{
    storecube();
    for (int i = 0; i < 3; i++)
        for (int j = 0; j < 3; j++)
            tcube[3][i][j] = cube[3][2 - j][i];
    for (int i = 0; i < 3; i++)
    {
        tcube[0][i][0] = cube[4][i][0];
        tcube[4][i][0] = cube[2][2 - i][2];
        tcube[2][i][2] = cube[5][2 - i][0];
        tcube[5][i][0] = cube[0][i][0];
    }
    store_back_cube();
    cout << 'L' << ' ';
}

void Li()
{
    storecube();
    for (int i = 0; i < 3; i++)
        for (int j = 0; j < 3; j++)
            tcube[3][2 - j][i] = cube[3][i][j];
    for (int i = 0; i < 3; i++)
    {
        tcube[4][i][0] = cube[0][i][0];
        tcube[2][2 - i][2] = cube[4][i][0];
        tcube[5][2 - i][0] = cube[2][i][2];
        tcube[0][i][0] = cube[5][i][0];
    }
    store_back_cube();
    cout << "Li" << ' ';
}

void R()
{
    storecube();
    for (int i = 0; i < 3; i++)
        for (int j = 0; j < 3; j++)
            tcube[1][i][j] = cube[1][2 - j][i];
    for (int i = 0; i < 3; i++)
    {
        tcube[0][i][2] = cube[5][i][2];
        tcube[4][i][2] = cube[0][i][2];
        tcube[2][i][0] = cube[4][2 - i][2];
        tcube[5][i][2] = cube[2][2 - i][0];
    }
    store_back_cube();
    cout << 'R' << ' ';
}

void Ri()
{
    storecube();
    for (int i = 0; i < 3; i++)
        for (int j = 0; j < 3; j++)
            tcube[1][2 - j][i] = cube[1][i][j];
    for (int i = 0; i < 3; i++)
    {
        tcube[5][i][2] = cube[0][i][2];
        tcube[0][i][2] = cube[4][i][2];
        tcube[4][2 - i][2] = cube[2][i][0];
        tcube[2][2 - i][0] = cube[5][i][2];
    }
    store_back_cube();
    cout << "Ri" << ' ';
}

void U()
{
    storecube();
    for (int i = 0; i < 3; i++)
        for (int j = 0; j < 3; j++)
            tcube[4][i][j] = cube[4][2 - j][i];
    for (int j = 0; j < 3; j++)
    {
        tcube[0][0][j] = cube[1][0][j];
        tcube[1][0][j] = cube[2][0][j];
        tcube[2][0][j] = cube[3][0][j];
        tcube[3][0][j] = cube[0][0][j];
    }
    store_back_cube();
    cout << 'U' << ' ';
}

void Ui()
{
    storecube();
    for (int i = 0; i < 3; i++)
        for (int j = 0; j < 3; j++)
            tcube[4][2 - j][i] = cube[4][i][j];
    for (int j = 0; j < 3; j++)
    {
        tcube[1][0][j] = cube[0][0][j];
        tcube[2][0][j] = cube[1][0][j];
        tcube[3][0][j] = cube[2][0][j];
        tcube[0][0][j] = cube[3][0][j];
    }
    store_back_cube();
    cout << "Ui" << ' ';
}

void D()
{
    storecube();
    for (int i = 0; i < 3; i++)
        for (int j = 0; j < 3; j++)
            tcube[5][i][j] = cube[5][2 - j][i];
    for (int j = 0; j < 3; j++)
    {
        tcube[0][2][j] = cube[3][2][j];
        tcube[3][2][j] = cube[2][2][j];
        tcube[2][2][j] = cube[1][2][j];
        tcube[1][2][j] = cube[0][2][j];
    }
    store_back_cube();
    cout << 'D' << ' ';
}

void Di()
{
    storecube();
    for (int i = 0; i < 3; i++)
        for (int j = 0; j < 3; j++)
            tcube[5][2 - j][i] = cube[5][i][j];
    for (int j = 0; j < 3; j++)
    {
        tcube[3][2][j] = cube[0][2][j];
        tcube[2][2][j] = cube[3][2][j];
        tcube[1][2][j] = cube[2][2][j];
        tcube[0][2][j] = cube[1][2][j];
    }
    store_back_cube();
    cout << "Di" << ' ';
}

void doo(string a)
{
    if (optime == 0)
    {
        if (a == "F")  F();
        if (a == "Fi")  Fi();
        if (a == "B")  B();
        if (a == "Bi")  Bi();
        if (a == "L")  L();
        if (a == "Li")  Li();
        if (a == "R")  R();
        if (a == "Ri")  Ri();
    }
    if (optime == 1)
    {
        change_back_front();
        if (a == "F")  R();
        if (a == "Fi")  Ri();
        if (a == "B")  L();
        if (a == "Bi")  Li();
        if (a == "L")  F();
        if (a == "Li")  Fi();
        if (a == "R")  B();
        if (a == "Ri")  Bi();
        changefront();
    }
    if (optime == 2)
    {
        change_back_front();
        change_back_front();
        if (a == "F")  B();
        if (a == "Fi")  Bi();
        if (a == "B")  F();
        if (a == "Bi")  Fi();
        if (a == "L")  R();
        if (a == "Li")  Ri();
        if (a == "R")  L();
        if (a == "Ri")  Li();
        changefront();
        changefront();
    }
    if (optime == 3)
    {
        changefront();
        if (a == "F")  L();
        if (a == "Fi")  Li();
        if (a == "B")  R();
        if (a == "Bi")  Ri();
        if (a == "L")  B();
        if (a == "Li")  Bi();
        if (a == "R")  F();
        if (a == "Ri")  Fi();
        change_back_front();
    }
}//函数转换表

/// 底面及一二层的复原由于色块顺序较为杂乱，采用了减治、分类、枚举的思想
/// 减治：通过转换视角，使每一层的还原均是将目标色块转到特定位置 
/// 分类：每次操作的目标色块出现位置可能不同，因而分类讨论
/// 枚举：每种分类下不同位置的目标色块转至特定位置的方法略有不同，进行枚举 

void set_downcross_upface()
{
    if (cube[0][0][1] == f && cube[4][2][1] == d)
    {
        doo("F"); doo("F");
        return;
    }
    if (cube[3][0][1] == f && cube[4][1][0] == d)
    {
        Ui(); doo("F"); doo("F");
        return;
    }
    if (cube[1][0][1] == f && cube[4][1][2] == d)
    {
        U(); doo("F"); doo("F");
        return;
    }
    if (cube[2][0][1] == f && cube[4][0][1] == d)
    {
        U(); U(); doo("F"); doo("F");
        return;
    }
} //底面十字之顶面查找

void set_downcross_floor3()
{
    if (cube[0][0][1] == d && cube[4][2][1] == f)
    {
        Ui(); D(); doo("Ri"); Di(); doo("F");
        return;
    }
    if (cube[3][0][1] == d && cube[4][1][0] == f)
    {
        Di(); doo("L"); D(); doo("Fi");
        return;
    }
    if (cube[1][0][1] == d && cube[4][1][2] == f)
    {
        D(); doo("Ri"); Di(); doo("F");
        return;
    }
    if (cube[2][0][1] == d && cube[4][0][1] == f)
    {
        U(); D(); doo("Ri"); Di(); doo("F");
        return;
    }
    set_downcross_upface();
} //底面十字之三层查找

void set_downcross_floor2()
{
    if (cube[0][1][0] == f && cube[3][1][2] == d)
    {
        doo("Fi");
        return;
    }
    if (cube[0][1][0] == d && cube[3][1][2] == f)
    {
        Di(); doo("L"); D();
        return;
    }
    if (cube[0][1][2] == f && cube[1][1][0] == d)
    {
        doo("F");
        return;
    }
    if (cube[0][1][2] == d && cube[1][1][0] == f)
    {
        D(); doo("Ri"); Di();
        return;
    }
    if (cube[2][1][2] == f && cube[3][1][0] == d)
    {
        Di(); doo("L"); doo("L"); D(); doo("Fi");
        return;
    }
    if (cube[2][1][2] == d && cube[3][1][0] == f)
    {
        Di(); doo("Li"); D();
        return;
    }
    if (cube[2][1][0] == f && cube[1][1][2] == d)
    {
        D(); doo("R"); doo("R"); Di(); doo("F");
        return;
    }
    if (cube[2][1][0] == d && cube[1][1][2] == f)
    {
        D(); doo("R"); Di();
        return;
    }
    set_downcross_floor3();
} //底面十字之二层查找

void set_downcross_floor1()
{
    if (cube[5][0][1] == f && cube[0][2][1] == d)
    {
        doo("F"); Di(); doo("L"); D();
        return;
    }
    if (cube[5][1][0] == f && cube[3][2][1] == d)
    {
        doo("Li"); doo("Fi");
        return;
    }
    if (cube[5][1][2] == f && cube[1][2][1] == d)
    {
        Di(); doo("Fi"); D(); D(); doo("Ri"); Di();
        return;
    }
    if (cube[5][2][1] == f && cube[2][2][1] == d)
    {
        Di(); doo("R"); D(); doo("F");
        return;
    }
    set_downcross_floor2();
} //底面十字之一层查找

void set_downcross_downface()
{
    if (cube[5][0][1] == d && cube[0][2][1] == f)
        return;
    if (cube[5][1][0] == d && cube[3][2][1] == f)
    {
        doo("Li"); doo("Li"); Ui(); doo("F"); doo("F");
        return;
    }
    if (cube[5][1][2] == d && cube[1][2][1] == f)
    {
        doo("R"); doo("R"); U(); doo("F"); doo("F");
        return;
    }
    if (cube[5][2][1] == d && cube[2][2][1] == f)
    {
        doo("B"); doo("B"); U(); U(); doo("F"); doo("F");
        return;
    }
    set_downcross_floor1();
} //底面十字之底面查找

void set_downcross()
{
    for (int i = 0; i < 4; i++)
    {
        set_downcross_downface();
        changefront();
    }
} //底面十字复原，上面是逐层讨论，分类枚举的几个函数 

void set_downrest_upface()
{
    if (cube[4][2][0] == d && cube[3][0][2] == f)
    {
        doo("Li"); U(); U(); doo("L"); U(); doo("Li"); Ui(); doo("L");
        return;
    }
    if (cube[4][2][2] == d && cube[0][0][2] == f)
    {
        U(); doo("Li"); U(); U(); doo("L"); U(); doo("Li"); Ui(); doo("L");
        return;
    }
    if (cube[4][0][2] == d && cube[1][0][2] == f)
    {
        U(); U(); doo("Li"); U(); U(); doo("L"); U(); doo("Li"); Ui(); doo("L");
        return;
    }
    if (cube[4][0][0] == d && cube[2][0][2] == f)
    {
        Ui(); doo("Li"); U(); U(); doo("L"); U(); doo("Li"); Ui(); doo("L");
        return;
    }
} //底面四角之顶面查找

void set_downrest_floor3()
{
    if (cube[0][0][0] == d && cube[4][2][0] == f)
    {
        Ui(); doo("Li"); U(); doo("L");
        return;
    }
    if (cube[3][0][2] == d && cube[0][0][0] == f)
    {
        doo("Li"); Ui(); doo("L");
        return;
    }
    if (cube[1][0][0] == d && cube[4][2][2] == f)
    {
        doo("Li"); U(); doo("L");
        return;
    }
    if (cube[0][0][2] == d && cube[1][0][0] == f)
    {
        U(); doo("Li"); Ui(); doo("L");
        return;
    }
    if (cube[2][0][0] == d && cube[4][0][2] == f)
    {
        U(); doo("Li"); U(); doo("L");
        return;
    }
    if (cube[1][0][2] == d && cube[2][0][0] == f)
    {
        U(); U(); doo("Li"); Ui(); doo("L");
        return;
    }
    if (cube[3][0][0] == d && cube[4][0][0] == f)
    {
        U(); U(); doo("Li"); U(); doo("L");
        return;
    }
    if (cube[2][0][2] == d && cube[3][0][0] == f)
    {
        Ui(); doo("Li"); Ui(); doo("L");
        return;
    }
    set_downrest_upface();
} //底面四角之三层查找

void set_downrest_floor1()
{
    if (cube[0][2][0] == d && cube[3][2][2] == f)
    {
        doo("Li"); U(); doo("L"); Ui(); doo("Li"); U(); doo("L");
        return;
    }
    if (cube[3][2][2] == d && cube[5][0][0] == f)
    {
        doo("F"); Ui(); doo("Fi"); doo("Li"); Ui(); doo("L");
        return;
    }
    if (cube[0][2][2] == d && cube[5][0][2] == f)
    {
        doo("R"); Ui(); doo("Ri"); U(); doo("Li"); Ui(); doo("L");
        return;
    }
    if (cube[1][2][0] == d && cube[0][2][2] == f)
    {
        doo("R"); doo("Li"); U(); doo("Ri"); doo("L");
        return;
    }
    if (cube[3][2][0] == d && cube[2][2][2] == f)
    {
        doo("L"); U(); doo("Li"); U(); doo("Li"); U(); doo("L");
        return;
    }
    if (cube[2][2][2] == d && cube[5][2][0] == f)
    {
        doo("Bi"); Ui(); doo("B"); doo("Li"); Ui(); doo("L");
        return;
    }
    if (cube[2][2][0] == d && cube[1][2][2] == f)
    {
        doo("B"); U(); doo("Bi"); doo("Li"); U(); doo("L");
        return;
    }
    if (cube[1][2][2] == d && cube[5][2][2] == f)
    {
        doo("Ri"); Ui(); doo("R"); Ui(); doo("Li"); Ui(); doo("L");
        return;
    }
    set_downrest_floor3();
}//底面四角之一层查找

void set_downrest_downface()
{
    if (cube[5][0][0] == d && cube[0][2][0] == f)
        return;
    if (cube[5][0][2] == d && cube[1][2][0] == f)
    {
        doo("R"); Ui(); doo("Ri"); doo("Li"); U(); doo("L");
        return;
    }
    if (cube[5][2][0] == d && cube[3][2][0] == f)
    {
        doo("Bi"); Ui(); doo("B"); Ui(); doo("Li"); U(); doo("L");
        return;
    }
    if (cube[5][2][2] == d && cube[2][2][0] == f)
    {
        doo("B"); U(); doo("Bi"); U(); doo("Li"); Ui(); doo("L");
        return;
    }
    set_downrest_floor1();
} //底面四角之底面查找

void set_downrest()
{
    for (int i = 0; i < 4; i++)
    {
        set_downrest_downface();
        changefront();
    }
} //底面四角复原，上面是逐层讨论，分类枚举的几个函数 

// 二三层还原需要一些公式，先写出来 
void formula_a1()
{
    doo("R"); Ui(); doo("Ri"); doo("F"); doo("Ri"); doo("Fi"); doo("R");
} //二层复原公式1

void formula_a2()
{
    doo("Fi"); U(); doo("F"); doo("Ri"); doo ("F"); doo("R"); doo("Fi");
} //二层复原公式2

void formula_b()
{
    F(); R(); U(); Ri(); Ui(); Fi();
} //顶面十字复原公式

void formula_c1()
{
    doo("Ri"); Ui(); doo("R"); Ui(); doo("Ri"); Ui(); Ui(); doo("R");
} //顶面四角复原公式1

void formula_c2()
{
    doo("L"); U(); doo("Li"); U(); doo("L"); U(); U(); doo("Li");
} //顶面四角复原公式2

void formula_d()
{
    doo("R"); doo("R"); doo("F"); doo("F"); doo("Ri"); doo("Bi"); doo("R"); doo("F"); doo("F"); doo("Ri"); doo("B"); doo("Ri");
} //第三层角块变换公式

void set_secondfloor_floor3()
{
    if (cube[0][0][1] == f && cube[4][2][1] == r)
    {
        U(); formula_a1();
        return;
    }
    if (cube[1][0][1] == f && cube[4][1][2] == r)
    {
        U(); U(); formula_a1();
        return;
    }
    if (cube[2][0][1] == f && cube[4][0][1] == r)
    {
        Ui(); formula_a1();
        return;
    }
    if (cube[3][0][1] == f && cube[4][1][0] == r)
    {
        formula_a1();
        return;
    }
    if (cube[0][0][1] == r && cube[4][2][1] == f)
    {
        U(); U(); formula_a2();
        return;
    }
    if (cube[1][0][1] == r && cube[4][1][2] == f)
    {
        Ui(); formula_a2();
        return;
    }
    if (cube[2][0][1] == r && cube[4][0][1] == f)
    {
        formula_a2();
        return;
    }
    if (cube[3][0][1] == r && cube[4][1][0] == f)
    {
        U(); formula_a2();
        return;
    }
}//二层复原之三层查找

void set_secondfloor_floor2()
{
    if (cube[0][1][2] == f && cube[1][1][0] == r)
        return;
    if (cube[0][1][2] == r && cube[1][1][0] == f)
    {
        formula_a1(); Ui(); formula_a1();
        return;
    }
    if (cube[1][1][2] == f && cube[2][1][0] == r)
    {
        changefront();
        formula_a1();
        change_back_front();
        U(); formula_a2();
        return;
    }
    if (cube[1][1][2] == r && cube[2][1][0] == f)
    {
        changefront();
        formula_a1();
        change_back_front();
        formula_a1();
        return;
    }
    if (cube[2][1][2] == f && cube[3][1][0] == r)
    {
        changefront(); changefront();
        formula_a1();
        change_back_front(); change_back_front();
        U(); U(); formula_a2();
        return;
    }
    if (cube[2][1][2] == r && cube[3][1][0] == f)
    {
        changefront(); changefront();
        formula_a1();
        change_back_front(); change_back_front();
        U(); formula_a1();
        return;
    }
    if (cube[3][1][2] == f && cube[0][1][0] == r)
    {
        change_back_front();
        formula_a1();
        changefront();
        Ui(); formula_a2();
        return;
    }
    if (cube[3][1][2] == r && cube[0][1][0] == f)
    {
        change_back_front();
        formula_a1();
        changefront();
        U(); U(); formula_a1();
        return;
    }
    set_secondfloor_floor3();
}//二层复原之二层查找

void set_secondfloor()
{
    for (int i = 0; i < 4; i++)
    {
        set_secondfloor_floor2();
        changefront();
    }
} //二层复原

/// 顶面与第三层 采用新的思路：对特定色块颜色进行判断确定状态，再层层递归 

void set_topcross()
{
    int set = 0;
    if (cube[4][0][1] == u) set++;
    if (cube[4][1][0] == u) set++;
    if (cube[4][1][2] == u) set++;
    if (cube[4][2][1] == u) set++; // 确定顶面棱块情况 
    if (set == 4) return;
    if (set == 2) 
    {
    	while (cube[4][1][2] != u || cube[4][0][1] == u)
			U();
		formula_b();
		set_topcross();
	}
	if (set == 0)
	{
		formula_b();
		set_topcross();
	}
} //顶面十字复原

void set_toprest_1()
{
	while (cube[4][0][0] != u)
	{
		U();
	}
	if (cube[2][0][0] == u)
		formula_c1();
	else
	{
		U();
		formula_c2();
	}
	return;
}

void set_toprest_0()
{
	while (cube[3][0][0] != u)
	{
		U();
	}
	formula_c1();
	set_toprest_1();
	return;
}

void set_toprest_2()
{
	while (cube[2][0][2] != u)
	{
		U();
	}
	formula_c1();
	set_toprest_1();
	return;
}

void set_toprest()
{
    int set = 0;
    if (cube[4][0][0] == u) set++;
    if (cube[4][0][2] == u) set++;
    if (cube[4][2][0] == u) set++;
    if (cube[4][2][2] == u) set++;
	if (set == 0)
		set_toprest_0();
	if (set == 1)
		set_toprest_1();
	if (set == 2)
		set_toprest_2();
	if (set == 4)
		return;
	return;
}//顶面四角复原

void set_thirdfloor_1()
{
	while (cube[0][0][0] != cube[0][0][1])
	{
		U();
	}
	if (cube[3][0][1] == cube[1][0][0])
	{
		formula_c1();
		set_toprest_1();
	}
	else
	{
		formula_c2();
		set_toprest_1();
	}
}

void set_thirdfloor_2()
{
	while (cube[1][0][0] != cube[1][0][2])
	{
		U();
	}
	formula_d();
}

void set_thirdfloor()
{
    int set1 = 0, set2 = 0;
	for (int i = 0; i < 4; i++)
	{
		if (cube[i][0][0] == cube[i][0][2])
		{
			set1++;
			if (cube[i][0][0] == cube[i][0][1])
				set2++;
		}
	} 
	if (set1 == 4 && set2 == 4)
		return;
	if (set1 == 4 && set2 == 1)
		set_thirdfloor_1();
	if (set1 == 4 && set2 == 0)
	{
		formula_c1();
		Ui();
		formula_c2();
		set_thirdfloor_1();
	}
	if (set1 == 1)
	{
		set_thirdfloor_2();
		set_thirdfloor();
	}
	if (set1 == 0)
	{
		formula_d();
		set_thirdfloor_2();
		set_thirdfloor();
	}
}//三层复原

void set_rotate()
{
	while (cube[0][0][0] != f)
    	U();
} // 第三层颜色与中心块匹配 

int main()
{
    for (int k = 0; k < 6; k++)
        for (int i = 0; i < 3; i++)
            for (int j = 0; j < 3; j++)
                cin >> cube[k][i][j];
    changevision(); // 将魔方侧面的编号由输入时的前0后1左2右3转化为前0右1后2左3，便于for循环 
    setcenter();
    set_downcross();
    set_downrest();
    set_secondfloor();
    set_topcross();
    set_toprest();
    set_thirdfloor();
    set_rotate();
    change_back_vision();
    return 0;
}

