// mtflist.h : This file contains the header file for a Move-To-Front doubly linked list
// Scott Elliott
// MTF List Header

#ifndef MTFLIST_H
#define MTFLIST_H

#include "CDLinkedList.h"

class MtfList : public CDLinkedList {
public:
  MtfList();
  virtual bool contains(int anEntry) override;
};

#endif // MTFLIST_H