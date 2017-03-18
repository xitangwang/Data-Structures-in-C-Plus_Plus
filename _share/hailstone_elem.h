/******************************************************************************************
* Data Structures in C++ -- 函数对象：按照Hailstone规则转化一个T类对象
* 丁酉鸡年二月 2017/3/18 9:15
* @author 西唐王, xtwyzh@gmail.com, xtwroot.com
* xtwroot Copyright (c) 2017. All rights reserved.
******************************************************************************************/

#pragma once

template <typename T> struct Hailstone { //函数对象：按照Hailstone规则转化一个T类对象
   virtual void operator() ( T& e ) { //假设T可直接做算术运算
      int step = 0; //转换所需步数
      while ( 1 != e ) { //按奇、偶逐步转换，直至为1
         ( e % 2 ) ? e = 3 * e + 1 : e /= 2;
         step++;
      }
      e = step; //返回转换所经步数
   }
};