/******************************************************************************************
* Data Structures in C++ -- 函数对象：递减一个T类对象
* 丁酉鸡年二月 2017/3/18 9:15
* @author 西唐王, xtwyzh@gmail.com, xtwroot.com
* xtwroot Copyright (c) 2017. All rights reserved.
******************************************************************************************/

#pragma once

template <typename T> struct Decrease //函数对象：递减一个T类对象
   {  virtual void operator() ( T& e ) { e--; }  }; //假设T可直接递减或已重载--
