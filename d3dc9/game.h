// �U�C ifdef �϶��O�إߥ����H��U�q DLL �ץX���зǤ覡�C
// �o�� DLL �����Ҧ��ɮ׳��O�ϥΩR�O�C���ҩw�q GAME_EXPORTS �Ÿ��sĶ���C
// �b�R�O�C�w�q���Ÿ��C����M�׳������w�q�o�ӲŸ�
// �o�ˤ@�ӡA��l�{���ɤ��]�t�o�ɮת������L�M��
// �|�N GAME_API �禡�����q DLL �פJ���A�ӳo�� DLL �h�|�N�o�ǲŸ�����
// �ץX���C
#ifdef GAME_EXPORTS
#define GAME_API __declspec(dllexport)
#else
#define GAME_API __declspec(dllimport)
#endif
HHOOK m_hook = NULL;			//�i�{

// �o�����O�O�q game.dll �ץX��
class GAME_API Cgame {
public:
	Cgame(void);
	// TODO: �b���[�J�z����k�C
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