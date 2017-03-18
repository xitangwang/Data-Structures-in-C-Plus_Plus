/******************************************************************************************
* Data Structures in C++ -- 函数对象：累计T类对象的特征（比如总和），以便校验对象集合：累计T类对象的特征（比如总和），以便校验对象集合
* 丁酉鸡年二月 2017/3/18 9:15
* @author 西唐王, xtwyzh@gmail.com, xtwroot.com
* xtwroot Copyright (c) 2017. All rights reserved.
******************************************************************************************/

#pragma once

template <typename T> struct Crc { //函数对象：累计T类对象的特征（比如总和），以便校验对象集合
   T& c;
   Crc ( T& crc ) : c ( crc ) {}
   virtual void operator() ( T& e ) { c += e; } //假设T可直接相加
};