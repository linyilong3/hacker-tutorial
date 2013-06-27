#include "Hook.h"
#include <Windows.h>

struct _vk_data
{
	//true不让系统响应该键盘消息，false响应键盘消息
	bool no_call_next;
	bool is_hook;
};
struct _hook_data
{
	HHOOK hook;
	struct _vk_data hook_vk[256];
	char hook_vk_count;
	func_key_callback call_back;
};

struct _hook_data *s_hook = NULL;

LRESULT CALLBACK key_board_proc(int code,WPARAM w_param,LPARAM l_param)
{
	if (s_hook->call_back != NULL)
	{

		PKBDLLHOOKSTRUCT hook_struct = (PKBDLLHOOKSTRUCT)l_param;
		if (s_hook->hook_vk[hook_struct->vkCode].is_hook ==  true)
		{
			s_hook->call_back(hook_struct->vkCode);
			return s_hook->hook_vk[hook_struct->vkCode].no_call_next;
		}
	}
	return 0;
}

void clean_hook()
{
	UnhookWindowsHookEx(s_hook->hook);
	free(s_hook);
	s_hook = NULL;
}

void hook_global_keyboard( )
{
	HMODULE module = GetModuleHandle(NULL);
	s_hook->hook = SetWindowsHookEx(WH_KEYBOARD_LL,(HOOKPROC)key_board_proc,module,0);
}

void set_hook_key( const char key,bool no_call_next)
{
	s_hook->hook_vk[key].is_hook = true;;
	s_hook->hook_vk[key].no_call_next = no_call_next;
	s_hook->hook_vk_count++;
}

void clear_hook_key(const char key )
{
	s_hook->hook_vk[key].is_hook = false;
	s_hook->hook_vk_count--;
}

void set_hook_key_call_back( func_key_callback call_back )
{
	s_hook->call_back = call_back;
}

void init_hook()
{
	s_hook = (struct _hook_data *)malloc(sizeof(struct _hook_data));
	memset(s_hook,0,sizeof(struct _hook_data));
}
