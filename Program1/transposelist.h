// transposelist.h : This file contains the header file for a transpose doublylinked list
// Scott Elliott
// CSS501 - Fall 2025
// Program 1 - Transpose List Header

#ifndef TRANSPOSELIST_H
#define TRANSPOSELIST_H

#include "CDLinkedList.h"

class TransposeList : public CDLinkedList {
public:
  TransposeList();
  virtual bool contains(int anEntry) override;
};

#endif // TRANSPOSELIST_H