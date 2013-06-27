#pragma once


//在使用该模块的时候必须要调用这个
void init_hook();
//结束后清理
void clean_hook();

typedef int (*func_key_callback)(int code);

//开始hook所有的键盘消息
void hook_global_keyboard();

//设置要hook的键，no_call_next为true则不会响应该键盘消息，为false则响应该消息
void set_hook_key(const char key,bool no_call_next);

//清除某个要hook的键
void clear_hook_key(const char key);

//当hook到响应的键的时候要响应的
void set_hook_key_call_back(func_key_callback call_back);
