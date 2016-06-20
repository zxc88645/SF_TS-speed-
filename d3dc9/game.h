// 下列 ifdef 區塊是建立巨集以協助從 DLL 匯出的標準方式。
// 這個 DLL 中的所有檔案都是使用命令列中所定義 GAME_EXPORTS 符號編譯的。
// 在命令列定義的符號。任何專案都不應定義這個符號
// 這樣一來，原始程式檔中包含這檔案的任何其他專案
// 會將 GAME_API 函式視為從 DLL 匯入的，而這個 DLL 則會將這些符號視為
// 匯出的。
#ifdef GAME_EXPORTS
#define GAME_API __declspec(dllexport)
#else
#define GAME_API __declspec(dllimport)
#endif
HHOOK m_hook = NULL;			//進程

// 這個類別是從 game.dll 匯出的
class GAME_API Cgame {
public:
	Cgame(void);
	// TODO: 在此加入您的方法。
};

extern GAME_API int ngame;

GAME_API void UnHook();
GAME_API void SetHook();

void check();
bool HookDrawIndexedPrimitive();
bool Hook_GetTickCount();
bool HookCreateQuery();
bool Hook_QueryPerformanceCounter();
//ULONG_PTR DrawIndexedPrimitive();