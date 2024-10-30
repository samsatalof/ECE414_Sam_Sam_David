void getcmd(char *line, char *cmd, int *np)
{
    int num = 0;
    while (*line != ' ')
    {
        *cmd = *line;
        cmd++;
        line++;
    }
    line++;
    while (*line != '\0')
    {
        num = num * 10 + (*line - '0');
        line++;
    }
    *np = num;
}
