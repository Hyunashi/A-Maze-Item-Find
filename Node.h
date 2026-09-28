#pragma once //prevents header from being included multiple times in compilation

struct Node
{
    int row;
    int col;

    int g;
    int h;
    int f;

    int parentRow;
    int parentCol;
};
