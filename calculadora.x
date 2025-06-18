struct inputs{
    float num1;
    float num2;
    char operador;
};

program CALCULADORA_PROG{
    version CALCULADORA_VER{
        float SUM(inputs)=1;
        float RES(inputs)=2;
        float MUL(inputs)=3;
        float DIV(inputs)=4;
    }=1;
}=0x2fffffff;
